#include <iostream>
#include "stringhash.h"
#include <vector>
#include <string>
using namespace std;


/*
Bloom Filter = 位数组 + K个哈希函数
增加一个元素：
1.经过k个哈希函数计算，得到bitmap位数组里面的一组位的序号
2.把相应的位置成1

搜索一个元素：
1.经过k个哈希函数计算，得到bitmap位数组里面的一组位的序号
2.判断上面几个位置的值，如果全是1，证明相应的key存在，如果有一个是0，则证明key不在bloom filter中

Bloom Filter能提供删除操作吗？ 没有提供
不可以，由于产生哈希冲突，可能不同key共用一个或者多个位，删除的话，会导致其他key无法判断存在。

Bloom Filter查询一个key值是否存在，如果查出来key经过k个哈希函数处理后，对应的位都是1，能说明这个key存在吗？
Bloom Filter说数据在，其实数据不一定在！！！  会存在误判！！！
如果Bloom Filter说数据不在，那么数据肯定是不存在的！！！ 肯定的！！！


错误率和 位数组大小和哈希函数的个数有关系


应用场景一：提示过滤一些非法的网站，或者钓鱼网站等等
浏览器 https://www.xxx.com/ ，浏览器可能就会提示非法网站
Bloom Filter：把所有可能怀疑有问题的网站的URL添加到布隆过滤器当中；当要访问的时候首先，会去查找当前访问的
网址URL是否在黑名单中；如果存在(有误判率)，会进行提示当前网站有风险，禁止访问！
如果URL不存在，那肯定是白名单上的合法的网站，直接访问！

场景二：redis缓存中的应用
拿着key去redis缓存层中查key到底在不在，而且效率要求高，最好还省内存
Bloom Filter     setBit(key)     getBit(key) => key不存在 => 直接去DB里面查数据 => 缓存redis => 返回
getBit(key) => key存在 => redis中找key (有极低的概率，找不到，就去DB中找，误判)
*/

// 布隆过滤器实现
class BloomFilter
{
public:
	BloomFilter(int bitSize = 1471)
		: bitSize_(bitSize)
	{
		bitMap_.resize(bitSize_ / 32 + 1);
	}

public:
	// 添加元素   O(1)
	void setBit(const char* str)
	{
		// 计算k组哈希函数的值
		int idx1 = BKDRHash(str) % bitSize_;
		int idx2 = RSHash(str) % bitSize_;
		int idx3 = APHash(str) % bitSize_;
	
		// 把相应的idx1 idx2 idx3 这几个位全部置1
		int index = 0;
		int offset = 0;

		index = idx1 / 32;
		offset = idx1 % 32;
		bitMap_[index] |= (1 << offset);

		index = idx2 / 32;
		offset = idx2 % 32;
		bitMap_[index] |= (1 << offset);

		index = idx3 / 32;
		offset = idx3 % 32;
		bitMap_[index] |= (1 << offset);
	}

	// 查询元素  O(1)
	bool getBit(const char* str)
	{
		// 计算k组哈希函数的值
		int idx1 = BKDRHash(str) % bitSize_;
		int idx2 = RSHash(str) % bitSize_;
		int idx3 = APHash(str) % bitSize_;

		int index = 0;
		int offset = 0;

		index = idx1 / 32;
		offset = idx1 % 32;
		if (0 == (bitMap_[index] & (1 << offset)))
		{
			return false;
		}

		index = idx2 / 32;
		offset = idx2 % 32;
		if (0 == (bitMap_[index] & (1 << offset)))
		{
			return false;
		}

		index = idx3 / 32;
		offset = idx3 % 32;
		if (0 == (bitMap_[index] & (1 << offset)))
		{
			return false;
		}

		return true;
	}
private:
	int bitSize_; // 位图的长度
	vector<int> bitMap_; // 位图数组
};

// URL黑名单
class BlackList
{
public:
	void add(string url)
	{
		blackList_.setBit(url.c_str());
	}

	bool query(string url)
	{
		return blackList_.getBit(url.c_str());
	}
private:
	BloomFilter blackList_;
};

int main()
{
	BlackList list;
	list.add("http://www.baidu.com");
	list.add("http://www.tmall.com");
	list.add("http://www.tencent.com");
	list.add("http://www.jd.com");

	string url = "http://www.alibaba.com";
	cout << list.query(url) << endl;

	return 0;
}