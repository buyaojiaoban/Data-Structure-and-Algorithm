#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
using namespace std;

// �������飬��ż���������������ߣ�������������������ұ�
void AdjustArray(int arr[], int size)
{
	int* p = arr;
	int* q = arr + size - 1;
	while (p < q)
	{
		while (p < q)
		{
			// p->������
			if ((*p & 0x1) == 1)//�������һλ�϶���1�����ʽ�ӵ���0����ż��������1����������
			{					//ע�⣺λ�������ȼ��ܵ�Ҫ������,�ȹ�ϵ���������;λ����һ��������
				break;
			}
			p++;
		}
		
		while (p < q)
		{
			// q->��ż��
			if ((*q & 0x1) == 0)
			{
				break;
			}
			q--;
		}
		//��ʱp->������qָ��ż��
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
// �����ַ��� ˫ָ��
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
//����ʵ��
class Array
{
public:
	Array(int size = 10) : mCur(0), mCap(size)
	{
		mpArr = new int[mCap]();//mpArr = new int[mCap_];����С�����ǲ���ʼ���������ǰ������Ԫ�س�ʼ��Ϊ0
	}
	~Array()
	{
		delete []mpArr;
		mpArr = nullptr;
	}

public:
	//ĩβ����Ԫ��
	void push_back(int val)
	{
		if (mCur == mCap)
		{
			expand(mCap * 2);
		}
		mpArr[mCur++] = val;
	}
	//ĩβɾ��Ԫ��
	void pop_back()
	{
		if (mCur == 0)
		{
			return;
		}
		mCur--;
	}
	//��λ������Ԫ��
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

		//�ƶ�Ԫ��
		for (int i = mCur - 1; i >= pos; i--)
		{
			mpArr[i + 1] = mpArr[i];
		}
		mpArr[pos] = val;
		mCur++;
	}
	//��λ��ɾ��
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
	//Ԫ�ز�ѯ,�����±�
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
	// �ڲ��������ݽӿ�
	void expand(int size)
	{
		int* p = new int[size];
		memcpy(p, mpArr, sizeof(int) * mCap);
		delete[]mpArr;
		mpArr = p;
		mCap = size;
	}
private:
	int* mpArr;// ָ������ݵ������ڴ�
	int mCap;// ���������
	int mCur;// ������ЧԪ�ظ���
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