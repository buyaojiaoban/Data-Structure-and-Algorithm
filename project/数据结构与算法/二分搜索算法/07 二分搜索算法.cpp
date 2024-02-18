#include <iostream>
#include <vector>
using namespace std;

#if 0
/*
二分搜索算法       有序
		0					5					10
	  first                middle              last
arr		12  25  34  39  45  57  63  78  82  96  100

int middle = (first+last)/2
此时用需要找的数跟middle比较，判断左右
if(arr[middle] > val)  last = middle - 1;  // last = 4,即45 
if(arr[middle] < val)  first = middle + 1;   
然后又middle = (first+last)/2，然后又去判断


循环条件!!!    while(first <= last)

时间复杂度：O(logn) 对数事件 2为底
						  57
					   /	  \				  
					  /        \
					 34        82
					/  \      /   \
				   12   39   63    96
                     \    \    \     \
					  25   45   78    100

二分搜索算法，实际上就是对上面这棵BST树从root根结点开始搜索的过程，每一次搜索只会沿着一条路径搜索下去
，每一个结点的值大于其左子树上所有结点值，小于其右子树上所有结点的值

即二分搜索的时间复杂度：就是上面这棵BST树的层数/高度！！！  L=logn  (2为底)
即结点总个数： 2^0 + 2^1 + 2^2 + 2^3 ... +2^(L-1) = n    2^L - 1 = 0;   2^L = n + 1;    1不看， L=logn
*/

// 二分搜索非递归实现
int BinarySearch(int arr[], int size, int val)
{
	int first = 0;
	int last = size - 1;

	while (first <= last)
	{
		int mid = (first + last) / 2;
		if (arr[mid] == val)
		{
			return mid;
		}
		else if (arr[mid] > val)
		{
			last = mid - 1;
		}
		else
		{
			first = mid + 1;
		}
	}
	return -1;
}

int main()
{
	int arr[] = { 12, 25, 34, 39, 45, 57, 63, 78, 82, 96, 100 };
	int size = sizeof arr / sizeof(arr[0]);
	cout << BinarySearch(arr, size, 39) << endl;
	cout << BinarySearch(arr, size, 12) << endl;
	cout << BinarySearch(arr, size, 64) << endl;
	cout << BinarySearch(arr, size, 100) << endl;

	return 0;
}
#endif



/*
二分搜索算法的递归实现

算法导论中有一句话：串行逻辑是给人看的，循环逻辑是给计算机看的，递归逻辑是给神看的！

递归:
	形式: 函数自己调用自己
	1.不管是什么数据规模，求解问题的方式是一样的！
	2.不同规模的数据，其计算结果是有关系可寻的
递归函数：
1.一定要搞清楚递归函数的意义是什么， 返回值、参数列表，它能完成什么功能！
2.一定有递归结束的条件！！！
3.每个数据规模要写好它们之间的计算关系

递归问题的思考是水平方向上的！   n-1 和 n的关系    
递归代码的具体执行是垂直方向上的！

int func1(int n)  func1这个函数，接收一个数据n，求n的阶乘，并把结果返回回去！


数组参与的递归：
数组 => 进行数据规模的缩减   ，数组一定会有起始的下标和末尾的下标
*/

// 二分搜索算法的递归实现
int BinarySearch(int arr[], int i, int j, int val) // 在arr数组的[i,j]范围内,二分搜索val,找到的话返回值的下标,找不到返回-1
{
	if (i > j) // 递归结束条件
		return -1;
	int mid = (i + j) / 2;
	if (arr[mid] == val)
		return mid;
	else if (arr[mid] > val)
	{
		return BinarySearch(arr, i, mid - 1, val);
	}
	else
	{
		return BinarySearch(arr, mid + 1, j, val);
	}
}
int main()
{
	int arr[] = { 12, 25, 34, 39, 45, 57, 63, 78, 82, 96, 100 };
	int size = sizeof arr / sizeof(arr[0]);

	cout << BinarySearch(arr, 0, size - 1, 45) << endl;
	return 0;
}