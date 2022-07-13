#pragma once

//ѡ������
//˼�룺
//�����򲿷��ҵ���С���󣩵�ֵ�ƶ�����ǰ�棨���棩��ֱ������


int Select_swap = 0;
int Select_com = 0;


template <class T>
int Max(T a[],int k)
{
	//��ǰ������ǰk��Ԫ��[0 - k-1]�����Ԫ�ص�λ��
	int pos = 0;
	for (int i = 1; i < k; i++)
	{
		Select_com++;
		if (a[pos] <= a[i])//Ϊ���ȶ�������Լӵ��ں�=
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
	//ÿ�εݼ�����[ 1��size-1 ]��Ȼ���ҵ����Ԫ�ؽ���λ��
	for (int size = len; size > 1; size--)
	{
		int t = Max(a, size);
		SeSwap(a[t], a[size - 1]);
		
	}


	////��ӡ���
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







////�Ľ�ѡ������  ԭ����ԭ�������ź���Ļ�����Ҫ������ʱ�����ܲ�
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
//			//���forѭ����ȫ��ִ��if������ʾ�Ѿ��ź��򣬲���ִ��else������ѭ��
//			if (a[pos] <= a[i])
//				pos = i;
//			//ֻҪ��һ���ط�û���ź����һ����ִ��else��䣬����������һ��forѭ��
//			else
//				sorted = false;
//		}
//		Swap(a[pos], s[size - 1]);
//	}
//}