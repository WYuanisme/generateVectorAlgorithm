//----------------------------------------------------------------
// code by Wang Yuan
// date:2019/09/12
// function:Counting Sequence plus Complement algorithm (���������㷨)
// input:totalNetNum		output:MTV
//---------��������-----------------------------------------------
// ����������ԭ�����İ�λȡ��
// ��1����൱��ȡ����0��1���Ϊ1��1��1���Ϊ0
// ���ɵ����в�������FA��FB��FC������MTV��
//----------------------------------------------------------------


#include "CSPC.h"
#include <math.h>
#include <vector>



CSPC::CSPC(int totalNetNum1)
{
    totalNetNum = totalNetNum1;
    column = ceil(log2(totalNetNum));            // MTV������=2*column
    vector<int> STV(2 * column, 0);              // һ�������STV����ʼ��Ϊ2*column��0
    for (int i = 0; i != totalNetNum; ++i)       // ��i������
    {
        vector<int> stv1(column, 0);             // һ�������ԭ��������ʼ��Ϊcolumn��0
        vector<int> stv2(column, 0);             // һ������Ĳ�����������ʼ��Ϊcolumn��0
        // ��iת���ɶ�������
        stv1=convertToBinary(i);
        // �Ѷ���������λȡ��
        stv2 = reverse(stv1);
        // ��stv1��stv2ƴ�������STV
        for (unsigned int j = 0; j != column; ++j)
        {
            STV[j] = stv1[j];
            STV[j + column] = stv2[j];
        }
        // ��i�������STV���ɺ��ˣ�����װ��MTV��
        MTV.push_back(STV);
    }
}


CSPC::~CSPC()
{
}

vector<vector<int>> CSPC::getMTV()
{
    return MTV;
}

vector<int> CSPC::convertToBinary(int decimal)
{
    // ���˼·�ͻ�ͼ��������Ƶ�˼·һ����
    // ������7�����磬�ڶ������磬i=2��ת���ɶ�������ֻ��2λ��û��3λ������ҪԤ�ȳ�ʼ��������column��0���ٸ���Ӧλ��ֵ���Ͳ������0~7�Ķ�������λ����ͬ���������С������λ��0
    vector<int> binary(column, 0);            // �������ת���Ķ���������˳���ţ��������������λ���0λ
    int quotient = decimal;                   // ��
    int remainder;                            // ���� 
    unsigned  int index= column-1;
    while (quotient != 0)
    {
        remainder = quotient % 2;
        quotient = quotient / 2;
        binary[index] = remainder;
        --index;
    }
    return binary;
}

vector<int> CSPC::reverse(vector<int> number)
{
    vector<int> reversedNumber;     // ��� ��λȡ�����ֵ
    for (unsigned  int i = 0; i != number.size(); ++i)
    {
        reversedNumber.push_back(number[i] ^ 1);    // ��1����൱��ȡ����0��1���Ϊ1��1��1���Ϊ0
    }
    return reversedNumber;
}