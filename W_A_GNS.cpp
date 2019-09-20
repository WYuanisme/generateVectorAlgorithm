//----------------------------------------------------------------
// code by Wang Yuan
// date:2019/09/10
// function:GNS algorithm
// input:totalNetNum		output:MTV
//---------调试说明-----------------------------------------------
// 15组：组数=4，每组网络数=4，最后一组网络数=3
// 16组：组数=4，每组网络数=4，均匀分组
// 17组：组数=4，每组网络数=5，最后一组网络数=2
// 20组：组数=4，每组网络数=5，均匀分组
// 21组：组数=4，每组网络数=5，最后一组网络数=1
//
// 生成的所有测试向量FA、FB、FC保存在MTV中
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
    groupNetNum = ceil(sqrt(totalNetNum));              // 每组网络数
    double t = (double)totalNetNum / groupNetNum;
    groupNum = ceil((t));                               // 组数
    lastGroupNetNum = totalNetNum - (groupNum - 1)* groupNetNum;    // 最后一组网络数，如果分布均匀，最后一组网络数令为0
    if (lastGroupNetNum == groupNetNum)
    {
        lastGroupNetNum = 0;
    }

    //ofstream outfile;
    //outfile.open("C:\\Users\\10057\\Desktop\\gns_STV.txt");

    //-------------Fa 组间走步序列--------------------------------------------------
    vector<int> Fa(groupNetNum);	// Fa有groupNetNum个元素，每个元素的值都为0
    vector<vector<int> > FA;		// 创建一个空二维容器FA，实际容器大小为FA[totalNetNum][groupNetNum]

    int a;	// 注意a的作用域
    // 分组不均匀情况 
    if (lastGroupNetNum != 0)
    {
        // 生成第i组的Fa,共0~ （groupNum - 2）组,不包括最后一组
        for (int i = 0; i != groupNum - 1; ++i)
        {
            // 初始化Fa，使Fa所有（0~（groupNetNum-1）个）元素为1
            for (int k = 0; k != groupNetNum; ++k)
            {
                Fa[k] = 1;
            }
            // 第i组的Fa的第（groupNetNum - 1 - i）个元素为0，其余为1
            a = groupNetNum - 1 - i;
            Fa[a] = 0;
            // 输出第i组，0~（groupNetNum-1）个第j个网络的Fa，同组的Fa相同
            for (int j = 0; j != groupNetNum; ++j)
            {
                // 将生成的第j个网络的Fa存入FA
                FA.push_back(Fa);
            }
        }
        // 生成最后一组的Fa,有0~（lastGroupNetNum-1）个相同的Fa
        for (int j = 0; j != lastGroupNetNum; ++j)
        {
            // 初始化Fa，使Fa所有（0~（groupNetNum-1）个）元素为1
            for (int k = 0; k != groupNetNum; ++k)
            {
                Fa[k] = 1;
            }
            Fa[a - 1] = 0;
            FA.push_back(Fa);
        }
    }

    // 分组均匀的情况
    else
        // 生成第i组的Fa,共0~ （groupNum - 1）组
        for (int i = 0; i != groupNum; ++i)
        {
            // 初始化Fa，使Fa所有（0~（groupNetNum-1）个）元素为1
            for (int j = 0; j != groupNetNum; ++j)
            {
                Fa[j] = 1;
            }
            // 第i组的Fa的第（groupNetNum - 1 - i）个元素为0，其余为1
            a = groupNetNum - 1 - i;
            Fa[a] = 0;
            // 输出第i组，0~（groupNetNum-1）个网络的Fa，同组的Fa相同
            for (int k = 0; k != groupNetNum; ++k)
            {
                FA.push_back(Fa);
            }
        }

    //-------------Fb 组内走步序列--------------------------------------------------
    vector<int> Fb(groupNetNum);
    vector< vector<int> > FB;
    vector<int> A(0);
    // 多生成groupNetNum个元素是为了方便后面Fc移位
    for (int i = 0; i != 2; ++i)
    {
        for (int j = 0; j != groupNetNum; ++j)
        {
            A.push_back(groupNetNum - 1 - j);
        }
    }
    // 网络分组均匀
    if (lastGroupNetNum == 0)
    {
        // 第i组
        for (int i = 0; i != groupNum; ++i)
        {
            // 第i组的 第j个网络
            for (int j = 0; j != groupNetNum; ++j)
            {
                // 第i组的 第j个网络的 第k个元素//初始化第i组的第j个网络的Fb为全1
                for (int k = 0; k != groupNetNum; ++k)
                {
                    Fb[k] = 1;
                }
                //第j个网络的 第（groupNetNum - 1 - j）元素为0
                Fb[A[j]] = 0;
                FB.push_back(Fb);
            }
        }
    }
    // 网络分组分布不均匀
    else
    {
        // 生成第i组的Fb,共0~ （groupNum - 2）组,不包括最后一组
        for (int i = 0; i != groupNum - 1; ++i)
        {
            // 第i组的 第j个网络
            for (int j = 0; j != groupNetNum; ++j)
            {
                // 初始化第i组的第j个网络的Fb为全1
                for (int k = 0; k != groupNetNum; ++k)
                {
                    Fb[k] = 1;
                }
                // 第j个网络的 第（groupNetNum - 1 - j）元素为0
                Fb[A[j]] = 0;
                FB.push_back(Fb);
            }
        }
        // 生成最后一组的Fb
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

    //-------------Fc 移位的组内走步序列--------------------------------------------------
    vector<int> Fc(groupNetNum);
    vector< vector<int> > FC;
    // 网络分组均匀
    if (lastGroupNetNum == 0)
    {
        // 第i组
        for (int i = 0; i != groupNum; ++i)
        {
            // 第i组的 第j个网络
            for (int j = 0; j != groupNetNum; ++j)
            {
                // 初始化，全1
                for (int k = 0; k != groupNetNum; ++k)
                {
                    Fc[k] = 1;
                }
                Fc[A[j + i]] = 0;
                FC.push_back(Fc);
            }
        }
    }

    // 网络分组分布不均匀
    else
        // 生成第i组的Fc,共0~ （groupNum - 2）组,不包括最后一组
        for (int i = 0; i != groupNum - 1; i++)
        {
            // 第i组的 第j个网络
            for (int j = 0; j != groupNetNum; ++j)
            {
                // 初始化，全1
                for (int k = 0; k != groupNetNum; ++k)
                {
                    Fc[k] = 1;
                }
                Fc[A[j + i]] = 0;
                FC.push_back(Fc);
            }
        }
    // 生成最后一组的Fc
    for (int j = 0; j != lastGroupNetNum; ++j)
    {
        for (int k = 0; k != groupNetNum; ++k)
        {
            Fc[k] = 1;
        }
        Fc[A[j + groupNum - 1]] = 0;
        FC.push_back(Fc);
    }

    //------------将FA、FB、FC合并成STV--------------------------------------
    vector<int> mtv_temp(3 * groupNetNum);
    vector<vector<int>> MTV_temp(totalNetNum, vector<int>(mtv_temp));       // 用MTV_temp存储生成的测试向量

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

    MTV = MTV_temp; // 将生成的测试向量存入类的私有成员STV
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