//---------����˵��-----------------------------------------------
//15�飺����=4��ÿ��������=4�����һ��������=3
//16�飺����=4��ÿ��������=4�����ȷ���
//17�飺����=4��ÿ��������=5�����һ��������=2
//20�飺����=4��ÿ��������=5�����ȷ���
//21�飺����=4��ÿ��������=5�����һ��������=1
//----------------------------------------------------------------


#include<iostream>
#include <stdio.h> 
#include <stdlib.h>
#include <string>
#include <Math.h>
#include<vector>
#include<fstream>
#include <regex>
#include <sstream>
using namespace std;

int main()
{
	//-------------�������--------------------------------------------------
	int totalNetNum;
	cout << "������������Ϊ��";
	cin >> totalNetNum;
	int groupNetNum = ceil(sqrt(totalNetNum));
	cout << "ÿ��������Ϊ��" << groupNetNum << endl;
	double t = (double)totalNetNum / groupNetNum;
	int groupNum = ceil((t));
	cout << "����Ϊ��" << groupNum << endl;
	int lastGroupNetNum = totalNetNum - (groupNum - 1)* groupNetNum;

	if (lastGroupNetNum == groupNetNum)
	{ lastGroupNetNum = 0; }
	else
	{ cout << "�ֲ����������һ����������" << lastGroupNetNum << endl;}

	//ofstream outfile;
	//outfile.open("C:\\Users\\10057\\Desktop\\gns_result.txt");

	//-------------Fa ����߲�����--------------------------------------------------
	vector<int> Fa(groupNetNum);	//Fa��groupNum��Ԫ�أ�ÿ��Ԫ�ص�ֵ��Ϊ0
	cout << "\n Fa��" << endl;

	int a;	//ע��a��������
	if (lastGroupNetNum != 0)	//���鲻������� 
	{
		for (int i = 0; i != groupNum - 1; ++i)	 //���ɵ�i���Fa,��0~ ��groupNum - 2����,���������һ��
		{
			cout << "��" << i << "���FaΪ��" << endl;
			for (int j = 0; j != groupNetNum; ++j)	//��ʼ��Fa��ʹFa���У�0~��groupNetNum-1������Ԫ��Ϊ0
			{ Fa[j] = 0; }
			a = groupNetNum - 1 - i;	//��i���Fa�ĵڣ�groupNetNum - 1 - i����Ԫ��Ϊ1������Ϊ0
			Fa[a] = 1;
			for (int k = 0; k != groupNetNum; ++k)	//�����i�飬0~��groupNetNum-1���������Fa��ͬ���Fa��ͬ
			{
				cout << ' ' ;
				for (auto it : Fa)  //��Χfor��䣬���Ա�������������Ԫ��//�����i���k�������Fa
				{ 
					cout << it << ' ';
				/*	outfile << it << ' ';*/
				}
				cout << ' ' << ' ' << ' ' << ' ' << ' ';
				/*outfile << ' ' << ' ' << ' ' << ' ' << ' ';*/
			}
			cout << "\n" << endl;
			/*outfile << "\n" << endl;*/
		}
		cout << "��" << groupNum - 1 << "���FaΪ��" << endl;
		for (int i = 0; i != lastGroupNetNum; ++i)	//�������һ���Fa,��0~��lastGroupNetNum-1������ͬ��Fa
		{
			for (int j = 0; j != groupNetNum; ++j)	//��ʼ��Fa��ʹFa���У�0~��groupNetNum-1������Ԫ��Ϊ0
			{ Fa[j] = 0;}
			Fa[a - 1] = 1;
			cout << ' ';
			for (auto it : Fa)
			{ 
				cout << it << ' ';
			/*	outfile << it << ' ';*/
			}
			cout << ' ' << ' ' << ' ' << ' ' << ' ';
			/*outfile << ' ' << ' ' << ' ' << ' ' << ' ';*/
		}
		cout << "\n" << endl;
	}

	//������ȵ����
	else  
		for (int i = 0; i != groupNum; ++i)		//���ɵ�i���Fa,��0~ ��groupNum - 1����
		{
			cout << "��" << i << "���FaΪ��" << endl;
			for (int j = 0; j != groupNetNum; ++j)		//��ʼ��Fa��ʹFa���У�0~��groupNetNum-1������Ԫ��Ϊ0
			{ Fa[j] = 0; }
			a = groupNetNum - 1 - i;		//��i���Fa�ĵڣ�groupNetNum - 1 - i����Ԫ��Ϊ1������Ϊ0
			Fa[a] = 1;

			for (int k = 0; k != groupNetNum; ++k)		//�����i�飬0~��groupNetNum-1���������Fa��ͬ���Fa��ͬ
			{
				cout << ' ';
				for (auto it : Fa)		//�����i���k�������Fa
				{ cout << it << ' ';}
				cout << ' ' << ' ' << ' ' << ' ' << ' ';
			}
			cout << "\n" << endl;
		}

	//-------------Fb �����߲�����--------------------------------------------------

	vector<int> Fb(groupNetNum);
	//�����λ
	vector<int> A(0);
	cout << "\n Fb��" << endl;

	for (int i = 0; i != 2; ++i)
	{
		for (int j = 0; j != groupNetNum; ++j)
		{
			A.push_back((groupNetNum - 1 - j));
		}
	}

	if (lastGroupNetNum == 0)		//����������
	{
		for (int i = 0; i != groupNum; ++i)		//��i��
		{
			cout << "��" << i << "���FbΪ��" << endl;
			for (int j = 0; j != groupNetNum; ++j)		//��i��� ��j������
			{
				for (int k = 0; k != groupNetNum; ++k)		//��i��� ��j������� ��k��Ԫ��//��ʼ����i��ĵ�j�������FbΪȫ0
				{
					Fb[k] = 0;
				}
				Fb[A[j]] = 1;		//��j������� �ڣ�groupNetNum - 1 - j��Ԫ��Ϊ1
				cout << ' ';
				for (auto it : Fb)		//�����i��� ��j������� Fb
				{
					cout << it << ' ';
				}
				cout << ' ' << ' ' << ' ' << ' ' << ' ';
			}
			cout << "\n" << endl;
		}
	}
	//�������ֲ�������
	else
	{
		for (int i = 0; i != groupNum - 1; ++i)		//���ɵ�i���Fb,��0~ ��groupNum - 2����,���������һ��
		{
			cout << "��" << i << "���FbΪ��" << endl;
			for (int j = 0; j != groupNetNum; ++j)		//��i��� ��j������
			{
				for (int k = 0; k != groupNetNum; ++k)		//��ʼ����i��ĵ�j�������FbΪȫ0
				{ Fb[k] = 0;}
				Fb[A[j]] = 1;		//��j������� �ڣ�groupNetNum - 1 - j��Ԫ��Ϊ1
				cout << ' ';
				for (auto it : Fb)		//�����i��� ��j������� Fb
				{ cout << it << ' '; }
				cout << ' ' << ' ' << ' ' << ' ' << ' ';
			}
			cout << "\n" << endl;
		}
		cout << "��" << groupNum - 1 << "���FbΪ��" << endl;
		for (int j = 0; j != lastGroupNetNum; ++j)		//�������һ���Fb
		{
			for (int k = 0; k != groupNetNum; ++k)
			{ Fb[k] = 0; }
			Fb[A[j]] = 1;
			cout << ' ';
			for (auto it : Fb)
			{ cout << it << ' '; }
			cout << ' ' << ' ' << ' ' << ' ' << ' ';
		}
		cout << "\n" << endl;
	}

	//-------------Fc ��λ�������߲�����--------------------------------------------------

	vector<int> Fc(groupNetNum);
	cout << "\n Fc��" << endl;
	
	if (lastGroupNetNum == 0)		//����������
	{
		for (int i = 0; i != groupNum; ++i)		//��i��
		{
			for (int j = 0; j != groupNetNum; ++j)		//��i��� ��j������
			{
				for (int k = 0; k != groupNetNum; ++k)		//��ʼ����ȫ0
				{	Fc[k] = 0;}

				Fc[A[j + i]] = 1;
				for (auto it : Fc)
				{
					cout << it << ' ';
				}
				cout << ' ' << ' ' << ' ' << ' ' << ' ';
			}
			cout << "\n" << endl;
		}
	}

	//�������ֲ�������
	else
		for (int i = 0; i != groupNum - 1; i++)		//���ɵ�i���Fc,��0~ ��groupNum - 2����,���������һ��
		{
			for (int j = 0; j != groupNetNum; ++j)		//��i��� ��j������
			{
				for (int k = 0; k != groupNetNum; ++k)		//��ʼ����ȫ0
				{
					Fc[k] = 0;
				}

				Fc[A[j + i]] = 1;

				for (auto it : Fc)
				{
					cout << it << ' ';
				}
				cout << ' ' << ' ' << ' ' << ' ' << ' ';
			}
			cout << "\n" << endl;
		}
	for (int j = 0; j != lastGroupNetNum; ++j)		//�������һ���Fc			
	{
		for (int k = 0; k != groupNetNum; ++k)
		{
			Fc[k] = 0;
		}
		Fc[A[j + groupNum-1]] = 1;
		for (auto it : Fc)
		{
			cout << it << ' ';
		}
		cout << ' ' << ' ' << ' ' << ' ' << ' ';
	}
	cout << "\n" << endl;




	outfile.close();





	system("pause");

}