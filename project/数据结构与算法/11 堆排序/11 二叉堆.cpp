#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <queue>
#include <functional>
#include <vector>
using namespace std;

/*
堆排序

优先级队列 priority_queue 底层默认是大根堆  从大到小排序

完全二叉树：最后一层的叶子节点都是靠左排列的，而且每一层的节点都是满的

大根堆和小根堆
基于二叉堆的基础，规定了当前节点和两个孩子节点值的大小关系

怎么得到第一个非叶子节点的下标？
(n-1)/2

满足 0 <= i <= (n-1)/2，n代表最后一个元素的下标。
如果arr[i] <= arr[2 * i+1] && arr[i] <= arr[2 * i+2]，就是小根堆
如果arr[i] >= arr[2 * i+1] && arr[i] >= arr[2 * i+2]，就是大根堆

大根堆：堆顶元素的值是整个序列最大的值
小根堆：堆顶元素的值是整个序列最小的值

入堆上浮，出堆下沉


*/
priority_queue<int, vector<int>, greater<int>> pque;

// 优先级队列实现  push pop top empty size
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
	// 入堆操作
	void push(int val)
	{
		// 判断扩容
		if (size_ == cap_)
		{
			int* p = new int[2 * cap_];
			memcpy(p, que_, cap_ * sizeof(int)); // 这里只是整数，可以用内存拷贝，但如果是对象还有外部资源，就不行
			delete[]que_;
			que_ = p;
			cap_ *= 2;
		}

		if (size_ == 0) // 表示原来堆里面是空的
		{
			// 只有一个元素，不用进行堆的上浮调整
			que_[size_] = val;
		}
		else
		{
			// 堆里面有多个元素，需要进行上浮调整
			siftUp(size_, val);
		}
		size_++;
	}

	// 出堆操作
	void pop()
	{
		if (size_ == 0)
			throw "container is empty!";

		size_--;
		if (size_ > 0)
		{
			// 删除堆顶元素后，还有剩余元素，要进行堆的下沉调整
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
	// 入堆上浮调整  O(logn)     空间复杂度：O(1)
	void siftUp(int i, int val)
	{
		while (i > 0) // 最多计算到根节点(0号位节点)
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
		// 把val放到i的位置
		que_[i] = val;
	}

	// 出堆下沉调整  O(logn)
	void siftDown(int i, int val)
	{
		// i下沉不能超过最后一个有孩子的节点
		while (i <= size_ / 2 - 1)
		{
			int child = 2 * i + 1; // 第i个节点的左孩子
			if (child + 1 < size_ && comp_(que_[child + 1], que_[child]))
			{
				child = child + 1; // 如果i节点右孩子的值大于左孩子，child记录右孩子的下标
			}

			if (comp_(que_[child], val))
			{
				que_[i] = que_[child];
				i = child;
			}
			else
			{
				break; // 已经满足堆的性质，提前结束
			}
		}
		que_[i] = val;
	}
private:
	int* que_; // 指向动态扩容的数组
	int size_; // 数组元素的个数
	int cap_; // 数组的总空间大小
	Comp comp_; // 比较器对象
};


int main()
{
	//PriorityQueue que; // 基于大根堆实现的优先级队列
	// 基于小根堆实现的优先级队列
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