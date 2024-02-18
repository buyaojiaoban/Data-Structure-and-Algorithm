#include <iostream>
#include "stringhash.h"
#include <vector>
#include <string>
using namespace std;


/*
Bloom Filter = λ���� + K����ϣ����
����һ��Ԫ�أ�
1.����k����ϣ�������㣬�õ�bitmapλ���������һ��λ�����
2.����Ӧ��λ�ó�1

����һ��Ԫ�أ�
1.����k����ϣ�������㣬�õ�bitmapλ���������һ��λ�����
2.�ж����漸��λ�õ�ֵ�����ȫ��1��֤����Ӧ��key���ڣ������һ����0����֤��key����bloom filter��

Bloom Filter���ṩɾ�������� û���ṩ
�����ԣ����ڲ�����ϣ��ͻ�����ܲ�ͬkey����һ�����߶��λ��ɾ���Ļ����ᵼ������key�޷��жϴ��ڡ�

Bloom Filter��ѯһ��keyֵ�Ƿ���ڣ���������key����k����ϣ��������󣬶�Ӧ��λ����1����˵�����key������
Bloom Filter˵�����ڣ���ʵ���ݲ�һ���ڣ�����  ��������У�����
���Bloom Filter˵���ݲ��ڣ���ô���ݿ϶��ǲ����ڵģ����� �϶��ģ�����


�����ʺ� λ�����С�͹�ϣ�����ĸ����й�ϵ


Ӧ�ó���һ����ʾ����һЩ�Ƿ�����վ�����ߵ�����վ�ȵ�
����� https://www.xxx.com/ ����������ܾͻ���ʾ�Ƿ���վ
Bloom Filter�������п��ܻ������������վ��URL��ӵ���¡���������У���Ҫ���ʵ�ʱ�����ȣ���ȥ���ҵ�ǰ���ʵ�
��ַURL�Ƿ��ں������У��������(��������)���������ʾ��ǰ��վ�з��գ���ֹ���ʣ�
���URL�����ڣ��ǿ϶��ǰ������ϵĺϷ�����վ��ֱ�ӷ��ʣ�

��������redis�����е�Ӧ��
����keyȥredis������в�key�����ڲ��ڣ�����Ч��Ҫ��ߣ���û�ʡ�ڴ�
Bloom Filter     setBit(key)     getBit(key) => key������ => ֱ��ȥDB��������� => ����redis => ����
getBit(key) => key���� => redis����key (�м��͵ĸ��ʣ��Ҳ�������ȥDB���ң�����)
*/

// ��¡������ʵ��
class BloomFilter
{
public:
	BloomFilter(int bitSize = 1471)
		: bitSize_(bitSize)
	{
		bitMap_.resize(bitSize_ / 32 + 1);
	}

public:
	// ���Ԫ��   O(1)
	void setBit(const char* str)
	{
		// ����k���ϣ������ֵ
		int idx1 = BKDRHash(str) % bitSize_;
		int idx2 = RSHash(str) % bitSize_;
		int idx3 = APHash(str) % bitSize_;
	
		// ����Ӧ��idx1 idx2 idx3 �⼸��λȫ����1
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

	// ��ѯԪ��  O(1)
	bool getBit(const char* str)
	{
		// ����k���ϣ������ֵ
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
	int bitSize_; // λͼ�ĳ���
	vector<int> bitMap_; // λͼ����
};

// URL������
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