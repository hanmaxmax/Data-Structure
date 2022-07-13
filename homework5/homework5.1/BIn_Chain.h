//此文件用于实现节点类、链表类、箱子排序
#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

//节点类
template<class T>
class ChainNode
{
	friend class Chain;
	T data;
	ChainNode* link;
public:
	ChainNode()
	{
		data = 0;
		link = 0;
	};
	ChainNode(T x)
	{
		data = x;
	}
};


//链表类
template<class T>
class Chain
{
	ChainNode<T>* first;
	int size;
public:
	Chain();
	~Chain();
	void Insert(T);
	void Show();
	void BinSort(int);
	ChainNode* returnFirst() { return first; }

};

template<class T>
Chain<T>::Chain()
{
	first = new ChainNode(0);
	size = 0;
}

template<class T>
Chain<T>::~Chain()
{
	ChainNode<T>* current = first->link;
	while (current != first)
	{
		current = first->link;
		delete first;
		first = current;
	}
	size = 0;
}

template<class T>
void Chain<T>::Insert(T x)
{
	if (size == 0)
	{
		ChainNode* newnode = new ChainNode(x);
		newnode->link = first;
		first->link = newnode;
		size++;
		return;
	}

	ChainNode* current = first;

	for (int pos = 0; pos < size; pos++)
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

template<class T>
void Chain<T>::Show()
{
	ChainNode* temp = first->link;
	for (int i = 0; i < size; i++)
	{
		cout << setiosflags(ios::left);
		cout << setw(20) << temp->data << endl;
		temp = temp->link;
	}

}

template<class T>
void Chain<T>::BinSort(int range)
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
		b = current->data;
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