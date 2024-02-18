#include <iostream>
using namespace std;

/*
快排分割求top k

平均时间复杂度：O(n) 和大小根堆一样的时间复杂度

最差时间：O(n^2)  
引入快排的优化，三数取中
*/

// 快排分割函数
int Partation(int arr[], int begin, int end) // 求前k个最小的 
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

int Partation2(int arr[], int begin, int end) // 求前k个最大的
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

// 求top k的函数
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

	// 求值最小的前3个元素  返回下标2就行
	int k = 3;
	SelectTopK(arr, 0, size - 1, k);

	for (int i = 0; i < k; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;

	return 0;
}