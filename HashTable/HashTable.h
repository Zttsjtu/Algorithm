//HashTable.h 开放寻址法哈希表类（HashTable类）
#ifndef _HAXI_H_
#define _HAXI_H_
const int SUCCESS = 1;//成功
const int UNSUCCESS = 0;//不成功
const int DUPLICATE = -1;//关节字冲突（重复），不能再插入
const int N = 4;//hashsize[]的容量
int hashsize[N] = { 11, 19, 37, 73 };
//哈希表容量递增表，一个合适的素数序列，（重）建哈希表用到


template<typename D>class HashTable
{//带数据元素类型D模板的开放寻址法哈希表类
private://6个私有成员函数，5个私有数据成员
	D *elem;//数据元素存储基址，动态分配数组
	int count, length;//数据元素个数，哈希表容量
	int sizeindex;//hashsize[sizeindex]为当前容量
	int	*rando;//随机数数组指针
	int Hash(KeyType Key)
	{//一个简单的哈希函数
		return Key%length;
	}
	int Hash2(KeyType Key)//用于双重散列探索法
	{//双重散列探查法的第二个哈希函数
		return Key % (length - 2);
	}
	void Random()
	{//建立伪随机数组(用于随机探查法)
		bool *ra = new bool[length];//
		rando = new int[length];
		int i;
		for (i = 1; i<length; i++)//设置ra[i]的初值
			ra[i] = false;//i不在随机数数组中的标志
		//		srand(time(0));//设置随机数种子
		for (i = 1; i<length; i++)//依次给rando[i]赋随机值
		{
			do
			{
				rando[i] = rand() % (length - 1) + 1;//给rando[i]赋值（1-length-1）
				if (!ra[rando[i]])//伪随机数组中没有此数
					ra[rando[i]] = true;//赋值成功
				else
					rando[i] = 0;
			} while (rando[i] == 0);//赋值失败则重新赋值
			cout << "rando[" << i << "]=" << rando[i] << endl;
		}
		delete[]ra;
	}
	int d(int i, KeyType Key)//增量序列函数
	{//返回第i次冲突的增量
		switch (type)
		{
		case 0: return i;//线性探查法
		case 1: return ((i + 1) / 2)*((i + 1) / 2)*(int)pow(-1, i - 1);
			//二次探查法（1，-1,4，-4,9，-9，......）
		case 2: return i*Hash2(Key);//双重散列探查法
		case 3: return rando[i];//随机探查法(由Random()建立的一个伪随机数列)
		default:return i;//默认线性探查法
		}
	}
	//开放寻址法求得关键字为Key的第i次冲突的地址p
	void collision(KeyType Key, int &p, int i)
	{
		p = (Hash(Key) + d(i, Key)) % length;//哈希函数加增量后再求余
		if (p<0)//得到负数（双重探查可能出现）
			p = p + length;//保证非负
	}
	//重建哈希表
	void RecreateHashTable()
	{
		int i, len = length;//原容量
		D *p = elem;//p指向哈希表原有数据空间
		sizeindex++;//增大容量为下一个序列数
		if (sizeindex<N)
		{
			length = hashsize[sizeindex];
			elem = new D[length];
			assert(elem != NULL);
			for (i = 0; i<length; i++)//未填数据的标志
				elem[i].key = EMPTY;
			for (i = 0; i<len; i++)//将p所指原elem中的数据插入到重建的哈希表中
			if (p[i].key != EMPTY && p[i].key != TOMB)
				InsertHash(p[i]);
			delete[]p;
			if (type == 3)//随机探查法
				Random();
		}
	}
public://7个公有成员函数，1个共有数据成员
	int type;//探查法类型(0-3)
	HashTable()
	{//构造函数，构造一个空的哈希表
		count = 0;
		sizeindex = 0;
		length = hashsize[sizeindex];
		elem = new D[length];
		assert(elem != NULL);
		for (int i = 0; i<length; i++)
			elem[i].key = EMPTY;//未填数据的格式
		cout << "请输入探查法的类型（0：线性；1：二次；2：双散列；3：随机）：";
		cin >> type;
		if (type == 3)
			Random();
		else
			rando = NULL;
	}
	~HashTable()
	{//析构函数，销毁哈希表
		if (elem != NULL)
			delete[]elem;
		if (type == 3)
			delete[]rando;
	}
	//在开放寻址哈希表中查找关键字为Key的元素，若查找成功，以p指向待查数据元素在表中位置
	//并返回SUCCESS；否则，以p指示插入位置，并返回UNSUCCESS
	//c用以计冲突次数，其初值置零，供建表插入时参考
	bool SearchHash(KeyType Key, int &p, int &c)
	{
		int c1, tomb = -1;//存找到的第一个墓碑地址（被删除数据）
		p = Hash(Key);//哈希地址
		//下面的while代码段，如果哈希地址处数据不是要查找的数据，
		//则求下一个探查地址p，进行查找，直到碰撞次数超出定义的阈值

		while (elem[p].key == TOMB || elem[p].key != EMPTY && !EQ(Key, elem[p].key))
		{
			if (elem[p].key == TOMB && tomb == -1)//数据已被删除,且是找到的第一个墓碑
			{
				tomb = p;
				c1 = c;//冲突次数存于c1
			}
			c++;//冲突次数+1
			if (c <= hashsize[sizeindex]/2)//在冲突次数阈值内，求下一个探查地址p
				collision(Key, p, c);
			else
				break;
		}
		if EQ(Key, elem[p].key)//查找成功
			return true;
		else//查找不成功
		{
			if (tomb != -1)//查找过程中遇到过墓碑
			{
				p = tomb;//将墓碑作为插入位置
				c = c1;//冲突次数
			}
			return false;
		}
	}
	//查找不成功时将数据元素e插入到开放寻址哈希表中，并返回SUCCESS；查找成功时返回
	//DUPLICATE，不插入数据元素；若冲突次数过大，则不插入，并重建哈希表，返回UNSUCCESS
	int InsertHash(D e)
	{

		int p, c = 0;
		if (SearchHash(e.key, p, c))//查找成功，已有与e相同关键字 元素，不再插入
			return DUPLICATE;
		else if (c <= hashsize[sizeindex]/2)//为找到，冲突次数c也未达到上限(c的阈值可调)，插入
		{
			elem[p] = e;
			++count;
			return SUCCESS;
		}
		else//未找到，但冲突次数已达到上限，重建哈希表
		{
			cout << "按哈希地址的顺序遍历重建前的哈希表：" << endl;
			TraverseHash(Visit);
			cout << "重建哈希表" << endl;
			RecreateHashTable();
			return UNSUCCESS;
		}
	}
	//从哈希表中删除关节字为Key的数据元素，成功返回true，并将该位置的关键字设为TMOB;
	//不成功返回false
	bool DeleteHash(KeyType Key, D &e)
	{

		int p, c=0;//一定要赋初值，不然c会是个随机的数
		if (SearchHash(Key, p, c))//查找成功
		{
			e = elem[p];
			elem[p].key = TOMB;
			--count;
			return true;
		}
		else
			return false;
	}
	//返回元素[i]的值
	D GetElem(int i)const
	{
		return elem[i];
	}
	//按哈希地址的顺序遍历哈希表H
	void TraverseHash(void(*visit)(int, D*))const
	{
		int i;
		cout << "哈希地址0～" << length - 1 << endl;
		for (i = 0; i<length; i++)
		if (elem[i].key != EMPTY && elem[i].key != TOMB)
			visit(i, &elem[i]);
	}
};
#endif

