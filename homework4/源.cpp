#include <iostream>
#include <queue>
using namespace std;
struct point
{
	int hang;
	int lie;

	point(int i,int j)
	{
		hang = i;
		lie = j;
	}
	point() {}
};

//创建初始全局变量 
int** visit;//用来标识该点是否被遍历到了
char** pic;//用来存储图像
int n;//n是表示格子有 n*n 个
int T = 0;//记录融化时间
int flag = 0;


//函数声明
void init();//将visit数组全部置为0
void print();//打印图像
void change();
void bfc(int i, int j);
void melt();//金属融化——判断融化的金属块#，并将其换为液体~
bool judge();//判断金属是否已经融化完



int main()
{
	cin >> n;

	//初始化图像数组和visit标记数组
	pic = new char* [n];
	for (int i = 0; i < n; i++)
	{
		pic[i] = new char[n];
	}
	visit = new int* [n];
	for (int i = 0; i < n; i++)
	{
		visit[i] = new int[n];
	}
	init();
	
	//输入图像
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> pic[i][j];
	

	//判断是否永远不会融化
	change();
	melt();
	if (flag==0)
	{
		cout << -1 << endl;
		return 0;
	}
	T++;

	cout << "T = " << T << "：" << endl;
	print();


	

	while (judge())
	{
		change();
		melt();
		T++;

		cout << "T = " << T << "：" << endl;
		print();
	}

	cout << "T最终为：" << T << endl;



}


void change()
{
	//第一行 & 最后一行
	for (int i = 0; i < n; i++)
	{
		//pic[0][i] , pic[n-1][i]
		if (pic[0][i] != '#' && visit[0][i] == 0)
		{
			bfc(0, i);
		}

		if (pic[n - 1][i] != '#' && visit[n - 1][i] == 0)
		{
			bfc(n-1, i);
		}

	}

	//第一列 & 最后一列
	for (int i = 1; i < n-1; i++)
	{
		//pic[i][0] , pic[i][n-1]
		if (pic[i][0] != '#' && visit[i][0] == 0)
		{
			bfc(i, 0);
		}

		if (pic[i][n - 1] != '#' && visit[i][n - 1] == 0)
		{
			bfc(i, n-1);
		}

	}

}



void bfc(int i, int j)
{
	point root(i, j);
	queue<point> qu;

	qu.push(root);
	visit[i][j] = 1; pic[i][j] = '~';
	

	while (!qu.empty())
	{
		point temp = qu.front();
		qu.pop();
		int a = temp.hang;
		int b = temp.lie;
		if (a - 1 >= 0 && pic[a - 1][b] != '#' && visit[a - 1][b] == 0)
		{
			point ppoint(a - 1, b);
			qu.push(ppoint);
			visit[a - 1][b] = 1; pic[a - 1][b] = '~';
			
		}

		if (a + 1 < n && pic[a + 1][b] != '#' && visit[a + 1][b] == 0)
		{
			point ppoint(a + 1, b);
			qu.push(ppoint);
			visit[a + 1][b] = 1; pic[a + 1][b] = '~';
			
		}

		if (b - 1 >= 0 && pic[a][b - 1] != '#' && visit[a][b - 1] == 0)
		{
			point ppoint(a, b-1);
			qu.push(ppoint);
			visit[a][b - 1] = 1; pic[a][b - 1] = '~';
		}

		if (b + 1 < n && pic[a][b + 1] != '#' && visit[a][b + 1] == 0)
		{
			point ppoint(a, b + 1);
			qu.push(ppoint);
			visit[a][b + 1] = 1; pic[a][b + 1] = '~';
		}
	}


}



void melt()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (pic[i][j] == '#')
			{
				int count = 0;
				//当这个#上面是液体
				if (i - 1 >= 0 && pic[i - 1][j] == '~')
				{
					count++;
				}
				
				//当这个#下面是液体
				if (i + 1 < n && pic[i + 1][j] == '~')
				{
					count++;
				}
				
				//当这个#左面是液体
				if (j - 1 >= 0 && pic[i][j - 1] == '~')
				{
					count++;
				}
				
				//当这个#右面是液体
				if (j + 1 < n && pic[i][j + 1] == '~')
				{
					count++;
				}
				
				//判断是否有大于等于两个面是液体
				if (count >= 2)
				{
					pic[i][j] = '+';//金属融化
					flag = 1;
				}

			}
		}
	}

	//再将有标记的字块置为~
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (pic[i][j] == '+')
			{
				pic[i][j] = '~';
			}
		}
	}

}






void init()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			visit[i][j] = 0;
		}
	}

}


void print()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << pic[i][j];
		cout << endl;
	}
	cout << endl;
}



bool judge()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (pic[i][j] == '#')
			{
				return true;
			}
		}
	}
	return false;
}



































































//#include<iostream>
//using namespace std;
//
//static int N, T;//N:边长；T:时间
//
//
//void Change(char **pic);
//void Output(char **pic);
//void Melt(char **pic);
//
//
//
//
//int main()
//{
//	//输出N及图形的样子
//	cout << "N=? （5≤N≤1000）" << endl;
//	cin >> N;
//	cout << "图形的样子？" << endl;
//
//	//pic是存储图形的二维数组
//	char** pic = new char* [N];
//	for (int i = 0; i < N; i++)
//		pic[i] = new char[N];
//	//下面输入二维数组pic
//	for (int i = 0; i < N; i++)
//		for (int j = 0; j < N; j++)
//			cin >> pic[i][j];
//
//	Change(pic);//把中空的格子由 _ 改成 *
//	Output(pic);
//	Melt(pic);
//}
//
//
////把中空的格子由 _ 改成 *
//void Change(char** pic)
//{
//	//遍历整个图形
//	for (int m = 0; m < N; m++)
//		for (int n = 0; n < N; n++)
//		{
//			//依次判断每个为 _ 的格子的前后左右（也可能是前前或者后后后）是否有#
//			if (pic[m][n] == '_' && m > 0 && n > 0 && m < N - 1 && n < N - 1)
//			{
//				int x = 0;
//				int I1 = m, I2 = m, J1 = n, J2 = n;
//
//				//根据‘_’四个方向上是否都有‘#’来初步判断是否中空
//				while (I1 > -1)
//				{
//					if (pic[I1--][n] == '#')
//					{
//						x++;
//						break;
//					}
//				}
//				while (I2 < N)
//				{
//					if (pic[I2++][n] == '#')
//					{
//						x++;
//						break;
//					}
//				}
//				while (J1 > -1)
//				{
//					if (pic[m][J1--] == '#')
//					{
//						x++;
//						break;
//					}
//				}
//				while (J2 < N)
//				{
//					if (pic[m][J2++] == '#')
//					{
//						x++;
//						break;
//					}
//				}
//				if (x == 4)
//					pic[m][n] = '*';
//			}
//		}
//
//	//筛选出中空的格子
//	while (1)
//	{
//		int l = 0;
//		for (int i = 0; i < N; i++)
//			for (int j = 0; j < N; j++)
//			{
//				if (pic[i][j] == '_')
//				{
//					if (i > 0 && pic[i - 1][j] == '*')
//					{
//						l++;
//						pic[i - 1][j] = '_';
//					}
//					if (i < N - 1 && pic[i + 1][j] == '*')
//					{
//						l++;
//						pic[i + 1][j] = '_';
//					}
//					if (j > 0 && pic[i][j - 1] == '*')
//					{
//						l++;
//						pic[i][j - 1] = '_';
//					}
//					if (j < N - 1 && pic[i][j + 1] == '*')
//					{
//						l++;
//						pic[i][j + 1] = '_';
//					}
//				}
//			}
//		if (l == 0)
//			break;
//	}
//}
//
////"融化"操作
//void Melt(char **pic)
//{
//	T = 0;
//	while (1)
//	{
//		int count = 0;
//		for (int i = 0; i < N; i++)
//			for (int j = 0; j < N; j++)
//				if (pic[i][j] != '_')
//					count++;
//		if (count == 0)
//			break;
//
//		for (int m = 0; m < N; m++)
//			for (int n = 0; n < N; n++)
//			{
//				if (pic[m][n] == '#')
//				{
//					int x = 0;
//					if (m > 0 && pic[m - 1][n] == '_')
//						x++;
//					if (m < N - 1 && pic[m + 1][n] == '_')
//						x++;
//					if (n > 0 && pic[m][n - 1] == '_')
//						x++;
//					if (n < N - 1 && pic[m][n + 1] == '_')
//						x++;
//					if (x > 1)
//						pic[m][n] = '1';
//				}
//			}
//		for (int m = 0; m < N; m++)
//			for (int n = 0; n < N; n++)
//				if (pic[m][n] == '1')
//					pic[m][n] = '_';
//
//		T++;
//		Change(pic);
//		cout << "T=" << T << endl;
//		Output(pic);
//	}
//	cout << T;
//	system("pause");
//}
//
//
//void Output(char** pic)
//{
//	cout << endl;
//	for (int i = 0; i < N; i++)
//	{
//		for (int j = 0; j < N; j++)
//			cout << pic[i][j];
//		cout << endl;
//	}
//	cout << endl;
//}
//
