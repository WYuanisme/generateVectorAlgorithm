//----------------------------------------------------------------
// code by Wang Yuan
// date:2019/09/10
// function:GNS algorithm
// input:totalNetNum		output:MTV
//---------����˵��-----------------------------------------------
// 15�飺����=4��ÿ��������=4�����һ��������=3
// 16�飺����=4��ÿ��������=4�����ȷ���
// 17�飺����=4��ÿ��������=5�����һ��������=2
// 20�飺����=4��ÿ��������=5�����ȷ���
// 21�飺����=4��ÿ��������=5�����һ��������=1
//
// ���ɵ����в�������FA��FB��FC������MTV��
//----------------------------------------------------------------


#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <fstream>
#include <sstream>
#include "W_A_GNS.h"



W_A_GNS::W_A_GNS(int totalNetNum1)
{
    totalNetNum = totalNetNum1;
    groupNetNum = ceil(sqrt(totalNetNum));              // ÿ��������
    double t = (double)totalNetNum / groupNetNum;
    groupNum = ceil((t));                               // ����
    lastGroupNetNum = totalNetNum - (groupNum - 1)* groupNetNum;    // ���һ��������������ֲ����ȣ����һ����������Ϊ0
    if (lastGroupNetNum == groupNetNum)
    {
        lastGroupNetNum = 0;
    }

    //ofstream outfile;
    //outfile.open("C:\\Users\\10057\\Desktop\\gns_STV.txt");

    //-------------Fa ����߲�����--------------------------------------------------
    vector<int> Fa(groupNetNum);	// Fa��groupNetNum��Ԫ�أ�ÿ��Ԫ�ص�ֵ��Ϊ0
    vector<vector<int> > FA;		// ����һ���ն�ά����FA��ʵ��������СΪFA[totalNetNum][groupNetNum]

    int a;	// ע��a��������
    // ���鲻������� 
    if (lastGroupNetNum != 0)
    {
        // ���ɵ�i���Fa,��0~ ��groupNum - 2����,���������һ��
        for (int i = 0; i != groupNum - 1; ++i)
        {
            // ��ʼ��Fa��ʹFa���У�0~��groupNetNum-1������Ԫ��Ϊ1
            for (int k = 0; k != groupNetNum; ++k)
            {
                Fa[k] = 1;
            }
            // ��i���Fa�ĵڣ�groupNetNum - 1 - i����Ԫ��Ϊ0������Ϊ1
            a = groupNetNum - 1 - i;
            Fa[a] = 0;
            // �����i�飬0~��groupNetNum-1������j�������Fa��ͬ���Fa��ͬ
            for (int j = 0; j != groupNetNum; ++j)
            {
                // �����ɵĵ�j�������Fa����FA
                FA.push_back(Fa);
            }
        }
        // �������һ���Fa,��0~��lastGroupNetNum-1������ͬ��Fa
        for (int j = 0; j != lastGroupNetNum; ++j)
        {
            // ��ʼ��Fa��ʹFa���У�0~��groupNetNum-1������Ԫ��Ϊ1
            for (int k = 0; k != groupNetNum; ++k)
            {
                Fa[k] = 1;
            }
            Fa[a - 1] = 0;
            FA.push_back(Fa);
        }
    }

    // ������ȵ����
    else
        // ���ɵ�i���Fa,��0~ ��groupNum - 1����
        for (int i = 0; i != groupNum; ++i)
        {
            // ��ʼ��Fa��ʹFa���У�0~��groupNetNum-1������Ԫ��Ϊ1
            for (int j = 0; j != groupNetNum; ++j)
            {
                Fa[j] = 1;
            }
            // ��i���Fa�ĵڣ�groupNetNum - 1 - i����Ԫ��Ϊ0������Ϊ1
            a = groupNetNum - 1 - i;
            Fa[a] = 0;
            // �����i�飬0~��groupNetNum-1���������Fa��ͬ���Fa��ͬ
            for (int k = 0; k != groupNetNum; ++k)
            {
                FA.push_back(Fa);
            }
        }

    //-------------Fb �����߲�����--------------------------------------------------
    vector<int> Fb(groupNetNum);
    vector< vector<int> > FB;
    vector<int> A(0);
    // ������groupNetNum��Ԫ����Ϊ�˷������Fc��λ
    for (int i = 0; i != 2; ++i)
    {
        for (int j = 0; j != groupNetNum; ++j)
        {
            A.push_back(groupNetNum - 1 - j);
        }
    }
    // ����������
    if (lastGroupNetNum == 0)
    {
        // ��i��
        for (int i = 0; i != groupNum; ++i)
        {
            // ��i��� ��j������
            for (int j = 0; j != groupNetNum; ++j)
            {
                // ��i��� ��j������� ��k��Ԫ��//��ʼ����i��ĵ�j�������FbΪȫ1
                for (int k = 0; k != groupNetNum; ++k)
                {
                    Fb[k] = 1;
                }
                //��j������� �ڣ�groupNetNum - 1 - j��Ԫ��Ϊ0
                Fb[A[j]] = 0;
                FB.push_back(Fb);
            }
        }
    }
    // �������ֲ�������
    else
    {
        // ���ɵ�i���Fb,��0~ ��groupNum - 2����,���������һ��
        for (int i = 0; i != groupNum - 1; ++i)
        {
            // ��i��� ��j������
            for (int j = 0; j != groupNetNum; ++j)
            {
                // ��ʼ����i��ĵ�j�������FbΪȫ1
                for (int k = 0; k != groupNetNum; ++k)
                {
                    Fb[k] = 1;
                }
                // ��j������� �ڣ�groupNetNum - 1 - j��Ԫ��Ϊ0
                Fb[A[j]] = 0;
                FB.push_back(Fb);
            }
        }
        // �������һ���Fb
        for (int j = 0; j != lastGroupNetNum; ++j)
        {
            for (int k = 0; k != groupNetNum; ++k)
            {
                Fb[k] = 1;
            }
            Fb[A[j]] = 0;
            FB.push_back(Fb);
        }
    }

    //-------------Fc ��λ�������߲�����--------------------------------------------------
    vector<int> Fc(groupNetNum);
    vector< vector<int> > FC;
    // ����������
    if (lastGroupNetNum == 0)
    {
        // ��i��
        for (int i = 0; i != groupNum; ++i)
        {
            // ��i��� ��j������
            for (int j = 0; j != groupNetNum; ++j)
            {
                // ��ʼ����ȫ1
                for (int k = 0; k != groupNetNum; ++k)
                {
                    Fc[k] = 1;
                }
                Fc[A[j + i]] = 0;
                FC.push_back(Fc);
            }
        }
    }

    // �������ֲ�������
    else
        // ���ɵ�i���Fc,��0~ ��groupNum - 2����,���������һ��
        for (int i = 0; i != groupNum - 1; i++)
        {
            // ��i��� ��j������
            for (int j = 0; j != groupNetNum; ++j)
            {
                // ��ʼ����ȫ1
                for (int k = 0; k != groupNetNum; ++k)
                {
                    Fc[k] = 1;
                }
                Fc[A[j + i]] = 0;
                FC.push_back(Fc);
            }
        }
    // �������һ���Fc
    for (int j = 0; j != lastGroupNetNum; ++j)
    {
        for (int k = 0; k != groupNetNum; ++k)
        {
            Fc[k] = 1;
        }
        Fc[A[j + groupNum - 1]] = 0;
        FC.push_back(Fc);
    }

    //------------��FA��FB��FC�ϲ���STV--------------------------------------
    vector<int> mtv_temp(3 * groupNetNum);
    vector<vector<int>> MTV_temp(totalNetNum, vector<int>(mtv_temp));       // ��MTV_temp�洢���ɵĲ�������

    for (int i = 0; i != totalNetNum; ++i)
    {
        for (int j = 0; j != groupNetNum; ++j)
        {
            MTV_temp[i][j] = FA[i][j];
        }
        for (int j = 0; j != groupNetNum; ++j)
        {
            MTV_temp[i][j + groupNetNum] = FB[i][j];
        }
        for (int j = 0; j != groupNetNum; ++j)
        {
            MTV_temp[i][j + 2 * groupNetNum] = FC[i][j];
        }
    }

    //for (int i = 0; i != totalNetNum; ++i) 
    //{
    //    for (int j = 0; j != 3 * groupNetNum; ++j)
    //    {
    //        outfile << MTV_temp[i][j];
    //    }
    //    outfile << "\n";
    //}
    //outfile.close();

    MTV = MTV_temp; // �����ɵĲ��������������˽�г�ԱSTV
}


W_A_GNS::~W_A_GNS()
{
}
vector<vector<int>> W_A_GNS::getMTV()
{
    return MTV;
}
int W_A_GNS::getGroupNum()
{
    return groupNum;
}
int W_A_GNS::getGroupNetNum()
{
    return groupNetNum;
}
int W_A_GNS::getLastGroupNetNum()
{
    return lastGroupNetNum;
}