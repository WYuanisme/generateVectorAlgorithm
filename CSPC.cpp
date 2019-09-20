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


#include "CSPC.h"
#include <math.h>
#include <vector>



CSPC::CSPC(int totalNetNum1)
{
    totalNetNum = totalNetNum1;
    column = ceil(log2(totalNetNum));            // MTV的列数=2*column
    vector<int> STV(2 * column, 0);              // 一个网络的STV，初始化为2*column个0
    for (int i = 0; i != totalNetNum; ++i)       // 第i个网络
    {
        vector<int> stv1(column, 0);             // 一个网络的原向量，初始化为column个0
        vector<int> stv2(column, 0);             // 一个网络的补偿向量，初始化为column个0
        // 把i转换成二进制数
        stv1=convertToBinary(i);
        // 把二进制数按位取反
        stv2 = reverse(stv1);
        // 把stv1和stv2拼起来存进STV
        for (unsigned int j = 0; j != column; ++j)
        {
            STV[j] = stv1[j];
            STV[j + column] = stv2[j];
        }
        // 第i个网络的STV生成好了，把它装进MTV里
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
    // 编程思路和画图计算二进制的思路一样的
    // 比如有7个网络，第二个网络，i=2，转换成二进制数只有2位，没有3位，所以要预先初始化容器，column个0，再给相应位赋值，就不会出现0~7的二进制数位数不同的情况，较小的数高位是0
    vector<int> binary(column, 0);            // 用来存放转换的二进制数，顺序存放，二进制数的最高位存第0位
    int quotient = decimal;                   // 商
    int remainder;                            // 余数 
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
    vector<int> reversedNumber;     // 存放 按位取反后的值
    for (unsigned  int i = 0; i != number.size(); ++i)
    {
        reversedNumber.push_back(number[i] ^ 1);    // 与1异或相当于取反：0与1异或为1，1与1异或为0
    }
    return reversedNumber;
}