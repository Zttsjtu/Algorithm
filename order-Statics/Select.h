#ifndef SELECT_HH
#define SELECT_HH
template<typename T>
class Select
{
public:
	T RandomSelect(vector<T> &A,int p,int q,int k);//期望线性时间做选择
	T WorseLinearSelect(vector<T> &A,int p,int q,int k);//最坏情况线性时间的选择
private:
	void Swap(T &m,T &n);//交换数据
	int Random_Partition(vector<T> &A,int p,int q);//随机快排分划
	void insertion_sort(vector<T> &A,int p,int q);//插入排序
	T GetMedian(vector<T> &A,int p,int q);
	int partitionWithPivot(vector<T> &A,int p,int q,T piovt);//根据指定主元pivot来划分数据并返回主元的顺序位置
};

template<typename T>//交换数据
void Select<T>::Swap(T &m,T &n)
{
	T tmp;
	tmp=m;
	m=n;
	n=tmp;
}

/***********随机快速排序分划程序*************/
template<typename T>
int Select<T>::Random_Partition(vector<T> &A,int p,int q)
{
	//随机选择主元，与第一个元素交换
	srand(time(NULL));
	int m=rand()%(q-p+1)+p;
	Swap(A[m],A[p]);
	//下面与常规快排划分一样
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
/***********随机选择统计函数*************/
template<typename T>
T Select<T>::RandomSelect(vector<T> &A,int p,int q,int k)//随机选择统计，以期望线性时间做选择
{
	if (p==q) return A[p];
	int pivot=Random_Partition(A,p,q);//随机选择主元，把数组进行划分为两部分
	int i=pivot-p+1;
	if (i==k )return A[pivot];
	else if (i<k) return RandomSelect(A,pivot+1,q,k-i);//第k小的数不在主元左边，则在右边递归选择
	else return RandomSelect(A,p,pivot-1,k);//第k小的数不在主元右边，则在左边递归选择
}

template<typename T>//插入排序
void Select<T>::insertion_sort(vector<T> &A,int p,int q)
{
	int i,j;
	T key;
	int len=q-p+1;
	for (j=p+1;j<=q;j++)
	{
		i=j-1;
		key=A[j];
		while (i>=p&&A[i]>key)
		{
			A[i+1]=A[i];
			i--;
		}
		A[i+1]=key;
	}
}
/*
 *	利用插入排序选择中位数
 */
template<typename T>
T Select<T>::GetMedian(vector<T> &A,int p,int q)
{
	insertion_sort(A,p,q);//插入排序
	return A[(q-p)/2 + p];//返回中位数,有两个中位数的话返回较小的那个
}
/*
 *	根据指定的划分主元pivot来划分数组
 *	并返回主元的顺序位置
 */
template<typename T>
int  Select<T>::partitionWithPivot(vector<T> &A,int p,int q,T piovt)
{
	//先把主元交换到数组首元素
	for (int i=p;i<q;i++)
	{
		if (A[i] == piovt)
		{
			Swap(A[i],A[p]);
			break;
		}
	}
	//常规的快速排序划分程序
	//
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
/*
 *	最坏情况下线性时间选择算法
 *	此算法依然是建立在快速排序的划分算法基础之上的
 *	但是与randomizedSelect算法的不同指之处，就是次算法的本质
 *	是保证了每次划分选择的划分主元一定是一个较好的主元，算法先对数组5个一组进行分组
 *	然后选择每组的中位数，再递归的选择各组中位数中的中位数作为数组的划分主元，以此保证划分的平衡性
 *	选择中位数的时候必须使用递归调用的方法才能降低时间复杂度
 *	从而保证在最坏情况下都得到一个好的划分
 *	最坏情况下时间复杂度为O(n)
 */
template<typename T>
T Select<T>::WorseLinearSelect(vector<T> &A,int p,int q,int k)
{
	// 将输入数组的n个元素划分为n/5（上取整）组，每组5个元素，
	// 且至多只有一个组有剩下的n%5个元素组成。
	if (p==q) return A[p];

	int len=q-p+1;
	int medianCount=1;
	if (len>5)
		medianCount = len%5 >0 ? len/5 + 1 : len/5;
	vector<T> medians(medianCount);//存放每组的中位数

	// 寻找每个组的中位数。首先对每组中的元素（至多为5个）进行插入排序，
	// 然后从排序后的序列中选择出中位数。
	int m=p;
	for (int j=0,m=p;j<medianCount-1;j++)
	{
		medians[j] = GetMedian(A,m,m+4);
		m+=5;
	}
	medians[medianCount-1] = GetMedian(A,m,q);
	//对第2步中找出的n/5（上取整）个中位数，递归调用SELECT以找出其中位数pivot。
	//（如果是偶数去下中位数）
	int pivot = WorseLinearSelect(medians,0,medianCount-1,(medianCount+1)/2);
	//调用PARTITION过程，按照中位数pivot对输入数组进行划分。确定中位数pivot的位置r。
	int r = partitionWithPivot(A,p,q,pivot);
	int num = r-p+1;
	//如果num=k，则返回pivot。否则，如果k<num，则在地区间递归调用SELECT以找出第k小的元素，
	//若干k>num，则在高区找第(k-num)个最小元素。
	if(num==k) return pivot;
	else if (num>k) return WorseLinearSelect(A,p,r-1,k);
    else return WorseLinearSelect(A,r+1,q,k-num);
}
#endif 
