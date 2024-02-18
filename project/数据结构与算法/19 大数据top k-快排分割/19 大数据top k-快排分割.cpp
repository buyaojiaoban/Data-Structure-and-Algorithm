#include <iostream>
using namespace std;

/*
���ŷָ���top k

ƽ��ʱ�临�Ӷȣ�O(n) �ʹ�С����һ����ʱ�临�Ӷ�

���ʱ�䣺O(n^2)  
������ŵ��Ż�������ȡ��
*/

// ���ŷָ��
int Partation(int arr[], int begin, int end) // ��ǰk����С�� 
{
	int val = arr[begin];
	int l = begin;
	int r = end;

	while (l < r)
	{
		while (l<r && arr[r]>val)
			r--;

		if (l < r)
		{
			arr[l] = arr[r];
			l++;
		}

		while (l < r && arr[l] < val)
			l++;

		if (l < r)
		{
			arr[r] = arr[l];
			r--;
		}
	}

	arr[l] = val;
	return l;
}

int Partation2(int arr[], int begin, int end) // ��ǰk������
{
	int val = arr[begin];
	int l = begin;
	int r = end;

	while (l < r)
	{
		while (l < r && arr[r] < val)
			r--;

		if (l < r)
		{
			arr[l] = arr[r];
			l++;
		}

		while (l < r && arr[l] > val)
			l++;

		if (l < r)
		{
			arr[r] = arr[l];
			r--;
		}
	}

	arr[l] = val;
	return l;
}

// ��top k�ĺ���
void SelectTopK(int arr[], int begin, int end, int k)
{
	int pos = Partation2(arr, begin, end);
	if (pos == k - 1)
	{
		return;
	}
	else if (pos > k - 1)
	{
		Partation2(arr, begin, pos - 1);
	}
	else
	{
		Partation2(arr, pos + 1, end);
	}
}

int main()
{
	int arr[] = { 64,45,52,80,66,68,0,2,18,75 };
	int size = sizeof arr / sizeof arr[0];

	// ��ֵ��С��ǰ3��Ԫ��  �����±�2����
	int k = 3;
	SelectTopK(arr, 0, size - 1, k);

	for (int i = 0; i < k; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;

	return 0;
}