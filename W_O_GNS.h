#pragma once
#include <vector>

using namespace std;
class W_O_GNS 
{
private:
    int totalNetNum;        // 网络总数
    int groupNetNum;        // 每组网络数 
    int groupNum;           // 组数 
    int lastGroupNetNum;    // 最后一组网络数,若分组均匀，lastGroupNetNum等于0
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

