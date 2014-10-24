#include <iostream>
#include <vector>
#include <time.h>
using namespace std;
#include "Select.h"
#define  N 10   //排序数组大小
#define  K 100   //排序数组范围0～K
////打印数组
void print_element(vector<int> A)
{
	int len=A.size();
	for (int i=0;i<len;i++)
	{
		std::cout<<A[i]<<" ";
	}
	std::cout<<std::endl;
}
int main()
{
	Select <int> s1;
	int a[10]={23,4,34,345,3,21,45,246,98,50};
	vector<int> vec_int(a,a+10);
	cout<<"原始数组"<<endl;
	print_element(vec_int);
	// 期望线性时间做选择测试
	cout<<"期望线性时间做选择测试"<<endl;
	for(int i=1;i<=N;i++)
	{
		int kMin=s1.RandomSelect(vec_int,0,N-1,i);
		cout<<"第"<<i<<"小的数是："<<kMin<<endl;
	}
	//最坏情况线性时间的选择测试
	cout<<"最坏情况线性时间的选择测试"<<endl;
	for(int i=1;i<=N;i++)
	{
		int kMin=s1.WorseLinearSelect(vec_int,0,N-1,i);
		cout<<"第"<<i<<"小的数是："<<kMin<<endl;
	}
	system("PAUSE");
	return 0;
}
