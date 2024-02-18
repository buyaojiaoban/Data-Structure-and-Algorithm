#include <iostream>
#include <vector>
using namespace std;

#if 0
/*
���������㷨       ����
		0					5					10
	  first                middle              last
arr		12  25  34  39  45  57  63  78  82  96  100

int middle = (first+last)/2
��ʱ����Ҫ�ҵ�����middle�Ƚϣ��ж�����
if(arr[middle] > val)  last = middle - 1;  // last = 4,��45 
if(arr[middle] < val)  first = middle + 1;   
Ȼ����middle = (first+last)/2��Ȼ����ȥ�ж�


ѭ������!!!    while(first <= last)

ʱ�临�Ӷȣ�O(logn) �����¼� 2Ϊ��
						  57
					   /	  \				  
					  /        \
					 34        82
					/  \      /   \
				   12   39   63    96
                     \    \    \     \
					  25   45   78    100

���������㷨��ʵ���Ͼ��Ƕ��������BST����root����㿪ʼ�����Ĺ��̣�ÿһ������ֻ������һ��·��������ȥ
��ÿһ������ֵ�����������������н��ֵ��С���������������н���ֵ

������������ʱ�临�Ӷȣ������������BST���Ĳ���/�߶ȣ�����  L=logn  (2Ϊ��)
������ܸ����� 2^0 + 2^1 + 2^2 + 2^3 ... +2^(L-1) = n    2^L - 1 = 0;   2^L = n + 1;    1������ L=logn
*/

// ���������ǵݹ�ʵ��
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
���������㷨�ĵݹ�ʵ��

�㷨��������һ�仰�������߼��Ǹ��˿��ģ�ѭ���߼��Ǹ���������ģ��ݹ��߼��Ǹ��񿴵ģ�

�ݹ�:
	��ʽ: �����Լ������Լ�
	1.������ʲô���ݹ�ģ���������ķ�ʽ��һ���ģ�
	2.��ͬ��ģ�����ݣ�����������й�ϵ��Ѱ��
�ݹ麯����
1.һ��Ҫ������ݹ麯����������ʲô�� ����ֵ�������б��������ʲô���ܣ�
2.һ���еݹ����������������
3.ÿ�����ݹ�ģҪд������֮��ļ����ϵ

�ݹ������˼����ˮƽ�����ϵģ�   n-1 �� n�Ĺ�ϵ    
�ݹ����ľ���ִ���Ǵ�ֱ�����ϵģ�

int func1(int n)  func1�������������һ������n����n�Ľ׳ˣ����ѽ�����ػ�ȥ��


�������ĵݹ飺
���� => �������ݹ�ģ������   ������һ��������ʼ���±��ĩβ���±�
*/

// ���������㷨�ĵݹ�ʵ��
int BinarySearch(int arr[], int i, int j, int val) // ��arr�����[i,j]��Χ��,��������val,�ҵ��Ļ�����ֵ���±�,�Ҳ�������-1
{
	if (i > j) // �ݹ��������
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