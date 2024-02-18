#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

/*
堆排序：
1.从第一个非叶子节点开始，把二叉堆调整成一个大根堆   (n-1)/2
从第 (n-1)/2 号位元素开始到堆顶元素(0),进行下沉操作
2.把堆顶元素和末尾元素进行交换，从 0 号位继续开始进行堆的下沉调整

时间复杂度：O(n*logn)  空间复杂度:O(1)  稳定性：不稳定

快排&归并&希尔&堆排性能
1.不管是快排，或者归并排序，遍历元素的时候都是按照顺序遍历的，对CPU缓存是友好的(CPU缓存命中率高)，但是堆排序，访问元素
的时候，是按照父子节点的关系访问的，并不是按照顺序访问的，所以排序过程中，不管是上浮调整，还是下沉调整，对CPU缓存不友好

2.堆排序的过程中，进行元素下沉调整所作的无效比较过多，因为它本身就小，所以最终下沉到的地方，和末尾位置相差不远，中间做了
很多比较，无用功太多！
*/

// 堆的下沉调整
void siftDown(int arr[], int i, int size)
{
	int val = arr[i];
	while (i <= size/2 - 1) // 不能写(size-1-1)/2
	{
		int child = 2 * i + 1;
		if (child + 1 < size && arr[child + 1] > arr[child])
		{
			child = child + 1;
		}

		if (arr[child] > val)
		{
			arr[i] = arr[child];
			i = child; // i继续指向它的孩子，继续调整
		}
		else
		{
			break; // 满足大根堆
		}
	}
	arr[i] = val;
}

// 堆排序
void HeapSort(int arr[], int size)
{
	int n = size - 1;
	// 从第一个非叶子节点
	for (int i = (n - 1) / 2; i >= 0; i--)
	{
		siftDown(arr, i, size);
	}

	// 把堆顶元素和末尾元素进行交换，从堆顶开始进行下沉操作
	for (int i = n; i > 0; i--)
	{
		int tmp = arr[0];
		arr[0] = arr[i];
		arr[i] = tmp;

		siftDown(arr, 0, i); // 第三个参数，参与调整的元素的个数
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