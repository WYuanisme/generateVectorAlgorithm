#pragma once
#include <vector>

using namespace std;
class W_A_GNS
{
private:
    int totalNetNum;        // ��������
    int groupNetNum;        // ÿ�������� 
    int groupNum;           // ���� 
    int lastGroupNetNum;    // ���һ��������,��������ȣ�lastGroupNetNum����0
    vector<vector<int>> MTV;
public:
    W_A_GNS() = default;
    W_A_GNS(int totalNetNum1);
    virtual ~W_A_GNS();
    vector<vector<int>> getMTV();
    int getGroupNum();
    int getGroupNetNum();
    int getLastGroupNetNum();
};

