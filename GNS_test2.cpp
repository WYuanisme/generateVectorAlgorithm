//---------����˵��-----------------------------------------------
//15�飺����=4��ÿ��������=4�����һ��������=3
//16�飺����=4��ÿ��������=4�����ȷ���
//17�飺����=4��ÿ��������=5�����һ��������=2
//20�飺����=4��ÿ��������=5�����ȷ���
//21�飺����=4��ÿ��������=5�����һ��������=1
//
//���ɵ����в�������FA��FB��FC����������gns_result.txt��
//Ҳ�����ڶ�ά����FA��FB��FC
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
	{
		lastGroupNetNum = 0;
	}
	else
	{
		cout << "�ֲ����������һ����������" << lastGroupNetNum << endl;
	}

	ofstream outfile;
	outfile.open("C:\\Users\\10057\\Desktop\\gns_result.txt");

	//-------------Fa ����߲�����--------------------------------------------------
	vector<int> Fa(groupNetNum);	//Fa��groupNetNum��Ԫ�أ�ÿ��Ԫ�ص�ֵ��Ϊ0
	outfile << "\n Fa��" << endl;
	vector<vector<int> > FA;		//����һ���ն�ά����FA��ʵ��������СΪFA[totalNetNum][groupNetNum]
									//vector�����ܹ���Ч��������ô�ڶ���vector�����ʱ���趨���СҲûʲô��Ҫ�ˣ���ʵ����ô�����ܿ��ܸ���
	
	int a;	//ע��a��������
	if (lastGroupNetNum != 0)	//���鲻������� 
	{
		for (int i = 0; i != groupNum - 1; ++i)	 //���ɵ�i���Fa,��0~ ��groupNum - 2����,���������һ��
		{
			outfile << "��" << i << "���FaΪ��" << endl;
			for (int k = 0; k != groupNetNum; ++k)	//��ʼ��Fa��ʹFa���У�0~��groupNetNum-1������Ԫ��Ϊ0
			{
				Fa[k] = 0;
			}
			a = groupNetNum - 1 - i;	//��i���Fa�ĵڣ�groupNetNum - 1 - i����Ԫ��Ϊ1������Ϊ0
			Fa[a] = 1;
			for (int j = 0; j != groupNetNum; ++j)	//�����i�飬0~��groupNetNum-1������j�������Fa��ͬ���Fa��ͬ
			{
				FA.push_back(Fa);		//�����ɵĵ�j�������Fa����FA
				outfile << ' ';
				for (auto it : Fa)  //��Χfor��䣬���Ա�������������Ԫ��//�����i���k�������Fa
				{
					outfile << it << ' ';
				}
				outfile << ' ' << ' ' << ' ' << ' ' << ' ';
				//for (int k = 0; k != groupNetNum; ++k)
				//{
			    //   FA[i * groupNetNum + j].push_back(Fa[k]);		//��֪��Ϊʲôvector subscript���±꣩ out of range
				//}
			}
			outfile << "\n" << endl;	
		}
		outfile << "��" << groupNum - 1 << "���FaΪ��" << endl;
		for (int j = 0; j != lastGroupNetNum; ++j)	//�������һ���Fa,��0~��lastGroupNetNum-1������ͬ��Fa
		{
			for (int k = 0; k != groupNetNum; ++k)	//��ʼ��Fa��ʹFa���У�0~��groupNetNum-1������Ԫ��Ϊ0
			{
				Fa[k] = 0;
			}
			Fa[a - 1] = 1;
			FA.push_back(Fa);
			outfile << ' ';
			for (auto it : Fa)
			{
				outfile << it << ' ';
				FA[(groupNum - 1)*groupNetNum + j].push_back(it);
			}
			outfile << ' ' << ' ' << ' ' << ' ' << ' ';	
		}
		outfile << "\n" << endl;
	}

	//������ȵ����
	else
		for (int i = 0; i != groupNum; ++i)		//���ɵ�i���Fa,��0~ ��groupNum - 1����
		{
			outfile << "��" << i << "���FaΪ��" << endl;
			for (int j = 0; j != groupNetNum; ++j)		//��ʼ��Fa��ʹFa���У�0~��groupNetNum-1������Ԫ��Ϊ0
			{
				Fa[j] = 0;
			}
			a = groupNetNum - 1 - i;		//��i���Fa�ĵڣ�groupNetNum - 1 - i����Ԫ��Ϊ1������Ϊ0
			Fa[a] = 1;

			for (int k = 0; k != groupNetNum; ++k)		//�����i�飬0~��groupNetNum-1���������Fa��ͬ���Fa��ͬ
			{
				FA.push_back(Fa);
				outfile << ' ';
				for (auto it : Fa)		//�����i���k�������Fa
				{
					outfile << it << ' ';
				}
				outfile << ' ' << ' ' << ' ' << ' ' << ' ';
			}
			outfile << "\n" << endl;
		}

	//-------------Fb �����߲�����--------------------------------------------------

	vector<int> Fb(groupNetNum);
	vector< vector<int> > FB;
	vector<int> A(0);
	for (int i = 0; i != 2; ++i)		//������groupNetNum��Ԫ����Ϊ�˷������Fc��λ
	{
		for (int j = 0; j != groupNetNum; ++j)
		{
			A.push_back(groupNetNum - 1 - j);
		}
	}
	outfile << "\n Fb��" << endl;
	if (lastGroupNetNum == 0)		//����������
	{
		for (int i = 0; i != groupNum; ++i)		//��i��
		{
			outfile << "��" << i << "���FbΪ��" << endl;
			for (int j = 0; j != groupNetNum; ++j)		//��i��� ��j������
			{
				for (int k = 0; k != groupNetNum; ++k)		//��i��� ��j������� ��k��Ԫ��//��ʼ����i��ĵ�j�������FbΪȫ0
				{
					Fb[k] = 0;
				}
				Fb[A[j]] = 1;		//��j������� �ڣ�groupNetNum - 1 - j��Ԫ��Ϊ1
				FB.push_back(Fb);
				outfile << ' ';
				for (auto it : Fb)		//�����i��� ��j������� Fb
				{
					outfile << it << ' ';
				}
				outfile << ' ' << ' ' << ' ' << ' ' << ' ';
			}
			outfile << "\n" << endl;
		}
	}
	//�������ֲ�������
	else
	{
		for (int i = 0; i != groupNum - 1; ++i)		//���ɵ�i���Fb,��0~ ��groupNum - 2����,���������һ��
		{
			outfile << "��" << i << "���FbΪ��" << endl;
			for (int j = 0; j != groupNetNum; ++j)		//��i��� ��j������
			{
				for (int k = 0; k != groupNetNum; ++k)		//��ʼ����i��ĵ�j�������FbΪȫ0
				{
					Fb[k] = 0;
				}
				Fb[A[j]] = 1;		//��j������� �ڣ�groupNetNum - 1 - j��Ԫ��Ϊ1
				FB.push_back(Fb);
				outfile << ' ';
				for (auto it : Fb)		//�����i��� ��j������� Fb
				{
					outfile << it << ' ';
				}
				outfile << ' ' << ' ' << ' ' << ' ' << ' ';
			}
			outfile << "\n" << endl;
		}
		outfile << "��" << groupNum - 1 << "���FbΪ��" << endl;
		for (int j = 0; j != lastGroupNetNum; ++j)		//�������һ���Fb
		{
			for (int k = 0; k != groupNetNum; ++k)
			{
				Fb[k] = 0;
			}
			Fb[A[j]] = 1;
			FB.push_back(Fb);
			outfile << ' ';
			for (auto it : Fb)
			{
				outfile << it << ' ';
			}
			outfile << ' ' << ' ' << ' ' << ' ' << ' ';
		}
		outfile << "\n" << endl;
	}

	//-------------Fc ��λ�������߲�����--------------------------------------------------

	vector<int> Fc(groupNetNum);
	vector< vector<int> > FC;
	outfile << "\n Fc��" << endl;

	if (lastGroupNetNum == 0)		//����������
	{
		for (int i = 0; i != groupNum; ++i)		//��i��
		{
			for (int j = 0; j != groupNetNum; ++j)		//��i��� ��j������
			{
				for (int k = 0; k != groupNetNum; ++k)		//��ʼ����ȫ0
				{
					Fc[k] = 0;
				}

				Fc[A[j + i]] = 1;
				FC.push_back(Fc);
				for (auto it : Fc)
				{
					outfile << it << ' ';
				}
				outfile << ' ' << ' ' << ' ' << ' ' << ' ';
			}
			outfile << "\n" << endl;
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
				FC.push_back(Fc);
				for (auto it : Fc)
				{
					outfile << it << ' ';
					FC[i*groupNetNum + j].push_back(it);
				}
				outfile << ' ' << ' ' << ' ' << ' ' << ' ';
			}
			outfile << "\n" << endl;
		}
	for (int j = 0; j != lastGroupNetNum; ++j)		//�������һ���Fc			
	{
		for (int k = 0; k != groupNetNum; ++k)
		{
			Fc[k] = 0;
		}
		Fc[A[j + groupNum - 1]] = 1;
		FC.push_back(Fc);
		for (auto it : Fc)
		{
			outfile << it << ' ';
		}
		outfile << ' ' << ' ' << ' ' << ' ' << ' ';
	}
	outfile << "\n" << endl;

 outfile.close();
 system("pause");
}