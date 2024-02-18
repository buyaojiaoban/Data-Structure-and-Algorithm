#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

/*
归并排序   磁盘排序

也采用“分治思想”，先进行序列划分，再进行元素的有序合并。

再归的过程中，进行的数据合并，达到排序的效果！

1.递到什么程度才开始归 2.归的过程中怎么进行数据合并 

二路归并
int mid = (begin + end)/2

归的过程中，利用额外的内存空间，把两个小段有序的序列，合并成大段有序的序列

时间复杂度：O(nlogn)  空间复杂度O(n)  稳定性：稳定
*/

// 归并过程函数
void Merge(int arr[], int l, int m, int r)
{
	int* p = new int[r - l + 1]; // 开辟空间
	int idx = 0;
	int i = l; // 左边小段首元素
	int j = m + 1; // 右边小段首元素

	while (i <= m && j <= r)
	{
		if (arr[i] <= arr[j]) // 稳定排序的关键
		{
			p[idx++] = arr[i++];
		}
		else
		{
			p[idx++] = arr[j++];
		}
	}
	while (i <= m) // 说明左边小段还有剩余
	{
		p[idx++] = arr[i++];
	}

	while (j <= r) // 说明右边小段还有剩余
	{
		p[idx++] = arr[j++];
	}

	// 再把合并好的大段有序的结果，拷贝到原始arr数组[l, r]区间内
	for (i = l, j = 0; i <= r; i++, j++)
	{
		arr[i] = p[j];
	}

	delete[]p;
}

// 归并排序递归接口
void MergeSort(int arr[], int begin, int end)
{
	// 递归结束的条件
	if (begin >= end)
	{
		return;
	}

	int mid = (begin + end) / 2;
	// 先递
	MergeSort(arr, begin, mid);
	MergeSort(arr, mid + 1, end);
	// 再归并  [begin, mid]  [mid+1, end] 把两个小段有序的序列，合并成大段有序的序列
	Merge(arr, begin, mid, end);
}

// 归并排序
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