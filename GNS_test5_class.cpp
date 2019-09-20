//----------------------------------------------------------------
// code by Wang Yuan
// date:2019/07
// function:GNS algorithm
// input:totalNetNum		output:STV��gns_STV.txt
//---------����˵��-----------------------------------------------
// 15�飺����=4��ÿ��������=4�����һ��������=3
// 16�飺����=4��ÿ��������=4�����ȷ���
// 17�飺����=4��ÿ��������=5�����һ��������=2
// 20�飺����=4��ÿ��������=5�����ȷ���
// 21�飺����=4��ÿ��������=5�����һ��������=1
//
// ���ɵ����в�������FA��FB��FC����������gns_STV.txt��
// Ҳ�����ڶ�ά��������STV��PTV��
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
int totalNetNum;    // ��������������ȫ�ֱ���

class GNS {
private:
    int groupNetNum;        // ÿ�������� gns[0]
    int groupNum;           // ���� gns[1]
    int lastGroupNetNum;    // ���һ��������,gns[2] ,��������ȣ�lastGroupNetNum����0
    vector<vector<int>> STV;
public:
    GNS(const int totalNetNum);         // ���캯��
    int operator[](int index) const;    // �±����������
    vector<vector<int>> generateSTV();  // ����STV
};

// ���캯��
GNS::GNS(const int totalNetNum) {
    groupNetNum = ceil(sqrt(totalNetNum));
    double t = (double)totalNetNum / groupNetNum;
    groupNum = ceil((t));
    lastGroupNetNum = totalNetNum - (groupNum - 1)* groupNetNum;
    if (lastGroupNetNum == groupNetNum) {
        lastGroupNetNum = 0;
    }
}
// �±����������
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
        throw "�±�Ƿ�";   //�׳��쳣
    }
}

// ����STV
vector<vector<int>> GNS::generateSTV() {
    ofstream outfile;
    outfile.open("C:\\Users\\10057\\Desktop\\gns_STV.txt");

    //-------------Fa ����߲�����--------------------------------------------------
    vector<int> Fa(groupNetNum);	// Fa��groupNetNum��Ԫ�أ�ÿ��Ԫ�ص�ֵ��Ϊ0
    vector<vector<int> > FA;		// ����һ���ն�ά����FA��ʵ��������СΪFA[totalNetNum][groupNetNum]
                                    
    int a;	// ע��a��������
    // ���鲻������� 
    if (lastGroupNetNum != 0) {	
        // ���ɵ�i���Fa,��0~ ��groupNum - 2����,���������һ��
        for (int i = 0; i != groupNum - 1; ++i) {	
            // ��ʼ��Fa��ʹFa���У�0~��groupNetNum-1������Ԫ��Ϊ0
            for (int k = 0; k != groupNetNum; ++k) {	
                Fa[k] = 0;
            }
            // ��i���Fa�ĵڣ�groupNetNum - 1 - i����Ԫ��Ϊ1������Ϊ0
            a = groupNetNum - 1 - i;	
            Fa[a] = 1;
            // �����i�飬0~��groupNetNum-1������j�������Fa��ͬ���Fa��ͬ
            for (int j = 0; j != groupNetNum; ++j) {
                // �����ɵĵ�j�������Fa����FA
                FA.push_back(Fa);		
            }
        }
        // �������һ���Fa,��0~��lastGroupNetNum-1������ͬ��Fa
        for (int j = 0; j != lastGroupNetNum; ++j) {	
            // ��ʼ��Fa��ʹFa���У�0~��groupNetNum-1������Ԫ��Ϊ0
            for (int k = 0; k != groupNetNum; ++k) {	
                Fa[k] = 0;
            }
            Fa[a - 1] = 1;
            FA.push_back(Fa);
        }
    }

    // ������ȵ����
    else
        // ���ɵ�i���Fa,��0~ ��groupNum - 1����
        for (int i = 0; i != groupNum; ++i) {
            // ��ʼ��Fa��ʹFa���У�0~��groupNetNum-1������Ԫ��Ϊ0
            for (int j = 0; j != groupNetNum; ++j) {	
                Fa[j] = 0;
            }
            // ��i���Fa�ĵڣ�groupNetNum - 1 - i����Ԫ��Ϊ1������Ϊ0
            a = groupNetNum - 1 - i;		
            Fa[a] = 1;
            // �����i�飬0~��groupNetNum-1���������Fa��ͬ���Fa��ͬ
            for (int k = 0; k != groupNetNum; ++k) {		
                FA.push_back(Fa);
            }
        }

    //-------------Fb �����߲�����--------------------------------------------------
    vector<int> Fb(groupNetNum);
    vector< vector<int> > FB;
    vector<int> A(0);
    // ������groupNetNum��Ԫ����Ϊ�˷������Fc��λ
    for (int i = 0; i != 2; ++i) {		
        for (int j = 0; j != groupNetNum; ++j) {
            A.push_back(groupNetNum - 1 - j);
        }
    }
    // ����������
    if (lastGroupNetNum == 0) {		
        // ��i��
        for (int i = 0; i != groupNum; ++i) {	
            // ��i��� ��j������
            for (int j = 0; j != groupNetNum; ++j) {	
                // ��i��� ��j������� ��k��Ԫ��//��ʼ����i��ĵ�j�������FbΪȫ0
                for (int k = 0; k != groupNetNum; ++k) {		
                    Fb[k] = 0;
                }
                //��j������� �ڣ�groupNetNum - 1 - j��Ԫ��Ϊ1
                Fb[A[j]] = 1;		
                FB.push_back(Fb);
            }
        }
    }
    // �������ֲ�������
    else {
        // ���ɵ�i���Fb,��0~ ��groupNum - 2����,���������һ��
        for (int i = 0; i != groupNum - 1; ++i) {
            // ��i��� ��j������
            for (int j = 0; j != groupNetNum; ++j) {
                // ��ʼ����i��ĵ�j�������FbΪȫ0
                for (int k = 0; k != groupNetNum; ++k) {		
                    Fb[k] = 0;
                }
                // ��j������� �ڣ�groupNetNum - 1 - j��Ԫ��Ϊ1
                Fb[A[j]] = 1;		
                FB.push_back(Fb);
            }
        } 
        // �������һ���Fb
        for (int j = 0; j != lastGroupNetNum; ++j) {		
            for (int k = 0; k != groupNetNum; ++k) {
                Fb[k] = 0;
            }
            Fb[A[j]] = 1;
            FB.push_back(Fb);
        }
    }

    //-------------Fc ��λ�������߲�����--------------------------------------------------
    vector<int> Fc(groupNetNum);
    vector< vector<int> > FC;
    // ����������
    if (lastGroupNetNum == 0) {	
        // ��i��
        for (int i = 0; i != groupNum; ++i) {	
            // ��i��� ��j������
            for (int j = 0; j != groupNetNum; ++j) {
                // ��ʼ����ȫ0
                for (int k = 0; k != groupNetNum; ++k) {
                    Fc[k] = 0;
                }
                Fc[A[j + i]] = 1;
                FC.push_back(Fc);
            }
        }
    }

    // �������ֲ�������
    else
        // ���ɵ�i���Fc,��0~ ��groupNum - 2����,���������һ��
        for (int i = 0; i != groupNum - 1; i++) {	
            // ��i��� ��j������
            for (int j = 0; j != groupNetNum; ++j) {
                // ��ʼ����ȫ0
                for (int k = 0; k != groupNetNum; ++k) {		
                    Fc[k] = 0;
                }
                Fc[A[j + i]] = 1;
                FC.push_back(Fc);
            }
        }
    // �������һ���Fc
    for (int j = 0; j != lastGroupNetNum; ++j) {					
        for (int k = 0; k != groupNetNum; ++k) {
            Fc[k] = 0;
        }
        Fc[A[j + groupNum - 1]] = 1;
        FC.push_back(Fc);
    }

    //------------��FA��FB��FC�ϲ���STV--------------------------------------
    vector<int> stv1(3 * groupNetNum);
    vector<vector<int>> STV1(totalNetNum, vector<int>(stv1));       // ��STV1�洢���ɵĲ�������

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
    STV = STV1; // �����ɵĲ��������������˽�г�ԱSTV
    return STV;
}




int main(){
    cout << "������������Ϊ��";
    cin >> totalNetNum;
    GNS gns(totalNetNum);
    cout << "ÿ��������Ϊ��" << gns[0] << endl;
    cout << "����Ϊ��" << gns[1] << endl;
    if (gns[2] != 0) {
        cout << "�ֲ����������һ����������" << gns[2] << endl;
    }
    vector<vector<int>> stv;
    stv = gns.generateSTV();

    system("pause");
}

#endif