#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;


/*
����̽���ϣ���ȱ�ݣ�
1.������ϣ��ͻʱ��һ��һ������һ�����е�λ�ã��������������������O(n)ʱ�临�Ӷȣ��洢�����ˣ�������ѯɾ����������
������ϣ��ͻԽ���أ���Խ����O(n)ʱ�临�Ӷȡ�
�ܷ��Ż��أ�  ������̽�����治���Ż�
2.���̻߳����У��̰߳�ȫ���⣬����̽�����õ��Ļ�������ʵ�ֵĹ�ϣ��ֻ�ܸ�ȫ�ֵı��û���������֤��ϣ���ԭ�Ӳ�������֤
�̰߳�ȫ��
��ʽ��ϣ���ڶ��̻߳����£����Բ��÷ֶε������ȱ�֤���̰߳�ȫ������һ���Ĳ������������Ч�ʣ�

����̽����һ���Ż�������̽�⣬�����ұ���һ�Σ������һ�Σ����ұ�

��ʽ��ϣ������  vector<list<int>> table;
װ�����ӣ���ϣ����Ͱ��ռ��һ���ı����󣬾�Ҫ����������

��ϣ����ɾ�飺����������O(1)����Ϊ��ϣ��ͻ�Ĵ���

��ʽ��ϣ��
�Ż�һ���������ȴ���ĳ��ָ����ֵ��ʱ�򣬰�Ͱ������������ת���ɺ���� O(logn)
�Ż�������ʽ��ϣ��ÿ��Ͱ�����Դ����Լ��Ļ���������ͬͰ�е�������������Բ���ִ��������

*/

// ��ʽ��ϣ��
class HashTable
{
public:
	HashTable(int size = primes_[0], double loadFactor = 0.75)
		: useBucketNum_(0)
		, loadFactor_(loadFactor)
		, primeIdx_(0)
	{
		if (size != primes_[0])
		{
			for (; primeIdx_ < PRIME_SIZE; primeIdx_++)
			{
				if (primes_[primeIdx_] >= size)
					break;
			}

			if (primeIdx_ == PRIME_SIZE)
			{
				primeIdx_--;
			}
		}

		table_.resize(primes_[primeIdx_]); // resize�������ٿռ䣬���ᴴ��Ԫ��
	}

public:
	// ����Ԫ�� �����ظ�����key
	void insert(int key)
	{
		// �ж�����
		double factor = useBucketNum_ * 1.0 / table_.size();
		cout << "factor:" << factor << endl;
		if (factor > loadFactor_) // ����װ�����ӣ�����
		{
			expand();
		}

		int idx = key % table_.size();  // O(1)
		if (table_[idx].empty())
		{
			useBucketNum_++;
			table_[idx].emplace_front(key);
		}
		else
		{
			// ʹ��ȫ�ֵ�::find�����㷨�������ǵ����Լ��ĳ�Ա����find
			auto it = ::find(table_[idx].begin(), table_[idx].end(), key);  // O(n)
			if (it == table_[idx].end())
			{
				// key������
				table_[idx].emplace_front(key);
			}
		}
	}

	// ɾ��Ԫ��
	void erase(int key)
	{
		int idx = key % table_.size();  // O(1)
		// �������ڵ���������ɢ�н���Ƚϼ��У�ɢ�к��������⣡������
		//                 ���ɢ�н���Ƚ���ɢ��������һ�㲻���������Ϊ��װ������
		auto it = ::find(table_[idx].begin(), table_[idx].end(), key); // O(n)
		if (it != table_[idx].end())
		{
			table_[idx].erase(it);
			if (table_[idx].empty())
			{
				useBucketNum_--;
			}
		}
	}

	// ����Ԫ��
	bool find(int key)
	{
		int idx = key % table_.size();  // O(1)
		auto it = ::find(table_[idx].begin(), table_[idx].end(), key); // 
		return it != table_[idx].end();
	}

private:
	// ���ݺ���
	void expand()
	{
		if (primeIdx_ + 1 == PRIME_SIZE)
		{
			throw "hashtable can not expand anymore!";
		}

		primeIdx_++;
		useBucketNum_ = 0;

		vector<list<int>> oldTable;
		// swap�᲻��Ч�ʺܵͣ����� ���������������ĳ�Ա����  Ч�ʺܸ�
		/*
		�����������ʹ�õĿռ�������allocator��һ���ģ���ôֱ�ӽ������������ĳ�Ա�������ɣ�Ч�ʸ�
		�����������ʹ�õĿռ�������allocator�ǲ�һ���ģ���ô��ζ���������������ⲿ���ڴ�ķ�ʽ��һ��
		����vec1ָ������ڴ�ص��ڴ棬�����ͷ��ڴ����ڴ�����ͷŽ������ڴ�أ�vec2�Ŀռ�����������ͨ�ģ��Ƕ��ϵ��ڴ��ͷ�
		��ô������vec2�ͷŵĻ�����ֱ�Ӱ��ڴ�free�ˣ��޷��������ڴ��
		�������������ⲿ���ڴ�ķ�ʽ��һ��������ҪЧ�ʵ͵��������ݵĽ���
		*/
		table_.swap(oldTable);
		table_.resize(primes_[primeIdx_]);

		for (auto list : oldTable)
		{
			for (auto key : list)
			{
				int idx = key % table_.size();
				if (table_[idx].empty())
				{
					useBucketNum_++;
				}
				table_[idx].emplace_front(key);
			}
		}
	}

private:
	vector<list<int>> table_; // ��ϣ������ݽṹ
	int useBucketNum_;        // ��¼Ͱ�ĸ���
	double loadFactor_;       // ��¼��ϣ��װ������

	static const int PRIME_SIZE = 10; // ������Ĵ�С
	static int primes_[PRIME_SIZE];   // ������
	int primeIdx_; // ��ǰʹ�õ������±�
};

int HashTable::primes_[PRIME_SIZE] = { 3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773 };


int main()
{
	HashTable htable;
	htable.insert(21);
	htable.insert(32);
	htable.insert(14);
	htable.insert(15);

	htable.insert(22);

	htable.insert(67);

	cout << htable.find(67) << endl;
	htable.erase(67);
	cout << htable.find(67) << endl;

	return 0;
}