#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <memory>
using namespace std;


/*
λͼ����
������һ��λ��0����1�����洢���ݵ�״̬���Ƚ��ʺ�״̬�򵥣��������Ƚϴ�Ҫ���ڴ�ʹ���ʵ͵����ⳡ��


�������⣺
��1�ڸ����������ֵ������1�ڣ��ʶ�����ЩԪ���ظ��ˣ�˭�ǵ�һ���ظ��ģ�˭�ǵ�һ�����ظ��ģ� �ڴ�����100M

=>��ϣ��Ļ� 1�� = 100M ��ϣ��洢-��100*4 *2 = 800M

λͼ�㷨�� bitmapλͼ����
7 8 12 15 16 19
1.��Ҫ֪��Ԫ�����е����ֵ���������ֵ������bitmapλͼ���� char bitmap[19/8 +1] //[3]
2.���� / %����������ӳ�䵽Ԫ�ض�Ӧ��λ
3.��ȡ��λ��ֵ 0��ʾû���ֹ� 1��ʾ���ֹ���
��λ�ȡ��λ��ֵ�� bitmap[index] & (1 << offset)
��ΰ����λ���ó�1  bitmap[index] | (1<<offset)

int bitmap[1��/32 +1] 3.2M*4

˭�ǵ�һ�����ظ��ģ�
ԭ��1��λ�������ݵ�״̬������������λ����  ��������


ȱ�ݣ�int ����ֵ��20������      unsigned int ����ֵ40������
1 3 1000000000
����ֻ������ֵ��������λͼ���飬int bitmap[1000000000/32 +1]  30*4M
��ϣ��Ļ� -> 3*4 *2 = 24byte

λͼ�㷨�Ƽ����������У����ݵĸ��� >= �����������ֵ����ֵ�൱
*/

int main()
{
	vector<int> vec{ 12,78,12,90,123,90,8,9 };

	// ����λͼ����
	
	//��Ҫ֪�����ֵ
	int max = vec[0];
	for (int i = 1; i < vec.size(); i++) // O(n)
	{
		if (vec[i] > max)
			max = vec[i];
	}


	int* bitmap = new int[max / 32 + 1](); // ����Ԫ�ض�Ҫ��ʼ��0
	unique_ptr<int> ptr(bitmap);

	// �ҵ�һ���ظ����ֵ�����
	for (auto key : vec)
	{
		int index = key / 32;
		int offset = key % 32;

		// ȡkey��Ӧ��λ��ֵ
		if (0 == (bitmap[index] & (1 << offset)))
		{
			// ��ʾkeyû�г��ֹ�
			bitmap[index] |= (1 << offset);
		}
		else
		{
			/*
			cout << key << "�ǵ�һ���ظ����ֵ�����" << endl;
			return 0;
			*/
			cout << key << "�ظ����ֹ���" << endl;
		}
	}

	return 0;
}