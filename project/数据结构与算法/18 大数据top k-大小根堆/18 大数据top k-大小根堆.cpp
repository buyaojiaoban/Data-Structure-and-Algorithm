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
��������top k����

44 35 76 80 28 8 18 22 82 37
1.�������������ֵ��С��ǰ3��Ԫ��,�ܹ���O(n)����ʱ�����ҵ�top k��Ԫ���أ�
��������С�ģ���Ҫ��һ��������ѡ����Ѷ�Ԫ�ص�ֵ������
˼�룺�Ѵ���ѶѶ��Ĵ�ֵ���ϵ���̭������Сֵ

2.�������������ֵ����ǰ3��Ԫ��
�á�С���ѡ����Ѷ�Ԫ��ֵ��С
˼�룺��k��Ԫ�ع���С���ѣ��ѶѶ�СԪ�ز�����̭�����Ѵ�Ԫ�طŽ���
*/



int main()
{
	vector<int> vec;
	srand(time(NULL));
	for (int i = 0; i < 1000; i++)
	{
		vec.push_back(rand() % 10000);
	}
	
	// ��vec��ֵ��С��ǰ5��Ԫ��
	priority_queue<int> maxheap; // Ĭ���Ǹ������
	int k = 5;

	// ��ǰk��Ԫ�ع���һ�������
	for (int i = 0; i < k; ++i)
	{
		maxheap.push(vec[i]);
	}

	// ����ʣ���Ԫ�أ�ֱ�����
	for (int i = k; i < vec.size(); i++)
	{
		if (maxheap.top() > vec[i])
		{
			maxheap.pop();
			maxheap.push(vec[i]);
		}
	}

	// ������
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

	// ��vec��ֵ����ǰ5��Ԫ��
	priority_queue<int,vector<int>,greater<int>> minheap; // С����

	// ��ǰk��Ԫ�ع���һ��С����
	for (int i = 0; i < k; ++i)
	{
		minheap.push(vec[i]);
	}

	// ����ʣ���Ԫ�أ�ֱ�����
	for (int i = k; i < vec.size(); i++)
	{
		if (minheap.top() < vec[i])
		{
			minheap.pop();
			minheap.push(vec[i]);
		}
	}

	// ������
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
���ظ��������/��С��ǰk������
*/

// ���غ�top k�����ۺ�����
int main()
{
	vector<int> vec;
	srand(time(NULL));
	for (int i = 0; i < 10000; i++)
	{
		vec.push_back(rand() % 1000);
	}

	// ͳ���ظ�������С��ǰ3������
	int k = 3;
	unordered_map<int, int> map;
	for (auto key : vec)
	{
		map[key]++;
	}

	// �������ѵ�ʱ����Ҫ��key-value��ֵ��
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


	// ͳ���ظ���������ǰ3������
	unordered_map<int, int> map2;
	for (auto key : vec)
	{
		map2[key]++;
	}

	// ����С���ѵ�ʱ����Ҫ��key-value��ֵ��
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