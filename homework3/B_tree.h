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
////Record��B������������ͣ�order��B���Ľ���
//template <class Record>
//class B_node 
//{
//public:
//	int count;//�ڵ�ؼ��ָ���
//	Record* data;//���ڵ�ؼ�������
//	B_node <Record>** branch;//����ָ������,����branch[0]ָ���һ��������������keysС��data[0]��������
//
//	//���캯��
//	B_node();
//};
//
//template <class Record>
//B_node<Record>::B_node()
//{
//	data = new Record[order - 1];
//	branch = new B_node <Record>*[order];
//	count = 0;
//	for (int i = 0; i < order; i++)//����ָ�������ʼ��
//    {
//        branch[i] = NULL;
//    }
//    for (int i = 0; i < order-1; i++)//�ؼ��������ʼ��
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
//	if (node != NULL)//�ж�Ԫ���Ƿ�Ϊ��
//	{
//		int i, j;
//		//ÿ���ڵ��С�����ӡ
//		for (i = 0; i < node->count; i++)
//		{	
//			//�ж��Ƿ�Ҷ�ڵ�,���ǵĻ���Ҫ���ӽڵ���Ѱ�Ҵ�ӡ
//			if (node->branch[0]!=NULL)//�ж��Ƿ���Ҷ�ӽڵ�
//			{
//				printpoint(node->branch[i], count - 3);
//			}
//			for (j = count; j >= 0; j--)
//			{
//				cout << "-";
//			}
//			cout << "|" << node->data[i] << "|" << endl;
//		}
//		if (node->branch[0] != NULL)//�ӽڵ����ȹؼ�������һ��
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
////current���������ݹ飬�����ǿ�ָ�����ָ��B����ĳ������/�ڵ�
////target������Ҫ���ҵ�ֵ
////����ֵ������������û�ҵ�
////���ս�������ҵ��ˣ���current��target���ڽڵ㣬position��targetֵ�ڽڵ��е�λ��
//{
//	Error_code result = not_present;//result��ʼ��Ϊ�Ҳ������ҵ����ٸ���
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
////������ǰ�ڵ㣬������ڵ�����û��target
//template <class Record>
//Error_code B_tree<Record> ::search_node(B_node<Record>* current, const Record& target, int& position)
////position���������ش��ε�
////����ҵ��ˣ�position����recursive_search_tree��������target��λ�ã�������sucess�ı�ʶ
////���û�ҵ���position����recursive_search_tree��������С��target��λ�ã�������not_present�ı�ʶ
//{
//	position = 0;
//	while (position < current->count && target > current->data[position])
//		position++; //�Ȱ�position��ͷָ��target��λ�� �� ����������target��λ��
//	if (position < current->count && target == current->data[position])
//		return success;
//	else
//		return not_present;//�����˽ڵ���û��target����position��ָ����Ӧ��λ���ˣ�
//}
//
////��new_entry��������
////�����ַ���ֵ
////success������ɹ�
////duplicate_error��ԭ�����Ѵ��ڣ�����ʧ��
//template <class Record>
//Error_code B_tree<Record> ::insert(const Record& new_entry)
//{
//	Record median;
//	B_node<Record>* right_branch,* new_root;
//	Error_code result = push_down(root, new_entry, median, right_branch);
//	if (result == overflow) 
//		//�����󷵻ص���һ��ѹջ������Ҳ���Ǹ��ڵ�ѹ��ջ��ʱ����Ȼ��overflow��˵�����ڵ�ҲҪ���в�ֵ����
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
//		//�����ǰ�����Ľڵ�Ϊ�գ��򷵻�overflow�����־
//		median = new_entry;
//		right_branch = NULL;
//		result = overflow;
//	}
//	else 
//	{
//		//����new_entry�ڵ��Ƿ��Ѿ���current�ڵ������ˣ�����Ѿ�������򷵻�duplicate_error�������������ֵ�Ѵ���
//		if ( search_node(current, new_entry, position) == success )
//			result = duplicate_error;
//		//
//		else 
//		{
//			Record extra_entry;
//			B_node<Record>* extra_branch;
//			//�����ǵݹ�ľ�����push_down�����push_down���ݹ�������������Ľڵ���NULL������overflow�����������ĳ�ڵ��﷢���˸���ֵ�����ò����ˣ�����duplicate_error
//			result = push_down(
//				current->branch[position],
//				new_entry,
//				extra_entry,
//				extra_branch);
//			//��������һ��ѹջ�����ķ���ֵ��overflow����������ߵ���NULL
//			//�������ص����Ǹ�ѹջ������Ӧ���ǵ����ڶ���ѹջ��������NULL�ڵ����һ���ڵ㣩�����current��������ֵӦ�ò���Ľڵ�
//			if (result == overflow) 
//			{
//				// ������ֵ���뵽Ӧ�ò��뵽�Ľڵ�����
//				if (current->count < order - 1) 
//					//Ӧ����Ľڵ���ֵ�ĸ������С��order-1��֤����ʹ��������һ����ֵ��Ҳ���������
//				{
//					result = success;//���ķ���ֵΪsuccess��˵���ܳɹ�����
//					push_in(current, extra_entry,extra_branch, position);//ֱ���ڸýڵ������ֵ
//				}
//				else 
//					//current�ڵ�Ҫ����
//					//���ڽڵ�Ҫ���ѵĻ����Ʊػ�����һ��ѹջ������current�ڵ㣨Ҳ���ǵ�ǰ�����ѽڵ����һ���ڵ㣩����һ��ֵ
//					//���Ը���һ��ѹջ�����ķ���ֵӦ����overflow�������ص��Ǹ�ѹջ�����л�Ӧ�²���һ��ֵ
//					split_node(current, extra_entry,extra_branch, position,right_branch, median);
//			}
//		}
//	}
//	return result;
//}
//
//template <class Record>
//void B_tree<Record> ::push_in(B_node<Record>* current,const Record& entry,B_node<Record>* right_branch,int position)
////current�Ǵ�����Ľڵ�
////entry�Ǳ��²���Ľڵ��е���ֵ���������½ڵ�
////right_branch���²����ֵ�����������
////position���Σ����²����ֵ������
//{
//	for (int i = current->count; i > position; i--) 
//	{
//		// Shift all later data to the right.��position�ڵط�
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
//	B_node<Record>* current, //�����ѵĽڵ�
//	const Record& extra_entry, // ��ֵ
//	B_node<Record>* extra_branch,
//	// �²����ֵ�����������
//	int position,// ���������ֵ��λ��
//	B_node<Record>*& right_half, // ���ѽڵ㣬��ԭ�ڵ���Ұ�ߵ���ֵ�Ž��¶���Ľڵ�right_half����
//	Record& median) // �ڵ��м�ֵ
//{
//	//��ԭ�ڵ���Ұ�ߵ���ֵ�Ž��¶���Ľڵ�right_half����
//	right_half = new B_node<Record>;
//	int mid = order / 2; 
//	
//	// ��ʱ���м�ڵ���������
//	if (position <= mid) 
//		//���������Ľڵ������ߣ��Ȱ�ԭ�ڵ㣨 �ؼ��ֵ���Ŀ = order-1 ���Ұ�ߵ�����ȫ���Ƶ��½ڵ���
//	{ 
//		for (int i = mid; i < order - 1; i++) 
//		{ 
//			right_half->data[i - mid] = current->data[i];
//			right_half->branch[i + 1 - mid] = current->branch[i + 1];
//		}
//		current->count = mid;
//		right_half->count = order - 1 - mid;
//		push_in(current, extra_entry,extra_branch, position);//�ٰ���ֵ���뵽����
//	}
//	else 
//		//���������Ľڵ����Ұ�ߣ��Ȱ�ԭ�ڵ㣨 �ؼ��ֵ���Ŀ = order-1 ���Ұ�ߵ����֣���ȥ�м��Ǹ�����Ϊ�˸��½ڵ��ڵط���ȫ���Ƶ��½ڵ���
//	{ 
//		mid++; 
//		for (int i = mid; i < order - 1; i++) 
//		{
//			// Move entries to right_half .
//			right_half->data[i - mid] = current->data[i];
//			right_half->branch[i + 1 - mid] = current->branch[i + 1];
//		}
//		current->count = mid;//���µ�ǰ�ڵ�ؼ����ж���
//		right_half->count = order - 1 - mid;
//		push_in(right_half, extra_entry, extra_branch, position - mid);//�ٰ���ֵ���뵽�Ұ��
//	}
//	median = current->data[current->count - 1];
//	// ���м�ֵ����ڵ�ɾ��������������ڵ�ԭ�������һ��ֵת�Ƶ�ԭ���м�ֵ�ڵĵط����и��ǣ�
//	right_half->branch[0] = current->branch[current -> count];
//	current->count --;//���¹ؼ��ֵ���ֵ
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
//			//��ɾ����ֵ��������ڵ����棬position������λ������
//			result = success;
//			if (current->branch[position] != NULL) 
//			{
//				//����Ҷ�ڵ���ɾ��
//				copy_in_predecessor(current, position);
//				recursive_remove(current -> branch[position], current->data[position]);
//			}
//			else 
//				//��Ҷ�ڵ���ɾ����ֱ��ɾ������
//				remove_data(current, position);
//		}
//		else 
//			//Ҫɾ����ֵ��������ڵ���������±���
//			result = recursive_remove(current -> branch[position], target);
//
//		if (current->branch[position] != NULL)
//			if (current->branch[position]->count < (order - 1) / 2)//˵��ɾ��֮�󣬽ڵ�Ĺؼ������Ѿ�������Ҫ���ˣ�������Ҫ�ϲ�
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
////static const int m = 3;  //������С��Ϊ3
////static const int key_max = 2 * m - 1;//�ؼ���������
////static const int key_min = m - 1;//�ؼ�����С����
////static const int child_max = key_max + 1;//�ӽڵ�������(������Կ����ӽڵ�����ؼ������й�)
////static const int child_min = key_min + 1;//�ӽڵ���С����
////
////template <class T>
////class BTree;//ǰ������
/////*
////����:BTnode
////*/
////template <class T>
////class BTnode
////{
////    friend class BTree<T>;//��Ԫ����
////public:
////    BTnode()
////    {
////        keyNum = 0;
////        parent = NULL;//���ڵ��ʼ��
////        isleaf = true;
////        int i;
////        for (i = 0; i < child_max; i++)//����ָ�������ʼ��
////        {
////            pchild[i] = NULL;
////        }
////        for (i = 0; i < key_max; i++)//�ؼ��������ʼ��
////        {
////            keyvalue[i] = '\0';
////        }
////    }
////private:
////    bool isleaf;//�жϽڵ��Ƿ���Ҷ�ӽڵ�
////    int keyNum;//�ؼ��ָ���
////    BTnode<T>* parent;//ָ�򸸽ڵ�
////    BTnode<T>* pchild[child_max];//����ָ������
////    T   keyvalue[key_max];//�ؼ�������
////};
////
/////*
////����:BTree
////*/
////template <class T>
////class BTree
////{
////public:
////    /*
////   ������:BTree
////   ��������:�޲ι��캯��
////   ��������:��
////   ��������ֵ: ��
////   */
////
////    BTree()
////    {
////        root = NULL;
////    }
////    /*
////   ������:BTree_insert
////   ��������:����ؼ���
////   ��������:T value
////   ��������ֵ: bool�����жϲ����Ƿ�ɹ�
////   */
////
////    bool BTree_insert(T value)
////    {
////        if (contain(value))//�������Ƿ�����ͬ�Ĺؼ���
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
////                newnode->isleaf = false;//���ϲ�������֪newnode�Ѿ����ӽڵ�
////                SplitBlock(newnode, 0, root);//�ֿ����
////                root = newnode;//���¸��ڵ�
////            }
////            Notfull_insert(root, value);//�����δ���Ĳ���
////            return true;
////        }
////    }
////
////    /*
////     ������:SplitBlock
////     ��������:�ѽڵ����
////     ��������:BTnode<T>* node_parent,int child_index,BTnode<T>* node_child
////     ��������ֵ: ��
////     */
////
////    void SplitBlock(BTnode<T>* node_parent, int child_index, BTnode<T>* node_child)
////    {
////        BTnode<T>* node_right = new BTnode<T>();
////        node_right->isleaf = node_child->isleaf;
////        node_right->keyNum = key_min;
////        int i;
////        //node_right�����ؼ���
////        for (i = 0; i < key_min; i++)
////        {
////            node_right->keyvalue[i] = node_child->keyvalue[i + child_min];
////        }
////        //�жϷ��ѵĽڵ��Ƿ���Ҷ�ӽڵ�,������ǵĻ���Ҫ�����ĺ��Ӹ�ֵ��ȥ
////        if (!node_child->isleaf)
////        {
////            for (i = 0; i < child_min; i++)
////            {
////                node_right->pchild[i] = node_child->pchild[i + child_min];
////                node_child->pchild[i + child_min]->parent = node_right->pchild[i];
////            }
////        }
////        node_child->keyNum = key_min;//�����ӽڵ�Ĺؼ�����
////        //�Ѹ��ڵ�ؼ��ֺ���ָ�������� ����ֵ
////        for (i = node_parent->keyNum; i > child_index; i--)
////        {
////            node_parent->keyvalue[i] = node_parent->keyvalue[i - 1];
////            node_parent->pchild[i + 1] = node_parent->pchild[i];
////            node_child->pchild[i]->parent = node_parent->pchild[i + 1];
////        }
////        node_parent->keyNum++;//���¸��ڵ�ؼ�����
////        node_parent->pchild[child_index + 1] = node_right;
////        node_right->parent = node_parent->pchild[child_index + 1];
////        //���м���Ǹ��ؼ������Ƶ����ڵ�
////        node_parent->keyvalue[child_index] = node_child->keyvalue[key_min];
////    }
////
////
////    /*
////    ������:Notfull_insert
////    ��������:��û�����Ľڵ������ӹؼ���
////    ��������:BTnode<T>* node,T value
////    ��������ֵ:��
////    */
////    void Notfull_insert(BTnode<T>* node, T value)
////    {
////
////        int node_keynum = node->keyNum;//��ȡ�ڵ�ؼ�����
////        if (node->isleaf)//node��Ҷ�ӽڵ�
////        {
////            while (node_keynum > 0 && value < node->keyvalue[node_keynum - 1])
////            {
////                node->keyvalue[node_keynum] = node->keyvalue[node_keynum - 1];//�ѹؼ��������ƶ�
////                --node_keynum;
////            }
////            node->keyvalue[node_keynum] = value;
////            node->keyNum++;
////        }
////        else//node���ڲ��ڵ�
////        {
////            while (node_keynum > 0 && value < node->keyvalue[node_keynum - 1])
////            {
////                --node_keynum;
////            }
////            //�ڱ���С�ͱ������м��Ǹ��ӽڵ����Һ���λ��,
////            //����������еĶ�С���ڵ�һ���ӽڵ���Ѱ��
////            BTnode<T>* node_child = node->pchild[node_keynum];
////            if (node_child->keyNum == key_max)
////            {
////                SplitBlock(node, node_keynum, node_child);
////                if (value > node->keyvalue[node_keynum])//����ֵ���ӽڵ��м��ֵ�Ƚ�
////                {
////                    node_child = node->pchild[node_keynum + 1];
////                }
////            }
////            Notfull_insert(node_child, value);//��������Ѱ�Һ��ʵ�λ��
////        }
////    }
////
////    /*
////    ������:contain
////    ��������:�����Ƿ�����ͬԪ��������
////    ��������:T value
////    ��������ֵ:bool����
////    */
////    bool contain(T value)
////    {
////        if (BTree_find(root, value) != NULL)
////            return true;
////        return false;
////    }
////
////    /*
////    ������:BTree_find
////    ��������:�����Ƿ�����ͬԪ��������
////    ��������:BTnode<T>* node,T value
////    ��������ֵ: BTnode<T>*
////    */
////    BTnode<T>* BTree_find(BTnode<T>* node, T value)
////    {
////        if (node == NULL)//��ǰ�ڵ�Ϊ�յ�ʱ��
////        {
////            return NULL;
////        }
////        else//��ǰ�ڵ㲻Ϊ��
////        {
////            int i;
////            //�ڱ���С�ͱ�������м��ӽڵ���Ѱ����ȵ�
////            for (i = 0; i < node->keyNum; i++)
////            {
////                if (value <= node->keyvalue[i])
////                {
////                    break;
////                }
////            }
////
////            //У�鵱ǰ�Ĺؼ����Ƿ���ڲ��ҵĹؼ���
////            if (i < node->keyNum && value == node->keyvalue[i])//i���±����ֵkeyNum-1
////            {
////                return node;
////            }
////            else
////            {
////                //���֮ǰ�Ȳ��ҹؼ�û����ȵĹؼ��ֲ��ҵ�ǰ�ڵ���Ҷ�ӽڵ�Ļ�
////                //��ô��B����û��һ���Ĺؼ���(��Ϊ����ȹؼ��ָ���)
////                if (node->isleaf)
////                {
////                    return NULL;
////                }
////                else//�������Ҷ�ӽڵ�����������ӽڵ���Ѱ��
////                {
////                    return BTree_find(node->pchild[i], value);//�����return������
////                }
////            }
////        }
////    }
////
////    /*
////    ������:printpoint
////    ��������:��ӡԪ��
////    ��������:BTnode<T>* node,int count
////    ��������ֵ:��
////    */
////    void printpoint(BTnode<T>* node, int count)
////    {
////        if (node != NULL)//�ж�Ԫ���Ƿ�Ϊ��
////        {
////            int i, j;
////            //ÿ���ڵ��С�����ӡ
////            for (i = 0; i < node->keyNum; i++)
////            {
////                //�ж��Ƿ�Ҷ�ڵ�,���ǵĻ���Ҫ���ӽڵ���Ѱ�Ҵ�ӡ
////                if (!node->isleaf)//�ж��Ƿ���Ҷ�ӽڵ�
////                {
////                    printpoint(node->pchild[i], count - 3);
////                }
////                for (j = count; j >= 0; j--)
////                {
////                    cout << "-";
////                }
////                cout << "|" << node->keyvalue[i] << "|" << endl;
////            }
////            if (!node->isleaf)//�ӽڵ����ȹؼ�������һ��
////            {
////                printpoint(node->pchild[i], count - 3);
////            }
////        }
////    }
////    /*
////    ������:printpoint
////    ��������:printpoint�޲κ�������ֵ��ȥ
////    ��������:��
////    ��������ֵ:��
////    */
////    void printpoint()
////    {
////        printpoint(root, key_max * 5);
////    }
////    /*
////    ������:BTree_delete
////    ��������:ɾ������
////    ��������:T value
////    ��������ֵ:bool����
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
////            else//�����ڵ�ֻ��һ���ؼ���ʱ�Ҳ�ΪҶ�ӽڵ�
////            {
////                BTnode<T>* node_child1 = root->pchild[0];
////                BTnode<T>* node_child2 = root->pchild[1];
////                //����һ�����ĸ߶�
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
////   ������:MergeBlock
////   ��������:�ϲ���
////   ��������:BTnode<T>* node_parent,int child_index
////   ��������ֵ:��
////   */
////    void MergeBlock(BTnode<T>* node_parent, int child_index)
////    {
////        BTnode<T>* node_child1 = node_parent->pchild[child_index];
////        BTnode<T>* node_child2 = node_parent->pchild[child_index + 1];
////        //�����ڵ�Ľڵ��Ӧ�Ĺؼ�������
////        node_child1->keyvalue[key_min] = node_parent->keyvalue[child_index];
////        node_child1->keyNum = key_max;
////        int i;
////        for (i = 0; i < key_min; i++)
////        {
////            node_child1->keyvalue[child_min + i] = node_child2->keyvalue[i];
////        }
////        //�ж�node_child1�Ƿ���Ҷ�ӽڵ�,����Ҷ�ӽڵ���Ҫ��node_child2���ӽڵ㸳ֵ��node_child1
////        if (!node_child1->isleaf)
////        {
////            for (i = 0; i < child_min; i++)
////            {
////                node_child1->pchild[i + child_min] = node_child2->pchild[i];
////            }
////        }
////        //��Ϊ���ڵ�����һ���ؼ���,��ؼ��ֺ������ֵҪ��ǰ�ƶ�һ��
////        node_parent->keyNum--;
////        for (i = child_index; i < node_parent->keyNum; i++)
////        {
////            node_parent->keyvalue[i] = node_parent->keyvalue[i + 1];
////            //�ӽڵ�ҲҪ��ǰ�ƶ�һλ
////            node_parent->pchild[i + 1] = node_parent->pchild[i + 2];
////        }
////        delete node_child2;
////        node_child2 = NULL;
////    }
////    /*
////  ������:getprev
////  ��������:����ߵ��ֵܽڵ�����һ������
////  ��������:BTnode<T>* node
////  ��������ֵ:����ֵܵ����Ĺؼ���
////  */
////    T getprev(BTnode<T>* node)
////    {
////        //�ڱȽڵ�λ��С�Ľڵ�����һ������ֵ��Ϊ
////        while (!node->isleaf)
////        {
////            node = node->pchild[node->keyNum];
////        }
////        node->keyNum--;
////        return node->keyvalue[node->keyNum - 1];
////    }
////    /*
////  ������:getnext
////  ��������:���ұߵ��ֵܽڵ�����һ����С��
////  ��������:BTnode<T>* node
////  ��������ֵ:�ұ��ֵܵ���С�Ĺؼ���
////  */
////    T getnext(BTnode<T>* node)
////    {
////        //�ڱȽڵ�λ�ô�Ľڵ�����һ����С��
////        while (!node->isleaf)
////        {
////            node = node->pchild[0];
////        }
////        return node->keyvalue[0];
////    }
////    /*
////    ������:BTree_deletebalance
////    ��������:�õݹ�ɾ�������޸�
////    ��������:BTnode<T>* node
////    ��������ֵ:��
////    */
////    void BTree_deletebalance(BTnode<T>* node, T value)
////    {
////        int i;
////        //�ڵ�ǰ�ڵ����Һ�������ʹ��value�����������
////        for (i = 0; i < node->keyNum && value > node->keyvalue[i]; i++)
////        {
////
////        }
////        //�����ǰi�Ĺؼ��ֵ���value
////        if (i < node->keyNum && value == node->keyvalue[i])
////        {
////            //�жϵ�ǰ�ڵ��Ƿ���Ҷ�ӽڵ�,����ǵĻ�ֱ��ɾ��,����������֤�����value��Ҷ�ӽڵ�Ļ�,Ҷ�ӽڵ�keyNumһ����>=child_min
////            if (node->isleaf)
////            {
////                node->keyNum--;
////                //��i����Ķ���ǰ�ƶ�һλ
////                for (; i < node->keyNum; i++)
////                {
////                    node->keyvalue[i] = node->keyvalue[i + 1];
////                }
////                return;
////            }
////            else//��ǰ�ڵ�Ϊ�ڽڵ�
////            {
////                //����ؼ��ֶ���valueС�Ľڵ�
////                BTnode<T>* node_left = node->pchild[i];
////                //����ؼ��ֶ���value��Ľڵ�
////                BTnode<T>* node_right = node->pchild[i + 1];
////                if (node_left->keyNum >= child_min)//���ӽڵ��еĹؼ��������ڵ���child_min
////                {
////                    T prev_replace = getprev(node_left);
////                    //���ݲ�ƽ�����pre_replace
////                    BTree_deletebalance(node_left, prev_replace);
////                    //��ǰ�̵Ĺؼ����滻��ǰɾ���Ĺؼ���
////                    node->keyvalue[i] = prev_replace;
////                    return;
////                }
////                else if (node_right->keyNum >= child_min)//���ӽڵ��еĹؼ��������ڵ���child_min
////                {
////                    T next_replace = getnext(node_right);
////                    //��������ҵ������Ǹ��ݹ��滻
////                    BTree_deletebalance(node_right, next_replace);
////                    //��ǰ�̵Ĺؼ����滻��ǰɾ���Ĺؼ���
////                    node->keyvalue[i] = next_replace;
////                    return;
////                }
////                else//�����ӽڵ��еĹؼ�����������key_min
////                {
////                    //�ϲ������ӽڵ�
////                    MergeBlock(node, i);
////                    //�ںϲ��Ľڵ���ɾ��valueֵ
////                    BTree_deletebalance(node_left, value);
////                }
////            }
////        }
////        else//�ؼ��ֲ��ڵ�ǰ�ڵ�(���沽�豣֤�˱��������нڵ�ؼ��������Ǵ��ڵ���child_min)
////        {
////            //��(<<value<<)��������
////            BTnode<T>* node_child = node->pchild[i];//����i = node->keyNum
////            BTnode<T>* node_left = NULL;
////            BTnode<T>* node_right = NULL;
////            if (node_child->keyNum == key_min)//��ǰ�ڵ�ֻ�������ؼ���,������ǰ�ڵ�ʹ֮���ڵ���child_min
////            {
////                //�ж��Ƿ��������ֵܽڵ�
////                if (i > 0)
////                {
////                    node_left = node->pchild[i - 1];
////                }
////                if (i <= node->keyNum - 1)
////                {
////                    node_right = node->pchild[i + 1];
////                }
////                int j;
////                //��ǰ���ֵܵĹؼ��������ڵ���child_min
////                if (node_left && node_left->keyNum >= child_min)
////                {
////                    //�Ѹ��ڵ��i-1��Ӧ�Ĺؼ�������
////                    for (j = node_child->keyNum; j > 0; j--)
////                    {
////                        node_child->keyvalue[j] = node_child->keyvalue[j - 1];
////                    }
////                    node_child->keyvalue[0] = node->keyvalue[i - 1];
////                    //����ӽڵ�����ֵܽڵ㲻��Ҷ�ӽڵ�
////                    if (!node_left->isleaf)
////                    {
////                        //�����ֵ����ұߵ��ӽڵ�ָ�븳ֵ��node_child
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
////                    //�Ѹ��ڵ��i��Ӧ�Ĺؼ�������
////                    node_child->keyvalue[node_child->keyNum] = node->keyvalue[i];
////                    node_child->keyNum++;
////                    //�����ֵܽڵ���С�Ĺؼ��ָ�ֵ�����ڵ��iλ��
////                    node->keyvalue[i] = node_right->keyvalue[0];
////                    node_right->keyNum--;
////                    //�����ֵܵĹؼ�����ǰ�ƶ�һλ
////                    for (j = 0; j < node_right->keyNum; j++)
////                    {
////                        node_right->keyvalue[j] = node_right->keyvalue[j + 1];
////                    }
////                    //������ֵܲ���Ҷ�ӽڵ�����Ҫ�����ֵ�����ߵ��ӽڵ�ָ�븳ֵ��node_child
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
////                else if (node_left)//node_leftֻ��child_min-1���ؼ���
////                {
////                    //�����ֵܺϲ�
////                    MergeBlock(node, i - 1);
////                    //�����ӽڵ�
////                    node_child = node_left;
////                }
////                else if (node_right)
////                {
////                    //�����ֵܺϲ�,�ӽڵ��������
////                    MergeBlock(node, i);
////                }
////            }
////            BTree_deletebalance(node_child, value);
////        }
////    }
////private:
////    BTnode<T>* root;//���ڵ�
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
//////	int n;//��ǰ�ڵ��йؼ��ֵĸ���
//////	Node<T>** child;//���ӵĵ�ַ
//////	T* key;//�ؼ���
//////	bool leaf;//����Ƿ�ΪҶ��
//////
//////	//���캯����������Ϊ�ڵ��еĹؼ��ָ���
//////	Node(int t = 0)
//////	{
//////		n = t;//Ĭ�Ͻڵ��йؼ���Ϊ0��
//////		child = NULL;
//////		key = NULL;
//////		leaf = true;//��ʼ����ʱ�򶼳�ʼΪҶ��
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
////////��Ա����
//////private:
//////	Node<T>* root;//���ڵ�
//////	int t;//����
//////	int node_num;//�ڵ����
//////
//////
//////public:
//////	Btree(int m = 2)
//////	{
//////		t = m;//����Ĭ��Ϊ2���Ǿ��Ƕ�����AVL��
//////		root = new Node<T>;//��ʼ�����ڵ�
//////		node_num = 0;//��ʼ���ڵ����Ϊ0
//////	}
//////	~Btree()
//////	{
//////		PostOrder_Delete(root);
//////	}
//////	//����Ԫ��
//////	//�˺�����û������ʵ�ֹ��ܣ��������м����վ��Ĺ��ܣ�����ݹ���㣺root���ڵ㣩,��ʵ�ֵݹ鹦��
//////	Node<T>* B_Tree_Search(const T& element)
//////	{
//////		return search(root, element);
//////	}
//////	
//////	//����Ԫ��
//////	//�˺�����û������ʵ�ֹ��ܣ��������м����վ��Ĺ��ܣ�����ݹ���㣺root���ڵ㣩,��ʵ�ֵݹ鹦��
//////	void B_Tree_Insert(const T &k)
//////	{
//////		Insert(root, k);
//////	}
//////
//////	//ɾ��Ԫ��
//////	void B_Tree_Delete(const T& k);
//////	void Print();//�ṹ�����B��
//////	int size()const { return node_num; }//���B���Ľڵ���
//////
//////private:
//////	//�������ɾ��
//////	void PostOrder_Delete(Node<T>*& cur);
//////
//////	//���Ҳ��ֵĺ���
//////	Node<T>* search(Node<T>* r, const T& elem);//r�ǵݹ��õģ�elem�Ǵ����ҵ�Ԫ��
//////
//////	//���벿�ֵĺ���
//////	void B_Tree_Split_Child(Node<T>* x, int i);//x��i�����ѱ�
//////	void Insert(Node<T>*& r, const T& k);//�뵥���Ĳ��Ҳ�ͬ������Ҫ����ָ������÷�ֹ�޷���������
//////	void B_Tree_Insert_NonFull(Node<T>* x, const T& k);//����ǿ�Ԫ��
//////
//////	//ɾ�����ֺ���
//////	void Merge_Node(Node<T>*& x, int i, Node<T>*& y, Node<T>*& z);//�ϲ�x�ĵ�i���ӽ��y�͵�i+1���ӽ��z����ʱy��z��key��������t-1
//////	T Search_Predecessor(Node<T>* y); //����ǰ��
//////	T Search_Successor(Node<T>* z);   //���Һ��
//////
//////	void Shift_To_Left_Child(Node<T>*& x, int i, Node<T>*& y, Node<T>*& z);
//////	void Shift_To_Right_Child(Node<T>*& x, int i, Node<T>*& y, Node<T>*& z);
//////	void B_Tree_Delete_NoNone(Node<T>* x, const T& k);//ɾ���ڲ����x��k
//////
//////};
//////
//////
////////���ҹ���ʵ��
//////template <class T>
//////Node<T>* Btree<T>::search(Node<T>* x, const T& k)
////////x�ǵݹ��õģ�k�Ǵ����ҵ�Ԫ��
//////{
//////	//˼�룺���ڸ��ڵ㣨�����±������Ľڵ㣩�����е�key�дӴ�С��������������¼��������
//////	//1. ��key�����ҵ��˼�ֵ��ֱ�ӷ���
//////	//2. ��key�����ҵ��˼�ֵ�Ĵ�С���䣬�����䷶Χ������һ��ڵ����
//////	//3. �˽ڵ��n���ؼ��ָ�����=0��Ҳ�������ǿյ�
//////
//////
//////	int i = 0;
//////	while (i<x->n && k>x->key[i])//iС�ڸýڵ�ؼ��ֵĸ��� && �����ҵ�Ԫ��ֵ>��i���ؼ���
//////	//i = �ýڵ�����йؼ�����С��k��Ԫ�ظ���
//////	{
//////		++i;
//////	}
//////
//////	if (i<x->n && k==x->key[i])//�ڸղű����Ľڵ�����ɹؼ����������Ҫ���ҵ����ֵ
//////		//�ҵ��ˡ����ݹ����
//////	{
//////		return x;//�����ҵ��ĸ�Ԫ�صĵ�ַ
//////	}
//////	else if (x->leaf)//else��ʾû�ڴ˽ڵ��ҵ������Ҵ˽ڵ��Ѿ���Ҷ�ڵ㣨���߿գ��ˣ�û�к�����
//////		//������û�ҵ�
//////	{	
//////		return NULL;
//////	}
//////	else//��Ȼ�ýڵ�û�У���i���������ĵڼ������ӿ����У����Զ��ӽڵ�child[i]����search�ݹ�
//////	{
//////		return search(x->child[i], k);
//////	}
//////}
//////
//////
////////���빦��ʵ��
//////template<typename T>
//////void Btree<T>::Insert(Node<T>*& r, const T& k)
////////r�ǵݹ��õģ�k�Ǵ����ҵ�Ԫ��
//////{
//////
//////
//////}