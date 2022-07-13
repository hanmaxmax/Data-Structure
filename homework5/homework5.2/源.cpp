#include <iostream>
#include <math.h>
#include"快速排序.h"
using namespace std;


//创建全局变量
int m, n, k;//行数n，列数m，激光照射次数k
int** arr;//arr是储存矩阵的二维数组

//函数声明
int bin_dec(int index);//二进制转十进制
int Sort_max(int*, int);//排序 + 找相等元素的最大个数

int main()
{
	//用户输入行数、列数、照射次数、矩阵
	cout << "请输入行数n，列数m，激光照射次数k：" << endl;
	cin >> n >> m >> k;
	arr = new int* [n];
	for (int i = 0; i < n; i++)
	{
		arr[i] = new int[m];
	}

	cout << "请输入矩阵：" << endl;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> arr[i][j];

	//计算每行0的个数，存在数组count里
	int* count = new int[n];
	for (int i = 0; i < n; i++)
	{
		int c = 0;
		for (int j = 0; j < m; j++)
		{
			if (arr[i][j] == 0)
			{
				c++;
			}
			count[i] = c;
		}
	}

	//把count里面小于等于k的 奇偶行 区分开
	int* ou = new int[n];//ou存放 0的个数为偶数 && 0的个数<=k 的那几行的脚标
	int* ji = new int[n];//ji存放 0的个数为奇数 && 0的个数<=k 的那几行的脚标
	int count_ou = 0;
	int count_ji = 0;
	for (int i = 0; i < n; i++)
	{
		if (count[i] <= k && count[i] % 2 == 0)
			ou[count_ou++] = i;
		if (count[i] <= k && count[i] % 2 == 1)
			ji[count_ji++] = i;
	}
	int maxx = 0;//maxx记录最大导通行数

	if (k % 2 == 0)//k是偶数
	{
		int* temp = new int[count_ou];
		for (int i = 0; i < count_ou; i++)
		{
			temp[i]=bin_dec(ou[i]);//temp存的是：将（ 0的个数为偶数 && 0的个数<=k ）的那几行01串转化为10进制数
		}

		//最大导通数是十进制排序好的数组里 相等元素的最大个数
		cout << "最大导通数为：" << Sort_max(temp,count_ou) << endl;

	}


	if (k % 2 == 1)//k是奇数
	{
		int* temp = new int[count_ji];
		for (int i = 0; i < count_ji; i++)
		{
			temp[i] = bin_dec(ji[i]);//temp存的是：将（ 0的个数为偶数 && 0的个数<=k ）的那几行01串转化为10进制数
		}

		//最大导通数是十进制排序好的数组里 相等元素的最大个数
		cout << "最大导通数为：" << Sort_max(temp,count_ji) << endl;

	}
}



int bin_dec(int index)
{
	int sum = 0;
	for (int i = 0; i < m; i++)
	{
		sum += arr[index][i] * pow(2.0, i);
	}
	return sum;
}


int Sort_max(int* temp,int t)
{
	//快排
	QuickSort(temp, t);

	//找排序之后的序列中，相同元素的最大个数
	int maxx = 1;
	for (int i = 0; i < t; i++)
	{
		int ma = 1;
		for (int j = i + 1; j < t; j++)
		{
			if (temp[j] == temp[i])
			{
				ma++;
			}
			else
				break;
		}
		maxx = maxx >= ma ? maxx : ma;
	}

	return maxx;
}
