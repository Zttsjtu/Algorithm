#include <iostream>
#include <vector>
#include <time.h>
#include <Windows.h>
using namespace std;
#include "Sort.h"
#include "CTimer.h"

#define  N 100   //排序数组大小
// 随机参数排序数组
void Random(vector<int> &a,int n)  
{  
	int i=0;  
	srand( (unsigned)time( NULL ) );  
	while(i<n)  
	{  
		a[i++]=rand();  
	}  
}  
int main()
{
	Sort<int> sort1;
	CTimer t;
	vector<int > vec_int(N);
	Random(vec_int,N);
	cout<<"源数组：";
	//sort1.print_element(vec_int);
	t.Start();
	sort1.Quick_Sort(vec_int,0,vec_int.size()-1);
	cout<<"快速排序:"<<t.End()<<"ms"<<endl;
//	sort1.print_element(vec_int);
	Random(vec_int,N);
	t.Start();
	sort1.Random_Quick_Sort(vec_int,0,vec_int.size()-1);
	cout<<"随机化快速排序:"<<t.End()<<"ms"<<endl;
//	sort1.print_element(vec_int);
	Random(vec_int,N);
	t.Start();
	sort1.insertion_sort(vec_int);
	cout<<"插入排序:"<<t.End()<<"ms"<<endl;
//	sort1.print_element(vec_int);
	Random(vec_int,N);
	t.Start();
	sort1.merge_sort(vec_int,0,vec_int.size()-1);
	cout<<"归并排序:"<<t.End()<<"ms"<<endl;
//	sort1.print_element(vec_int);
	Random(vec_int,N);
	t.Start();
	sort1.HeapSort(vec_int,false);
	cout<<"非递归堆排序:"<<t.End()<<"ms"<<endl;
//	sort1.print_element(vec_int);
	Random(vec_int,N);
	t.Start();
	sort1.HeapSort(vec_int,true);
	cout<<"递归堆排序:"<<t.End()<<"ms"<<endl;
	//sort1.print_element(vec_int);
	system("PAUSE");
    return 0;
}
