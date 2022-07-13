//插入排序
//思想：
//从无序元素中依次取一个元素插入到有序元素的正确位置上，类似扑克牌

#pragma once
#include <iostream>
using namespace std;

int Insert_swap = 0;
int Insert_com = 0;



void Insert(int a[], int k, const int& x)
{
	//把元素x插入到前k个数组元素里面，并将此元素后面的元素依次向后移动一位
	int i;
	Insert_com++;
	for (i = k - 1; i >= 0 && x < a[i]; i--)
	{
		a[i + 1] = a[i];
		Insert_com++;
		Insert_swap++;
	}
	a[i + 1] = x;//跳出循环的条件是 x>=a[i] 或 i<0
	Insert_swap++;
}


void InsertionSort(int a[], int n)
{
	for (int i = 1; i < n; i++)
	{
		int t = a[i];
		Insert(a, i , t);
	}


	////打印结果
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