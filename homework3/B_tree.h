//#include <iostream>
//using namespace std;
//
//enum Error_code
//{
//	not_present, success, overflow, duplicate_error
//};
// int order;
//
//
////Record是B树存的数据类型，order是B树的阶数
//template <class Record>
//class B_node 
//{
//public:
//	int count;//节点关键字个数
//	Record* data;//本节点关键字数组
//	B_node <Record>** branch;//子树指针数组,例如branch[0]指向第一棵子树（即所有keys小于data[0]的子树）
//
//	//构造函数
//	B_node();
//};
//
//template <class Record>
//B_node<Record>::B_node()
//{
//	data = new Record[order - 1];
//	branch = new B_node <Record>*[order];
//	count = 0;
//	for (int i = 0; i < order; i++)//子树指针数组初始化
//    {
//        branch[i] = NULL;
//    }
//    for (int i = 0; i < order-1; i++)//关键字数组初始化
//    {
//        data[i] = '\0';
//    }
//
//}
//
//template <class Record>
//class B_tree 
//{
//public: 
//	Error_code recursive_search_tree(B_node<Record>* current, Record& target);
//	Error_code search_node(B_node<Record>* current, const Record& target, int& position);
//	Error_code insert(const Record& new_entry);
//	Error_code push_down(B_node<Record>* current, const Record& new_entry, Record& median, B_node<Record>*& right_branch);
//	void push_in(B_node<Record>* current, const Record& entry, B_node<Record>* right_branch, int position);
//	void split_node( B_node<Record>* current, const Record& extra_entry, B_node<Record>* extra_branch,int position,B_node<Record>*& right_half, Record& median); 
//	Error_code remove(const Record& target);
//	Error_code recursive_remove(B_node<Record>* current, const Record& target);
//	void remove_data(B_node<Record>* current, int position);
//	void copy_in_predecessor(B_node<Record>* current, int position);
//	void restore(B_node<Record>* current, int position);
//	void move_left(B_node<Record>* current, int position);
//	void move_right(B_node<Record>* current, int position);
//	void combine(B_node<Record>* current, int position);
//	void printpoint(B_node<Record>* node,int count);
//	void printpoint();
//	void printpoint2();
//	int getHeight();
//
//
//	B_tree()
//	{
//		root = NULL;
//	}
//
//	B_node<Record>* root;
//};
//
//
//template <class Record>
//void B_tree<Record> ::printpoint(B_node<Record>* node, int count)
//{
//
//	if (node != NULL)//判断元素是否为空
//	{
//		int i, j;
//		//每个节点从小到大打印
//		for (i = 0; i < node->count; i++)
//		{	
//			//判断是否叶节点,不是的话则要往子节点中寻找打印
//			if (node->branch[0]!=NULL)//判断是否是叶子节点
//			{
//				printpoint(node->branch[i], count - 3);
//			}
//			for (j = count; j >= 0; j--)
//			{
//				cout << "-";
//			}
//			cout << "|" << node->data[i] << "|" << endl;
//		}
//		if (node->branch[0] != NULL)//子节点数比关键字数多一个
//		{
//			printpoint(node->branch[i], count - 3);
//		}
//	}
//}
//
//
//template <class Record>
//void B_tree<Record> ::printpoint()
//{
//	printpoint(root, order * 5);
//}
//
//
//
//
//
//
//template <class Record>
//Error_code B_tree<Record> ::recursive_search_tree(B_node<Record>* current, Record& target)
////current——用来递归，可以是空指针或者指向B树的某棵子树/节点
////target——需要查找的值
////返回值——用来存找没找到
////最终结果——找到了，则current存target所在节点，position存target值在节点中的位置
//{
//	Error_code result = not_present;//result初始化为找不到，找到了再更改
//	int position;
//	if (current != NULL)
//	{
//		result = search_node(current, target, position);
//		if (result == not_present)
//			result = recursive_search_tree(current->branch[position], target);
//		else
//			target = current->data[position];
//	}
//	return result;
//}
//
////搜索当前节点，看这个节点里有没有target
//template <class Record>
//Error_code B_tree<Record> ::search_node(B_node<Record>* current, const Record& target, int& position)
////position是用来返回传参的
////如果找到了，position就向recursive_search_tree函数返回target的位置；并返回sucess的标识
////如果没找到，position就向recursive_search_tree函数返回小于target的位置；并返回not_present的标识
//{
//	position = 0;
//	while (position < current->count && target > current->data[position])
//		position++; //先把position箭头指向target的位置 或 可以索引到target的位置
//	if (position < current->count && target == current->data[position])
//		return success;
//	else
//		return not_present;//表明此节点里没有target（但position已指到相应的位置了）
//}
//
////将new_entry插入树里
////有两种返回值
////success：插入成功
////duplicate_error：原数据已存在，插入失败
//template <class Record>
//Error_code B_tree<Record> ::insert(const Record& new_entry)
//{
//	Record median;
//	B_node<Record>* right_branch,* new_root;
//	Error_code result = push_down(root, new_entry, median, right_branch);
//	if (result == overflow) 
//		//如果最后返回到第一个压栈函数（也就是根节点压的栈）时，仍然是overflow，说明根节点也要进行插值分裂
//	{
//		new_root = new B_node<Record>;
//		new_root->count = 1;
//		new_root->data[0] = median;
//		new_root->branch[0] = root;
//		new_root->branch[1] = right_branch;
//		root = new_root;
//		result = success;
//	}
//	return result;
//}
//
//
//template <class Record>
//Error_code B_tree<Record> ::push_down(B_node<Record>* current,const Record& new_entry,Record& median,B_node<Record>*& right_branch)
//{
//	Error_code result;
//	int position;
//	if (current == NULL) 
//	{
//		//如果当前检索的节点为空，则返回overflow溢出标志
//		median = new_entry;
//		right_branch = NULL;
//		result = overflow;
//	}
//	else 
//	{
//		//搜索new_entry节点是否已经在current节点里面了，如果已经在树里，则返回duplicate_error，表明待插入的值已存在
//		if ( search_node(current, new_entry, position) == success )
//			result = duplicate_error;
//		//
//		else 
//		{
//			Record extra_entry;
//			B_node<Record>* extra_branch;
//			//下面是递归的精华，push_down里调用push_down，递归出口是最后检索的节点是NULL，返回overflow，或者最后在某节点里发现了该数值，则不用插入了，返回duplicate_error
//			result = push_down(
//				current->branch[position],
//				new_entry,
//				extra_entry,
//				extra_branch);
//			//如果在最后一个压栈函数的返回值是overflow，代表最后走到了NULL
//			//则它返回到的那个压栈函数（应该是倒数第二个压栈函数——NULL节点的上一个节点）里面的current就是新数值应该插入的节点
//			if (result == overflow) 
//			{
//				// 将新数值插入到应该插入到的节点里面
//				if (current->count < order - 1) 
//					//应插入的节点中值的个数如果小于order-1，证明即使插入了这一个数值，也并不会分裂
//				{
//					result = success;//更改返回值为success，说明能成功插入
//					push_in(current, extra_entry,extra_branch, position);//直接在该节点插入新值
//				}
//				else 
//					//current节点要分裂
//					//由于节点要分裂的话，势必会在上一个压栈函数的current节点（也就是当前被分裂节点的上一个节点）插入一个值
//					//所以给上一个压栈函数的返回值应该是overflow，代表返回的那个压栈函数中还应新插入一个值
//					split_node(current, extra_entry,extra_branch, position,right_branch, median);
//			}
//		}
//	}
//	return result;
//}
//
//template <class Record>
//void B_tree<Record> ::push_in(B_node<Record>* current,const Record& entry,B_node<Record>* right_branch,int position)
////current是待插入的节点
////entry是被新插入的节点中的新值，用来更新节点
////right_branch是新插入的值下面的新子树
////position传参，传新插入的值在哪里
//{
//	for (int i = current->count; i > position; i--) 
//	{
//		// Shift all later data to the right.给position腾地方
//		current->data[i] = current->data[i - 1];
//		current->branch[i + 1] = current->branch[i];
//	}
//	current->data[position] = entry;
//	current->branch[position + 1] = right_branch;
//	current->count++;
//}
//
//
//template <class Record>
//void B_tree<Record> ::split_node(
//	B_node<Record>* current, //待分裂的节点
//	const Record& extra_entry, // 新值
//	B_node<Record>* extra_branch,
//	// 新插入的值下面的新子树
//	int position,// 待插入的新值的位置
//	B_node<Record>*& right_half, // 分裂节点，将原节点的右半边的数值放进新定义的节点right_half里面
//	Record& median) // 节点中间值
//{
//	//将原节点的右半边的数值放进新定义的节点right_half里面
//	right_half = new B_node<Record>;
//	int mid = order / 2; 
//	
//	// 暂时把中间节点留在左半边
//	if (position <= mid) 
//		//如果待插入的节点在左半边，先把原节点（ 关键字的数目 = order-1 ）右半边的数字全部移到新节点中
//	{ 
//		for (int i = mid; i < order - 1; i++) 
//		{ 
//			right_half->data[i - mid] = current->data[i];
//			right_half->branch[i + 1 - mid] = current->branch[i + 1];
//		}
//		current->count = mid;
//		right_half->count = order - 1 - mid;
//		push_in(current, extra_entry,extra_branch, position);//再把新值插入到左半边
//	}
//	else 
//		//如果待插入的节点在右半边，先把原节点（ 关键字的数目 = order-1 ）右半边的数字（除去中间那个——为了给新节点腾地方）全部移到新节点中
//	{ 
//		mid++; 
//		for (int i = mid; i < order - 1; i++) 
//		{
//			// Move entries to right_half .
//			right_half->data[i - mid] = current->data[i];
//			right_half->branch[i + 1 - mid] = current->branch[i + 1];
//		}
//		current->count = mid;//更新当前节点关键字有多少
//		right_half->count = order - 1 - mid;
//		push_in(right_half, extra_entry, extra_branch, position - mid);//再把新值插入到右半边
//	}
//	median = current->data[current->count - 1];
//	// 把中间值从左节点删除（方法：把左节点原来的最后一个值转移到原来中间值在的地方进行覆盖）
//	right_half->branch[0] = current->branch[current -> count];
//	current->count --;//更新关键字的数值
//}
//
//
//template <class Record>
//Error_code B_tree<Record> :: remove(const Record& target)
//{
//	Error_code result;
//	result = recursive_remove(root, target);
//	if (root != NULL && root->count == 0)
//	{ // root is now empty.
//		B_node<Record>* old_root = root;
//		root = root->branch[0];
//		delete old_root;
//	}
//	return result;
//}
//
//
//
//
//
//template <class Record>
//Error_code B_tree<Record> ::recursive_remove(B_node<Record>* current, const Record& target)
//{
//	Error_code result;
//	int position;
//	if (current == NULL) 
//		result = not_present;
//	else 
//	{
//		if (search_node(current, target, position)== success) 
//		{
//			//待删除的值就在这个节点里面，position是它的位置索引
//			result = success;
//			if (current->branch[position] != NULL) 
//			{
//				//不在叶节点里删除
//				copy_in_predecessor(current, position);
//				recursive_remove(current -> branch[position], current->data[position]);
//			}
//			else 
//				//在叶节点里删除，直接删除即可
//				remove_data(current, position);
//		}
//		else 
//			//要删除的值不在这个节点里，继续向下遍历
//			result = recursive_remove(current -> branch[position], target);
//
//		if (current->branch[position] != NULL)
//			if (current->branch[position]->count < (order - 1) / 2)//说明删除之后，节点的关键字数已经不满足要求了，所以需要合并
//				restore(current, position);
//	}
//	return result;
//}
//
//
//
//template <class Record>
//void B_tree<Record> :: remove_data(B_node<Record>* current, int position)
//{
//	for (int i = position; i < current->count - 1; i++)
//		current->data[i] = current->data[i + 1];
//	current->count--;
//}
//
//
//
//template <class Record>
//void B_tree < Record> ::copy_in_predecessor(
//	B_node<Record>* current,
//	int position)
//{
//	B_node<Record> * leaf = current->branch[position];
//	// First go left from the current entry.
//	while (leaf->branch[leaf->count] != NULL)
//		leaf = leaf->branch[leaf->count];
//	// Move as far rightward as possible.
//	current->data[position] = leaf->data[leaf->count - 1];
//}
//
//
//
//template <class Record>
//void B_tree<Record> ::restore(B_node<Record>* current, int position)
//{
//	if (position == current->count) // case: rightmost branch
//		if (current->branch[position - 1]->count > (order - 1) / 2)
//			move_right(current, position - 1);
//		else
//			combine(current, position);
//	else if (position == 0) // case: leftmost branch
//		if (current->branch[1]->count > (order - 1) / 2)
//			move_left(current, 1);
//		else
//			combine(current, 1);
//	else // remaining cases: intermediate branches
//		if (current->branch[position - 1] -> count > (order - 1) / 2)
//			move_right(current, position - 1);
//		else if (current->branch[position + 1] ->count > (order - 1) / 2)
//			move_left(current, position + 1);
//		else combine(current, position);
//}
//
//
//
//
//
//template <class Record>
//void B_tree<Record> :: move_left(B_node<Record>* current,int position)
//{
//	B_node<Record>* left_branch = current->branch[position - 1],
//						 * right_branch = current->branch[position];
//	left_branch->data[left_branch->count] =	current->data[position - 1]; 
//	left_branch->branch[++left_branch->count] = right_branch->branch[0];
//	current->data[position - 1] = right_branch -> data[0];
//	// Add the right-hand entry to the parent.
//	right_branch->count--;
//	for (int i = 0; i < right_branch->count; i++) 
//	{
//		// Move right-hand entries to fill the hole.
//		right_branch->data[i] = right_branch->data[i + 1];
//		right_branch->branch[i] = right_branch->branch[i + 1];
//	}
//	right_branch->branch[right_branch->count] = right_branch->branch[right_branch->count + 1];
//}
//
//
//
//
//template <class Record>
//void B_tree<Record> :: move_right(B_node<Record> * current, int position)
//{
//	B_node<Record>* right_branch = current->branch[position + 1],
//						 * left_branch = current->branch[position];
//	right_branch->branch[right_branch->count + 1] = right_branch->branch[right_branch->count];
//	for (int i = right_branch->count; i > 0; i--) 
//	{
//		// Make room for new entry.
//		right_branch->data[i] = right_branch->data[i - 1];
//		right_branch->branch[i] = right_branch->branch[i - 1];
//	}
//	right_branch->count++;
//	right_branch->data[0] = current->data[position];
//	// Take entry from parent.
//	right_branch->branch[0] = left_branch->branch[left_branch->count--];
//	current->data[position] = left_branch->data[left_branch->count];
//}
//
//
//
//
//template <class Record>
//void B_tree<Record> :: combine(B_node<Record>* current, int position)
//{
//	int i;
//	B_node<Record>* left_branch = current->branch[position - 1],
//						 * right_branch = current->branch[position];
//	left_branch->data[left_branch->count] = current->data[position - 1];
//	left_branch->branch[++left_branch->count] = right_branch->branch[0];
//	for (i = 0; i < right_branch->count; i++) 
//	{
//		left_branch->data[left_branch->count] = right_branch->data[i];
//		left_branch->branch[++left_branch->count] = right_branch->branch[i + 1];
//	}
//	current->count--;
//	for (i = position - 1; i < current->count; i++) 
//	{
//		current->data[i] = current->data[i + 1];
//		current->branch[i + 1] = current->branch[i + 2];
//	}
//	delete right_branch;
//}
//
//
//
//
//
//template <class Record>
//int B_tree<Record> ::getHeight()
//{
//	B_node<Record>* current = root;
//	int sum = 0;
//	
//	while (current != NULL)
//	{
//		current = current->branch[0];
//		sum++;
//		cout << sum<<"  ";
//	}
//	return sum;
//
//}
//
//
//
//
//
//
//
////#include <iostream>
////using namespace std;
////static const int m = 3;  //定义最小度为3
////static const int key_max = 2 * m - 1;//关键字最大个数
////static const int key_min = m - 1;//关键字最小个数
////static const int child_max = key_max + 1;//子节点最大个数(这里可以看出子节点数与关键字数有关)
////static const int child_min = key_min + 1;//子节点最小个数
////
////template <class T>
////class BTree;//前置声明
/////*
////类名:BTnode
////*/
////template <class T>
////class BTnode
////{
////    friend class BTree<T>;//友元函数
////public:
////    BTnode()
////    {
////        keyNum = 0;
////        parent = NULL;//父节点初始化
////        isleaf = true;
////        int i;
////        for (i = 0; i < child_max; i++)//子树指针数组初始化
////        {
////            pchild[i] = NULL;
////        }
////        for (i = 0; i < key_max; i++)//关键字数组初始化
////        {
////            keyvalue[i] = '\0';
////        }
////    }
////private:
////    bool isleaf;//判断节点是否是叶子节点
////    int keyNum;//关键字个数
////    BTnode<T>* parent;//指向父节点
////    BTnode<T>* pchild[child_max];//子树指针数组
////    T   keyvalue[key_max];//关键字数组
////};
////
/////*
////类名:BTree
////*/
////template <class T>
////class BTree
////{
////public:
////    /*
////   函数名:BTree
////   函数作用:无参构造函数
////   函数参数:无
////   函数返回值: 无
////   */
////
////    BTree()
////    {
////        root = NULL;
////    }
////    /*
////   函数名:BTree_insert
////   函数作用:插入关键字
////   函数参数:T value
////   函数返回值: bool类型判断插入是否成功
////   */
////
////    bool BTree_insert(T value)
////    {
////        if (contain(value))//看树中是否有相同的关键字
////        {
////            return false;
////        }
////        else
////        {
////            if (root == NULL)
////            {
////                root = new BTnode<T>();
////            }
////            if (root->keyNum == key_max)
////            {
////                BTnode<T>* newnode = new BTnode<T>();
////                newnode->pchild[0] = root;
////                newnode->isleaf = false;//由上步操作可知newnode已经有子节点
////                SplitBlock(newnode, 0, root);//分块操作
////                root = newnode;//更新根节点
////            }
////            Notfull_insert(root, value);//插入块未满的操作
////            return true;
////        }
////    }
////
////    /*
////     函数名:SplitBlock
////     函数作用:把节点分裂
////     函数参数:BTnode<T>* node_parent,int child_index,BTnode<T>* node_child
////     函数返回值: 无
////     */
////
////    void SplitBlock(BTnode<T>* node_parent, int child_index, BTnode<T>* node_child)
////    {
////        BTnode<T>* node_right = new BTnode<T>();
////        node_right->isleaf = node_child->isleaf;
////        node_right->keyNum = key_min;
////        int i;
////        //node_right拷贝关键字
////        for (i = 0; i < key_min; i++)
////        {
////            node_right->keyvalue[i] = node_child->keyvalue[i + child_min];
////        }
////        //判断分裂的节点是否是叶子节点,如果不是的话就要把它的孩子赋值过去
////        if (!node_child->isleaf)
////        {
////            for (i = 0; i < child_min; i++)
////            {
////                node_right->pchild[i] = node_child->pchild[i + child_min];
////                node_child->pchild[i + child_min]->parent = node_right->pchild[i];
////            }
////        }
////        node_child->keyNum = key_min;//更新子节点的关键字数
////        //把父节点关键字和子指针往后移 倒序赋值
////        for (i = node_parent->keyNum; i > child_index; i--)
////        {
////            node_parent->keyvalue[i] = node_parent->keyvalue[i - 1];
////            node_parent->pchild[i + 1] = node_parent->pchild[i];
////            node_child->pchild[i]->parent = node_parent->pchild[i + 1];
////        }
////        node_parent->keyNum++;//更新父节点关键字数
////        node_parent->pchild[child_index + 1] = node_right;
////        node_right->parent = node_parent->pchild[child_index + 1];
////        //把中间的那个关键字上移到父节点
////        node_parent->keyvalue[child_index] = node_child->keyvalue[key_min];
////    }
////
////
////    /*
////    函数名:Notfull_insert
////    函数作用:往没有满的节点中增加关键字
////    函数参数:BTnode<T>* node,T value
////    函数返回值:无
////    */
////    void Notfull_insert(BTnode<T>* node, T value)
////    {
////
////        int node_keynum = node->keyNum;//获取节点关键字数
////        if (node->isleaf)//node是叶子节点
////        {
////            while (node_keynum > 0 && value < node->keyvalue[node_keynum - 1])
////            {
////                node->keyvalue[node_keynum] = node->keyvalue[node_keynum - 1];//把关键字往后移动
////                --node_keynum;
////            }
////            node->keyvalue[node_keynum] = value;
////            node->keyNum++;
////        }
////        else//node是内部节点
////        {
////            while (node_keynum > 0 && value < node->keyvalue[node_keynum - 1])
////            {
////                --node_keynum;
////            }
////            //在比它小和比它大中间那个子节点中找合适位置,
////            //如果它比所有的都小则在第一个子节点中寻找
////            BTnode<T>* node_child = node->pchild[node_keynum];
////            if (node_child->keyNum == key_max)
////            {
////                SplitBlock(node, node_keynum, node_child);
////                if (value > node->keyvalue[node_keynum])//插入值和子节点中间的值比较
////                {
////                    node_child = node->pchild[node_keynum + 1];
////                }
////            }
////            Notfull_insert(node_child, value);//继续往下寻找合适的位置
////        }
////    }
////
////    /*
////    函数名:contain
////    函数作用:查找是否有相同元素在数中
////    函数参数:T value
////    函数返回值:bool类型
////    */
////    bool contain(T value)
////    {
////        if (BTree_find(root, value) != NULL)
////            return true;
////        return false;
////    }
////
////    /*
////    函数名:BTree_find
////    函数作用:查找是否有相同元素在数中
////    函数参数:BTnode<T>* node,T value
////    函数返回值: BTnode<T>*
////    */
////    BTnode<T>* BTree_find(BTnode<T>* node, T value)
////    {
////        if (node == NULL)//当前节点为空的时候
////        {
////            return NULL;
////        }
////        else//当前节点不为空
////        {
////            int i;
////            //在比它小和比它大的中间子节点中寻找相等的
////            for (i = 0; i < node->keyNum; i++)
////            {
////                if (value <= node->keyvalue[i])
////                {
////                    break;
////                }
////            }
////
////            //校验当前的关键字是否等于查找的关键字
////            if (i < node->keyNum && value == node->keyvalue[i])//i是下标最大值keyNum-1
////            {
////                return node;
////            }
////            else
////            {
////                //如果之前比查找关键没有相等的关键字并且当前节点是叶子节点的话
////                //那么在B树中没有一样的关键字(因为后面比关键字更大)
////                if (node->isleaf)
////                {
////                    return NULL;
////                }
////                else//如果不是叶子节点则在下面的子节点中寻找
////                {
////                    return BTree_find(node->pchild[i], value);//这里的return别忘了
////                }
////            }
////        }
////    }
////
////    /*
////    函数名:printpoint
////    函数作用:打印元素
////    函数参数:BTnode<T>* node,int count
////    函数返回值:无
////    */
////    void printpoint(BTnode<T>* node, int count)
////    {
////        if (node != NULL)//判断元素是否为空
////        {
////            int i, j;
////            //每个节点从小到大打印
////            for (i = 0; i < node->keyNum; i++)
////            {
////                //判断是否叶节点,不是的话则要往子节点中寻找打印
////                if (!node->isleaf)//判断是否是叶子节点
////                {
////                    printpoint(node->pchild[i], count - 3);
////                }
////                for (j = count; j >= 0; j--)
////                {
////                    cout << "-";
////                }
////                cout << "|" << node->keyvalue[i] << "|" << endl;
////            }
////            if (!node->isleaf)//子节点数比关键字数多一个
////            {
////                printpoint(node->pchild[i], count - 3);
////            }
////        }
////    }
////    /*
////    函数名:printpoint
////    函数作用:printpoint无参函数传递值过去
////    函数参数:无
////    函数返回值:无
////    */
////    void printpoint()
////    {
////        printpoint(root, key_max * 5);
////    }
////    /*
////    函数名:BTree_delete
////    函数作用:删除函数
////    函数参数:T value
////    函数返回值:bool类型
////    */
////    bool BTree_delete(T value)
////    {
////        if (!contain(value))
////        {
////            return false;
////        }
////        if (root->keyNum == 1)
////        {
////            if (root->isleaf)
////            {
////                delete root;
////                root = NULL;
////                return true;
////            }
////            else//当根节点只有一个关键字时且不为叶子节点
////            {
////                BTnode<T>* node_child1 = root->pchild[0];
////                BTnode<T>* node_child2 = root->pchild[1];
////                //减少一层树的高度
////                if (node_child1->keyNum == key_min && node_child2->keyNum == key_min)
////                {
////                    MergeBlock(root, 0);
////                    delete root;
////                    root = node_child1;
////                }
////            }
////        }
////        BTree_deletebalance(root, value);
////    }
////    /*
////   函数名:MergeBlock
////   函数作用:合并块
////   函数参数:BTnode<T>* node_parent,int child_index
////   函数返回值:无
////   */
////    void MergeBlock(BTnode<T>* node_parent, int child_index)
////    {
////        BTnode<T>* node_child1 = node_parent->pchild[child_index];
////        BTnode<T>* node_child2 = node_parent->pchild[child_index + 1];
////        //将父节点的节点对应的关键字下移
////        node_child1->keyvalue[key_min] = node_parent->keyvalue[child_index];
////        node_child1->keyNum = key_max;
////        int i;
////        for (i = 0; i < key_min; i++)
////        {
////            node_child1->keyvalue[child_min + i] = node_child2->keyvalue[i];
////        }
////        //判断node_child1是否是叶子节点,不是叶子节点则要将node_child2的子节点赋值给node_child1
////        if (!node_child1->isleaf)
////        {
////            for (i = 0; i < child_min; i++)
////            {
////                node_child1->pchild[i + child_min] = node_child2->pchild[i];
////            }
////        }
////        //因为父节点下移一个关键字,则关键字后的所有值要往前移动一个
////        node_parent->keyNum--;
////        for (i = child_index; i < node_parent->keyNum; i++)
////        {
////            node_parent->keyvalue[i] = node_parent->keyvalue[i + 1];
////            //子节点也要往前移动一位
////            node_parent->pchild[i + 1] = node_parent->pchild[i + 2];
////        }
////        delete node_child2;
////        node_child2 = NULL;
////    }
////    /*
////  函数名:getprev
////  函数作用:在左边的兄弟节点中找一个最大的
////  函数参数:BTnode<T>* node
////  函数返回值:左边兄弟的最大的关键字
////  */
////    T getprev(BTnode<T>* node)
////    {
////        //在比节点位置小的节点中找一个最大的值最为
////        while (!node->isleaf)
////        {
////            node = node->pchild[node->keyNum];
////        }
////        node->keyNum--;
////        return node->keyvalue[node->keyNum - 1];
////    }
////    /*
////  函数名:getnext
////  函数作用:在右边的兄弟节点中找一个最小的
////  函数参数:BTnode<T>* node
////  函数返回值:右边兄弟的最小的关键字
////  */
////    T getnext(BTnode<T>* node)
////    {
////        //在比节点位置大的节点中找一个最小的
////        while (!node->isleaf)
////        {
////            node = node->pchild[0];
////        }
////        return node->keyvalue[0];
////    }
////    /*
////    函数名:BTree_deletebalance
////    函数作用:用递归删除并做修复
////    函数参数:BTnode<T>* node
////    函数返回值:无
////    */
////    void BTree_deletebalance(BTnode<T>* node, T value)
////    {
////        int i;
////        //在当前节点中找合适坐标使得value在这个区间内
////        for (i = 0; i < node->keyNum && value > node->keyvalue[i]; i++)
////        {
////
////        }
////        //如果当前i的关键字等于value
////        if (i < node->keyNum && value == node->keyvalue[i])
////        {
////            //判断当前节点是否是叶子节点,如果是的话直接删除,下面的情况保证了如果value在叶子节点的话,叶子节点keyNum一定是>=child_min
////            if (node->isleaf)
////            {
////                node->keyNum--;
////                //把i后面的都往前移动一位
////                for (; i < node->keyNum; i++)
////                {
////                    node->keyvalue[i] = node->keyvalue[i + 1];
////                }
////                return;
////            }
////            else//当前节点为内节点
////            {
////                //里面关键字都比value小的节点
////                BTnode<T>* node_left = node->pchild[i];
////                //里面关键字都比value大的节点
////                BTnode<T>* node_right = node->pchild[i + 1];
////                if (node_left->keyNum >= child_min)//左子节点中的关键字数大于等于child_min
////                {
////                    T prev_replace = getprev(node_left);
////                    //传递不平衡点让pre_replace
////                    BTree_deletebalance(node_left, prev_replace);
////                    //让前继的关键字替换当前删除的关键字
////                    node->keyvalue[i] = prev_replace;
////                    return;
////                }
////                else if (node_right->keyNum >= child_min)//右子节点中的关键字数大于等于child_min
////                {
////                    T next_replace = getnext(node_right);
////                    //在左边中找到最大的那个递归替换
////                    BTree_deletebalance(node_right, next_replace);
////                    //让前继的关键字替换当前删除的关键字
////                    node->keyvalue[i] = next_replace;
////                    return;
////                }
////                else//左右子节点中的关键字数都等于key_min
////                {
////                    //合并两个子节点
////                    MergeBlock(node, i);
////                    //在合并的节点中删除value值
////                    BTree_deletebalance(node_left, value);
////                }
////            }
////        }
////        else//关键字不在当前节点(下面步骤保证了遍历的所有节点关键字数都是大于等于child_min)
////        {
////            //在(<<value<<)的区间找
////            BTnode<T>* node_child = node->pchild[i];//这里i = node->keyNum
////            BTnode<T>* node_left = NULL;
////            BTnode<T>* node_right = NULL;
////            if (node_child->keyNum == key_min)//当前节点只有两个关键字,补给当前节点使之大于等于child_min
////            {
////                //判断是否有左右兄弟节点
////                if (i > 0)
////                {
////                    node_left = node->pchild[i - 1];
////                }
////                if (i <= node->keyNum - 1)
////                {
////                    node_right = node->pchild[i + 1];
////                }
////                int j;
////                //当前左兄弟的关键字数大于等于child_min
////                if (node_left && node_left->keyNum >= child_min)
////                {
////                    //把父节点的i-1对应的关键字下移
////                    for (j = node_child->keyNum; j > 0; j--)
////                    {
////                        node_child->keyvalue[j] = node_child->keyvalue[j - 1];
////                    }
////                    node_child->keyvalue[0] = node->keyvalue[i - 1];
////                    //如果子节点的左兄弟节点不是叶子节点
////                    if (!node_left->isleaf)
////                    {
////                        //把左兄弟最右边的子节点指针赋值给node_child
////                        for (j = node_child->keyNum + 1; j > 0; j--)
////                        {
////                            node_child->pchild[j - 1]->parent = node_child->pchild[j]->parent;
////                            node_child->pchild[j] = node_child->pchild[j - 1];
////
////                        }
////                        node_left->pchild[node_left->keyNum]->parent = node_child->pchild[0];
////                        node_child->pchild[0] = node_left->pchild[node_left->keyNum];
////                    }
////                    node_child->keyNum++;
////                    node->keyvalue[i - 1] = node_left->keyvalue[node_left->keyNum - 1];
////                    node_left->keyNum--;
////                }
////                else if (node_right && node_right->keyNum >= child_min)
////                {
////                    //把父节点的i对应的关键字下移
////                    node_child->keyvalue[node_child->keyNum] = node->keyvalue[i];
////                    node_child->keyNum++;
////                    //把右兄弟节点最小的关键字赋值给父节点的i位置
////                    node->keyvalue[i] = node_right->keyvalue[0];
////                    node_right->keyNum--;
////                    //把右兄弟的关键字往前移动一位
////                    for (j = 0; j < node_right->keyNum; j++)
////                    {
////                        node_right->keyvalue[j] = node_right->keyvalue[j + 1];
////                    }
////                    //如果右兄弟不是叶子节点则需要把右兄弟最左边的子节点指针赋值给node_child
////                    if (!node_right->isleaf)
////                    {
////                        node_right->pchild[0]->parent = node_child->pchild[node_child->keyNum]->parent;
////                        node_child->pchild[node_child->keyNum] = node_right->pchild[0];
////                        for (j = 0; j < node_right->keyNum + 1; j++)
////                        {
////                            node_right->pchild[j + 1]->parent = node_right->pchild[j]->parent;
////                            node_right->pchild[j] = node_right->pchild[j + 1];
////
////                        }
////
////                    }
////                }
////                else if (node_left)//node_left只有child_min-1个关键字
////                {
////                    //把左兄弟合并
////                    MergeBlock(node, i - 1);
////                    //更新子节点
////                    node_child = node_left;
////                }
////                else if (node_right)
////                {
////                    //把右兄弟合并,子节点无需更新
////                    MergeBlock(node, i);
////                }
////            }
////            BTree_deletebalance(node_child, value);
////        }
////    }
////private:
////    BTnode<T>* root;//根节点
////};
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
////
//////#pragma once
//////#include <iostream>
//////using namespace std;
//////
//////
//////template <class T>
//////class Node
//////{
//////public:
//////	int n;//当前节点中关键字的个数
//////	Node<T>** child;//孩子的地址
//////	T* key;//关键字
//////	bool leaf;//标记是否为叶子
//////
//////	//构造函数——参数为节点中的关键字个数
//////	Node(int t = 0)
//////	{
//////		n = t;//默认节点中关键字为0个
//////		child = NULL;
//////		key = NULL;
//////		leaf = true;//初始化的时候都初始为叶子
//////	}
//////	~Node()
//////	{
//////		n = 0;
//////		child = NULL;
//////		key = NULL;
//////	}
//////};
//////
//////
//////template<class T>
//////class Btree
//////{
////////成员变量
//////private:
//////	Node<T>* root;//根节点
//////	int t;//阶数
//////	int node_num;//节点个数
//////
//////
//////public:
//////	Btree(int m = 2)
//////	{
//////		t = m;//阶数默认为2（那就是二叉树AVL）
//////		root = new Node<T>;//初始化根节点
//////		node_num = 0;//初始化节点个数为0
//////	}
//////	~Btree()
//////	{
//////		PostOrder_Delete(root);
//////	}
//////	//查找元素
//////	//此函数并没有真正实现功能，而是起到中间过度站点的功能（传入递归起点：root根节点）,以实现递归功能
//////	Node<T>* B_Tree_Search(const T& element)
//////	{
//////		return search(root, element);
//////	}
//////	
//////	//插入元素
//////	//此函数并没有真正实现功能，而是起到中间过度站点的功能（传入递归起点：root根节点）,以实现递归功能
//////	void B_Tree_Insert(const T &k)
//////	{
//////		Insert(root, k);
//////	}
//////
//////	//删除元素
//////	void B_Tree_Delete(const T& k);
//////	void Print();//结构化输出B树
//////	int size()const { return node_num; }//获得B树的节点数
//////
//////private:
//////	//后根次序删除
//////	void PostOrder_Delete(Node<T>*& cur);
//////
//////	//查找部分的函数
//////	Node<T>* search(Node<T>* r, const T& elem);//r是递归用的，elem是待查找的元素
//////
//////	//插入部分的函数
//////	void B_Tree_Split_Child(Node<T>* x, int i);//x的i孩子裂变
//////	void Insert(Node<T>*& r, const T& k);//与单纯的查找不同，这里要传入指针的引用防止无法真正分裂
//////	void B_Tree_Insert_NonFull(Node<T>* x, const T& k);//插入非空元素
//////
//////	//删除部分函数
//////	void Merge_Node(Node<T>*& x, int i, Node<T>*& y, Node<T>*& z);//合并x的第i个子结点y和第i+1个子结点z，此时y和z的key个数都是t-1
//////	T Search_Predecessor(Node<T>* y); //查找前驱
//////	T Search_Successor(Node<T>* z);   //查找后继
//////
//////	void Shift_To_Left_Child(Node<T>*& x, int i, Node<T>*& y, Node<T>*& z);
//////	void Shift_To_Right_Child(Node<T>*& x, int i, Node<T>*& y, Node<T>*& z);
//////	void B_Tree_Delete_NoNone(Node<T>* x, const T& k);//删除内部结点x的k
//////
//////};
//////
//////
////////查找功能实现
//////template <class T>
//////Node<T>* Btree<T>::search(Node<T>* x, const T& k)
////////x是递归用的，k是待查找的元素
//////{
//////	//思想：先在根节点（及往下遍历到的节点）所含有的key中从大到小遍历，会出现以下几种情况：
//////	//1. 在key们中找到了键值，直接返回
//////	//2. 在key们中找到了键值的大小区间，在区间范围内往下一层节点遍历
//////	//3. 此节点的n（关键字个数）=0，也就是他是空的
//////
//////
//////	int i = 0;
//////	while (i<x->n && k>x->key[i])//i小于该节点关键字的个数 && 待查找的元素值>第i个关键字
//////	//i = 该节点的所有关键字里小于k的元素个数
//////	{
//////		++i;
//////	}
//////
//////	if (i<x->n && k==x->key[i])//在刚才遍历的节点的若干关键字里，存在我要查找的这个值
//////		//找到了——递归出口
//////	{
//////		return x;//返回找到的该元素的地址
//////	}
//////	else if (x->leaf)//else表示没在此节点找到，并且此节点已经是叶节点（或者空）了，没有孩子了
//////		//整棵树没找到
//////	{	
//////		return NULL;
//////	}
//////	else//虽然该节点没有，但i给出了他的第几个孩子可能有，所以对子节点child[i]进行search递归
//////	{
//////		return search(x->child[i], k);
//////	}
//////}
//////
//////
////////插入功能实现
//////template<typename T>
//////void Btree<T>::Insert(Node<T>*& r, const T& k)
////////r是递归用的，k是待查找的元素
//////{
//////
//////
//////}