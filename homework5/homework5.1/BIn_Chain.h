//���ļ�����ʵ�ֽڵ��ࡢ�����ࡢ��������
#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

//�ڵ���
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


//������
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
	//������������
	ChainNode** bottom, ** top;
	bottom = new ChainNode * [range + 1];//����������
	top = new ChainNode * [range + 1];//��������β

	//��ԭ�����еĽڵ������������
	int b;
	for (b = 0; b <= range; b++)
	{
		bottom[b] = 0;//�Ƚ�ÿ�������ÿ�
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

	//�����������еĽڵ��ٷŻ�ԭ����ʵ������
	ChainNode* y = 0;
	for (b = 0; b <= range; b++)
	{
		if (bottom[b])//������Ӳ���
		{
			//�ȴ���ͷ
			if (y)//���ǵ�һ���ǿյ����ӣ�ֱ����һ����ͷ����һ����β����
			{
				y->link = bottom[b];
			}
			else//�ǵ�һ���ǿյ����ӣ�Ҫ����ͷ����first��ϵ����
			{
				first->link = bottom[b];
			}
			//�ٴ���β
			y = top[b];
		}
	}

	if (y)
		y->link = first;//������ͷ�ڵ�ĵ�������ת��ȥ�γ�ѭ��

	delete[]bottom;
	delete[]top;

}