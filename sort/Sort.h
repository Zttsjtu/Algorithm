#ifndef SORT_HH
#define SORT_HH
template<typename T >
class Sort
{
	public:
		void insertion_sort(vector<T> &A);//插入排序
		void merge_sort(vector<T> &A,int p,int r);//归并排序
		void print_element(vector<T> A);//打印数组
		void Quick_Sort(vector<T> &A,int p,int q);//快速排序
		int Partition(vector<T> &A,int p,int q);//分划
		void Swap(T &m,T &n);//交换数据
		void Random_Quick_Sort(vector<T> &A,int p,int q);//随机化快速排序
		int Random_Partition(vector<T> &A,int p,int q);//随机化分划
		void HeapSort(vector<T> &A,bool IsRecurFlag);		
    private:
		void merge(vector<T> &A,int p,int q,int r);// 归并排序子程序
		void HeapAdjust(vector<T> &A,int i,int n);//非递归调整堆
		void HeapAdjust_Recursive(vector<T> &A,int i,int n);//递归调整堆
		void BuildBigHeap(vector<T> &A,bool IsRecurFlag);//建大顶堆
};
template<typename T>//插入排序
void Sort<T>::insertion_sort(vector<T> &A)
{
	int i,j;
	T key;
	int len=A.size();
	for (j=1;j<len;j++)
	{
		i=j-1;
		key=A[j];
		while (i>=0&&A[i]>key)
		{
			A[i+1]=A[i];
			i--;
		}
		A[i+1]=key;
	}
}

template<typename T>// 归并排序子程序
void Sort<T>::merge(vector<T> &A,int p,int q,int r)
{
	int n1=q-p+1;
	int n2=r-q;
	T *L=new T[n1+1];
	T *R=new T[n2+1];

	for (int i=0;i<n1;i++)
	    L[i]=A[i+p];
	for (int i=0;i<n2;i++)
	    R[i]=A[i+q+1];

	L[n1]=R[n2]=INT_MAX;

	int i=0,j=0;
	for (int k=p;k<=r;k++)
	{
		if (L[i]>R[j])
		{
			A[k]=R[j];
			j++;
		}
		else
		{
			A[k]=L[i];
			i++;
		}
	}

	delete[] L;
	delete[] R;

}

template<typename T>//归并排序
void Sort<T>::merge_sort(vector<T> &A,int p,int r)
{
	if (p<r)
	{
		int mid=(p+r)/2;
		merge_sort(A,p,mid);
		merge_sort(A,mid+1,r);
		merge(A,p,mid,r);
	}
}

template<typename T>//交换数据
void Sort<T>::Swap(T &m,T &n)
{
	/*T tmp;
	tmp=m;
	m=n;
	n=tmp;*/
	m ^=n;
	n ^=m;
	m ^=n;
}

/***********快速排序分划程序*************/
template<typename T>
int Sort<T>::Partition(vector<T> &A,int p,int q)
{
	T x=A[p];
	int i=p;
	for (int j=p+1;j<=q;j++)
	{
		if (A[j]<x)
		{
			i=i+1;
			Swap(A[i],A[j]);
		}
	}
	Swap(A[p],A[i]);
	return i;
}
template<typename T>//快速排序
void Sort<T>::Quick_Sort(vector<T> &A,int p,int q)
{
	if(p<q)
	{
		int i=Partition(A,p,q);
		Quick_Sort(A,p,i-1);
		Quick_Sort(A,i+1,q);
	}
}

template<typename T>//随机化快速排序分划程序
int Sort<T>::Random_Partition(vector<T> &A,int p,int q)
{
	int i=rand()%(q-p)+p;
	Swap(A[i],A[p]);
	 return Partition(A,p,q);
}

template<typename T>//随机化快速排序
void Sort<T>::Random_Quick_Sort(vector<T> &A,int p,int q)
{
	if (p<q)
	{
		int i=Random_Partition(A,p,q);
		Random_Quick_Sort(A,p,i-1);
		Random_Quick_Sort(A,i+1,q);
	}
}
//从i节点开始调整,n为节点总数 从0开始计算 i节点的子节点为 2*i+1, 2*i+2
template<typename T>
void Sort<T>::HeapAdjust(vector<T> &A,int i,int n)
{
	T temp = A[i];
	int j = 2*i+1;//下标从0开始
	while (j<n)//非递归实现
	{
		if (j+1<n&&A[j+1]>A[j])//找出子节点的最小值
			j++;
        if(A[j]<=temp)//子节点不大于父节点，调整结束
			break;

		A[i] = A[j];// 子节点最大值大于父节点，值赋给父节点；
		i = j;
		j = 2*i+1;//下标从0开始
	}
	A[i] = temp;//调整结束
}
//从i节点开始调整,n为节点总数 从0开始计算 i节点的子节点为 2*i+1, 2*i+2
template<typename T>
void Sort<T>::HeapAdjust_Recursive(vector<T> &A,int i,int n)//递归调整堆
{
	int lchild = 2*i+1;
	int rchild = 2*i+2;
	int max = i;
	if (i<=(n-1)/2)//从最大非叶节点开始调整
	{
		if (lchild<n&&A[lchild]>A[max])
		{
			max=lchild;
		}
		if(rchild<n&&A[rchild]>A[max])
		{
			max=rchild;
		}
		if (max!=i)//子节点值比父节点大，调整
		{
			Swap(A[i],A[max]);
			HeapAdjust_Recursive(A,max,n);//递归
		}
	}
}
//初始从待排序数组建大顶堆
//数组从0开始计算，建堆从p到q
template<typename T>
void Sort<T>::BuildBigHeap(vector<T> &A,bool IsRecurFlag)
{
	int n=A.size();
	for(int i=(n-1)/2;i>=0;i--)//从最大的非叶节点开始
	{
		if (IsRecurFlag)
		HeapAdjust_Recursive(A,i,n);
		else
		HeapAdjust(A,i,n);
	}
}
//堆排序，首先建大顶堆
template<typename T>
void Sort<T>::HeapSort(vector<T> &A,bool IsRecurFlag)
{
	int len = A.size();
	BuildBigHeap(A,IsRecurFlag);//建大顶堆
	for(int i=len-1;i>=0;i--)
	{
		Swap(A[0],A[i]);//未排序堆第一个和最后一个交换
		if (IsRecurFlag)//递归
		HeapAdjust_Recursive(A,0,i);
		else//非递归
		HeapAdjust(A,0,i);//调整为大顶堆
	}
}

template<typename T>//打印数组
void Sort<T>::print_element(vector<T> A)
{
	int len=A.size();
	for (int i=0;i<len;i++)
	{
		std::cout<<A[i]<<" ";
	}
	std::cout<<std::endl;
}
#endif
