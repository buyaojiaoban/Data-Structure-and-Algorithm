#include <iostream>
#include <vector>
#include <stdlib.h>
#include <queue>
#include <time.h>
#include <unordered_map>
#include <functional>
using namespace std;

#if 0
/*
大数据求top k问题

44 35 76 80 28 8 18 22 82 37
1.求出上面序列中值最小的前3个元素,能够在O(n)线性时间内找到top k的元素呢？
这里求最小的，需要用一个“大根堆”，堆顶元素的值是最大的
思想：把大根堆堆顶的大值不断的淘汰，放入小值

2.求出上面序列中值最大的前3个元素
用“小根堆”，堆顶元素值最小
思想：用k个元素构建小根堆，把堆顶小元素不断淘汰掉，把大元素放进来
*/



int main()
{
	vector<int> vec;
	srand(time(NULL));
	for (int i = 0; i < 1000; i++)
	{
		vec.push_back(rand() % 10000);
	}
	
	// 求vec中值最小的前5个元素
	priority_queue<int> maxheap; // 默认是个大根堆
	int k = 5;

	// 由前k个元素构建一个大根堆
	for (int i = 0; i < k; ++i)
	{
		maxheap.push(vec[i]);
	}

	// 遍历剩余的元素，直到最后
	for (int i = k; i < vec.size(); i++)
	{
		if (maxheap.top() > vec[i])
		{
			maxheap.pop();
			maxheap.push(vec[i]);
		}
	}

	// 输出结果
	while (!maxheap.empty())
	{
		cout << maxheap.top() << " ";
		maxheap.pop();
	}
	cout << endl;

	/*for (auto key : vec)
	{
		cout << key << " ";
	}
	cout << endl;*/

	// 求vec中值最大的前5个元素
	priority_queue<int,vector<int>,greater<int>> minheap; // 小根堆

	// 由前k个元素构建一个小根堆
	for (int i = 0; i < k; ++i)
	{
		minheap.push(vec[i]);
	}

	// 遍历剩余的元素，直到最后
	for (int i = k; i < vec.size(); i++)
	{
		if (minheap.top() < vec[i])
		{
			minheap.pop();
			minheap.push(vec[i]);
		}
	}

	// 输出结果
	while (!minheap.empty())
	{
		cout << minheap.top() << " ";
		minheap.pop();
	}
	cout << endl;


	return 0;
}
#endif

/*
求重复次数最大/最小的前k个数字
*/

// 查重和top k问题综合起来
int main()
{
	vector<int> vec;
	srand(time(NULL));
	for (int i = 0; i < 10000; i++)
	{
		vec.push_back(rand() % 1000);
	}

	// 统计重复次数最小的前3个数字
	int k = 3;
	unordered_map<int, int> map;
	for (auto key : vec)
	{
		map[key]++;
	}

	// 放入大根堆的时候，需要放key-value键值对
	using Type = pair<int, int>;
	using Comp = function<bool(Type&, Type&)>;
	priority_queue<Type, vector<Type>, Comp> maxheap(
		[](Type& a, Type& b)->bool {
			return a.second < b.second;
		});

	auto it = map.begin();
	for (int i = 0; i < k; i++, ++it)
	{
		maxheap.push(*it);
	}

	for (; it != map.end(); ++it)
	{
		if (maxheap.top().second > it->second)
		{
			maxheap.pop();
			maxheap.push(*it);
		}
	}

	while (!maxheap.empty())
	{
		cout << "key:" << maxheap.top().first << " cnt:" << maxheap.top().second << endl;
		maxheap.pop();
	}


	cout << endl;


	// 统计重复次数最大的前3个数字
	unordered_map<int, int> map2;
	for (auto key : vec)
	{
		map2[key]++;
	}

	// 放入小根堆的时候，需要放key-value键值对
	using Type = pair<int, int>;
	using Comp = function<bool(Type&, Type&)>;
	priority_queue<Type, vector<Type>, Comp> minheap(
		[](Type& a, Type& b)->bool {
			return a.second > b.second;
		});

	it = map2.begin();
	for (int i = 0; i < k; i++, ++it)
	{
		minheap.push(*it);
	}

	for (; it != map2.end(); ++it)
	{
		if (minheap.top().second < it->second)
		{
			minheap.pop();
			minheap.push(*it);
		}
	}

	while (!minheap.empty())
	{
		cout << "key:" << minheap.top().first << " cnt:" << minheap.top().second << endl;
		minheap.pop();
	}

	return 0;
}