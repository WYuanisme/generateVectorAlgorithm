#pragma once
#include <vector>

using namespace std;
class W_O_GNS 
{
private:
    int totalNetNum;        // ��������
    int groupNetNum;        // ÿ�������� 
    int groupNum;           // ���� 
    int lastGroupNetNum;    // ���һ��������,��������ȣ�lastGroupNetNum����0
    vector<vector<int>> MTV;
public:
    W_O_GNS()=default;
    virtual ~W_O_GNS();
    W_O_GNS(int totalNetNum1);     
    vector<vector<int>> getMTV();
    int getGroupNum();
    int getGroupNetNum();
    int getLastGroupNetNum();
};

