//冒泡排序
//思想：
//左边元素比右边大则进行交换，每次排好一个最大值，然后在剩余n-1个元素中继续对比

#pragma once
#include <iostream>
using namespace std;

int Bubble_swap = 0;
int Bubble_com = 0;


void BSwap(int& a, int& b)
{
	int t = a;
	a = b;
	b = t;
	Bubble_swap++;
}


void Bubble(int a[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		Bubble_com++;
		if (a[i] > a[i + 1])
		{
			BSwap(a[i], a[i + 1]);
		}
	}
}


void BubbleSort(int a[], int n)
{
	for (int size = n; size > 1; size--)
	{
		Bubble(a, size);
	}

	////打印结果
	//cout << "BubbleSort: " << endl;
	//for (int i = 0; i < n; i++)
	//{
	//	cout << a[i] << " ";
	//}
	//cout << endl << endl;


}


void BubbleCount(int& a, int& b)
{
	a = Bubble_swap;
	b = Bubble_com;
	cout << "BubbleCount:" << endl;
	cout << "Swap: " << a << endl;
	cout << "Compare: " << b << endl << endl;;
}




////冒泡排序改进  原因：如果数组已经有序了(每次冒泡的排序)，Bubble函数没有必要再进行
//template<class T>
//bool Bubble(T a[], int n)
//{
//	bool swapped = false;
//	for (int i = 0; i < n; i++)
//	{
//		if (a[i] > a[i + 1])
//		{
//			Swap(a[i], a[i + 1]);
//			swapped = true;
//		}
//		return swapped;
//	}
//}
//
//template<class T>
//void BubbleSort(T a[], int n)
//{
//	for (int i = n; i > 1 && Bubble(a, i); i--);
//}
//
//
