//----------------------------------------------------------------
// code by Wang Yuan
// date:2019/09/12
// function:Counting Sequence plus Complement algorithm (计数补偿算法)
// input:totalNetNum		output:MTV
//---------————-----------------------------------------------

#pragma once

#include <vector>

using namespace std;

class CSPC
{
private:
    int totalNetNum;             // 网络总数
    unsigned  int column;                  // MTV的列数=2*column
    vector<vector<int>> MTV;
    // 私有函数，只有类内部的函数才能使用它们
    vector<int> convertToBinary(int decimal);   // 十进制数转换成二进制数
    vector<int> reverse(vector<int> number);    // 按位取反
public:
    CSPC()=default;
    CSPC(int totalNetNum1);
    virtual ~CSPC();
    vector<vector<int>> getMTV();
};

