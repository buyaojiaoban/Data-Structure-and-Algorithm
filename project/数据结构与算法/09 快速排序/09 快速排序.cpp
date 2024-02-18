#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

/*
快速排序   冒泡排序的升级算法

思想：选取一个基准数，把小于基准数的元素都调整到基准数的左边，把大于基准数的元素都调整到基准数的右边，对基准数左边和
右边的序列继续进行这样的操作，直到整个序列变成有序的
L
46 8 76 10 38 7 68 32 65 53
						 R

循环条件：L < R
1.选取基准数  val=arr[L]
2.从R开始往前找第一个小于val的数字，放到L的地方，放完后L++
3.从L开始往后找第一个大于val的数字，放到R的地方，放完后R--
4.重复上面的过程，直到所要处理的元素个数就一个

L == R; arr[L] = val


递归：
先搞清楚递归函数的意义，参数返回值；先递归函数要先写递归的结束条件，然后再写递归的规模n和规模n-1的递推关系

时间复杂度(最好、平均):O(nlogn)    
空间复杂度(最好、平均)：主要考虑递归的深度，每一次递归都是一次函数栈帧的开辟 O(logn) 递归的深度所占用的栈内存

稳定性：不稳定
5 7 7_ 3 2


快排算法优化：
1.随着快排算法执行，数据越来越趋于有序，在一定的范围内，可以采用插入排序代替快速排序
2.采用“三数取中”法，找合适的基准数,取的是数值在中间的数
*/

// 快排分割处理函数
int Partation(int arr[], int l, int r)
{
	/*
	优化化二：选择基准数的优化：“三数取中”法   arr[l]    arr[r]   arr[(l + r) / 2]  找这三个数，数值大小为中为基准数，
	然后把找到的这个基准数，和与arr[l]进行交换
	*/
	// 记录基准数
	int val = arr[l];

	// 一次快排处理  O(n) * O(logn) = O(nlogn)
	while (l < r)
	{
		while (l < r && arr[r] > val)
		{
			r--;
		}

		if (l < r) // 保证元素有效
		{
			arr[l] = arr[r];
			l++;
		}

		while (l < r && arr[l] < val)
		{
			l++;
		}

		if (l < r)
		{
			arr[r] = arr[l];
			r--;
		}
	}

	// l == r 的位置，就是放基准数的位置
	arr[l] = val;
	return l;
}

// 快排的递归接口
void QuickSort(int arr[], int begin, int end)
{
	if (begin >= end) // 快排递归结束条件
	{
		return;
	}

	/*
	// 优化一：当[begin, end]序列的元素个数小到指定数量，采用插入排序
	if (end - begin <= 100) 
	{
		InsertSort(arr, begin, end);
		return;
	}
	*/

	// 在[begin，end]区间的元素做一次快排分割处理
	int pos = Partation(arr, begin, end);
	
	// 对基准数的左边和右边的序列，再分别进行快排
	QuickSort(arr, begin, pos - 1);
	QuickSort(arr, pos + 1, end);
}

// 快速排序
void QuickSort(int arr[], int size)
{
	QuickSort(arr, 0, size - 1);
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

	QuickSort(arr, 10);

	for (int v : arr)
	{
		cout << v << " ";
	}
	cout << endl;
	return 0;
}