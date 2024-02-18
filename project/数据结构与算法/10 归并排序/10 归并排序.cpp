#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

/*
�鲢����   ��������

Ҳ���á�����˼�롱���Ƚ������л��֣��ٽ���Ԫ�ص�����ϲ���

�ٹ�Ĺ����У����е����ݺϲ����ﵽ�����Ч����

1.�ݵ�ʲô�̶Ȳſ�ʼ�� 2.��Ĺ�������ô�������ݺϲ� 

��·�鲢
int mid = (begin + end)/2

��Ĺ����У����ö�����ڴ�ռ䣬������С����������У��ϲ��ɴ�����������

ʱ�临�Ӷȣ�O(nlogn)  �ռ临�Ӷ�O(n)  �ȶ��ԣ��ȶ�
*/

// �鲢���̺���
void Merge(int arr[], int l, int m, int r)
{
	int* p = new int[r - l + 1]; // ���ٿռ�
	int idx = 0;
	int i = l; // ���С����Ԫ��
	int j = m + 1; // �ұ�С����Ԫ��

	while (i <= m && j <= r)
	{
		if (arr[i] <= arr[j]) // �ȶ�����Ĺؼ�
		{
			p[idx++] = arr[i++];
		}
		else
		{
			p[idx++] = arr[j++];
		}
	}
	while (i <= m) // ˵�����С�λ���ʣ��
	{
		p[idx++] = arr[i++];
	}

	while (j <= r) // ˵���ұ�С�λ���ʣ��
	{
		p[idx++] = arr[j++];
	}

	// �ٰѺϲ��õĴ������Ľ����������ԭʼarr����[l, r]������
	for (i = l, j = 0; i <= r; i++, j++)
	{
		arr[i] = p[j];
	}

	delete[]p;
}

// �鲢����ݹ�ӿ�
void MergeSort(int arr[], int begin, int end)
{
	// �ݹ����������
	if (begin >= end)
	{
		return;
	}

	int mid = (begin + end) / 2;
	// �ȵ�
	MergeSort(arr, begin, mid);
	MergeSort(arr, mid + 1, end);
	// �ٹ鲢  [begin, mid]  [mid+1, end] ������С����������У��ϲ��ɴ�����������
	Merge(arr, begin, mid, end);
}

// �鲢����
void MergeSort(int arr[], int size)
{
	MergeSort(arr, 0, size - 1);
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

	MergeSort(arr, 10);

	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;

	return 0;
}