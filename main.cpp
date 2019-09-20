//----------------------------------------------------------------
// code by Wang Yuan
// date:2019/09/12
// function:Counting Sequence plus Complement algorithm (计数补偿算法)
// input:totalNetNum		output:MTV
//---------————-----------------------------------------------
// 附加向量是原向量的按位取反
// 与1异或相当于取反：0与1异或为1，1与1异或为0
// 生成的所有测试向量FA、FB、FC保存在MTV中
//----------------------------------------------------------------

#include<iostream>
#include<vector>
#include "CSPC.h"

using namespace std;

int main()
{
    int totalNetNum;
    cout << "互联网络总数为：";
    cin >> totalNetNum;
    CSPC * p = new CSPC(totalNetNum);
    vector<vector<int>> MTV = p->getMTV();
    for (int i = 0; i != MTV.size(); ++i)
    {
        for (int j = 0; j != MTV[i].size(); ++j)
        {
            cout << MTV[i][j];
        }
        cout << "\n";
    }
    delete p;
    p = nullptr;

    system("pause");
}
