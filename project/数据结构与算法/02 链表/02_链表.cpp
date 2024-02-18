#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

// �ڵ�����
struct Node
{
	Node(int data = 0) : data_(data), next_(nullptr) {}
	int data_;
	Node* next_;
};

// ���������ʵ��
class Clink
{
public:
	Clink()
	{
		// ��head_��ʼ��ָ��ͷ�ڵ�
		head_ = new Node();
	}
	~Clink()
	{
		// �ڵ���ͷ�
		Node* p = head_;
		while (p != nullptr)
		{
			head_ = head_->next_;
			delete p;
			p = head_;
		}
		head_ = nullptr;
	}
public:
	// ����β�巨 O(n)
	void inserTail(int val)
	{
		// ���ҵ���ǰ�����ĩβ�ڵ�
		Node* p = head_;
		while (p->next_ != nullptr)
		{
			p = p->next_;
		}

		// �����½ڵ�
		Node* node = new Node(val);
		// ���½ڵ�ĵ�ַ����ĩβ�ڵ�ĵ�ַ��
		p->next_ = node;
	}
	// �����ͷ�巨 O(1)
	void inserHead(int val)
	{
		// �����½ڵ�
		Node* node = new Node(val);
		// ����Ԫ��
		node->next_ = head_->next_;
		head_->next_ = node;
	}
	// ����ڵ��ɾ��
	void Remove(int val) // ɾ��ֵΪval�ĵ�һ���ڵ�
	{
		// ������������Ϊval�Ľڵ�
		Node* q = head_;
		Node* p = head_->next_;
		while (p != nullptr)
		{
			if (p->data_ == val)
			{
				q->next_ = p->next_;
				delete p;
				return;
			}
			else 
			{
				q = p;
				p = p->next_;
			}
		}
	}
	// ɾ������ڵ�
	void RemoveAll(int val)
	{
		Node* q = head_;
		Node* p = head_->next_;
		while (p != nullptr)
		{
			if (p->data_ == val)
			{
				q->next_ = p->next_;
				delete p;
				// ��ָ��p��������
				p = q->next_;
			}
			else
			{
				q = p;
				p = p->next_;
			}
		}
	}
	// ����  O(n)
	bool Find(int val)
	{
		Node* p = head_->next_;
		while (p != nullptr)
		{
			if (p->data_ == val)
			{
				return true;
			}
			else
			{
				p = p->next_;
			}
		}
		return false;
	}
	// �����ӡ
	void show()
	{
		Node* p = head_->next_;
		while (p != nullptr)
		{
			cout << p->data_ << " ";
			p = p->next_;
		}
		cout << endl;
	}
private:
	Node* head_; //ָ�������ͷ�ڵ�

	friend void ReverseLink(Clink& link); //������Ԫ�������÷���head_ͷ�ڵ�
	friend bool GetLastkKNode(Clink& link, int k, int& val);
	friend void MergeLink(Clink& link1, Clink& link2);

};

// ����������
void ReverseLink(Clink &link)
{
	Node* head = link.head_;
	Node* p = head->next_;
	if (p == nullptr)
	{
		return;
	}

	head->next_ = nullptr; // ��ͷ�ڵ��ÿ�

	while (p != nullptr)
	{
		Node* q = p->next_;

		// pָ��ָ��Ľڵ����ͷ��
		p->next_ = head->next_;
		head->next_ = p;

		p = q;
	}
}

// ������k���ڵ��ֵ
bool GetLastkKNode(Clink& link, int k, int& val)
{
	Node* head = link.head_;
	Node* pre = head;
	Node* p = head;

	if (k < 1)
	{
		return false;
	}

	for (int i = 0; i < k; i++)
	{
		p = p->next_;
		if (p == nullptr)
		{
			return false;
		}
	}

	// pre��ͷ�ڵ㣬p��������k���ڵ�
	while (p != nullptr)
	{
		pre = pre->next_;
		p = p->next_;
	}

	val = pre->data_;
	return true;
}

// �ϲ�������������
void MergeLink(Clink& link1, Clink& link2)
{
	Node* p = link1.head_->next_;
	Node* q = link2.head_->next_;
	Node* last = link1.head_;
	link2.head_->next_ = nullptr; // �ڶ��������ܷ�����

	while (p != nullptr && q != nullptr)
	{
		if (p->data_ < q->data_)
		{
			last->next_ = p;
			p = p->next_;
			last = last->next_;
		}
		else
		{
			last->next_ =q;
			q = q->next_;
			last = last->next_;
		}
	}
	if (p != nullptr)
	{
		last->next_ = p;
	}
	else
	{
		last->next_ = q;
	}
}

// �������Ƿ���ڻ��� �ҳ�������ڽڵ�   ˫ָ���Ӧ��-����ָ��
bool IsLinkHasCircle(Node* head, int& val)
{
/* �ӣ��ʻ᲻�����ÿ��fast��������slow��һ����Ȼ�����Խ��ȥ�ˣ��޷��ж�����أ� ���������������
//  O  O
//  O     O     ��ʱ��߳��ְ���Խ��ȥ��״����ֻ���������Ѿ����������ˣ����Ը��������ܡ�*/
	Node* fast = head;
	Node* slow = head;

	while (fast != nullptr && fast->next_ != nullptr)
	{
		slow = slow->next_;
		fast = fast->next_->next_;

		if (slow == fast)
		{
			// ����ָ���ٴ�������������ڻ�
			fast = head;
			while (fast != slow) // ��ʱ�ж����л����������Ͳ���ʲô����ָ���ˣ�������ָͨ��
			{
				slow = slow->next_;
				fast = fast->next_;
			}
			val = slow->data_;
			return true;
		}
	}
	return false;
}

// �ж������������Ƿ��ཻ�������ཻ�Ľڵ��ֵ
bool IsLinkHasMerge(Node* head1, Node* head2, int& val)
{
	int cnt1 = 0, cnt2 = 0;
	Node* p = head1->next_;
	Node* q = head2->next_;

	while (p != nullptr)
	{
		cnt1++;
		p = p->next_;
	}

	while (q != nullptr)
	{
		cnt2++;
		q = q->next_;
	}

	p = head1;
	q = head2;
	if (cnt1 > cnt2)
	{
		// ��һ������
		int offset = cnt1 - cnt2;
		while(offset-- > 0)
		{
			p = p->next_;
		}
	}
	else
	{
		// �ڶ�������
		int offset = cnt2 - cnt1;
		while (offset-- > 0)
		{
			q = q->next_;
		}
	}

	while (p != nullptr && q != nullptr)
	{
		if (p == q)
		{
			val = p->data_;
			return true;
		}
		p = p->next_;
		q = q->next_;
	}

	return false;
}

#if 0
// �ж������������Ƿ��ཻ�������ཻ�Ľڵ��ֵ ���Ժ���
int main()
{
	Node head1;
	Node n1(25), n2(67), n3(32), n4(18);
	head1.next_ = &n1;
	n1.next_ = &n2;
	n2.next_ = &n3;
	n3.next_ = &n4;
	
	Node head2;
	Node n5(31);
	head2.next_ = &n5;
	n5.next_ = &n3;

	int val;
	if (IsLinkHasMerge(&head1, &head2, val))
	{
		cout << "�����ཻ���ཻ�ڵ��ֵ�ǣ�" << val << endl;
	}
	return 0;
}
#endif

#if 0
// �������Ƿ���ڻ��� �ҳ�������ڽڵ� ���Ժ���
int main()
{
	Node head;

	Node n1(25), n2(67), n3(32), n4(18);
	head.next_ = &n1;
	n1.next_ = &n2;
	n2.next_ = &n3;
	n3.next_ = &n4;
	n4.next_ = &n2;

	int val;
	if (IsLinkHasCircle(&head, val))
	{
		cout << "������ڻ���������ڽڵ��ǣ�" << val << endl;
	}
	return 0;
}
#endif

#if 0
// �ϲ�������������  ���Ժ���
int main()
{
	int arr1[] = { 25, 37, 52, 78,88,92,98,108 };
	int arr2[] = { 13,23,40,56,62,77,109 };

	Clink link1;
	Clink link2;

	for (int v : arr1)
	{
		link1.inserTail(v);
	}
	for (int v : arr2)
	{
		link2.inserTail(v);
	}

	link1.show();
	link2.show();

	MergeLink(link1, link2);
	link1.show();
	link2.show();

	return 0;
}
#endif

#if 0
// ���������� ������k���ڵ��ֵ  ���Ժ���
int main()
{
	Clink link;
	srand(time(0));
	for (int i = 0; i < 10; i++)
	{
		int val = rand() % 100;
		link.inserHead(val);
	}
	link.show();

	ReverseLink(link);
	link.show();

	int kval;
	int k = 7;
	if (GetLastkKNode(link, k, kval))
	{
		cout << "������" << k << "���ڵ��ֵ��" << kval << endl;
	}
}
#endif

#if 0
int main()
{
	Clink link;
	srand(time(0));
	for (int i = 0; i < 10; i++)
	{
		int val = rand() % 100;
		//link.inserTail(val);
		link.inserHead(val);
		cout << val << " ";
	}
	cout << endl;
	link.inserTail(66);
	link.inserHead(33);
	link.inserHead(66);
	link.inserHead(77);
	link.show();

	link.RemoveAll(66);
	link.show();

	return 0;
}
#endif