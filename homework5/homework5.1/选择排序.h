#pragma once

//选择排序
//思想：
//在无序部分找到最小（大）的值移动到最前面（后面），直到排完


int Select_swap = 0;
int Select_com = 0;


template <class T>
int Max(T a[],int k)
{
	//从前往后找前k个元素[0 - k-1]中最大元素的位置
	int pos = 0;
	for (int i = 1; i < k; i++)
	{
		Select_com++;
		if (a[pos] <= a[i])//为了稳定排序可以加等于号=
		{
			pos = i;
		}
	}
	return pos;
}

template <class T>
void SeSwap(T &a,T &b)
{
	T t = a;
	a = b;
	b = t;
	Select_swap++;
}


template <class T>
void SelectSort(T a[], int len)
{
	//每次递减遍历[ 1，size-1 ]，然后找到最大元素交换位置
	for (int size = len; size > 1; size--)
	{
		int t = Max(a, size);
		SeSwap(a[t], a[size - 1]);
		
	}


	////打印结果
	//cout << "SelectSort: " << endl;
	//for (int i = 0; i < len; i++)
	//{
	//	cout << a[i]<< " ";
	//}
	//cout << endl << endl;
}



void SelectCount(int& a, int& b)
{
	a = Select_swap;
	b = Select_com;
	cout << "SelectCount:" << endl;
	cout << "Swap: " << a << endl;
	cout << "Compare: " << b << endl << endl;
}







////改进选择排序  原因：若原数组已排好序的话还需要遍历，时间性能差
//template<class T>
//void SelectSort(T a[], int n)
//{
//	bool sorted = false;
//	for (int size = n; !sorted && (size > 1); size--)
//	{
//		int pos = 0;
//		sorted = true;
//
//		for (int i = 1; i < size; i++)
//		{
//			//如果for循环中全部执行if语句则表示已经排好序，不会执行else，跳出循环
//			if (a[pos] <= a[i])
//				pos = i;
//			//只要有一个地方没有排好序就一定会执行else语句，进而进行下一个for循环
//			else
//				sorted = false;
//		}
//		Swap(a[pos], s[size - 1]);
//	}
//}