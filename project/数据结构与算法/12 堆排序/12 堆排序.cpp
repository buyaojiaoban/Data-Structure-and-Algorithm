#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

/*
������
1.�ӵ�һ����Ҷ�ӽڵ㿪ʼ���Ѷ���ѵ�����һ�������   (n-1)/2
�ӵ� (n-1)/2 ��λԪ�ؿ�ʼ���Ѷ�Ԫ��(0),�����³�����
2.�ѶѶ�Ԫ�غ�ĩβԪ�ؽ��н������� 0 ��λ������ʼ���жѵ��³�����

ʱ�临�Ӷȣ�O(n*logn)  �ռ临�Ӷ�:O(1)  �ȶ��ԣ����ȶ�

����&�鲢&ϣ��&��������
1.�����ǿ��ţ����߹鲢���򣬱���Ԫ�ص�ʱ���ǰ���˳������ģ���CPU�������Ѻõ�(CPU���������ʸ�)�����Ƕ����򣬷���Ԫ��
��ʱ���ǰ��ո��ӽڵ�Ĺ�ϵ���ʵģ������ǰ���˳����ʵģ�������������У��������ϸ������������³���������CPU���治�Ѻ�

2.������Ĺ����У�����Ԫ���³�������������Ч�ȽϹ��࣬��Ϊ�������С�����������³����ĵط�����ĩβλ����Զ���м�����
�ܶ�Ƚϣ����ù�̫�࣡
*/

// �ѵ��³�����
void siftDown(int arr[], int i, int size)
{
	int val = arr[i];
	while (i <= size/2 - 1) // ����д(size-1-1)/2
	{
		int child = 2 * i + 1;
		if (child + 1 < size && arr[child + 1] > arr[child])
		{
			child = child + 1;
		}

		if (arr[child] > val)
		{
			arr[i] = arr[child];
			i = child; // i����ָ�����ĺ��ӣ���������
		}
		else
		{
			break; // ��������
		}
	}
	arr[i] = val;
}

// ������
void HeapSort(int arr[], int size)
{
	int n = size - 1;
	// �ӵ�һ����Ҷ�ӽڵ�
	for (int i = (n - 1) / 2; i >= 0; i--)
	{
		siftDown(arr, i, size);
	}

	// �ѶѶ�Ԫ�غ�ĩβԪ�ؽ��н������ӶѶ���ʼ�����³�����
	for (int i = n; i > 0; i--)
	{
		int tmp = arr[0];
		arr[0] = arr[i];
		arr[i] = tmp;

		siftDown(arr, 0, i); // ���������������������Ԫ�صĸ���
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

	HeapSort(arr, 10);

	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;

	return 0;
}