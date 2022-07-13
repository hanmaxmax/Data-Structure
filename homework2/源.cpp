#include <iostream>
#include <fstream>
#include <stack>
#include "hafuman.h"
#include <string>
#include<iomanip>
using namespace std;

//构造全局变量
int n = 100; int num = 0;
treeNode* tree = new treeNode[2 * n + 1];

//定义函数
int findmin(int x);//找到最小值和倒数第二小值
int creatRstr(stack<char>& st, int i);//形成编码进栈（即从子节点开始反向寻找编码）
void HufumanCode(char** str, string filename, int temnum, string datname);//对文件进行编码，并将压缩后的文件写进.dat
void BreakCode(string datname, int treehead,string goalname);//将压缩文件解压缩
string dec_bin(int k);//将十进制转换为二进制，并补齐0构成7位字符串


int main()
{
	string filename1 = "inputfile1.txt";
	string filename2 = "inputfile2.txt";

	//从text.txt文件中取字符并计算权重
	char ch; 
	int strnum = 0;//储存原文件有多少个字符
	ifstream fin(filename1);
	fin.get(ch); strnum++;
	while (!fin.eof()) 
	{
		int i = 0;
		for (; i < num; i++)
		{
			if (tree[i].word == ch)
			{
				tree[i].weight++;
				break;
			}
		}
		if (i == num)
		{
			tree[i].word = ch;
			tree[i].weight++;
			num++;
		}
		fin.get(ch); strnum++;
	}
	fin.close();

	////~~~~~~~~~~~~~~~~~~~测试代码——字符及其权重~~~~~~~~~~~~~~~~~~~~~~~
	//for (int i = 0; i < num; i++)
	//{
	//	cout << tree[i].word << "    " << tree[i].weight << endl;
	//}
	////~~~~~~~~~~~~~~~~~~~测试代码——字符及其权重~~~~~~~~~~~~~~~~~~~~~~~
	int temnum = num; 


	//构造哈夫曼树  
	//先找最小值和倒数第二小值
	int head;//这是根的索引值
	while (true)
	{
		int minn = findmin(-1);
		int minn2 = findmin(minn);
		if (minn != -1 && minn2 == -1)
		{
			head = minn;
			break;
		}
		int sum = tree[minn].weight + tree[minn2].weight;
		tree[num].weight = sum;
		tree[num].lchild = minn;
		tree[num].rchild = minn2;
		tree[minn].parent = num;
		tree[minn2].parent = num;
		num++;
	}
	
	//找到每个字符对应的编码
	char** str = new char* [temnum];
	for (int i = 0; i < temnum; i++)
	{
		str[i] = new char[80];//50为默认编码最大长度
	}
	for (int i = 0; i < temnum; i++)
	{
		stack<char> st;
		int strnum=creatRstr(st, i);
		for (int j = 0; j < strnum; j++)
		{
			char rch = st.top();
			st.pop();
			str[i][j] = rch;
		}
		str[i][strnum] = '\0';
	}

	////~~~~~~~~~~~~~~~~~~~测试代码——输出每个字符对应的编码~~~~~~~~~~~~~~~~~~~~~~~
	//for (int i = 0; i < temnum; i++)
	//{
	//	cout << tree[i].word << "   " << str[i] << endl;
	//}
	////~~~~~~~~~~~~~~~~~~~测试代码——输出每个字符对应的编码~~~~~~~~~~~~~~~~~~~~~~~




	//保存字符出现次数和对应编码
	ofstream outf("outputfile1.txt");
	outf << setiosflags(ios::left);
	//outf << setw(10) <<"字符"<< setw(10) << "次数" << setw(10) << "编码" << endl;
	for (int i = 0; i < temnum; i++)
	{
		outf << setw(5) << tree[i].word << setw(5)<< tree[i].weight << setw(10) <<str[i] << endl;
	}
	outf.close();





	//对文件进行编码，并将压缩后的文件写进.dat
	HufumanCode(str, filename2, temnum,"outputfile.dat");//返回 文件转换成01字符串后分割形成的ASCII——压缩后的ASCII字符串

	//将压缩文件解压缩
	BreakCode("outputfile.dat", head, "outputfile2.txt");


}





int findmin(int x)
{
	int a = 10000; int index = -1;//如果index真的返回-1，说明只剩一个treenode了
	for (int i = 0; i < num; i++)
	{
		if (tree[i].parent == -1 && i != x && tree[i].weight < a)
		{
			a = tree[i].weight;
			index = i;
		}
	}
	return index;
}

int creatRstr(stack<char>& st, int i)
{
	int strnum = 0;
	while (true)
	{
		int tmp = tree[i].parent;
		if (tmp == -1)
		{
			break;
		}
		//左0 右1
		if (tree[tmp].lchild == i)
		{
			st.push('0');
		}
		else
			st.push('1');
		strnum++;
		i = tree[i].parent;
	}
	return strnum;
}


void HufumanCode(char** str, string filename, int temnum ,string datname)
{
	char ch; 
	string before;//暂存01未处理字符串编码的地方
	int strnum = 0;//储存原文件有多少个字符
	ifstream fin(filename);
	fin.get(ch); strnum++;
	//先把文件按照编码方式转换成01字符串存在before里
	while (!fin.eof())
	{
		for (int i=0; i < temnum; i++)
		{
			if (tree[i].word == ch)
			{
				before += str[i];
				break;
			}
		}
		fin.get(ch); strnum++;
	}
	fin.close();
	
	//将before 01串不足8的倍数的部分补齐
	int temlen = before.length();
	if (temlen % 8 != 0)
	{
		for (int i = 0; i < 8 - temlen % 8; i++)
		{
			before += '0';
		}
	}

	//~~~~~~~~~~~~~~~~~~~测试代码——输出before 01字符串~~~~~~~~~~~~~~~~~~~~~~~
	cout << before << endl;
	//~~~~~~~~~~~~~~~~~~~测试代码——输出before 01字符串~~~~~~~~~~~~~~~~~~~~~~~

	//将01字符串每8个01字符合并成一个ASCII字符，并将压缩后的字符串存在last里
	//string last;//暂存压缩后的字符串
	ofstream fout(datname, ios::binary);//打开用于“写”的二进制磁盘文件 
	fout.write((char*)(&strnum), sizeof(int));//先存原文件一共有多少字符
	
	for (int i = 0; i < before.length(); i += 8)
	{
		int k = 0;
		for (int j = 7; j >= 0; j--)
		{
			if (before[i + j] == '1')
				k += pow(2.0, 7-j);
		}
		unsigned char c = k;
		fout.write((char *)(&c), 1);
	}

	////~~~~~~~~~~~~~~~~~~~测试代码——输出last字符串~~~~~~~~~~~~~~~~~~~~~~~
	//for (int i = 0; i < last.length(); i++)
	//	cout << last[i];
	////~~~~~~~~~~~~~~~~~~~测试代码——输出last字符串~~~~~~~~~~~~~~~~~~~~~~~

	
	fout.close();

}


void BreakCode(string datname, int treehead, string goalname)
{

	int strnum;
	ifstream fin(datname, ios::binary);
	fin.read((char*)(&strnum), sizeof(int));//将原文件的字符数strnum提取出来
	
	unsigned char s;
	string before;
	string code;
	while (fin.read((char*)&s, sizeof(s)))
	{
		int k = s;
		string bin_k = dec_bin(k);
		//cout << k<<"                "<<bin_k << endl;
		before += bin_k;
	}

	fin.close();

	////~~~~~~~~~~~~~~~~~~~测试代码——输出压缩文件的提取值~~~~~~~~~~~~~~~~~~~~~~~
	//cout << strnum << endl << len << endl;
	//for (int i = 0; i < len; i++)
		//cout << code[i];
	////~~~~~~~~~~~~~~~~~~~测试代码——输出压缩文件的提取值~~~~~~~~~~~~~~~~~~~~~~~



	////~~~~~~~~~~~~~~~~~~~测试代码——输出before 01字符串~~~~~~~~~~~~~~~~~~~~~~~
	//cout << strnum << endl;
	cout <<endl<< "----------------------------------------------------------------------------------" << endl;
	cout << before << endl;
	////~~~~~~~~~~~~~~~~~~~测试代码——输出before 01字符串~~~~~~~~~~~~~~~~~~~~~~~


	//利用解压后的01字符串编码解出正确字符
	int jishu = 0, i = 0;
	string mystr;
	while (jishu < strnum-1)
	{
		int h = treehead;

		while (1)
		{
			if (before[i] == '0')
			{
				if ( tree[h].lchild != -1)
				{
					h = tree[h].lchild; 
					i++;
				}
				else
					break;
			}
			
			else if(before[i] == '1')
			{
				if ( tree[h].rchild != -1)
				{
					h = tree[h].rchild; 
					i++;
				}
				else
					break;
			}
		}
		mystr += tree[h].word;
		jishu++;
	}

	cout << mystr;
	//将得到的解码字符串输入到文件中
	ofstream outfile(goalname);
	outfile << mystr;
	outfile.close();

}



string dec_bin(int k)
{
	string k_bin;
	int bin[8], length = 0;
	while (k != 0)
	{
		bin[length++] = k % 2;
		k = k / 2;
	}

	for (int i = 0; i < 8 - length; i++)
		k_bin += '0';

	for (int i = length - 1; i >= 0; i--)
		k_bin += char(bin[i] + '0');
	
	return k_bin;
}