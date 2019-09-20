//----------------------------------------------------------------
// code by Wang Yuan
// date:2019/09/12
// function:Counting Sequence plus Complement algorithm (���������㷨)
// input:totalNetNum		output:MTV
//---------��������-----------------------------------------------

#pragma once

#include <vector>

using namespace std;

class CSPC
{
private:
    int totalNetNum;             // ��������
    unsigned  int column;                  // MTV������=2*column
    vector<vector<int>> MTV;
    // ˽�к�����ֻ�����ڲ��ĺ�������ʹ������
    vector<int> convertToBinary(int decimal);   // ʮ������ת���ɶ�������
    vector<int> reverse(vector<int> number);    // ��λȡ��
public:
    CSPC()=default;
    CSPC(int totalNetNum1);
    virtual ~CSPC();
    vector<vector<int>> getMTV();
};

