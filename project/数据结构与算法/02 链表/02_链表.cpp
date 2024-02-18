#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

// 节点类型
struct Node
{
	Node(int data = 0) : data_(data), next_(nullptr) {}
	int data_;
	Node* next_;
};

// 单链表代码实现
class Clink
{
public:
	Clink()
	{
		// 给head_初始化指向头节点
		head_ = new Node();
	}
	~Clink()
	{
		// 节点的释放
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
	// 链表尾插法 O(n)
	void inserTail(int val)
	{
		// 先找到当前链表的末尾节点
		Node* p = head_;
		while (p->next_ != nullptr)
		{
			p = p->next_;
		}

		// 生成新节点
		Node* node = new Node(val);
		// 把新节点的地址放入末尾节点的地址域
		p->next_ = node;
	}
	// 链表的头插法 O(1)
	void inserHead(int val)
	{
		// 生成新节点
		Node* node = new Node(val);
		// 插入元素
		node->next_ = head_->next_;
		head_->next_ = node;
	}
	// 链表节点的删除
	void Remove(int val) // 删除值为val的第一个节点
	{
		// 先搜索数据域为val的节点
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
	// 删除多个节点
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
				// 对指针p进行重置
				p = q->next_;
			}
			else
			{
				q = p;
				p = p->next_;
			}
		}
	}
	// 搜索  O(n)
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
	// 链表打印
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
	Node* head_; //指向链表的头节点

	friend void ReverseLink(Clink& link); //定义友元函数，好访问head_头节点
	friend bool GetLastkKNode(Clink& link, int k, int& val);
	friend void MergeLink(Clink& link1, Clink& link2);

};

// 单链表逆序
void ReverseLink(Clink &link)
{
	Node* head = link.head_;
	Node* p = head->next_;
	if (p == nullptr)
	{
		return;
	}

	head->next_ = nullptr; // 把头节点置空

	while (p != nullptr)
	{
		Node* q = p->next_;

		// p指针指向的节点进行头插
		p->next_ = head->next_;
		head->next_ = p;

		p = q;
	}
}

// 求倒数第k个节点的值
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

	// pre在头节点，p在正数第k个节点
	while (p != nullptr)
	{
		pre = pre->next_;
		p = p->next_;
	}

	val = pre->data_;
	return true;
}

// 合并两个有序单链表
void MergeLink(Clink& link1, Clink& link2)
{
	Node* p = link1.head_->next_;
	Node* q = link2.head_->next_;
	Node* last = link1.head_;
	link2.head_->next_ = nullptr; // 第二个链表不能访问了

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

// 单链表是否存在环？ 找出环的入口节点   双指针的应用-快慢指针
bool IsLinkHasCircle(Node* head, int& val)
{
/* 坑：问会不会存在每次fast走两步，slow走一步，然后把它越过去了，无法判断相等呢？ 问题根本就有问题
//  O  O
//  O     O     此时左边出现把他越过去的状况，只有在它们已经相遇过后了，所以根本不可能。*/
	Node* fast = head;
	Node* slow = head;

	while (fast != nullptr && fast->next_ != nullptr)
	{
		slow = slow->next_;
		fast = fast->next_->next_;

		if (slow == fast)
		{
			// 快慢指针再次遇见，链表存在环
			fast = head;
			while (fast != slow) // 此时判断了有环，这两个就不是什么快慢指针了，就是普通指针
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

// 判断两个单链表是否相交，返回相交的节点的值
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
		// 第一个链表长
		int offset = cnt1 - cnt2;
		while(offset-- > 0)
		{
			p = p->next_;
		}
	}
	else
	{
		// 第二个链表长
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
// 判断两个单链表是否相交，返回相交的节点的值 测试函数
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
		cout << "链表相交，相交节点的值是：" << val << endl;
	}
	return 0;
}
#endif

#if 0
// 单链表是否存在环？ 找出环的入口节点 测试函数
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
		cout << "链表存在环，环的入口节点是：" << val << endl;
	}
	return 0;
}
#endif

#if 0
// 合并两个有序单链表  测试函数
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
// 单链表逆序 求倒数第k个节点的值  测试函数
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
		cout << "倒数第" << k << "个节点的值：" << kval << endl;
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