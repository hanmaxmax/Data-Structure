// ��������
// ˼�룺
// ��������ÿһ��������ߵ����Աȣ�˭��������һ������Ķ�Ӧλ��+1
// Ȼ����һ��������Ԫ�ش�С��������

#pragma once
#include <iostream>
using namespace std;

// δ�Ľ����������
template<class T>
void Rank(T a[], int n, int r[])
{
	for (int i = 0; i < n; i++)
	{
		r[i] = 0;
	}
	//����������ѭ����ÿ����������ߵ������д�С�Ƚϣ�Ȼ���������ڶ�Ӧ������λ����+1
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

//�Ľ����������(Rank�������䣬�ı�Rearrange����)
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
		//����Ҫ��whileѭ������Ϊÿ��ѭ��֮ǰ��֪����i��λ��Ӧ�÷�ʲô�����һ���֮��Ҳ��֪��������ʲô����֪����������ȥ������ȷλ�ã�������Ҫѭ��
		{
			int t = r[i];
			Swap(a[i], a[t]);
			Swap(r[i], r[t]);
		}
	}
}




