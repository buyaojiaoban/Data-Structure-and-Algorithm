#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
using namespace std;

// 整形数组，把偶数调整到数组的左边，把奇数调整到数组的右边
void AdjustArray(int arr[], int size)
{
	int* p = arr;
	int* q = arr + size - 1;
	while (p < q)
	{
		while (p < q)
		{
			// p->找奇数
			if ((*p & 0x1) == 1)//奇数最后一位肯定是1，这个式子等于0就是偶数，等于1就是奇数；
			{					//注意：位操作优先级很低要加括号,比关系运算符还低;位操作一定加括号
				break;
			}
			p++;
		}
		
		while (p < q)
		{
			// q->找偶数
			if ((*q & 0x1) == 0)
			{
				break;
			}
			q--;
		}
		//此时p->奇数，q指向偶数
		if (p < q)
		{
			int tmp = *p;
			*p = *q;
			*q = tmp;
			p++;
			q--;
		}
		
	}
}

int main()
{
	int arr[10] = { 0 };
	srand(time(0));
	for (int i = 0; i < 10; i++)
	{
		arr[i] = rand() % 100;
	}

	for (int v : arr)
	{
		cout << v << "  ";
	}
	cout << endl;

	AdjustArray(arr, 10);
	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;
}


#if 0
// 逆序字符串 双指针
void Reverse(char arr[], int size)
{
	char* p = arr;
	char* q = arr + size - 1;
	while (p < q)
	{
		char ch = *p;
		*p = *q;
		*q = ch;
		p++;
		q--;
	}
}
int main()
{
	char arr[] = "hello world";
	Reverse(arr, strlen(arr));
	cout << arr << endl;
}
#endif

#if 0
//数组实现
class Array
{
public:
	Array(int size = 10) : mCur(0), mCap(size)
	{
		mpArr = new int[mCap]();//mpArr = new int[mCap_];不加小括号是不初始化，加了是把里面的元素初始化为0
	}
	~Array()
	{
		delete []mpArr;
		mpArr = nullptr;
	}

public:
	//末尾增加元素
	void push_back(int val)
	{
		if (mCur == mCap)
		{
			expand(mCap * 2);
		}
		mpArr[mCur++] = val;
	}
	//末尾删除元素
	void pop_back()
	{
		if (mCur == 0)
		{
			return;
		}
		mCur--;
	}
	//按位置增加元素
	void insert(int pos, int val)
	{
		if (pos<0 || pos>mCur)
		{
			return;// throw "pos invalid!";
		}

		if (mCur == mCap)
		{
			expand(mCap * 2);
		}

		//移动元素
		for (int i = mCur - 1; i >= pos; i--)
		{
			mpArr[i + 1] = mpArr[i];
		}
		mpArr[pos] = val;
		mCur++;
	}
	//按位置删除
	void erase(int pos)
	{
		if (pos < 0 || pos >= mCur)
		{
			return;
		}
		for (int i = pos + 1; i < mCur; i++)
		{
			mpArr[i - 1] = mpArr[i];
		}

		mCur--;
	}
	//元素查询,返回下标
	int find(int val)
	{
		for (int i = 0; i < mCur; i++)
		{
			if (mpArr[i] == val)
			{
				return i;
			}
		}
		return -1;
	}
	void show()const
	{
		for (int i = 0; i < mCur; i++)
		{
			cout << mpArr[i] << "  ";
		}
		cout << endl;
	}
private:
	// 内部数组扩容接口
	void expand(int size)
	{
		int* p = new int[size];
		memcpy(p, mpArr, sizeof(int) * mCap);
		delete[]mpArr;
		mpArr = p;
		mCap = size;
	}
private:
	int* mpArr;// 指向可扩容的数组内存
	int mCap;// 数组的容量
	int mCur;// 数组有效元素个数
};

int main()
{
	Array arr;
	srand(time(0));
	for (int i = 0; i < 10; i++)
	{
		arr.push_back(rand() % 100);
	}
	arr.show();
	arr.pop_back();
	arr.show();

	arr.insert(0, 100);
	arr.show();

	arr.insert(10, 200);
	arr.show();

	int pos = arr.find(100);
	if (pos != -1)
	{
		arr.erase(pos);
		arr.show();
	}
	return 0;
}
#endif