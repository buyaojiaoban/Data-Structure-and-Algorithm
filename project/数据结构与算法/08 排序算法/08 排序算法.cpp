#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

#if 0
/*
冒泡排序
特点：相邻元素两两比较，把值大的元素往下交换。
缺点：数据交换的次数太多

写法技巧，先写一趟排序的操作
for (int j = 0; j < size - 1; ++j) // size-1; 注意 每次比较是j和j+1比较 如果是j<size那么在取到最后一个元素，j+1无效
{
		if (arr[j] > arr[j + 1])
		{
				int tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
		}
}

从小到大，每一躺确定一个最大值
从大到小，每一躺确定一个最小值

冒泡排序是所有排序算法效率最低的，原因在于数据交换的次数太多！

空间复杂度：O(1)   时间复杂度：O(n^2)   稳定性：稳定    最好时间复杂度：本来就是排好的，就只有一躺O(n)
*/
void BubbleSort(int arr[], int size)
{
	for (int i = 0; i < size - 1; ++i) // 趟数   i<size也可以  但-1表示最后一趟不用循环了，代码优化
	{
		bool flag = false;
		// 一趟的处理   
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
			// 如果一趟中，没有任何的数据交换，说明数据已经有序了  优化
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
选择排序
特点：每次在剩下的元素中选择值最小的元素，和当前元素进行交换.
缺点：相比于冒泡排序，交换的次数少了，但是比较的次数依然很多

写法思路：先写一趟的

时间复杂度O(n^2)   空间复杂度O(1)   稳定性：不稳定
5 5_ 3  选择排序后，交换后，就不稳定了 3 5_ 5
*/
void ChoiceSort1(int arr[], int size) // 这就是一趟处理的思路
{
	int min = arr[0];
	int k = 0;
	for (int j = 1; j < size; j++)
	{
		if (arr[j] < min)
		{
			min = arr[j];
			k = j; // 记录下标
		}
	}

	// 找到后面剩余序列中的最小值，和开始位置的值进行交换
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
				k = j; // 记录下标
			}
		}

		// 找到后面剩余序列中的最小值，和开始位置的值进行交换
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
插入排序

如果数据趋于有序，那么插入排序是所有排序算法中，效率最高的排序算法！
再基础排序算法中，插入排序 > 冒泡排序&选择排序
对于插入排序来说，不仅仅没有交换，而且比较的次数也少！

特点：从第二个元素开始，把前面的元素序列当作已经有序的，然后找合适的位置插入
优点：插入排序是普通排序里面效率最高的排序算法，而且在数据越趋于有序的情况下，插入排序的效率是最高的

时间复杂度:最坏，平均O(n^2) 最好：O(n)内层循环不进行数据交换，只是外层遍历了一遍  空间复杂度：O(1)   稳定性：稳定
*/
void InsertSort(int arr[], int size)
{
	for (int i = 1; i < size; i++) // size：因为最后一个元素也是要处理的  O(n)
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
希尔排序

特点：可以看作是多路的插入排序，分组的数据越趋于有序，整体上的数据也越趋于有序，插入排序效率完美体现
插入排序的优化

平均时间复杂度O(n^1.3)  最好时间复杂度O(n) 最坏：O(n^2) 空间复杂度:O(1) 稳定性：不稳定  把值相同的元素放入不同组里面

一般中等数据量的排序都用希尔排序，选择合适的增量序列，效率就已经不错了，如果数据量比较大，可以选择高级的排序算法，
如快速排序
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


