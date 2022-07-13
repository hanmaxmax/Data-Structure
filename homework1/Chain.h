//���ļ�����ʵ�ֽڵ��ࡢ�����ࡢ��������
#pragma once
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

//�ڵ���
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


//������
class Chain
{
	ChainNode * first;
	int size;
	int tempsize;//���������õ�
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