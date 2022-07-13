#pragma once
class treeNode
{
public:
	int weight;
	char word;
	int parent,lchild,rchild;
	treeNode()
	{
		weight = 0;
		parent = -1;
		lchild = -1;
		rchild = -1;
	}

};
