#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

#if 0
/*
ð������
�ص㣺����Ԫ�������Ƚϣ���ֵ���Ԫ�����½�����
ȱ�㣺���ݽ����Ĵ���̫��

д�����ɣ���дһ������Ĳ���
for (int j = 0; j < size - 1; ++j) // size-1; ע�� ÿ�αȽ���j��j+1�Ƚ� �����j<size��ô��ȡ�����һ��Ԫ�أ�j+1��Ч
{
		if (arr[j] > arr[j + 1])
		{
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
		}
}

��С����ÿһ��ȷ��һ�����ֵ
�Ӵ�С��ÿһ��ȷ��һ����Сֵ

ð�����������������㷨Ч����͵ģ�ԭ���������ݽ����Ĵ���̫�࣡

�ռ临�Ӷȣ�O(1)   ʱ�临�Ӷȣ�O(n^2)   �ȶ��ԣ��ȶ�    ���ʱ�临�Ӷȣ����������źõģ���ֻ��һ��O(n)
*/
void BubbleSort(int arr[], int size)
{
	for (int i = 0; i < size - 1; ++i) // ����   i<sizeҲ����  ��-1��ʾ���һ�˲���ѭ���ˣ������Ż�
	{
		bool flag = false;
		// һ�˵Ĵ���   
		for (int j = 0; j < size - 1 - i; ++j) 
		{
			if (arr[j] > arr[j + 1])
			{
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
				flag = true;
			}
		}

		if (!flag)
		{
			// ���һ���У�û���κε����ݽ�����˵�������Ѿ�������  �Ż�
			return;
		}
	}	
}
int main()
{
	int arr[10];
	srand(time(NULL));

	for (int i = 0; i < 10; ++i)
	{
		arr[i] = rand() % 100 + 1;
	}

	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;

	BubbleSort(arr, 10);
	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;

	return 0;
}
#endif


#if 0
/*
ѡ������
�ص㣺ÿ����ʣ�µ�Ԫ����ѡ��ֵ��С��Ԫ�أ��͵�ǰԪ�ؽ��н���.
ȱ�㣺�����ð�����򣬽����Ĵ������ˣ����ǱȽϵĴ�����Ȼ�ܶ�

д��˼·����дһ�˵�

ʱ�临�Ӷ�O(n^2)   �ռ临�Ӷ�O(1)   �ȶ��ԣ����ȶ�
5 5_ 3  ѡ������󣬽����󣬾Ͳ��ȶ��� 3 5_ 5
*/
void ChoiceSort1(int arr[], int size) // �����һ�˴����˼·
{
	int min = arr[0];
	int k = 0;
	for (int j = 1; j < size; j++)
	{
		if (arr[j] < min)
		{
			min = arr[j];
			k = j; // ��¼�±�
		}
	}

	// �ҵ�����ʣ�������е���Сֵ���Ϳ�ʼλ�õ�ֵ���н���
	if (k != 0)
	{
		int tmp = arr[0];
		arr[0] = arr[k];
		arr[k] = tmp;
	}
}

void ChoiceSort(int arr[], int size) 
{
	for (int i = 0; i < size - 1; ++i) // O(n)
	{
		int min = arr[i];
		int k = i;
		for (int j = i + 1; j < size; j++) // O(n)
		{
			if (arr[j] < min)
			{
				min = arr[j];
				k = j; // ��¼�±�
			}
		}

		// �ҵ�����ʣ�������е���Сֵ���Ϳ�ʼλ�õ�ֵ���н���
		if (k != i)
		{
			int tmp = arr[i];
			arr[i] = arr[k];
			arr[k] = tmp;
		}
	}
}
int main()
{
	int arr[10];
	srand(time(NULL));

	for (int i = 0; i < 10; ++i)
	{
		arr[i] = rand() % 100 + 1;
	}

	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;

	ChoiceSort(arr, 10);
	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;

	return 0;
}
#endif


#if 0
/*
��������

�����������������ô�������������������㷨�У�Ч����ߵ������㷨��
�ٻ��������㷨�У��������� > ð������&ѡ������
���ڲ���������˵��������û�н��������ұȽϵĴ���Ҳ�٣�

�ص㣺�ӵڶ���Ԫ�ؿ�ʼ����ǰ���Ԫ�����е����Ѿ�����ģ�Ȼ���Һ��ʵ�λ�ò���
�ŵ㣺������������ͨ��������Ч����ߵ������㷨������������Խ�������������£����������Ч������ߵ�

ʱ�临�Ӷ�:���ƽ��O(n^2) ��ã�O(n)�ڲ�ѭ�����������ݽ�����ֻ����������һ��  �ռ临�Ӷȣ�O(1)   �ȶ��ԣ��ȶ�
*/
void InsertSort(int arr[], int size)
{
	for (int i = 1; i < size; i++) // size����Ϊ���һ��Ԫ��Ҳ��Ҫ�����  O(n)
	{
		int val = arr[i];
		int j = i - 1;
		for (; j >= 0; --j) // O(n)
		{
			if (arr[j] <= val)
			{
				break;
			}
			arr[j + 1] = arr[j];
		}
		// val -> j+1
		arr[j + 1] = val;
	}
}

int main()
{
	int arr[10];
	srand(time(NULL));

	for (int i = 0; i < 10; ++i)
	{
		arr[i] = rand() % 100 + 1;
	}

	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;

	InsertSort(arr, 10);
	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;

	return 0;
}
#endif


#if 0
/*
ϣ������

�ص㣺���Կ����Ƕ�·�Ĳ������򣬷��������Խ�������������ϵ�����ҲԽ�������򣬲�������Ч����������
����������Ż�

ƽ��ʱ�临�Ӷ�O(n^1.3)  ���ʱ�临�Ӷ�O(n) ���O(n^2) �ռ临�Ӷ�:O(1) �ȶ��ԣ����ȶ�  ��ֵ��ͬ��Ԫ�ط��벻ͬ������

һ���е���������������ϣ������ѡ����ʵ��������У�Ч�ʾ��Ѿ������ˣ�����������Ƚϴ󣬿���ѡ��߼��������㷨��
���������
*/
void ShellSort(int arr[], int size)
{
	for (int gap = size / 2; gap > 0; gap /= 2) //
	{
		for (int i = gap; i < size; i++) // 0(n)
		{
			int val = arr[i];
			int j = i - gap;
			for (; j >= 0; j -= gap) // O(n)
			{
				if (arr[j] <= val)
				{
					break;
				}
				arr[j + gap] = arr[j];
			}
			arr[j + gap] = val;
		}
	}
}

int main()
{
	int arr[10];
	srand(time(NULL));

	for (int i = 0; i < 10; ++i)
	{
		arr[i] = rand() % 100 + 1;
	}

	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;

	ShellSort(arr, 10);
	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;

	return 0;
}
#endif


