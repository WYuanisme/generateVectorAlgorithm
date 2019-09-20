//---------调试说明-----------------------------------------------
//15组：组数=4，每组网络数=4，最后一组网络数=3
//16组：组数=4，每组网络数=4，均匀分组
//17组：组数=4，每组网络数=5，最后一组网络数=2
//20组：组数=4，每组网络数=5，均匀分组
//21组：组数=4，每组网络数=5，最后一组网络数=1
//----------------------------------------------------------------


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

int main()
{
	//-------------网络分组--------------------------------------------------
	int totalNetNum;
	cout << "互联网络总数为：";
	cin >> totalNetNum;
	int groupNetNum = ceil(sqrt(totalNetNum));
	cout << "每组网络数为：" << groupNetNum << endl;
	double t = (double)totalNetNum / groupNetNum;
	int groupNum = ceil((t));
	cout << "组数为：" << groupNum << endl;
	int lastGroupNetNum = totalNetNum - (groupNum - 1)* groupNetNum;

	if (lastGroupNetNum == groupNetNum)
	{ lastGroupNetNum = 0; }
	else
	{ cout << "分布不均，最后一组网络数：" << lastGroupNetNum << endl;}

	//ofstream outfile;
	//outfile.open("C:\\Users\\10057\\Desktop\\gns_result.txt");

	//-------------Fa 组间走步序列--------------------------------------------------
	vector<int> Fa(groupNetNum);	//Fa有groupNum个元素，每个元素的值都为0
	cout << "\n Fa：" << endl;

	int a;	//注意a的作用域
	if (lastGroupNetNum != 0)	//分组不均匀情况 
	{
		for (int i = 0; i != groupNum - 1; ++i)	 //生成第i组的Fa,共0~ （groupNum - 2）组,不包括最后一组
		{
			cout << "第" << i << "组的Fa为：" << endl;
			for (int j = 0; j != groupNetNum; ++j)	//初始化Fa，使Fa所有（0~（groupNetNum-1）个）元素为0
			{ Fa[j] = 0; }
			a = groupNetNum - 1 - i;	//第i组的Fa的第（groupNetNum - 1 - i）个元素为1，其余为0
			Fa[a] = 1;
			for (int k = 0; k != groupNetNum; ++k)	//输出第i组，0~（groupNetNum-1）个网络的Fa，同组的Fa相同
			{
				cout << ' ' ;
				for (auto it : Fa)  //范围for语句，可以遍历容器的所有元素//输出第i组第k个网络的Fa
				{ 
					cout << it << ' ';
				/*	outfile << it << ' ';*/
				}
				cout << ' ' << ' ' << ' ' << ' ' << ' ';
				/*outfile << ' ' << ' ' << ' ' << ' ' << ' ';*/
			}
			cout << "\n" << endl;
			/*outfile << "\n" << endl;*/
		}
		cout << "第" << groupNum - 1 << "组的Fa为：" << endl;
		for (int i = 0; i != lastGroupNetNum; ++i)	//生成最后一组的Fa,有0~（lastGroupNetNum-1）个相同的Fa
		{
			for (int j = 0; j != groupNetNum; ++j)	//初始化Fa，使Fa所有（0~（groupNetNum-1）个）元素为0
			{ Fa[j] = 0;}
			Fa[a - 1] = 1;
			cout << ' ';
			for (auto it : Fa)
			{ 
				cout << it << ' ';
			/*	outfile << it << ' ';*/
			}
			cout << ' ' << ' ' << ' ' << ' ' << ' ';
			/*outfile << ' ' << ' ' << ' ' << ' ' << ' ';*/
		}
		cout << "\n" << endl;
	}

	//分组均匀的情况
	else  
		for (int i = 0; i != groupNum; ++i)		//生成第i组的Fa,共0~ （groupNum - 1）组
		{
			cout << "第" << i << "组的Fa为：" << endl;
			for (int j = 0; j != groupNetNum; ++j)		//初始化Fa，使Fa所有（0~（groupNetNum-1）个）元素为0
			{ Fa[j] = 0; }
			a = groupNetNum - 1 - i;		//第i组的Fa的第（groupNetNum - 1 - i）个元素为1，其余为0
			Fa[a] = 1;

			for (int k = 0; k != groupNetNum; ++k)		//输出第i组，0~（groupNetNum-1）个网络的Fa，同组的Fa相同
			{
				cout << ' ';
				for (auto it : Fa)		//输出第i组第k个网络的Fa
				{ cout << it << ' ';}
				cout << ' ' << ' ' << ' ' << ' ' << ' ';
			}
			cout << "\n" << endl;
		}

	//-------------Fb 组内走步序列--------------------------------------------------

	vector<int> Fb(groupNetNum);
	//组间移位
	vector<int> A(0);
	cout << "\n Fb：" << endl;

	for (int i = 0; i != 2; ++i)
	{
		for (int j = 0; j != groupNetNum; ++j)
		{
			A.push_back((groupNetNum - 1 - j));
		}
	}

	if (lastGroupNetNum == 0)		//网络分组均匀
	{
		for (int i = 0; i != groupNum; ++i)		//第i组
		{
			cout << "第" << i << "组的Fb为：" << endl;
			for (int j = 0; j != groupNetNum; ++j)		//第i组的 第j个网络
			{
				for (int k = 0; k != groupNetNum; ++k)		//第i组的 第j个网络的 第k个元素//初始化第i组的第j个网络的Fb为全0
				{
					Fb[k] = 0;
				}
				Fb[A[j]] = 1;		//第j个网络的 第（groupNetNum - 1 - j）元素为1
				cout << ' ';
				for (auto it : Fb)		//输出第i组的 第j个网络的 Fb
				{
					cout << it << ' ';
				}
				cout << ' ' << ' ' << ' ' << ' ' << ' ';
			}
			cout << "\n" << endl;
		}
	}
	//网络分组分布不均匀
	else
	{
		for (int i = 0; i != groupNum - 1; ++i)		//生成第i组的Fb,共0~ （groupNum - 2）组,不包括最后一组
		{
			cout << "第" << i << "组的Fb为：" << endl;
			for (int j = 0; j != groupNetNum; ++j)		//第i组的 第j个网络
			{
				for (int k = 0; k != groupNetNum; ++k)		//初始化第i组的第j个网络的Fb为全0
				{ Fb[k] = 0;}
				Fb[A[j]] = 1;		//第j个网络的 第（groupNetNum - 1 - j）元素为1
				cout << ' ';
				for (auto it : Fb)		//输出第i组的 第j个网络的 Fb
				{ cout << it << ' '; }
				cout << ' ' << ' ' << ' ' << ' ' << ' ';
			}
			cout << "\n" << endl;
		}
		cout << "第" << groupNum - 1 << "组的Fb为：" << endl;
		for (int j = 0; j != lastGroupNetNum; ++j)		//生成最后一组的Fb
		{
			for (int k = 0; k != groupNetNum; ++k)
			{ Fb[k] = 0; }
			Fb[A[j]] = 1;
			cout << ' ';
			for (auto it : Fb)
			{ cout << it << ' '; }
			cout << ' ' << ' ' << ' ' << ' ' << ' ';
		}
		cout << "\n" << endl;
	}

	//-------------Fc 移位的组内走步序列--------------------------------------------------

	vector<int> Fc(groupNetNum);
	cout << "\n Fc：" << endl;
	
	if (lastGroupNetNum == 0)		//网络分组均匀
	{
		for (int i = 0; i != groupNum; ++i)		//第i组
		{
			for (int j = 0; j != groupNetNum; ++j)		//第i组的 第j个网络
			{
				for (int k = 0; k != groupNetNum; ++k)		//初始化，全0
				{	Fc[k] = 0;}

				Fc[A[j + i]] = 1;
				for (auto it : Fc)
				{
					cout << it << ' ';
				}
				cout << ' ' << ' ' << ' ' << ' ' << ' ';
			}
			cout << "\n" << endl;
		}
	}

	//网络分组分布不均匀
	else
		for (int i = 0; i != groupNum - 1; i++)		//生成第i组的Fc,共0~ （groupNum - 2）组,不包括最后一组
		{
			for (int j = 0; j != groupNetNum; ++j)		//第i组的 第j个网络
			{
				for (int k = 0; k != groupNetNum; ++k)		//初始化，全0
				{
					Fc[k] = 0;
				}

				Fc[A[j + i]] = 1;

				for (auto it : Fc)
				{
					cout << it << ' ';
				}
				cout << ' ' << ' ' << ' ' << ' ' << ' ';
			}
			cout << "\n" << endl;
		}
	for (int j = 0; j != lastGroupNetNum; ++j)		//生成最后一组的Fc			
	{
		for (int k = 0; k != groupNetNum; ++k)
		{
			Fc[k] = 0;
		}
		Fc[A[j + groupNum-1]] = 1;
		for (auto it : Fc)
		{
			cout << it << ' ';
		}
		cout << ' ' << ' ' << ' ' << ' ' << ' ';
	}
	cout << "\n" << endl;




	outfile.close();





	system("pause");

}