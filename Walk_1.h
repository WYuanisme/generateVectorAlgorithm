#pragma once
#include <vector>

using namespace std;

class Walk_1
{
private:
    vector<vector<int>> MTV;
    int totalNetNum;
public:
    Walk_1()=default;
    Walk_1(int totalNetNum1);
    virtual ~Walk_1();
    vector<vector<int>> getMTV();
};

