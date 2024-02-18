#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <queue>
#include <functional>
#include <vector>
using namespace std;

/*
������

���ȼ����� priority_queue �ײ�Ĭ���Ǵ����  �Ӵ�С����

��ȫ�����������һ���Ҷ�ӽڵ㶼�ǿ������еģ�����ÿһ��Ľڵ㶼������

����Ѻ�С����
���ڶ���ѵĻ������涨�˵�ǰ�ڵ���������ӽڵ�ֵ�Ĵ�С��ϵ

��ô�õ���һ����Ҷ�ӽڵ���±ꣿ
(n-1)/2

���� 0 <= i <= (n-1)/2��n�������һ��Ԫ�ص��±ꡣ
���arr[i] <= arr[2 * i+1] && arr[i] <= arr[2 * i+2]������С����
���arr[i] >= arr[2 * i+1] && arr[i] >= arr[2 * i+2]�����Ǵ����

����ѣ��Ѷ�Ԫ�ص�ֵ��������������ֵ
С���ѣ��Ѷ�Ԫ�ص�ֵ������������С��ֵ

����ϸ��������³�


*/
priority_queue<int, vector<int>, greater<int>> pque;

// ���ȼ�����ʵ��  push pop top empty size
class PriorityQueue
{
public:
	using Comp = function<bool(int, int)>;
	PriorityQueue(int cap = 20, Comp comp = greater<int>())
		: size_(0)
		, cap_(cap)
		, comp_(comp)
	{
		que_ = new int[cap_];
	}

	PriorityQueue(Comp comp)
		: size_(0)
		, cap_(20)
		, comp_(comp)
	{
		que_ = new int[cap_];
	}

	~PriorityQueue()
	{
		delete[]que_;
		que_ = nullptr;
	}

public:
	// ��Ѳ���
	void push(int val)
	{
		// �ж�����
		if (size_ == cap_)
		{
			int* p = new int[2 * cap_];
			memcpy(p, que_, cap_ * sizeof(int)); // ����ֻ���������������ڴ濽����������Ƕ������ⲿ��Դ���Ͳ���
			delete[]que_;
			que_ = p;
			cap_ *= 2;
		}

		if (size_ == 0) // ��ʾԭ���������ǿյ�
		{
			// ֻ��һ��Ԫ�أ����ý��жѵ��ϸ�����
			que_[size_] = val;
		}
		else
		{
			// �������ж��Ԫ�أ���Ҫ�����ϸ�����
			siftUp(size_, val);
		}
		size_++;
	}

	// ���Ѳ���
	void pop()
	{
		if (size_ == 0)
			throw "container is empty!";

		size_--;
		if (size_ > 0)
		{
			// ɾ���Ѷ�Ԫ�غ󣬻���ʣ��Ԫ�أ�Ҫ���жѵ��³�����
			siftDown(0, que_[size_]);
		}
	}

	bool empty() const { return size_ == 0; }

	int top() const 
	{
		if (size_ == 0)
			throw "container is empty!";
		return que_[0];
	}

	int size() const { return size_; }
private:
	// ����ϸ�����  O(logn)     �ռ临�Ӷȣ�O(1)
	void siftUp(int i, int val)
	{
		while (i > 0) // �����㵽���ڵ�(0��λ�ڵ�)
		{
			int father = (i - 1) / 2;
			if (comp_(val, que_[father]))
			{
				que_[i] = que_[father];
				i = father;
			}
			else
			{
				break;
			}
		}
		// ��val�ŵ�i��λ��
		que_[i] = val;
	}

	// �����³�����  O(logn)
	void siftDown(int i, int val)
	{
		// i�³����ܳ������һ���к��ӵĽڵ�
		while (i <= size_ / 2 - 1)
		{
			int child = 2 * i + 1; // ��i���ڵ������
			if (child + 1 < size_ && comp_(que_[child + 1], que_[child]))
			{
				child = child + 1; // ���i�ڵ��Һ��ӵ�ֵ�������ӣ�child��¼�Һ��ӵ��±�
			}

			if (comp_(que_[child], val))
			{
				que_[i] = que_[child];
				i = child;
			}
			else
			{
				break; // �Ѿ�����ѵ����ʣ���ǰ����
			}
		}
		que_[i] = val;
	}
private:
	int* que_; // ָ��̬���ݵ�����
	int size_; // ����Ԫ�صĸ���
	int cap_; // ������ܿռ��С
	Comp comp_; // �Ƚ�������
};


int main()
{
	//PriorityQueue que; // ���ڴ����ʵ�ֵ����ȼ�����
	// ����С����ʵ�ֵ����ȼ�����
	PriorityQueue que([](int a, int b) {return a < b; });
	//PriorityQueue que(20, less<int>());
	srand(time(NULL));

	for (int i = 0; i < 10; ++i)
	{
		que.push(rand() % 100);
	}

	while (!que.empty())
	{
		cout << que.top() << " ";
		que.pop();
	}
	cout << endl;



	for (int i = 0; i < 10; ++i)
	{
		pque.push(rand() % 100);
	}

	while (!pque.empty())
	{
		cout << pque.top() << " ";
		pque.pop();
	}
	cout << endl;
	return 0;
}