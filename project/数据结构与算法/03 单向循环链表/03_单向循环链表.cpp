#include <iostream>
using namespace std;

// 单项循环链表
class CircleLink
{
public:
	CircleLink()
	{
		head_ = new Node();
		tail_ = head_;
		head_->next_ = head_;
	}
	~CircleLink()
	{
		Node* p = head_->next_;
		while (p != head_)
		{
			head_->next_ = p->next_;
			delete p;
			p = head_->next_;
		}
		delete head_;
	}

public:
	// 尾插法  O(1)
	void InsertTail(int val)
	{
		Node* node = new Node(val);
		node->next_ = tail_->next_; // node->next_ = head_;
		tail_->next_ = node;
		tail_ = node; // 更新tail_指针指向新的尾节点
	}

	// 头插法
	void InserHead(int val)
	{
		Node* node = new Node(val);
		node->next_ = head_->next_;
		head_->next_ = node;
		if (node->next_ == head_)
		{
			tail_ = node;
		}
	}

private:
	struct Node
	{
		Node(int data = 0) :data_(data), next_(nullptr) {}
		int data_;
		Node* next_;
	};

	Node* head_; // 指向头节点
	Node* tail_; // 指向末尾节点
};
int main()
{

	return 0;
}