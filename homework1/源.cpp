#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#pragma comment(lib,"winmm.lib")
#include "Chain.h"
using namespace std;
vector<string> ban_v;

void createban_v();//创建停用词表的vector
bool isBanwords(string t);//判断字符串是不是停用词表里的词
string chuli(string );




int main()
{
	DWORD start = timeGetTime();//用于计算程序运行时间

	createban_v();//先建立停用词表


	//提取文件中的单词
	string filename = "text.txt";
	fstream fin;
	fin.open(filename.c_str(), ios::in);
	vector<string> v;
	string tmp;
	while (fin >> tmp)
	{
		v.push_back(tmp);
	}

	//创建26个字母对应的26个链表，并按首字母将各个单词插入对应链表中
	Chain* chainArr=new Chain[26];
	for (auto x : v)	
	{
		string arr = chuli(x);
		
		if (!isBanwords(arr))
		{
			int tem = arr[0] - 'a';
			chainArr[tem].Insert(arr);
		}
	}

	//排序之前，“读入文件时，同一个链表以字典序排序”的结果
	cout << "排序前：" << endl;
	for (int i = 0; i < 26; i++)
	{
		cout << "---------------" << char('a' + i) << "开头的单词：" << "---------------" << endl;
		chainArr[i].Show();

	}

	//排序之后，“按词频降序重排各链表”的结果
	cout << endl << endl << "-------------------------------------------------------------------------------------------------------------------" << endl << "排序后：" << endl;
	for (int i = 0; i < 26; i++)
	{
		cout << "---------------" << char('a' + i) << "开头的单词：" << "---------------" << endl;
		chainArr[i].mySort();
		chainArr[i].Show();
		
	}

	//创建数组，使所有链表的表头指针保存在一维数组中
	ChainNode** firstArr = new ChainNode*[26];
	for (int i = 0; i < 26; i++)
	{
		firstArr[i] = chainArr[i].returnFirst();
	}

	DWORD end = timeGetTime();//用于计算程序运行时间
	cout << endl << "程序运行时间为：" << end - start << "ms" << endl;

}


void createban_v()
{
	string filename = "banwords.txt";
	fstream fin;
	fin.open(filename.c_str(), ios::in);
	string tmp;
	while (fin >> tmp)
	{
		ban_v.push_back(tmp);
	}
}

bool isBanwords(string t)
{
	for (auto x : ban_v)
	{
		string arr = x;
		if (arr == t)
		{
			return true;
		}
	}
	return false;
}


string chuli(string x)
{
	int num = 0;
	char arr2[25] ;
	for (int i = 0; i < x.length(); i++)
	{
		if (x[i] <= 'Z' && x[i] >= 'A')
		{
			x[i] = x[i] - 'A' + 'a';
		}
		if (x[i] <= 'z' && x[i] >= 'a')
		{
			arr2[num++]=x[i];
		}
	}
	arr2[num] = '\0';
	string tem = arr2;
	return tem;
}



















//
//
//
//int main()
//{
//	DWORD start = timeGetTime();//用于计算程序运行时间
//
//	createban_v();//先建立停用词表
//
//
//
//	//提取文件中的单词
//	string filename = "text.txt";
//	fstream fin;
//	fin.open(filename.c_str(), ios::in);
//	vector<string> v;
//	string tmp;
//	while (fin >> tmp)
//	{
//		v.push_back(tmp);
//	}
//
//	//创建26个字母对应的26个链表，并按首字母将各个单词插入对应链表中
//	Chain* chainArr = new Chain[26];
//	for (auto x : v)
//	{
//		string arr = chuli(x);
//		//string arr = x;
//		if (!isBanwords(arr))
//		{
//			int tem = arr[0] - 'a';
//			chainArr[tem].Insert(arr);
//		}
//	}
//
//	//排序之前，“读入文件时，同一个链表以字典序排序”的结果
//	cout << "排序前：" << endl;
//	for (int i = 0; i < 26; i++)
//	{
//		cout << "---------------" << char('a' + i) << "开头的单词：" << "---------------" << endl;
//		chainArr[i].Show();
//
//	}
//
//	//排序之后，“按词频降序重排各链表”的结果
//	cout << endl << endl << "-------------------------------------------------------------------------------------------------------------------" << endl << "排序后：" << endl;
//	for (int i = 0; i < 26; i++)
//	{
//		cout << "---------------" << char('a' + i) << "开头的单词：" << "---------------" << endl;
//		chainArr[i].mySort();
//		chainArr[i].Show();
//
//	}
//
//	//创建数组，使所有链表的表头指针保存在一维数组中
//	ChainNode** firstArr = new ChainNode * [26];
//	for (int i = 0; i < 26; i++)
//	{
//		firstArr[i] = chainArr[i].returnFirst();
//	}
//
//	DWORD end = timeGetTime();//用于计算程序运行时间
//	cout << endl << "程序运行时间为：" << end - start << "ms" << endl;
//
//}