#include <iostream>
#include <math.h>
#include"��������.h"
using namespace std;


//����ȫ�ֱ���
int m, n, k;//����n������m�������������k
int** arr;//arr�Ǵ������Ķ�ά����

//��������
int bin_dec(int index);//������תʮ����
int Sort_max(int*, int);//���� + �����Ԫ�ص�������

int main()
{
	//�û������������������������������
	cout << "����������n������m�������������k��" << endl;
	cin >> n >> m >> k;
	arr = new int* [n];
	for (int i = 0; i < n; i++)
	{
		arr[i] = new int[m];
	}

	cout << "���������" << endl;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> arr[i][j];

	//����ÿ��0�ĸ�������������count��
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

	//��count����С�ڵ���k�� ��ż�� ���ֿ�
	int* ou = new int[n];//ou��� 0�ĸ���Ϊż�� && 0�ĸ���<=k ���Ǽ��еĽű�
	int* ji = new int[n];//ji��� 0�ĸ���Ϊ���� && 0�ĸ���<=k ���Ǽ��еĽű�
	int count_ou = 0;
	int count_ji = 0;
	for (int i = 0; i < n; i++)
	{
		if (count[i] <= k && count[i] % 2 == 0)
			ou[count_ou++] = i;
		if (count[i] <= k && count[i] % 2 == 1)
			ji[count_ji++] = i;
	}
	int maxx = 0;//maxx��¼���ͨ����

	if (k % 2 == 0)//k��ż��
	{
		int* temp = new int[count_ou];
		for (int i = 0; i < count_ou; i++)
		{
			temp[i]=bin_dec(ou[i]);//temp����ǣ����� 0�ĸ���Ϊż�� && 0�ĸ���<=k �����Ǽ���01��ת��Ϊ10������
		}

		//���ͨ����ʮ��������õ������� ���Ԫ�ص�������
		cout << "���ͨ��Ϊ��" << Sort_max(temp,count_ou) << endl;

	}


	if (k % 2 == 1)//k������
	{
		int* temp = new int[count_ji];
		for (int i = 0; i < count_ji; i++)
		{
			temp[i] = bin_dec(ji[i]);//temp����ǣ����� 0�ĸ���Ϊż�� && 0�ĸ���<=k �����Ǽ���01��ת��Ϊ10������
		}

		//���ͨ����ʮ��������õ������� ���Ԫ�ص�������
		cout << "���ͨ��Ϊ��" << Sort_max(temp,count_ji) << endl;

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
	//����
	QuickSort(temp, t);

	//������֮��������У���ͬԪ�ص�������
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
