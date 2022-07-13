//此文件用于实现节点类、链表类、箱子排序
#pragma once
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

//节点类
class ChainNode
{
	friend class Chain;
	string word;
	int wnum;
	ChainNode* link;
public:
	ChainNode() 
	{
		word = " ";
		wnum = 0;
		link = 0;
	};
	ChainNode(string x)
	{
		word = x;
		wnum = 1;
		link = 0;
	}
};


//链表类
class Chain
{
	ChainNode * first;
	int size;
	int tempsize;//链表排序用的
public:
	Chain();
	~Chain();
	void Insert(string);
	void Show();
	void BinSort(int);
	void InsertByNum(ChainNode* x);
	void mySort();
	ChainNode* returnFirst() { return first; }

};

Chain::Chain()
{
	first = new ChainNode;
	first->word = " ";
	first->link = first;
	size = 0;
}

Chain::~Chain()
{
	ChainNode* current = first->link;
	while (current != first)
	{
		current = first->link;
		delete first;
		first = current;
	}
	size = 0;
}


void Chain::Insert(string x)
{
	if (size==0)
	{
		ChainNode* newnode = new ChainNode(x);
		newnode->link = first;
		first->link = newnode;
		size ++;
		return;
	}

	ChainNode* current = first;

	for (int pos=0; pos < size ; pos++)
	{
		if (x < current->link->word)
			break;
		if (current->link->word == x)
		{
			current->link->wnum++;
			return;
		}
		current = current->link;
	}

	ChainNode* newnode = new ChainNode(x);
	newnode->link = current->link;
	current->link = newnode;
	size++;
	return;
	
}

void Chain::Show()
{
	ChainNode* temp = first->link;
	for (int i = 0; i < size; i++)
	{
		cout << setiosflags(ios::left);
		cout << setw(20)<<temp->word << temp->wnum << endl;
		temp = temp->link;
	}

}

void Chain::BinSort(int range)
{
	//构建箱子链表
	ChainNode** bottom, ** top;
	bottom = new ChainNode * [range + 1];//箱子链表首
	top = new ChainNode * [range + 1];//箱子链表尾

	//将原链表中的节点放入箱子链表
	int b;
	for (b = 0; b <= range; b++)
	{
		bottom[b] = 0;//先将每个箱子置空
	}
	ChainNode* current = first->link;
	for (; current; current = current->link)
	{
		b = current->wnum;
		if (bottom[b])
		{
			top[b]->link = current;
			top[b] = current;
		}
		else
		{
			bottom[b] = top[b] = current;
		}
	}

	//把箱子链表中的节点再放回原链表实现排序
	ChainNode* y = 0;
	for (b = 0; b <= range; b++)
	{
		if (bottom[b])//如果箱子不空
		{
			//先处理头
			if (y)//不是第一个非空的箱子，直接下一个的头连上一个的尾即可
			{
				y->link = bottom[b];
			}
			else//是第一个非空的箱子，要将其头部和first联系起来
			{
				first->link = bottom[b];
			}
			//再处理尾
			y = top[b];
		}
	}

	if (y)
		y->link = first;//将带有头节点的单向链表转回去形成循环

	delete[]bottom;
	delete[]top;

}

void Chain::mySort()
{
	tempsize = 0;
	ChainNode* tem = first->link;
	first->link = first;
	ChainNode* t;
	for (int i = 0; i < size; i++)
	{
		t = tem;
		InsertByNum(tem);
		tem = tem->link;
		delete t;



	}
}



void Chain::InsertByNum(ChainNode* x)
{

	if (first->link == first)
	{
		ChainNode* newnode = new ChainNode;
		newnode->word = x->word;
		newnode->wnum = x->wnum;
		newnode->link = first;
		first->link = newnode;
		tempsize++;
		return;
	}

	ChainNode* current = first;

	for (int pos = 0; pos < tempsize; pos++)
	{
		if (x->wnum >= current->link->wnum)
			break;
		current = current->link;
	}

	ChainNode* newnode = new ChainNode;
	newnode->wnum = x->wnum;
	newnode->word = x->word;
	newnode->link = current->link;
	current->link = newnode;
	tempsize++;
	return;


}