#include <iostream>
#include <fstream>
#include <stack>
#include "hafuman.h"
#include <string>
#include<iomanip>
using namespace std;

//����ȫ�ֱ���
int n = 100; int num = 0;
treeNode* tree = new treeNode[2 * n + 1];

//���庯��
int findmin(int x);//�ҵ���Сֵ�͵����ڶ�Сֵ
int creatRstr(stack<char>& st, int i);//�γɱ����ջ�������ӽڵ㿪ʼ����Ѱ�ұ��룩
void HufumanCode(char** str, string filename, int temnum, string datname);//���ļ����б��룬����ѹ������ļ�д��.dat
void BreakCode(string datname, int treehead,string goalname);//��ѹ���ļ���ѹ��
string dec_bin(int k);//��ʮ����ת��Ϊ�����ƣ�������0����7λ�ַ���


int main()
{
	string filename1 = "inputfile1.txt";
	string filename2 = "inputfile2.txt";

	//��text.txt�ļ���ȡ�ַ�������Ȩ��
	char ch; 
	int strnum = 0;//����ԭ�ļ��ж��ٸ��ַ�
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

	////~~~~~~~~~~~~~~~~~~~���Դ��롪���ַ�����Ȩ��~~~~~~~~~~~~~~~~~~~~~~~
	//for (int i = 0; i < num; i++)
	//{
	//	cout << tree[i].word << "    " << tree[i].weight << endl;
	//}
	////~~~~~~~~~~~~~~~~~~~���Դ��롪���ַ�����Ȩ��~~~~~~~~~~~~~~~~~~~~~~~
	int temnum = num; 


	//�����������  
	//������Сֵ�͵����ڶ�Сֵ
	int head;//���Ǹ�������ֵ
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
	
	//�ҵ�ÿ���ַ���Ӧ�ı���
	char** str = new char* [temnum];
	for (int i = 0; i < temnum; i++)
	{
		str[i] = new char[80];//50ΪĬ�ϱ�����󳤶�
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

	////~~~~~~~~~~~~~~~~~~~���Դ��롪�����ÿ���ַ���Ӧ�ı���~~~~~~~~~~~~~~~~~~~~~~~
	//for (int i = 0; i < temnum; i++)
	//{
	//	cout << tree[i].word << "   " << str[i] << endl;
	//}
	////~~~~~~~~~~~~~~~~~~~���Դ��롪�����ÿ���ַ���Ӧ�ı���~~~~~~~~~~~~~~~~~~~~~~~




	//�����ַ����ִ����Ͷ�Ӧ����
	ofstream outf("outputfile1.txt");
	outf << setiosflags(ios::left);
	//outf << setw(10) <<"�ַ�"<< setw(10) << "����" << setw(10) << "����" << endl;
	for (int i = 0; i < temnum; i++)
	{
		outf << setw(5) << tree[i].word << setw(5)<< tree[i].weight << setw(10) <<str[i] << endl;
	}
	outf.close();





	//���ļ����б��룬����ѹ������ļ�д��.dat
	HufumanCode(str, filename2, temnum,"outputfile.dat");//���� �ļ�ת����01�ַ�����ָ��γɵ�ASCII����ѹ�����ASCII�ַ���

	//��ѹ���ļ���ѹ��
	BreakCode("outputfile.dat", head, "outputfile2.txt");


}





int findmin(int x)
{
	int a = 10000; int index = -1;//���index��ķ���-1��˵��ֻʣһ��treenode��
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
		//��0 ��1
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
	string before;//�ݴ�01δ�����ַ�������ĵط�
	int strnum = 0;//����ԭ�ļ��ж��ٸ��ַ�
	ifstream fin(filename);
	fin.get(ch); strnum++;
	//�Ȱ��ļ����ձ��뷽ʽת����01�ַ�������before��
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
	
	//��before 01������8�ı����Ĳ��ֲ���
	int temlen = before.length();
	if (temlen % 8 != 0)
	{
		for (int i = 0; i < 8 - temlen % 8; i++)
		{
			before += '0';
		}
	}

	//~~~~~~~~~~~~~~~~~~~���Դ��롪�����before 01�ַ���~~~~~~~~~~~~~~~~~~~~~~~
	cout << before << endl;
	//~~~~~~~~~~~~~~~~~~~���Դ��롪�����before 01�ַ���~~~~~~~~~~~~~~~~~~~~~~~

	//��01�ַ���ÿ8��01�ַ��ϲ���һ��ASCII�ַ�������ѹ������ַ�������last��
	//string last;//�ݴ�ѹ������ַ���
	ofstream fout(datname, ios::binary);//�����ڡ�д���Ķ����ƴ����ļ� 
	fout.write((char*)(&strnum), sizeof(int));//�ȴ�ԭ�ļ�һ���ж����ַ�
	
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

	////~~~~~~~~~~~~~~~~~~~���Դ��롪�����last�ַ���~~~~~~~~~~~~~~~~~~~~~~~
	//for (int i = 0; i < last.length(); i++)
	//	cout << last[i];
	////~~~~~~~~~~~~~~~~~~~���Դ��롪�����last�ַ���~~~~~~~~~~~~~~~~~~~~~~~

	
	fout.close();

}


void BreakCode(string datname, int treehead, string goalname)
{

	int strnum;
	ifstream fin(datname, ios::binary);
	fin.read((char*)(&strnum), sizeof(int));//��ԭ�ļ����ַ���strnum��ȡ����
	
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

	////~~~~~~~~~~~~~~~~~~~���Դ��롪�����ѹ���ļ�����ȡֵ~~~~~~~~~~~~~~~~~~~~~~~
	//cout << strnum << endl << len << endl;
	//for (int i = 0; i < len; i++)
		//cout << code[i];
	////~~~~~~~~~~~~~~~~~~~���Դ��롪�����ѹ���ļ�����ȡֵ~~~~~~~~~~~~~~~~~~~~~~~



	////~~~~~~~~~~~~~~~~~~~���Դ��롪�����before 01�ַ���~~~~~~~~~~~~~~~~~~~~~~~
	//cout << strnum << endl;
	cout <<endl<< "----------------------------------------------------------------------------------" << endl;
	cout << before << endl;
	////~~~~~~~~~~~~~~~~~~~���Դ��롪�����before 01�ַ���~~~~~~~~~~~~~~~~~~~~~~~


	//���ý�ѹ���01�ַ�����������ȷ�ַ�
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
	//���õ��Ľ����ַ������뵽�ļ���
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