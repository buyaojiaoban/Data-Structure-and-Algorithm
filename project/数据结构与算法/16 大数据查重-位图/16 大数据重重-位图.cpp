#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <memory>
using namespace std;


/*
位图法：
就是用一个位（0或者1）来存储数据的状态，比较适合状态简单，数据量比较大，要求内存使用率低的问题场景


面试问题：
有1亿个整数，最大值不超过1亿，问都有哪些元素重复了？谁是第一个重复的？谁是第一个不重复的？ 内存限制100M

=>哈希表的话 1亿 = 100M 哈希表存储-》100*4 *2 = 800M

位图算法： bitmap位图数组
7 8 12 15 16 19
1.需要知道元素序列的最大值，根据最大值来定义bitmap位图数组 char bitmap[19/8 +1] //[3]
2.根据 / %两个操作，映射到元素对应的位
3.读取该位的值 0表示没出现过 1表示出现过了
如何获取该位的值， bitmap[index] & (1 << offset)
如何把这个位置置成1  bitmap[index] | (1<<offset)

int bitmap[1亿/32 +1] 3.2M*4

谁是第一个不重复的？
原来1个位保存数据的状态，现在用两个位保存  但不好做


缺陷：int 上限值是20亿左右      unsigned int 上限值40亿左右
1 3 1000000000
现在只有三个值，但是用位图数组，int bitmap[1000000000/32 +1]  30*4M
哈希表的话 -> 3*4 *2 = 24byte

位图算法推荐的数据序列：数据的个数 >= 序列里面数字的最大值相当
*/

int main()
{
	vector<int> vec{ 12,78,12,90,123,90,8,9 };

	// 定义位图数组
	
	//先要知道最大值
	int max = vec[0];
	for (int i = 1; i < vec.size(); i++) // O(n)
	{
		if (vec[i] > max)
			max = vec[i];
	}


	int* bitmap = new int[max / 32 + 1](); // 所有元素都要初始化0
	unique_ptr<int> ptr(bitmap);

	// 找第一个重复出现的数字
	for (auto key : vec)
	{
		int index = key / 32;
		int offset = key % 32;

		// 取key对应的位的值
		if (0 == (bitmap[index] & (1 << offset)))
		{
			// 表示key没有出现过
			bitmap[index] |= (1 << offset);
		}
		else
		{
			/*
			cout << key << "是第一个重复出现的数字" << endl;
			return 0;
			*/
			cout << key << "重复出现过！" << endl;
		}
	}

	return 0;
}