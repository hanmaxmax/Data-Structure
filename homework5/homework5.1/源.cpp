#include"冒泡排序.h"
#include"希尔排序.h"
#include"快速排序.h"
#include"插入排序.h"
#include"选择排序.h"
#include<iostream>
#include<fstream>
#include<time.h>
#include<algorithm>
using namespace std;
int arr[10000],brr[10000],crr[10000],drr[10000],err[10000],krr[10000];

bool istrue(int* a, int* b)
{
	for (int i = 0; i < 10000; i++)
	{
		if (a[i] != b[i])
		{
			return false;
		}
	}
	return true;
}


int main()
{
	int a, b;
	

	//生成随机数并写入文件
	srand((unsigned)time(NULL));
	ofstream outfile1("num.txt");
	for (int i = 0; i < 10000; i++)
	{
		outfile1 << rand() << endl;
	}
	outfile1.close();

	//从文件中读取随机数
	ifstream infile1("num.txt");
	for (int i = 0; i < 10000; i++)
	{
		infile1 >> arr[i];
		brr[i] = arr[i];
		crr[i] = arr[i];
		drr[i] = arr[i];
		err[i] = arr[i];
		krr[i] = arr[i];
	}
	infile1.close();

	sort(krr, krr + 10000);
	


	InsertionSort(arr, 10000);
	InsertCount(a,b);


	

	BubbleSort(brr, 10000);
	BubbleCount(a, b);

	

	ShellSort(crr, 10000);
	ShellCount(a, b);

	

	QuickSort(drr, 10000);
	QuickCount(a, b);

	

	SelectSort(err, 10000);
	SelectCount(a, b);

	//quickSort(arr, 10000);
	//quickCount(a, b);

	//检验程序是否正确——将排序后的结果与调用algorithm的结果对比
	cout << istrue(krr, arr) << ' ';
	cout << istrue(krr, brr) << ' ';
	cout << istrue(krr, crr) << ' ';
	cout << istrue(krr, drr) << ' ';
	cout << istrue(krr, err);

}
