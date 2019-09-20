//----------------------------------------------------------------
// code by Wang Yuan
// date:2019/07
// function:GNS algorithm
// input:totalNetNum		output:STV、gns_STV.txt
//---------调试说明-----------------------------------------------
// 15组：组数=4，每组网络数=4，最后一组网络数=3
// 16组：组数=4，每组网络数=4，均匀分组
// 17组：组数=4，每组网络数=5，最后一组网络数=2
// 20组：组数=4，每组网络数=5，均匀分组
// 21组：组数=4，每组网络数=5，最后一组网络数=1
//
// 生成的所有测试向量FA、FB、FC保存在桌面gns_STV.txt中
// 也保存在二维向量容器STV、PTV中
//----------------------------------------------------------------
#if 0

#include<iostream>
#include <stdio.h> 
#include <stdlib.h>
#include <string>
#include <Math.h>
#include<vector>
#include<fstream>
#include <regex>
#include <sstream>

using namespace std;
int totalNetNum;    // 互联网络总数，全局变量

class GNS {
private:
    int groupNetNum;        // 每组网络数 gns[0]
    int groupNum;           // 组数 gns[1]
    int lastGroupNetNum;    // 最后一组网络数,gns[2] ,若分组均匀，lastGroupNetNum等于0
    vector<vector<int>> STV;
public:
    GNS(const int totalNetNum);         // 构造函数
    int operator[](int index) const;    // 下标运算符重载
    vector<vector<int>> generateSTV();  // 生成STV
};

// 构造函数
GNS::GNS(const int totalNetNum) {
    groupNetNum = ceil(sqrt(totalNetNum));
    double t = (double)totalNetNum / groupNetNum;
    groupNum = ceil((t));
    lastGroupNetNum = totalNetNum - (groupNum - 1)* groupNetNum;
    if (lastGroupNetNum == groupNetNum) {
        lastGroupNetNum = 0;
    }
}
// 下标运算符重载
int GNS::operator[](int index) const {
    if (index == 0) {
        return groupNetNum;
    }
    else if (index == 1) {
        return groupNum;
    }
    else if (index == 2) {
        return lastGroupNetNum;
    }
    else {
        throw "下标非法";   //抛出异常
    }
}

// 生成STV
vector<vector<int>> GNS::generateSTV() {
    ofstream outfile;
    outfile.open("C:\\Users\\10057\\Desktop\\gns_STV.txt");

    //-------------Fa 组间走步序列--------------------------------------------------
    vector<int> Fa(groupNetNum);	// Fa有groupNetNum个元素，每个元素的值都为0
    vector<vector<int> > FA;		// 创建一个空二维容器FA，实际容器大小为FA[totalNetNum][groupNetNum]
                                    
    int a;	// 注意a的作用域
    // 分组不均匀情况 
    if (lastGroupNetNum != 0) {	
        // 生成第i组的Fa,共0~ （groupNum - 2）组,不包括最后一组
        for (int i = 0; i != groupNum - 1; ++i) {	
            // 初始化Fa，使Fa所有（0~（groupNetNum-1）个）元素为0
            for (int k = 0; k != groupNetNum; ++k) {	
                Fa[k] = 0;
            }
            // 第i组的Fa的第（groupNetNum - 1 - i）个元素为1，其余为0
            a = groupNetNum - 1 - i;	
            Fa[a] = 1;
            // 输出第i组，0~（groupNetNum-1）个第j个网络的Fa，同组的Fa相同
            for (int j = 0; j != groupNetNum; ++j) {
                // 将生成的第j个网络的Fa存入FA
                FA.push_back(Fa);		
            }
        }
        // 生成最后一组的Fa,有0~（lastGroupNetNum-1）个相同的Fa
        for (int j = 0; j != lastGroupNetNum; ++j) {	
            // 初始化Fa，使Fa所有（0~（groupNetNum-1）个）元素为0
            for (int k = 0; k != groupNetNum; ++k) {	
                Fa[k] = 0;
            }
            Fa[a - 1] = 1;
            FA.push_back(Fa);
        }
    }

    // 分组均匀的情况
    else
        // 生成第i组的Fa,共0~ （groupNum - 1）组
        for (int i = 0; i != groupNum; ++i) {
            // 初始化Fa，使Fa所有（0~（groupNetNum-1）个）元素为0
            for (int j = 0; j != groupNetNum; ++j) {	
                Fa[j] = 0;
            }
            // 第i组的Fa的第（groupNetNum - 1 - i）个元素为1，其余为0
            a = groupNetNum - 1 - i;		
            Fa[a] = 1;
            // 输出第i组，0~（groupNetNum-1）个网络的Fa，同组的Fa相同
            for (int k = 0; k != groupNetNum; ++k) {		
                FA.push_back(Fa);
            }
        }

    //-------------Fb 组内走步序列--------------------------------------------------
    vector<int> Fb(groupNetNum);
    vector< vector<int> > FB;
    vector<int> A(0);
    // 多生成groupNetNum个元素是为了方便后面Fc移位
    for (int i = 0; i != 2; ++i) {		
        for (int j = 0; j != groupNetNum; ++j) {
            A.push_back(groupNetNum - 1 - j);
        }
    }
    // 网络分组均匀
    if (lastGroupNetNum == 0) {		
        // 第i组
        for (int i = 0; i != groupNum; ++i) {	
            // 第i组的 第j个网络
            for (int j = 0; j != groupNetNum; ++j) {	
                // 第i组的 第j个网络的 第k个元素//初始化第i组的第j个网络的Fb为全0
                for (int k = 0; k != groupNetNum; ++k) {		
                    Fb[k] = 0;
                }
                //第j个网络的 第（groupNetNum - 1 - j）元素为1
                Fb[A[j]] = 1;		
                FB.push_back(Fb);
            }
        }
    }
    // 网络分组分布不均匀
    else {
        // 生成第i组的Fb,共0~ （groupNum - 2）组,不包括最后一组
        for (int i = 0; i != groupNum - 1; ++i) {
            // 第i组的 第j个网络
            for (int j = 0; j != groupNetNum; ++j) {
                // 初始化第i组的第j个网络的Fb为全0
                for (int k = 0; k != groupNetNum; ++k) {		
                    Fb[k] = 0;
                }
                // 第j个网络的 第（groupNetNum - 1 - j）元素为1
                Fb[A[j]] = 1;		
                FB.push_back(Fb);
            }
        } 
        // 生成最后一组的Fb
        for (int j = 0; j != lastGroupNetNum; ++j) {		
            for (int k = 0; k != groupNetNum; ++k) {
                Fb[k] = 0;
            }
            Fb[A[j]] = 1;
            FB.push_back(Fb);
        }
    }

    //-------------Fc 移位的组内走步序列--------------------------------------------------
    vector<int> Fc(groupNetNum);
    vector< vector<int> > FC;
    // 网络分组均匀
    if (lastGroupNetNum == 0) {	
        // 第i组
        for (int i = 0; i != groupNum; ++i) {	
            // 第i组的 第j个网络
            for (int j = 0; j != groupNetNum; ++j) {
                // 初始化，全0
                for (int k = 0; k != groupNetNum; ++k) {
                    Fc[k] = 0;
                }
                Fc[A[j + i]] = 1;
                FC.push_back(Fc);
            }
        }
    }

    // 网络分组分布不均匀
    else
        // 生成第i组的Fc,共0~ （groupNum - 2）组,不包括最后一组
        for (int i = 0; i != groupNum - 1; i++) {	
            // 第i组的 第j个网络
            for (int j = 0; j != groupNetNum; ++j) {
                // 初始化，全0
                for (int k = 0; k != groupNetNum; ++k) {		
                    Fc[k] = 0;
                }
                Fc[A[j + i]] = 1;
                FC.push_back(Fc);
            }
        }
    // 生成最后一组的Fc
    for (int j = 0; j != lastGroupNetNum; ++j) {					
        for (int k = 0; k != groupNetNum; ++k) {
            Fc[k] = 0;
        }
        Fc[A[j + groupNum - 1]] = 1;
        FC.push_back(Fc);
    }

    //------------将FA、FB、FC合并成STV--------------------------------------
    vector<int> stv1(3 * groupNetNum);
    vector<vector<int>> STV1(totalNetNum, vector<int>(stv1));       // 用STV1存储生成的测试向量

    for (int i = 0; i != totalNetNum; ++i) {
        for (int j = 0; j != groupNetNum; ++j) {
            STV1[i][j] = FA[i][j];
        }
        for (int j = 0; j != groupNetNum; ++j) {
            STV1[i][j + groupNetNum] = FB[i][j];
        }
        for (int j = 0; j != groupNetNum; ++j) {
            STV1[i][j + 2 * groupNetNum] = FC[i][j];
        }
    }

    for (int i = 0; i != totalNetNum; ++i) {
        for (int j = 0; j != 3 * groupNetNum; ++j) {
            outfile << STV1[i][j];
        }
        outfile << "\n";
    }
    outfile.close();
    STV = STV1; // 将生成的测试向量存入类的私有成员STV
    return STV;
}




int main(){
    cout << "互联网络总数为：";
    cin >> totalNetNum;
    GNS gns(totalNetNum);
    cout << "每组网络数为：" << gns[0] << endl;
    cout << "组数为：" << gns[1] << endl;
    if (gns[2] != 0) {
        cout << "分布不均，最后一组网络数：" << gns[2] << endl;
    }
    vector<vector<int>> stv;
    stv = gns.generateSTV();

    system("pause");
}

#endif