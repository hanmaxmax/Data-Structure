// 计数排序
// 思想：
// 把数组中每一个数和左边的数对比，谁大则在另一个数组的对应位置+1
// 然后按另一个数组中元素大小进行排序

#pragma once
#include <iostream>
using namespace std;

// 未改进版计数排序
template<class T>
void Rank(T a[], int n, int r[])
{
	for (int i = 0; i < n; i++)
	{
		r[i] = 0;
	}
	//首先用两层循环让每个数都和左边的数进行大小比较，然后给大的数在对应的数组位置里+1
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (a[j] <= a[i])
			{
				r[i]++;
			}
			else
				r[j]++;
		}
	}
}


template<class T>
void Rearrange(T a[], int n, int r[])
{
	T* u = new T[n + 1];
	for (int i = 0; i < n; i++)
	{
		u[r[i]] = a[i];
	}
	for (int i = 0; i < n; i++)
	{
		a[i] = u[i];
	}
	delete[]u;
}

//改进后计数排序(Rank函数不变，改变Rearrange函数)
template<class T>
void Swap(T &a,T &b)
{
	T temp = a;
	a = b;
	b = temp;
}

template<class T>
void Rearranger_new(T a[], int n, int r[])
{
	for (int i = 0; i < n; i++)
	{
		while (r[i] != i)
		//这里要用while循环，因为每次循环之前不知道第i个位置应该放什么，而且换完之后也不知道换成了什么（但知道被换掉过去的是正确位置），所以要循环
		{
			int t = r[i];
			Swap(a[i], a[t]);
			Swap(r[i], r[t]);
		}
	}
}




