#include "Walk_1.h"

#include <vector>


using namespace std;

Walk_1::Walk_1(int totalNetNum1)
{
    totalNetNum = totalNetNum1;
    for (int i=0;i!=totalNetNum;++i)    // ��i������
    {
        vector<int> STV_temp;           // ��һ����ʱ�������i�������STV
        for (int j = 0; j != totalNetNum; ++j)
        {
            if (i == j)                  // MTV�ĶԽ���ֵΪ1
            {
                STV_temp.push_back(1);
            }
            else
            {
                STV_temp.push_back(0);
            }
        }
        MTV.push_back(STV_temp);
    }
}


Walk_1::~Walk_1()
{
}

vector<vector<int>> Walk_1::getMTV()
{
    return MTV;
}
