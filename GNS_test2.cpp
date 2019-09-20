//---------调试说明-----------------------------------------------
//15组：组数=4，每组网络数=4，最后一组网络数=3
//16组：组数=4，每组网络数=4，均匀分组
//17组：组数=4，每组网络数=5，最后一组网络数=2
//20组：组数=4，每组网络数=5，均匀分组
//21组：组数=4，每组网络数=5，最后一组网络数=1
//
//生成的所有测试向量FA、FB、FC保存在桌面gns_result.txt中
//也保存在二维容器FA、FB、FC
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
	{
		lastGroupNetNum = 0;
	}
	else
	{
		cout << "分布不均，最后一组网络数：" << lastGroupNetNum << endl;
	}

	ofstream outfile;
	outfile.open("C:\\Users\\10057\\Desktop\\gns_result.txt");

	//-------------Fa 组间走步序列--------------------------------------------------
	vector<int> Fa(groupNetNum);	//Fa有groupNetNum个元素，每个元素的值都为0
	outfile << "\n Fa：" << endl;
	vector<vector<int> > FA;		//创建一个空二维容器FA，实际容器大小为FA[totalNetNum][groupNetNum]
									//vector对象能够高效增长，那么在定义vector对象的时候设定其大小也没什么必要了，事实上这么做性能可能更差
	
	int a;	//注意a的作用域
	if (lastGroupNetNum != 0)	//分组不均匀情况 
	{
		for (int i = 0; i != groupNum - 1; ++i)	 //生成第i组的Fa,共0~ （groupNum - 2）组,不包括最后一组
		{
			outfile << "第" << i << "组的Fa为：" << endl;
			for (int k = 0; k != groupNetNum; ++k)	//初始化Fa，使Fa所有（0~（groupNetNum-1）个）元素为0
			{
				Fa[k] = 0;
			}
			a = groupNetNum - 1 - i;	//第i组的Fa的第（groupNetNum - 1 - i）个元素为1，其余为0
			Fa[a] = 1;
			for (int j = 0; j != groupNetNum; ++j)	//输出第i组，0~（groupNetNum-1）个第j个网络的Fa，同组的Fa相同
			{
				FA.push_back(Fa);		//将生成的第j个网络的Fa存入FA
				outfile << ' ';
				for (auto it : Fa)  //范围for语句，可以遍历容器的所有元素//输出第i组第k个网络的Fa
				{
					outfile << it << ' ';
				}
				outfile << ' ' << ' ' << ' ' << ' ' << ' ';
				//for (int k = 0; k != groupNetNum; ++k)
				//{
			    //   FA[i * groupNetNum + j].push_back(Fa[k]);		//不知道为什么vector subscript（下标） out of range
				//}
			}
			outfile << "\n" << endl;	
		}
		outfile << "第" << groupNum - 1 << "组的Fa为：" << endl;
		for (int j = 0; j != lastGroupNetNum; ++j)	//生成最后一组的Fa,有0~（lastGroupNetNum-1）个相同的Fa
		{
			for (int k = 0; k != groupNetNum; ++k)	//初始化Fa，使Fa所有（0~（groupNetNum-1）个）元素为0
			{
				Fa[k] = 0;
			}
			Fa[a - 1] = 1;
			FA.push_back(Fa);
			outfile << ' ';
			for (auto it : Fa)
			{
				outfile << it << ' ';
				FA[(groupNum - 1)*groupNetNum + j].push_back(it);
			}
			outfile << ' ' << ' ' << ' ' << ' ' << ' ';	
		}
		outfile << "\n" << endl;
	}

	//分组均匀的情况
	else
		for (int i = 0; i != groupNum; ++i)		//生成第i组的Fa,共0~ （groupNum - 1）组
		{
			outfile << "第" << i << "组的Fa为：" << endl;
			for (int j = 0; j != groupNetNum; ++j)		//初始化Fa，使Fa所有（0~（groupNetNum-1）个）元素为0
			{
				Fa[j] = 0;
			}
			a = groupNetNum - 1 - i;		//第i组的Fa的第（groupNetNum - 1 - i）个元素为1，其余为0
			Fa[a] = 1;

			for (int k = 0; k != groupNetNum; ++k)		//输出第i组，0~（groupNetNum-1）个网络的Fa，同组的Fa相同
			{
				FA.push_back(Fa);
				outfile << ' ';
				for (auto it : Fa)		//输出第i组第k个网络的Fa
				{
					outfile << it << ' ';
				}
				outfile << ' ' << ' ' << ' ' << ' ' << ' ';
			}
			outfile << "\n" << endl;
		}

	//-------------Fb 组内走步序列--------------------------------------------------

	vector<int> Fb(groupNetNum);
	vector< vector<int> > FB;
	vector<int> A(0);
	for (int i = 0; i != 2; ++i)		//多生成groupNetNum个元素是为了方便后面Fc移位
	{
		for (int j = 0; j != groupNetNum; ++j)
		{
			A.push_back(groupNetNum - 1 - j);
		}
	}
	outfile << "\n Fb：" << endl;
	if (lastGroupNetNum == 0)		//网络分组均匀
	{
		for (int i = 0; i != groupNum; ++i)		//第i组
		{
			outfile << "第" << i << "组的Fb为：" << endl;
			for (int j = 0; j != groupNetNum; ++j)		//第i组的 第j个网络
			{
				for (int k = 0; k != groupNetNum; ++k)		//第i组的 第j个网络的 第k个元素//初始化第i组的第j个网络的Fb为全0
				{
					Fb[k] = 0;
				}
				Fb[A[j]] = 1;		//第j个网络的 第（groupNetNum - 1 - j）元素为1
				FB.push_back(Fb);
				outfile << ' ';
				for (auto it : Fb)		//输出第i组的 第j个网络的 Fb
				{
					outfile << it << ' ';
				}
				outfile << ' ' << ' ' << ' ' << ' ' << ' ';
			}
			outfile << "\n" << endl;
		}
	}
	//网络分组分布不均匀
	else
	{
		for (int i = 0; i != groupNum - 1; ++i)		//生成第i组的Fb,共0~ （groupNum - 2）组,不包括最后一组
		{
			outfile << "第" << i << "组的Fb为：" << endl;
			for (int j = 0; j != groupNetNum; ++j)		//第i组的 第j个网络
			{
				for (int k = 0; k != groupNetNum; ++k)		//初始化第i组的第j个网络的Fb为全0
				{
					Fb[k] = 0;
				}
				Fb[A[j]] = 1;		//第j个网络的 第（groupNetNum - 1 - j）元素为1
				FB.push_back(Fb);
				outfile << ' ';
				for (auto it : Fb)		//输出第i组的 第j个网络的 Fb
				{
					outfile << it << ' ';
				}
				outfile << ' ' << ' ' << ' ' << ' ' << ' ';
			}
			outfile << "\n" << endl;
		}
		outfile << "第" << groupNum - 1 << "组的Fb为：" << endl;
		for (int j = 0; j != lastGroupNetNum; ++j)		//生成最后一组的Fb
		{
			for (int k = 0; k != groupNetNum; ++k)
			{
				Fb[k] = 0;
			}
			Fb[A[j]] = 1;
			FB.push_back(Fb);
			outfile << ' ';
			for (auto it : Fb)
			{
				outfile << it << ' ';
			}
			outfile << ' ' << ' ' << ' ' << ' ' << ' ';
		}
		outfile << "\n" << endl;
	}

	//-------------Fc 移位的组内走步序列--------------------------------------------------

	vector<int> Fc(groupNetNum);
	vector< vector<int> > FC;
	outfile << "\n Fc：" << endl;

	if (lastGroupNetNum == 0)		//网络分组均匀
	{
		for (int i = 0; i != groupNum; ++i)		//第i组
		{
			for (int j = 0; j != groupNetNum; ++j)		//第i组的 第j个网络
			{
				for (int k = 0; k != groupNetNum; ++k)		//初始化，全0
				{
					Fc[k] = 0;
				}

				Fc[A[j + i]] = 1;
				FC.push_back(Fc);
				for (auto it : Fc)
				{
					outfile << it << ' ';
				}
				outfile << ' ' << ' ' << ' ' << ' ' << ' ';
			}
			outfile << "\n" << endl;
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
				FC.push_back(Fc);
				for (auto it : Fc)
				{
					outfile << it << ' ';
					FC[i*groupNetNum + j].push_back(it);
				}
				outfile << ' ' << ' ' << ' ' << ' ' << ' ';
			}
			outfile << "\n" << endl;
		}
	for (int j = 0; j != lastGroupNetNum; ++j)		//生成最后一组的Fc			
	{
		for (int k = 0; k != groupNetNum; ++k)
		{
			Fc[k] = 0;
		}
		Fc[A[j + groupNum - 1]] = 1;
		FC.push_back(Fc);
		for (auto it : Fc)
		{
			outfile << it << ' ';
		}
		outfile << ' ' << ' ' << ' ' << ' ' << ' ';
	}
	outfile << "\n" << endl;

 outfile.close();
 system("pause");
}