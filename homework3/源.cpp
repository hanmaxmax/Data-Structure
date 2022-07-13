#include"B_tree.h"
#include <graphics.h>
#include <time.h>
#include <conio.h>
#include <string>
#include <string.h>
#include<cstring>
#include<queue>
#include <iostream>
#include <graphics.h>		// ����ͼ�ο�ͷ�ļ�
#include <conio.h>
using namespace std;

// ����
// �ҵ���ײ����Ľڵ�λ��
// Ҷ�ڵ�û����ֱ�Ӳ���
// Ҷ�ڵ����ˣ����м�ڵ㼷��ȥ�����Ұ�߷ֿ��������ӽڵ�
// �������ϴ��ݣ�����һ�ѵ��м�ڵ������ڵ� 
//���м�ڵ㣺����ڵ�����ż�������м�ڵ���ƫ�������Ǹ��������磺0��1��2��3 ���м���2��



// ɾ��
// �м�ڵ��ɾ������ת��ΪҶ�ڵ㣩��
// ɾ������������ֱ��ǰ��������������������ײ�����һ�����ӣ���������������½ǣ���������
// Ȼ��ɾ������ֱ��ǰ�����Ǹ�Ҷ�ڵ㣩

// Ҷ�ڵ��ɾ������ / �ϲ�[�ϲ�Ҫɾ���ڵ㣬��������׷��]����
// ����ͻ����ֱ��ɾ��
// ��ͻ���ȿ����ֵܹ������裬�ٿ����ֵܣ���������ҵ�һ������ģ��Ǿͣ����ϸ��ڵ㼯��ƫ��
// ����������裬�Ǿͺ����ֵܺϲ������û�����ֵܣ���ֻ�ܺ��Һϲ��ˣ�
// �ϲ������ýڵ� + ���Ĵ��ϲ��ֵܽڵ� + ���ǵĸ��ڵ㣩��ͬ����һ���½ڵ㣬Ȼ��ɾ�� �����ǵĸ��ڵ㡱
// ����ϰѺϲ���ʱ�� ɾ�����ǵĸ��ڵ� �������£���> ���ڵ�ɾ��֮������Ҫ���ˣ��򸸽ڵ���������Լ����ֵܺϲ�����ʱֻ��һֱ����׷�ݣ������������ˣ�




enum Error_code
{
	not_present, success, overflow, duplicate_error
};
int order;


//int��B�������������

class B_node
{
public:
	int count;//�ڵ�ؼ��ָ���
	int* data;//���ڵ�ؼ�������
	B_node** branch;//����ָ������,����branch[0]ָ���һ��������������keysС��data[0]��������

	//���캯��
	B_node();
};


B_node::B_node()
{
	data = new int[order - 1];
	branch = new B_node * [order];
	count = 0;
	for (int i = 0; i < order; i++)//����ָ�������ʼ��
	{
		branch[i] = NULL;
	}
	for (int i = 0; i < order - 1; i++)//�ؼ��������ʼ��
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

	if (node != NULL)//�ж�Ԫ���Ƿ�Ϊ��
	{
		int i, j;
		//ÿ���ڵ��С�����ӡ
		for (i = 0; i < node->count; i++)
		{
			//�ж��Ƿ�Ҷ�ڵ�,���ǵĻ���Ҫ���ӽڵ���Ѱ�Ҵ�ӡ
			if (node->branch[0] != NULL)//�ж��Ƿ���Ҷ�ӽڵ�
			{
				printpoint(node->branch[i], count - 3);
			}
			for (j = count; j >= 0; j--)
			{
				cout << "-";
			}
			cout << "|" << node->data[i] << "|" << endl;
		}
		if (node->branch[0] != NULL)//�ӽڵ����ȹؼ�������һ��
		{
			printpoint(node->branch[i], count - 3);
		}
	}
}



void B_tree::printpoint()
{
	cout << endl;
	cout << "**********************��ʾ����*******************" << endl;
	cout << endl;
	printpoint(root, order * 5);
	cout << endl;
}







Error_code B_tree::recursive_search_tree(B_node* current, int& target)
//current���������ݹ飬�����ǿ�ָ�����ָ��B����ĳ������/�ڵ�
//target������Ҫ���ҵ�ֵ
//����ֵ������������û�ҵ�
//���ս�������ҵ��ˣ���current��target���ڽڵ㣬position��targetֵ�ڽڵ��е�λ��
{
	Error_code result = not_present;//result��ʼ��Ϊ�Ҳ������ҵ����ٸ���
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

//������ǰ�ڵ㣬������ڵ�����û��target

Error_code B_tree::search_node(B_node* current, const int& target, int& position)
//position���������ش��ε�
//����ҵ��ˣ�position����recursive_search_tree��������target��λ�ã�������sucess�ı�ʶ
//���û�ҵ���position����recursive_search_tree��������С��target��λ�ã�������not_present�ı�ʶ
{
	position = 0;
	while (position < current->count && target > current->data[position])
		position++; //�Ȱ�position��ͷָ��target��λ�� �� ����������target��λ��
	if (position < current->count && target == current->data[position])
		return success;
	else
		return not_present;//�����˽ڵ���û��target����position��ָ����Ӧ��λ���ˣ�
}


//��new_entry��������
//�����ַ���ֵ
//success������ɹ�
//duplicate_error��ԭ�����Ѵ��ڣ�����ʧ��

Error_code B_tree::insert(const int& new_entry)
{
	int median;
	B_node* right_branch, * new_root;
	Error_code result = push_down(root, new_entry, median, right_branch);
	if (result == overflow)
		//�����󷵻ص���һ��ѹջ������Ҳ���Ǹ��ڵ�ѹ��ջ��ʱ����Ȼ��overflow��˵�����ڵ�ҲҪ���в�ֵ����
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
		//�����ǰ�����Ľڵ�Ϊ�գ��򷵻�overflow�����־
		median = new_entry;
		right_branch = NULL;
		result = overflow;
	}
	else
	{
		//����new_entry�ڵ��Ƿ��Ѿ���current�ڵ������ˣ�����Ѿ�������򷵻�duplicate_error�������������ֵ�Ѵ���
		if (search_node(current, new_entry, position) == success)
			result = duplicate_error;
		//
		else
		{
			int extra_entry;
			B_node* extra_branch;
			//�����ǵݹ�ľ�����push_down�����push_down���ݹ�������������Ľڵ���NULL������overflow�����������ĳ�ڵ��﷢���˸���ֵ�����ò����ˣ�����duplicate_error
			result = push_down(
				current->branch[position],
				new_entry,
				extra_entry,
				extra_branch);
			//��������һ��ѹջ�����ķ���ֵ��overflow����������ߵ���NULL
			//�������ص����Ǹ�ѹջ������Ӧ���ǵ����ڶ���ѹջ��������NULL�ڵ����һ���ڵ㣩�����current��������ֵӦ�ò���Ľڵ�
			if (result == overflow)
			{
				// ������ֵ���뵽Ӧ�ò��뵽�Ľڵ�����
				if (current->count < order - 1)
					//Ӧ����Ľڵ���ֵ�ĸ������С��order-1��֤����ʹ��������һ����ֵ��Ҳ���������
				{
					result = success;//���ķ���ֵΪsuccess��˵���ܳɹ�����
					push_in(current, extra_entry, extra_branch, position);//ֱ���ڸýڵ������ֵ
				}
				else
					//current�ڵ�Ҫ����
					//���ڽڵ�Ҫ���ѵĻ����Ʊػ�����һ��ѹջ������current�ڵ㣨Ҳ���ǵ�ǰ�����ѽڵ����һ���ڵ㣩����һ��ֵ
					//���Ը���һ��ѹջ�����ķ���ֵӦ����overflow�������ص��Ǹ�ѹջ�����л�Ӧ�²���һ��ֵ
					split_node(current, extra_entry, extra_branch, position, right_branch, median);
			}
		}
	}
	return result;
}


void B_tree::push_in(B_node* current, const int& entry, B_node* right_branch, int position)
//current�Ǵ�����Ľڵ�
//entry�Ǳ��²���Ľڵ��е���ֵ���������½ڵ�
//right_branch���²����ֵ�����������
//position���Σ����²����ֵ������
{
	for (int i = current->count; i > position; i--)
	{
		// Shift all later data to the right.��position�ڵط�
		current->data[i] = current->data[i - 1];
		current->branch[i + 1] = current->branch[i];
	}
	current->data[position] = entry;
	current->branch[position + 1] = right_branch;
	current->count++;
}



void B_tree::split_node(
	B_node* current, //�����ѵĽڵ�
	const int& extra_entry, // ��ֵ
	B_node* extra_branch,
	// �²����ֵ�����������
	int position,// ���������ֵ��λ��
	B_node*& right_half, // ���ѽڵ㣬��ԭ�ڵ���Ұ�ߵ���ֵ�Ž��¶���Ľڵ�right_half����
	int& median) // �ڵ��м�ֵ
{
	//��ԭ�ڵ���Ұ�ߵ���ֵ�Ž��¶���Ľڵ�right_half����
	right_half = new B_node;
	int mid = order / 2;

	// ��ʱ���м�ڵ���������
	if (position <= mid)
		//���������Ľڵ������ߣ��Ȱ�ԭ�ڵ㣨 �ؼ��ֵ���Ŀ = order-1 ���Ұ�ߵ�����ȫ���Ƶ��½ڵ���
	{
		for (int i = mid; i < order - 1; i++)
		{
			right_half->data[i - mid] = current->data[i];
			right_half->branch[i + 1 - mid] = current->branch[i + 1];
		}
		current->count = mid;
		right_half->count = order - 1 - mid;
		push_in(current, extra_entry, extra_branch, position);//�ٰ���ֵ���뵽����
	}
	else
		//���������Ľڵ����Ұ�ߣ��Ȱ�ԭ�ڵ㣨 �ؼ��ֵ���Ŀ = order-1 ���Ұ�ߵ����֣���ȥ�м��Ǹ�����Ϊ�˸��½ڵ��ڵط���ȫ���Ƶ��½ڵ���
	{
		mid++;
		for (int i = mid; i < order - 1; i++)
		{
			// Move entries to right_half .
			right_half->data[i - mid] = current->data[i];
			right_half->branch[i + 1 - mid] = current->branch[i + 1];
		}
		current->count = mid;//���µ�ǰ�ڵ�ؼ����ж���
		right_half->count = order - 1 - mid;
		push_in(right_half, extra_entry, extra_branch, position - mid);//�ٰ���ֵ���뵽�Ұ��
	}
	median = current->data[current->count - 1];
	// ���м�ֵ����ڵ�ɾ��������������ڵ�ԭ�������һ��ֵת�Ƶ�ԭ���м�ֵ�ڵĵط����и��ǣ�
	right_half->branch[0] = current->branch[current->count];
	current->count--;//���¹ؼ��ֵ���ֵ
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
			//��ɾ����ֵ��������ڵ����棬position������λ������
			result = success;
			if (current->branch[position] != NULL)
			{
				//����Ҷ�ڵ���ɾ��
				copy_in_predecessor(current, position);
				recursive_remove(current->branch[position], current->data[position]);
			}
			else
				//��Ҷ�ڵ���ɾ����ֱ��ɾ������
				remove_data(current, position);
		}
		else
			//Ҫɾ����ֵ��������ڵ���������±���
			result = recursive_remove(current->branch[position], target);

		if (current->branch[position] != NULL)
			if (current->branch[position]->count < (order - 1) / 2)//˵��ɾ��֮�󣬽ڵ�Ĺؼ������Ѿ�������Ҫ���ˣ�������Ҫ�ϲ�
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



// �����м�ڵ�������������һ���ڵ㣨����ֱ��ǰ���������
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
		// �ȿ����ֵܵ�λ�Ӷ಻�࣬�ٿ���
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




//�����ж��������������Ƿ���ȷ
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
	cleardevice(); //ÿ�β���ǰ������
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
		{ //��ʾ��ǰ�ڵ������
			wchar_t s[100];
			swprintf_s(s, _T("%d"), current->data[i]);
			int size = 0;
			while (s[size++] != 0);
			size--;
			rectangle(preCharRihgt, top, preCharRihgt + size * leng, top + wid);
			//��һ��������ʾ����
			outtextxy(preCharRihgt + 2, top + 2, s);
			//��ʾ����
			totalleng += size * leng;
			if (current->branch[i] != nullptr)
			{ //���ʵ�ǰ�ڵ�ĺ��ӽڵ�
				qBn.push(current->branch[i]); //�Ѻ��ӽڵ�������
				qLeft.push(rowLeft);
				qTop.push(top + wid + marg);
				POINT pts[] = { {preCharRihgt, top + wid}, {rowLeft, top + wid + marg} };//�����������
				polyline(pts, 2); //������
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
	
	int n, m;//n�ǹؼ��ָ�����m��B���Ľ���
	cout << "������ؼ��ָ�����B���Ľ���������һ���ո�����������磺10 3��" << endl;
	cin >> n >> m;
	order = m;

	//�ָ�������ַ�����������ת��Ϊint���ͣ�ʹ����뵽int��arr������
	char* strbuf;
	char strdelimit[] = ",";//�ָ��
	char* p;
	int* arr = new int[n + 10];
	int j = 0;

	while (true)
	{
		int judge = 1;
		cout << "���������йؼ��֣����Զ��ŷָ��������� 10,3,12,4,5��" << endl;
		char* str = new char[n * 30];
		cin >> str;
		j = 0;

		p = strtok_s(str, strdelimit, &strbuf);
		if (is_int(p))
			arr[j++] = atoi(p);
		else
		{
			cout << "�����������Ͳ���ȷ,���������룡" << endl;
			judge = 0;
			continue;
		}

		while ((p = strtok_s(NULL, strdelimit, &strbuf)) != NULL)
		{
			if (is_int(p))
				arr[j++] = atoi(p);
			else
			{
				cout << "�����������Ͳ���ȷ�����������룡" << endl;
				judge = 0;
				break;
			}
		}
		if (!(judge == 0))
			break;
	}



	//��������
	int min = j;
	if (j > n) min = n;
	B_tree bt;
	for (int i = 0; i < min; i++)
	{
		bt.insert(arr[i]);
	}
	//bt.printpoint();


	//���롢ɾ������
	while (true)
	{
		cout << endl;
		cout << "��������Ҫִ�е�ָ��,�����á�I ���֡���ɾ���á�D ���֡������������á�MI ����1,����2,����#��������ɾ���á�MD ����1,����2,����#��" << endl;
		cout << "�����硾I 76��  ��D 56��  ��MI 76, 23, 51#��  ��MD 50, 4, 14#����" << endl;
		cout << "�������˳�������������0��" << endl;
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
				cout << "���ظ��Ĺؼ���" << endl;
			}
			break;

		case 'D':
			str = &str[2];
			k = atoi(str);
			if (bt.remove(k) == not_present)
			{
				cout << "δ�ҵ���Ӧ�Ĺؼ���" << endl;
			}
			break;

		case 'M':
			if (str[1] == 'I')
				//�������
			{
				//��ȡ������ַ��������ָ���ַ��������뵽int������
				str = &str[3];
				char* strbuf;
				char strdelimit[] = ",#";//�ָ��
				char* p;
				int j = 0;
				int* arr = new int[n + 10];

				arr[j++] = atoi(strtok_s(str, strdelimit, &strbuf));
				while ((p = strtok_s(NULL, strdelimit, &strbuf)) != NULL)
				{
					arr[j++] = atoi(p);
				}

				//�������е�Ԫ�ز��뵽B����
				for (int i = 0; i < j; i++)
				{
					if (bt.insert(arr[i]) == duplicate_error)
					{
						cout << "���ظ��Ĺؼ��֣�" << arr[i] << endl;
					}
				}
			}

			if (str[1] == 'D')
				//����ɾ��
			{
				//��ȡ������ַ��������ָ���ַ��������뵽int������
				str = &str[3];
				char* strbuf;
				char strdelimit[] = ",#";//�ָ��
				char* p;
				int j = 0;
				int* arr = new int[n + 10];

				arr[j++] = atoi(strtok_s(str, strdelimit, &strbuf));
				while ((p = strtok_s(NULL, strdelimit, &strbuf)) != NULL)
				{
					arr[j++] = atoi(p);
				}

				//�������е�Ԫ�ز��뵽B����
				for (int i = 0; i < j; i++)
				{
					if (bt.remove(arr[i]) == not_present)
					{
						cout << "δ�ҵ���Ӧ�Ĺؼ��֣�" << arr[i] << endl;
					}
				}
			}
			break;


		case '0':
			return 0;
		}

		//��ʾ����
		//bt.printpoint();
		
		initgraph(640, 480, SHOWCONSOLE);
		bt.show();


	}

}


