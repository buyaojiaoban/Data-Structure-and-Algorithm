#include <iostream>
#include <vector>
#include <unordered_set> // 只存key
#include <unordered_map>
#include <stdlib.h>
#include <time.h>
#include <string>
using namespace std;


#if 0
int main()
{
	/*
	模拟问题，vector中放原始的数据
	*/
	vector<int> vec;
	srand(time(NULL));
	for (int i = 0; i < 10000; i++)
	{
		vec.push_back(rand() % 10000);
	}
 
	// 找第一个出现重复的数字
	unordered_set<int> s1;
	for (auto key : vec)
	{
		auto it = s1.find(key); // 哈希表查询 O(1)
		if (it == s1.end()) // 表示没有找到，key是第一次出现
		{
			s1.insert(key);
		}
		else
		{
			cout << "key:" << key << endl;
			break;
		}
	}

	
	// 找所有重复出现的数字  就不加break就行    unordered_multiset允许key重复
	/*
	unordered_set<int> s2;  不允许key重复
	for (auto key : vec)
	{
		auto it = s2.find(key); // 哈希表查询 O(1)
		if (it == s2.end()) // 表示没有找到，key是第一次出现
		{
			s2.insert(key);
		}
		else
		{
			cout << "key:" << key << endl;
		}
	}
	*/

	// 统计重复数字以及出现的次数
	unordered_map<int, int> m1;
	for (int key : vec)
	{
		/*
		// pair first second
		auto it = m1.find(key);
		if (it == m1.end())
		{
			m1.emplace(key, 1);
		}
		else
		{
			it->second += 1;
		}
		*/
		m1[key]++;
	}

	for (auto pair : m1)
	{
		if (pair.second > 1)
		{
			cout << "key:" << pair.first << " cnt:" << pair.second << endl;
		}
	}


	// 一组数据有些数字是重复的，把重复的数字过滤掉，每个数字只出现一次
	unordered_set<int> s3; // 不允许key重复，直接过滤
	for (auto key : vec)
	{
		s3.emplace(key);
	}

	return 0;
}
#endif


#if 0
int main()
{
	string src = "jjhfgiyuhtytrs"; // 有一个原始字符串，里面有重复的也有没重复的字符
	// 让你找出来第一个没有重复出现过的字符
	unordered_map<char, int> m;
	for (char ch : src)
	{
		m[ch]++;
	}

	for (char ch : src)
	{
		if (m[ch] == 1)
		{
			cout << "第一个没有重复出现过的字符是：" << ch << endl;
			return 0;
		}
	}

	cout << "所有字符都有重复出现过！" << endl;

	return 0;
}
#endif

/*
查重的面试相关问题

有两个文件分别是a和b，里面放了很多ip地址(url地址、email地址)，让你找出来两个文件重复的ip，输出出来？

===> 哈希表(没有对内存过多强调) 把a文件中所有的ip存放在一个哈希表中，然后依次遍历文件b里面的ip，每遍历一个ip，在哈希表
中搜索一下，搜到的，即是两个文件重复的ip并输出； 用到了哈希表的查询O(1)


有两个文件分别是a和b，各自存放了约1亿条ip地址，每个ip地址是4个字节，限制内存使用100M，让找出来两个文件中重复
的ip地址并输出？

1亿 = 100M   1亿个ip放入哈希表 = 100*4 *2 = 800M
采用分治思想：先把两个文件，分解成小文件；
如：a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,  b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11
然后去源文件a和b中，将ip依次读出来 % 11 得到一个桶下标,然后写入对应的小文件当中
分完后大概每一个文件有1千万个ip地址 =》 10M   存入哈希表 10M*4 *2 =80M，此时就可以放入内存中了;此时只需要a1和b1，b2和a2
查重就可以了

*/
    