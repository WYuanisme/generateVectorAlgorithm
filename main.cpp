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

#include<iostream>
#include<vector>
#include "CSPC.h"

using namespace std;

int main()
{
    int totalNetNum;
    cout << "������������Ϊ��";
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
