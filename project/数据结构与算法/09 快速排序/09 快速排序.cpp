#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

/*
��������   ð������������㷨

˼�룺ѡȡһ����׼������С�ڻ�׼����Ԫ�ض���������׼������ߣ��Ѵ��ڻ�׼����Ԫ�ض���������׼�����ұߣ��Ի�׼����ߺ�
�ұߵ����м������������Ĳ�����ֱ���������б�������
L
46 8 76 10 38 7 68 32 65 53
						 R

ѭ��������L < R
1.ѡȡ��׼��  val=arr[L]
2.��R��ʼ��ǰ�ҵ�һ��С��val�����֣��ŵ�L�ĵط��������L++
3.��L��ʼ�����ҵ�һ������val�����֣��ŵ�R�ĵط��������R--
4.�ظ�����Ĺ��̣�ֱ����Ҫ�����Ԫ�ظ�����һ��

L == R; arr[L] = val


�ݹ飺
�ȸ�����ݹ麯�������壬��������ֵ���ȵݹ麯��Ҫ��д�ݹ�Ľ���������Ȼ����д�ݹ�Ĺ�ģn�͹�ģn-1�ĵ��ƹ�ϵ

ʱ�临�Ӷ�(��á�ƽ��):O(nlogn)    
�ռ临�Ӷ�(��á�ƽ��)����Ҫ���ǵݹ����ȣ�ÿһ�εݹ鶼��һ�κ���ջ֡�Ŀ��� O(logn) �ݹ�������ռ�õ�ջ�ڴ�

�ȶ��ԣ����ȶ�
5 7 7_ 3 2


�����㷨�Ż���
1.���ſ����㷨ִ�У�����Խ��Խ����������һ���ķ�Χ�ڣ����Բ��ò�����������������
2.���á�����ȡ�С������Һ��ʵĻ�׼��,ȡ������ֵ���м����
*/

// ���ŷָ����
int Partation(int arr[], int l, int r)
{
	/*
	�Ż�������ѡ���׼�����Ż���������ȡ�С���   arr[l]    arr[r]   arr[(l + r) / 2]  ��������������ֵ��СΪ��Ϊ��׼����
	Ȼ����ҵ��������׼��������arr[l]���н���
	*/
	// ��¼��׼��
	int val = arr[l];

	// һ�ο��Ŵ���  O(n) * O(logn) = O(nlogn)
	while (l < r)
	{
		while (l < r && arr[r] > val)
		{
			r--;
		}

		if (l < r) // ��֤Ԫ����Ч
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

	// l == r ��λ�ã����ǷŻ�׼����λ��
	arr[l] = val;
	return l;
}

// ���ŵĵݹ�ӿ�
void QuickSort(int arr[], int begin, int end)
{
	if (begin >= end) // ���ŵݹ��������
	{
		return;
	}

	/*
	// �Ż�һ����[begin, end]���е�Ԫ�ظ���С��ָ�����������ò�������
	if (end - begin <= 100) 
	{
		InsertSort(arr, begin, end);
		return;
	}
	*/

	// ��[begin��end]�����Ԫ����һ�ο��ŷָ��
	int pos = Partation(arr, begin, end);
	
	// �Ի�׼������ߺ��ұߵ����У��ٷֱ���п���
	QuickSort(arr, begin, pos - 1);
	QuickSort(arr, pos + 1, end);
}

// ��������
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