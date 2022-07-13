#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#pragma comment(lib,"winmm.lib")
#include "Chain.h"
using namespace std;
vector<string> ban_v;

void createban_v();//����ͣ�ôʱ��vector
bool isBanwords(string t);//�ж��ַ����ǲ���ͣ�ôʱ���Ĵ�
string chuli(string );




int main()
{
	DWORD start = timeGetTime();//���ڼ����������ʱ��

	createban_v();//�Ƚ���ͣ�ôʱ�


	//��ȡ�ļ��еĵ���
	string filename = "text.txt";
	fstream fin;
	fin.open(filename.c_str(), ios::in);
	vector<string> v;
	string tmp;
	while (fin >> tmp)
	{
		v.push_back(tmp);
	}

	//����26����ĸ��Ӧ��26��������������ĸ���������ʲ����Ӧ������
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

	//����֮ǰ���������ļ�ʱ��ͬһ���������ֵ������򡱵Ľ��
	cout << "����ǰ��" << endl;
	for (int i = 0; i < 26; i++)
	{
		cout << "---------------" << char('a' + i) << "��ͷ�ĵ��ʣ�" << "---------------" << endl;
		chainArr[i].Show();

	}

	//����֮�󣬡�����Ƶ�������Ÿ������Ľ��
	cout << endl << endl << "-------------------------------------------------------------------------------------------------------------------" << endl << "�����" << endl;
	for (int i = 0; i < 26; i++)
	{
		cout << "---------------" << char('a' + i) << "��ͷ�ĵ��ʣ�" << "---------------" << endl;
		chainArr[i].mySort();
		chainArr[i].Show();
		
	}

	//�������飬ʹ��������ı�ͷָ�뱣����һά������
	ChainNode** firstArr = new ChainNode*[26];
	for (int i = 0; i < 26; i++)
	{
		firstArr[i] = chainArr[i].returnFirst();
	}

	DWORD end = timeGetTime();//���ڼ����������ʱ��
	cout << endl << "��������ʱ��Ϊ��" << end - start << "ms" << endl;

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
//	DWORD start = timeGetTime();//���ڼ����������ʱ��
//
//	createban_v();//�Ƚ���ͣ�ôʱ�
//
//
//
//	//��ȡ�ļ��еĵ���
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
//	//����26����ĸ��Ӧ��26��������������ĸ���������ʲ����Ӧ������
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
//	//����֮ǰ���������ļ�ʱ��ͬһ���������ֵ������򡱵Ľ��
//	cout << "����ǰ��" << endl;
//	for (int i = 0; i < 26; i++)
//	{
//		cout << "---------------" << char('a' + i) << "��ͷ�ĵ��ʣ�" << "---------------" << endl;
//		chainArr[i].Show();
//
//	}
//
//	//����֮�󣬡�����Ƶ�������Ÿ������Ľ��
//	cout << endl << endl << "-------------------------------------------------------------------------------------------------------------------" << endl << "�����" << endl;
//	for (int i = 0; i < 26; i++)
//	{
//		cout << "---------------" << char('a' + i) << "��ͷ�ĵ��ʣ�" << "---------------" << endl;
//		chainArr[i].mySort();
//		chainArr[i].Show();
//
//	}
//
//	//�������飬ʹ��������ı�ͷָ�뱣����һά������
//	ChainNode** firstArr = new ChainNode * [26];
//	for (int i = 0; i < 26; i++)
//	{
//		firstArr[i] = chainArr[i].returnFirst();
//	}
//
//	DWORD end = timeGetTime();//���ڼ����������ʱ��
//	cout << endl << "��������ʱ��Ϊ��" << end - start << "ms" << endl;
//
//}