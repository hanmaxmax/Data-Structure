//��������
//˼�룺
//������Ԫ��������ȡһ��Ԫ�ز��뵽����Ԫ�ص���ȷλ���ϣ������˿���

#pragma once
#include <iostream>
using namespace std;

int Insert_swap = 0;
int Insert_com = 0;



void Insert(int a[], int k, const int& x)
{
	//��Ԫ��x���뵽ǰk������Ԫ�����棬������Ԫ�غ����Ԫ����������ƶ�һλ
	int i;
	Insert_com++;
	for (i = k - 1; i >= 0 && x < a[i]; i--)
	{
		a[i + 1] = a[i];
		Insert_com++;
		Insert_swap++;
	}
	a[i + 1] = x;//����ѭ���������� x>=a[i] �� i<0
	Insert_swap++;
}


void InsertionSort(int a[], int n)
{
	for (int i = 1; i < n; i++)
	{
		int t = a[i];
		Insert(a, i , t);
	}


	////��ӡ���
	//cout << "InsertSort: " << endl;
	//for (int i = 0; i < n; i++)
	//{
	//	cout << a[i] << " ";
	//}
	//cout << endl << endl;
}


void InsertCount(int &a,int &b)
{
	a = Insert_swap;
	b = Insert_com;
	cout << "InsertCount:" << endl;
	cout << "Swap: " << a << endl;
	cout << "Compare: " << b << endl << endl;

}