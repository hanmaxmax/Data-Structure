#include"B_tree.h"
#include <graphics.h>
#include <time.h>
#include <conio.h>
#include <string>
#include <string.h>
#include<cstring>
#include<queue>
#include <iostream>
#include <graphics.h>		// 引用图形库头文件
#include <conio.h>
using namespace std;

// 插入
// 找到最底层插入的节点位置
// 叶节点没满，直接插入
// 叶节点满了，将中间节点挤上去，左右半边分开成两个子节点
// 继续向上传递，将上一把的中间节点插进父节点 
//（中间节点：如果节点数是偶数，则中间节点是偏向后面的那个——例如：0，1，2，3 的中间是2）



// 删除
// 中间节点的删除（先转化为叶节点）：
// 删除：先用它的直接前驱——它的左子树的最底层的最后一个孩子（左子树的最底右下角）来代替它
// 然后删除它的直接前驱（那个叶节点）

// 叶节点的删除（借 / 合并[合并要删父节点，继续向上追溯]）：
// 不冲突——直接删除
// 冲突：先看左兄弟够不够借，再看右兄弟，如果两者找到一个够借的，那就：算上父节点集体偏移
// 如果都不够借，那就和左兄弟合并（如果没有左兄弟，就只能和右合并了）
// 合并：（该节点 + 它的待合并兄弟节点 + 它们的父节点）共同构成一个新节点，然后删除 “它们的父节点”
// 如果上把合并的时候 删除它们的父节点 —（导致）—> 父节点删除之后不满足要求了，则父节点继续和他自己的兄弟合并（此时只能一直往上追溯，不能再往下了）




enum Error_code
{
	not_present, success, overflow, duplicate_error
};
int order;


//int是B树存的数据类型

class B_node
{
public:
	int count;//节点关键字个数
	int* data;//本节点关键字数组
	B_node** branch;//子树指针数组,例如branch[0]指向第一棵子树（即所有keys小于data[0]的子树）

	//构造函数
	B_node();
};


B_node::B_node()
{
	data = new int[order - 1];
	branch = new B_node * [order];
	count = 0;
	for (int i = 0; i < order; i++)//子树指针数组初始化
	{
		branch[i] = NULL;
	}
	for (int i = 0; i < order - 1; i++)//关键字数组初始化
	{
		data[i] = '\0';
	}

}


class B_tree
{
public:
	Error_code recursive_search_tree(B_node* current, int& target);
	Error_code search_node(B_node* current, const int& target, int& position);
	Error_code insert(const int& new_entry);
	Error_code push_down(B_node* current, const int& new_entry, int& median, B_node*& right_branch);
	void push_in(B_node* current, const int& entry, B_node* right_branch, int position);
	void split_node(B_node* current, const int& extra_entry, B_node* extra_branch, int position, B_node*& right_half, int& median);
	Error_code remove(const int& target);
	Error_code recursive_remove(B_node* current, const int& target);
	void remove_data(B_node* current, int position);
	void copy_in_predecessor(B_node* current, int position);
	void restore(B_node* current, int position);
	void move_left(B_node* current, int position);
	void move_right(B_node* current, int position);
	void combine(B_node* current, int position);
	void printpoint(B_node* node, int count);
	void printpoint();
	int getHeight();
	void show();



	B_tree()
	{
		root = NULL;
	}

	B_node* root;
};



void B_tree::printpoint(B_node* node, int count)
{

	if (node != NULL)//判断元素是否为空
	{
		int i, j;
		//每个节点从小到大打印
		for (i = 0; i < node->count; i++)
		{
			//判断是否叶节点,不是的话则要往子节点中寻找打印
			if (node->branch[0] != NULL)//判断是否是叶子节点
			{
				printpoint(node->branch[i], count - 3);
			}
			for (j = count; j >= 0; j--)
			{
				cout << "-";
			}
			cout << "|" << node->data[i] << "|" << endl;
		}
		if (node->branch[0] != NULL)//子节点数比关键字数多一个
		{
			printpoint(node->branch[i], count - 3);
		}
	}
}



void B_tree::printpoint()
{
	cout << endl;
	cout << "**********************显示树形*******************" << endl;
	cout << endl;
	printpoint(root, order * 5);
	cout << endl;
}







Error_code B_tree::recursive_search_tree(B_node* current, int& target)
//current——用来递归，可以是空指针或者指向B树的某棵子树/节点
//target——需要查找的值
//返回值——用来存找没找到
//最终结果——找到了，则current存target所在节点，position存target值在节点中的位置
{
	Error_code result = not_present;//result初始化为找不到，找到了再更改
	int position;
	if (current != NULL)
	{
		result = search_node(current, target, position);
		if (result == not_present)
			result = recursive_search_tree(current->branch[position], target);
		else
			target = current->data[position];
	}
	return result;
}

//搜索当前节点，看这个节点里有没有target

Error_code B_tree::search_node(B_node* current, const int& target, int& position)
//position是用来返回传参的
//如果找到了，position就向recursive_search_tree函数返回target的位置；并返回sucess的标识
//如果没找到，position就向recursive_search_tree函数返回小于target的位置；并返回not_present的标识
{
	position = 0;
	while (position < current->count && target > current->data[position])
		position++; //先把position箭头指向target的位置 或 可以索引到target的位置
	if (position < current->count && target == current->data[position])
		return success;
	else
		return not_present;//表明此节点里没有target（但position已指到相应的位置了）
}


//将new_entry插入树里
//有两种返回值
//success：插入成功
//duplicate_error：原数据已存在，插入失败

Error_code B_tree::insert(const int& new_entry)
{
	int median;
	B_node* right_branch, * new_root;
	Error_code result = push_down(root, new_entry, median, right_branch);
	if (result == overflow)
		//如果最后返回到第一个压栈函数（也就是根节点压的栈）时，仍然是overflow，说明根节点也要进行插值分裂
	{
		new_root = new B_node;
		new_root->count = 1;
		new_root->data[0] = median;
		new_root->branch[0] = root;
		new_root->branch[1] = right_branch;
		root = new_root;
		result = success;
	}
	return result;
}



Error_code B_tree::push_down(B_node* current, const int& new_entry, int& median, B_node*& right_branch)
{
	Error_code result;
	int position;
	if (current == NULL)
	{
		//如果当前检索的节点为空，则返回overflow溢出标志
		median = new_entry;
		right_branch = NULL;
		result = overflow;
	}
	else
	{
		//搜索new_entry节点是否已经在current节点里面了，如果已经在树里，则返回duplicate_error，表明待插入的值已存在
		if (search_node(current, new_entry, position) == success)
			result = duplicate_error;
		//
		else
		{
			int extra_entry;
			B_node* extra_branch;
			//下面是递归的精华，push_down里调用push_down，递归出口是最后检索的节点是NULL，返回overflow，或者最后在某节点里发现了该数值，则不用插入了，返回duplicate_error
			result = push_down(
				current->branch[position],
				new_entry,
				extra_entry,
				extra_branch);
			//如果在最后一个压栈函数的返回值是overflow，代表最后走到了NULL
			//则它返回到的那个压栈函数（应该是倒数第二个压栈函数——NULL节点的上一个节点）里面的current就是新数值应该插入的节点
			if (result == overflow)
			{
				// 将新数值插入到应该插入到的节点里面
				if (current->count < order - 1)
					//应插入的节点中值的个数如果小于order-1，证明即使插入了这一个数值，也并不会分裂
				{
					result = success;//更改返回值为success，说明能成功插入
					push_in(current, extra_entry, extra_branch, position);//直接在该节点插入新值
				}
				else
					//current节点要分裂
					//由于节点要分裂的话，势必会在上一个压栈函数的current节点（也就是当前被分裂节点的上一个节点）插入一个值
					//所以给上一个压栈函数的返回值应该是overflow，代表返回的那个压栈函数中还应新插入一个值
					split_node(current, extra_entry, extra_branch, position, right_branch, median);
			}
		}
	}
	return result;
}


void B_tree::push_in(B_node* current, const int& entry, B_node* right_branch, int position)
//current是待插入的节点
//entry是被新插入的节点中的新值，用来更新节点
//right_branch是新插入的值下面的新子树
//position传参，传新插入的值在哪里
{
	for (int i = current->count; i > position; i--)
	{
		// Shift all later data to the right.给position腾地方
		current->data[i] = current->data[i - 1];
		current->branch[i + 1] = current->branch[i];
	}
	current->data[position] = entry;
	current->branch[position + 1] = right_branch;
	current->count++;
}



void B_tree::split_node(
	B_node* current, //待分裂的节点
	const int& extra_entry, // 新值
	B_node* extra_branch,
	// 新插入的值下面的新子树
	int position,// 待插入的新值的位置
	B_node*& right_half, // 分裂节点，将原节点的右半边的数值放进新定义的节点right_half里面
	int& median) // 节点中间值
{
	//将原节点的右半边的数值放进新定义的节点right_half里面
	right_half = new B_node;
	int mid = order / 2;

	// 暂时把中间节点留在左半边
	if (position <= mid)
		//如果待插入的节点在左半边，先把原节点（ 关键字的数目 = order-1 ）右半边的数字全部移到新节点中
	{
		for (int i = mid; i < order - 1; i++)
		{
			right_half->data[i - mid] = current->data[i];
			right_half->branch[i + 1 - mid] = current->branch[i + 1];
		}
		current->count = mid;
		right_half->count = order - 1 - mid;
		push_in(current, extra_entry, extra_branch, position);//再把新值插入到左半边
	}
	else
		//如果待插入的节点在右半边，先把原节点（ 关键字的数目 = order-1 ）右半边的数字（除去中间那个——为了给新节点腾地方）全部移到新节点中
	{
		mid++;
		for (int i = mid; i < order - 1; i++)
		{
			// Move entries to right_half .
			right_half->data[i - mid] = current->data[i];
			right_half->branch[i + 1 - mid] = current->branch[i + 1];
		}
		current->count = mid;//更新当前节点关键字有多少
		right_half->count = order - 1 - mid;
		push_in(right_half, extra_entry, extra_branch, position - mid);//再把新值插入到右半边
	}
	median = current->data[current->count - 1];
	// 把中间值从左节点删除（方法：把左节点原来的最后一个值转移到原来中间值在的地方进行覆盖）
	right_half->branch[0] = current->branch[current->count];
	current->count--;//更新关键字的数值
}



Error_code B_tree::remove(const int& target)
{
	Error_code result;
	result = recursive_remove(root, target);
	if (root != NULL && root->count == 0)
	{ // root is now empty.
		B_node* old_root = root;
		root = root->branch[0];
		delete old_root;
	}
	return result;
}






Error_code B_tree::recursive_remove(B_node* current, const int& target)
{
	Error_code result;
	int position;
	if (current == NULL)
		result = not_present;
	else
	{
		if (search_node(current, target, position) == success)
		{
			//待删除的值就在这个节点里面，position是它的位置索引
			result = success;
			if (current->branch[position] != NULL)
			{
				//不在叶节点里删除
				copy_in_predecessor(current, position);
				recursive_remove(current->branch[position], current->data[position]);
			}
			else
				//在叶节点里删除，直接删除即可
				remove_data(current, position);
		}
		else
			//要删除的值不在这个节点里，继续向下遍历
			result = recursive_remove(current->branch[position], target);

		if (current->branch[position] != NULL)
			if (current->branch[position]->count < (order - 1) / 2)//说明删除之后，节点的关键字数已经不满足要求了，所以需要合并
				restore(current, position);
	}
	return result;
}




void B_tree::remove_data(B_node* current, int position)
{
	for (int i = position; i < current->count - 1; i++)
		current->data[i] = current->data[i + 1];
	current->count--;
}



// 将该中间节点的左子树的最后一个节点（它的直接前驱）替代它
void B_tree::copy_in_predecessor(
	B_node* current,
	int position)
{
	B_node* leaf = current->branch[position];
	// First go left from the current entry.
	while (leaf->branch[leaf->count] != NULL)
		leaf = leaf->branch[leaf->count];
	// Move as far rightward as possible.
	current->data[position] = leaf->data[leaf->count - 1];
}




void B_tree::restore(B_node* current, int position)
{
	if (position == current->count) // case: rightmost branch
		if (current->branch[position - 1]->count > (order - 1) / 2)
			move_right(current, position - 1);
		else
			combine(current, position);
	else if (position == 0) // case: leftmost branch
		if (current->branch[1]->count > (order - 1) / 2)
			move_left(current, 1);
		else
			combine(current, 1);
	else // remaining cases: intermediate branches
		// 先看左兄弟的位子多不多，再看右
		if (current->branch[position - 1]->count > (order - 1) / 2)
			move_right(current, position - 1);
		else if (current->branch[position + 1]->count > (order - 1) / 2)
			move_left(current, position + 1);
		else combine(current, position);
}






void B_tree::move_left(B_node* current, int position)
{
	B_node* left_branch = current->branch[position - 1],
		* right_branch = current->branch[position];
	left_branch->data[left_branch->count] = current->data[position - 1];
	left_branch->branch[++left_branch->count] = right_branch->branch[0];
	current->data[position - 1] = right_branch->data[0];
	// Add the right-hand entry to the parent.
	right_branch->count--;
	for (int i = 0; i < right_branch->count; i++)
	{
		// Move right-hand entries to fill the hole.
		right_branch->data[i] = right_branch->data[i + 1];
		right_branch->branch[i] = right_branch->branch[i + 1];
	}
	right_branch->branch[right_branch->count] = right_branch->branch[right_branch->count + 1];
}




void B_tree::move_right(B_node* current, int position)
{
	B_node* right_branch = current->branch[position + 1],
		* left_branch = current->branch[position];
	right_branch->branch[right_branch->count + 1] = right_branch->branch[right_branch->count];
	for (int i = right_branch->count; i > 0; i--)
	{
		// Make room for new entry.
		right_branch->data[i] = right_branch->data[i - 1];
		right_branch->branch[i] = right_branch->branch[i - 1];
	}
	right_branch->count++;
	right_branch->data[0] = current->data[position];
	// Take entry from parent.
	right_branch->branch[0] = left_branch->branch[left_branch->count--];
	current->data[position] = left_branch->data[left_branch->count];
}



void B_tree::combine(B_node* current, int position)
{
	int i;
	B_node* left_branch = current->branch[position - 1],
		* right_branch = current->branch[position];
	left_branch->data[left_branch->count] = current->data[position - 1];
	left_branch->branch[++left_branch->count] = right_branch->branch[0];
	for (i = 0; i < right_branch->count; i++)
	{
		left_branch->data[left_branch->count] = right_branch->data[i];
		left_branch->branch[++left_branch->count] = right_branch->branch[i + 1];
	}
	current->count--;
	for (i = position - 1; i < current->count; i++)
	{
		current->data[i] = current->data[i + 1];
		current->branch[i + 1] = current->branch[i + 2];
	}
	delete right_branch;
}




int B_tree::getHeight()
{
	B_node* current = root;
	int sum = 0;

	while (current != NULL)
	{
		current = current->branch[0];
		sum++;
		cout << sum << "  ";
	}
	return sum;

}




//用于判断输入数据类型是否正确
bool is_int(char* p)
{
	int len = strlen(p);
	for (int i = 0; i < len; i++)
	{
		if (!('0' <= p[i] && p[i] <= '9'))
		{
			return false;
		}
	}
	return true;
}




void B_tree::show()
{
	
	//int wid = 20, leng = 10, marg = 30;
	int wid = 25, leng = 15, marg = 35;
	cleardevice(); //每次操作前先清屏
	if (root == NULL)
		return;
	queue<B_node*> qBn;
	queue<int> qLeft, qTop;
	qBn.push(root);
	qBn.push(nullptr);
	qLeft.push(0);
	qTop.push(0);
	qLeft.push(-1);
	qTop.push(-1);
	int rowLeft = 0;
	while (qBn.size() > 1)
	{
		B_node* current = qBn.front();
		int left, top;
		left = qLeft.front();
		top = qTop.front();
		qBn.pop();
		qLeft.pop();
		qTop.pop();
		if (current == nullptr)
		{
			qBn.push(nullptr);
			qLeft.push(-1);
			qTop.push(-1);
			rowLeft = 0;
			continue;
		}
		int totalleng = 0;
		int preCharRihgt = left;
		for (int i = 0; i < current->count; i++)
		{ //显示当前节点的数据
			wchar_t s[100];
			swprintf_s(s, _T("%d"), current->data[i]);
			int size = 0;
			while (s[size++] != 0);
			size--;
			rectangle(preCharRihgt, top, preCharRihgt + size * leng, top + wid);
			//画一个矩形显示数据
			outtextxy(preCharRihgt + 2, top + 2, s);
			//显示数据
			totalleng += size * leng;
			if (current->branch[i] != nullptr)
			{ //访问当前节点的孩子节点
				qBn.push(current->branch[i]); //把孩子节点放入队列
				qLeft.push(rowLeft);
				qTop.push(top + wid + marg);
				POINT pts[] = { {preCharRihgt, top + wid}, {rowLeft, top + wid + marg} };//两个点的坐标
				polyline(pts, 2); //画连线
				rowLeft += current->branch[i]->count * 20 + marg;
			}
			preCharRihgt = preCharRihgt + size * leng;
		}
		if (current->branch[current->count] != nullptr)
		{
			qBn.push(current->branch[current->count]);
			qLeft.push(rowLeft);
			qTop.push(top + wid + marg);
			POINT pts[] = { {preCharRihgt, top + wid}, {rowLeft, top + wid + marg} };
			polyline(pts, 2);
			rowLeft += current->branch[current->count]->count * 20 + marg;
		}
	}
}














int main()
{
	
	int n, m;//n是关键字个数，m是B树的阶数
	cout << "请输入关键字个数和B树的阶数，并用一个空格隔开：（例如：10 3）" << endl;
	cin >> n >> m;
	order = m;

	//分割输入的字符串，并将其转化为int类型，使其进入到int型arr数组里
	char* strbuf;
	char strdelimit[] = ",";//分割符
	char* p;
	int* arr = new int[n + 10];
	int j = 0;

	while (true)
	{
		int judge = 1;
		cout << "请输入所有关键字，并以逗号分隔：（例如 10,3,12,4,5）" << endl;
		char* str = new char[n * 30];
		cin >> str;
		j = 0;

		p = strtok_s(str, strdelimit, &strbuf);
		if (is_int(p))
			arr[j++] = atoi(p);
		else
		{
			cout << "输入数据类型不正确,请重新输入！" << endl;
			judge = 0;
			continue;
		}

		while ((p = strtok_s(NULL, strdelimit, &strbuf)) != NULL)
		{
			if (is_int(p))
				arr[j++] = atoi(p);
			else
			{
				cout << "输入数据类型不正确，请重新输入！" << endl;
				judge = 0;
				break;
			}
		}
		if (!(judge == 0))
			break;
	}



	//建树过程
	int min = j;
	if (j > n) min = n;
	B_tree bt;
	for (int i = 0; i < min; i++)
	{
		bt.insert(arr[i]);
	}
	//bt.printpoint();


	//插入、删除过程
	while (true)
	{
		cout << endl;
		cout << "请输入需要执行的指令,插入用“I 数字”，删除用“D 数字”，连续插入用“MI 数字1,数字2,……#”，连续删除用“MD 数字1,数字2,……#”" << endl;
		cout << "（例如【I 76】  【D 56】  【MI 76, 23, 51#】  【MD 50, 4, 14#】）" << endl;
		cout << "（若想退出操作，请输入0）" << endl;
		cout << endl;
		char* str = new char[n * 30];
		cin.getline(str, n * 30);
		int k;
		switch (str[0])
		{
		case 'I':
			str = &str[2];
			k = atoi(str);
			if (bt.insert(k) == duplicate_error)
			{
				cout << "有重复的关键字" << endl;
			}
			break;

		case 'D':
			str = &str[2];
			k = atoi(str);
			if (bt.remove(k) == not_present)
			{
				cout << "未找到相应的关键字" << endl;
			}
			break;

		case 'M':
			if (str[1] == 'I')
				//多项插入
			{
				//提取输入的字符串，并分割该字符串，进入到int数组中
				str = &str[3];
				char* strbuf;
				char strdelimit[] = ",#";//分割符
				char* p;
				int j = 0;
				int* arr = new int[n + 10];

				arr[j++] = atoi(strtok_s(str, strdelimit, &strbuf));
				while ((p = strtok_s(NULL, strdelimit, &strbuf)) != NULL)
				{
					arr[j++] = atoi(p);
				}

				//将数组中的元素插入到B树里
				for (int i = 0; i < j; i++)
				{
					if (bt.insert(arr[i]) == duplicate_error)
					{
						cout << "有重复的关键字：" << arr[i] << endl;
					}
				}
			}

			if (str[1] == 'D')
				//多项删除
			{
				//提取输入的字符串，并分割该字符串，进入到int数组中
				str = &str[3];
				char* strbuf;
				char strdelimit[] = ",#";//分割符
				char* p;
				int j = 0;
				int* arr = new int[n + 10];

				arr[j++] = atoi(strtok_s(str, strdelimit, &strbuf));
				while ((p = strtok_s(NULL, strdelimit, &strbuf)) != NULL)
				{
					arr[j++] = atoi(p);
				}

				//将数组中的元素插入到B树里
				for (int i = 0; i < j; i++)
				{
					if (bt.remove(arr[i]) == not_present)
					{
						cout << "未找到相应的关键字：" << arr[i] << endl;
					}
				}
			}
			break;


		case '0':
			return 0;
		}

		//显示树形
		//bt.printpoint();
		
		initgraph(640, 480, SHOWCONSOLE);
		bt.show();


	}

}


