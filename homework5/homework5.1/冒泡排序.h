//ð������
//˼�룺
//���Ԫ�ر��ұߴ�����н�����ÿ���ź�һ�����ֵ��Ȼ����ʣ��n-1��Ԫ���м����Ա�

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

	////��ӡ���
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




////ð������Ľ�  ԭ����������Ѿ�������(ÿ��ð�ݵ�����)��Bubble����û�б�Ҫ�ٽ���
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
