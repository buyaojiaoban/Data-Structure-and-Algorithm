#include <iostream>
#include <vector>
#include <unordered_set> // ֻ��key
#include <unordered_map>
#include <stdlib.h>
#include <time.h>
#include <string>
using namespace std;


#if 0
int main()
{
	/*
	ģ�����⣬vector�з�ԭʼ������
	*/
	vector<int> vec;
	srand(time(NULL));
	for (int i = 0; i < 10000; i++)
	{
		vec.push_back(rand() % 10000);
	}
 
	// �ҵ�һ�������ظ�������
	unordered_set<int> s1;
	for (auto key : vec)
	{
		auto it = s1.find(key); // ��ϣ���ѯ O(1)
		if (it == s1.end()) // ��ʾû���ҵ���key�ǵ�һ�γ���
		{
			s1.insert(key);
		}
		else
		{
			cout << "key:" << key << endl;
			break;
		}
	}

	
	// �������ظ����ֵ�����  �Ͳ���break����    unordered_multiset����key�ظ�
	/*
	unordered_set<int> s2;  ������key�ظ�
	for (auto key : vec)
	{
		auto it = s2.find(key); // ��ϣ���ѯ O(1)
		if (it == s2.end()) // ��ʾû���ҵ���key�ǵ�һ�γ���
		{
			s2.insert(key);
		}
		else
		{
			cout << "key:" << key << endl;
		}
	}
	*/

	// ͳ���ظ������Լ����ֵĴ���
	unordered_map<int, int> m1;
	for (int key : vec)
	{
		/*
		// pair first second
		auto it = m1.find(key);
		if (it == m1.end())
		{
			m1.emplace(key, 1);
		}
		else
		{
			it->second += 1;
		}
		*/
		m1[key]++;
	}

	for (auto pair : m1)
	{
		if (pair.second > 1)
		{
			cout << "key:" << pair.first << " cnt:" << pair.second << endl;
		}
	}


	// һ��������Щ�������ظ��ģ����ظ������ֹ��˵���ÿ������ֻ����һ��
	unordered_set<int> s3; // ������key�ظ���ֱ�ӹ���
	for (auto key : vec)
	{
		s3.emplace(key);
	}

	return 0;
}
#endif


#if 0
int main()
{
	string src = "jjhfgiyuhtytrs"; // ��һ��ԭʼ�ַ������������ظ���Ҳ��û�ظ����ַ�
	// �����ҳ�����һ��û���ظ����ֹ����ַ�
	unordered_map<char, int> m;
	for (char ch : src)
	{
		m[ch]++;
	}

	for (char ch : src)
	{
		if (m[ch] == 1)
		{
			cout << "��һ��û���ظ����ֹ����ַ��ǣ�" << ch << endl;
			return 0;
		}
	}

	cout << "�����ַ������ظ����ֹ���" << endl;

	return 0;
}
#endif

/*
���ص������������

�������ļ��ֱ���a��b��������˺ܶ�ip��ַ(url��ַ��email��ַ)�������ҳ��������ļ��ظ���ip�����������

===> ��ϣ��(û�ж��ڴ����ǿ��) ��a�ļ������е�ip�����һ����ϣ���У�Ȼ�����α����ļ�b�����ip��ÿ����һ��ip���ڹ�ϣ��
������һ�£��ѵ��ģ����������ļ��ظ���ip������� �õ��˹�ϣ��Ĳ�ѯO(1)


�������ļ��ֱ���a��b�����Դ����Լ1����ip��ַ��ÿ��ip��ַ��4���ֽڣ������ڴ�ʹ��100M�����ҳ��������ļ����ظ�
��ip��ַ�������

1�� = 100M   1�ڸ�ip�����ϣ�� = 100*4 *2 = 800M
���÷���˼�룺�Ȱ������ļ����ֽ��С�ļ���
�磺a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,  b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11
Ȼ��ȥԴ�ļ�a��b�У���ip���ζ����� % 11 �õ�һ��Ͱ�±�,Ȼ��д���Ӧ��С�ļ�����
�������ÿһ���ļ���1ǧ���ip��ַ =�� 10M   �����ϣ�� 10M*4 *2 =80M����ʱ�Ϳ��Է����ڴ�����;��ʱֻ��Ҫa1��b1��b2��a2
���ؾͿ�����

*/
    