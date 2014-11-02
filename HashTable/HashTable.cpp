// 验证HashTable类的成员函数
#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>
using namespace std;
// 对两个数值型关键字的比较约定为如下的宏定义
#define EQ(a, b) ((a)==(b))
const int EMPTY=0;//设置0为无数据标志(此时关键字不可为0)
const int TOMB=-1;//设置-1为删除数据标志(此时关键字不可为-1)
typedef int KeyType;
#include "HashTable.h"
// 定义模板<D>的实参HD及相应的I/O操作
struct HD
{
	KeyType key;
	int order;
};
void Visit(int i, HD* c)
{
	cout << '[' << i << "]: " << '(' << c->key << ", " << c->order << ')' << endl;
}
void Visit(HD c)
{
	cout << '(' << c.key << ", " << c.order << ')';
}
void InputFromFile(ifstream &f, HD &c)
{
	f >> c.key >> c.order;
}
void InputKey(int &k)
{
	cin >> k;
}

void main()
{
	HashTable<HD> h;
	int i, j, n, p=0;
	bool m;
	HD e;
	KeyType k;
	ifstream fin("input.txt");
	fin>>n;//由文件输入数据个数
	//建立哈希表
	for(i=0; i<n; i++)
	{
		InputFromFile(fin, e);
		j=h.InsertHash(e);
		if(j==DUPLICATE)
		{
			cout<<"哈希表中已有关键字为"<<e.key<<"的数据，无法再插入数据";
			Visit(e);
			cout<<endl;
		}
		if(j==UNSUCCESS)//插入不成功，重建哈希表
			j=h.InsertHash(e);
	}
	fin.close();
	cout<<"按哈希地址的顺序遍历哈希表："<<endl;
	h.TraverseHash(Visit);

	//删除数据测试
	cout<<"请输入待删除数据的关键字：";
	InputKey(k);
	m=h.DeleteHash(k, e);
	if (m)
	{
		cout << "成功删除数据";
		Visit(e);
		cout << endl;
	}
	else
		cout << "不存在关键字，无法删除！" << endl;
	cout << "按哈希地址的顺序遍历哈希表：" << endl;
	h.TraverseHash(Visit);
	//查询数据测试
	cout<<"请输入待查找数据的关键字：";
	InputKey(k);
	n=0;
	j=h.SearchHash(k, p, n);
	if(j==SUCCESS)
	{
		Visit(h.GetElem(p));
		cout<<endl;
	}
	else
		cout<<"未找到"<<endl;
	
	//插入数据测试
	cout<<"插入数据，请输入待插入数据的关键字：";
	InputKey(e.key);
	cout<<"请输入待插入数据的order：";
	cin>>e.order;
	j=h.InsertHash(e);
	if (j==DUPLICATE)
	{
		cout << "哈希表中已有关键字为" << e.key << "的数据，无法再插入数据";
		Visit(e);
		cout << endl;
	}
	if (j == UNSUCCESS)//插入不成功，重建哈希表
		j = h.InsertHash(e);
	cout<<"按哈希地址的顺序遍历哈希表："<<endl;
	h.TraverseHash(Visit);
	
}

