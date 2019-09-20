//----------------------------------------------------------------
// code by Wang Yuan
// date:2019/07
// function:GNS algorithm
// input:totalNetNum		output:STV��gns_PTV.txt
//---------����˵��-----------------------------------------------
// 15�飺����=4��ÿ��������=4�����һ��������=3
// 16�飺����=4��ÿ��������=4�����ȷ���
// 17�飺����=4��ÿ��������=5�����һ��������=2
// 20�飺����=4��ÿ��������=5�����ȷ���
// 21�飺����=4��ÿ��������=5�����һ��������=1
//
// ���ɵ����в�������FA��FB��FC����������gns_PTV.txt��
// Ҳ�����ڶ�ά��������STV��PTV��
//----------------------------------------------------------------

#if 0
#include<iostream>
#include <stdio.h> 
#include <stdlib.h>
#include <string>
#include <math.h>
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
	outfile.open("C:\\Users\\10057\\Desktop\\gns_PTV.txt");

	//-------------Fa ����߲�����--------------------------------------------------
	vector<int> Fa(groupNetNum);	// Fa��groupNetNum��Ԫ�أ�ÿ��Ԫ�ص�ֵ��Ϊ0
	vector<vector<int> > FA;		// ����һ���ն�ά����FA��ʵ��������СΪFA[totalNetNum][groupNetNum]
									// vector�����ܹ���Ч��������ô�ڶ���vector�����ʱ���趨���СҲûʲô��Ҫ�ˣ���ʵ����ô�����ܿ��ܸ���

	int a;	// ע��a��������
	if (lastGroupNetNum != 0)	// ���鲻������� 
	{
		for (int i = 0; i != groupNum - 1; ++i)	 //���ɵ�i���Fa,��0~ ��groupNum - 2����,���������һ��
		{
			for (int k = 0; k != groupNetNum; ++k)	//��ʼ��Fa��ʹFa���У�0~��groupNetNum-1������Ԫ��Ϊ0
			{
				Fa[k] = 0;
			}
			a = groupNetNum - 1 - i;	//��i���Fa�ĵڣ�groupNetNum - 1 - i����Ԫ��Ϊ1������Ϊ0
			Fa[a] = 1;
			for (int j = 0; j != groupNetNum; ++j)	//�����i�飬0~��groupNetNum-1������j�������Fa��ͬ���Fa��ͬ
			{
				FA.push_back(Fa);		//�����ɵĵ�j�������Fa����FA
			}
		}
		for (int j = 0; j != lastGroupNetNum; ++j)	//�������һ���Fa,��0~��lastGroupNetNum-1������ͬ��Fa
		{
			for (int k = 0; k != groupNetNum; ++k)	//��ʼ��Fa��ʹFa���У�0~��groupNetNum-1������Ԫ��Ϊ0
			{
				Fa[k] = 0;
			}
			Fa[a - 1] = 1;
			FA.push_back(Fa);
		}
	}

	//������ȵ����
	else
		for (int i = 0; i != groupNum; ++i)		//���ɵ�i���Fa,��0~ ��groupNum - 1����
		{
			for (int j = 0; j != groupNetNum; ++j)		//��ʼ��Fa��ʹFa���У�0~��groupNetNum-1������Ԫ��Ϊ0
			{
				Fa[j] = 0;
			}
			a = groupNetNum - 1 - i;		//��i���Fa�ĵڣ�groupNetNum - 1 - i����Ԫ��Ϊ1������Ϊ0
			Fa[a] = 1;
			for (int k = 0; k != groupNetNum; ++k)		//�����i�飬0~��groupNetNum-1���������Fa��ͬ���Fa��ͬ
			{
				FA.push_back(Fa);
			}
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
	if (lastGroupNetNum == 0)		//����������
	{
		for (int i = 0; i != groupNum; ++i)		//��i��
		{
			for (int j = 0; j != groupNetNum; ++j)		//��i��� ��j������
			{
				for (int k = 0; k != groupNetNum; ++k)		//��i��� ��j������� ��k��Ԫ��//��ʼ����i��ĵ�j�������FbΪȫ0
				{
					Fb[k] = 0;
				}
				Fb[A[j]] = 1;		//��j������� �ڣ�groupNetNum - 1 - j��Ԫ��Ϊ1
				FB.push_back(Fb);
			}
		}
	}
	//�������ֲ�������
	else
	{
		for (int i = 0; i != groupNum - 1; ++i)		//���ɵ�i���Fb,��0~ ��groupNum - 2����,���������һ��
		{
			for (int j = 0; j != groupNetNum; ++j)		//��i��� ��j������
			{
				for (int k = 0; k != groupNetNum; ++k)		//��ʼ����i��ĵ�j�������FbΪȫ0
				{
					Fb[k] = 0;
				}
				Fb[A[j]] = 1;		//��j������� �ڣ�groupNetNum - 1 - j��Ԫ��Ϊ1
				FB.push_back(Fb);
			}
		}
		for (int j = 0; j != lastGroupNetNum; ++j)		//�������һ���Fb
		{
			for (int k = 0; k != groupNetNum; ++k)
			{
				Fb[k] = 0;
			}
			Fb[A[j]] = 1;
			FB.push_back(Fb);
		}
	}

	//-------------Fc ��λ�������߲�����--------------------------------------------------
	vector<int> Fc(groupNetNum);
	vector< vector<int> > FC;

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
			}
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
			}
		}
	for (int j = 0; j != lastGroupNetNum; ++j)		//�������һ���Fc			
	{
		for (int k = 0; k != groupNetNum; ++k)
		{
			Fc[k] = 0;
		}
		Fc[A[j + groupNum - 1]] = 1;
		FC.push_back(Fc);
	}

	//------------��FA��FB��FC�ϲ���STV--------------------------------------
	vector<int> stv_intermediate(3 * groupNetNum);
	vector<vector<int>> STV(totalNetNum, vector<int>(stv_intermediate));

	for (int i = 0; i != totalNetNum; ++i)
	{
		for (int j = 0; j != groupNetNum; ++j)
		{
			STV[i][j] = FA[i][j];
		}
		for (int j = 0; j != groupNetNum; ++j)
		{
			STV[i][j + groupNetNum] = FB[i][j];
		}
		for (int j = 0; j != groupNetNum; ++j)
		{
			STV[i][j + 2 * groupNetNum] = FC[i][j];
		}
	}

	for (int i = 0; i != totalNetNum; ++i)
	{
		for (int j = 0; j != 3 * groupNetNum; ++j)
		{
			outfile << STV[i][j];
		}
		outfile << "\n";
	}

	//vector<int> ptv_intermediate(totalNetNum);
	//vector<vector<int>> PTV(3 * groupNetNum, vector<int>(ptv_intermediate));
	//for (int i = 0; i != 3 * groupNetNum; ++i)
	//{
	//	for (int j = 0; j != totalNetNum; ++j)
	//	{
	//		PTV[i][j] = STV[j][i];
	//	}
	//}


	outfile.close();
	system("pause");
}

#endif