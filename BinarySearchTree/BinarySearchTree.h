#include <iostream>
#include <stack>
using namespace std;

//二叉查找树节点定义，带模板
template <class T>
class  BinarySearchTreeNode
{
public:
	T key;//节点值，这里只有一个值，没有附带数据
	BinarySearchTreeNode<T>* parent;//指向双亲节点指针
	BinarySearchTreeNode<T>* left;//指向左孩子节点指针
	BinarySearchTreeNode<T>* right;//指向右孩子节点指针
};

/* 
二查查找树功能实现类，包括节点查找，最大、最小节点查找，
   前驱、后继节点查找，插入节点，删除节点功能实现，带模板
*/
template <class T>
class BinarySearchTree
{
public:
	BinarySearchTree();
	void tree_insert(const T& elem);
	int  tree_remove(const T& elem);
	BinarySearchTreeNode<T>* tree_search(const T& elem)const;
	BinarySearchTreeNode<T>* tree_minmum(BinarySearchTreeNode<T>* root)const;
	BinarySearchTreeNode<T>* tree_maxmum(BinarySearchTreeNode<T>* root)const;
	BinarySearchTreeNode<T>* tree_successor(const T& elem) const;
	BinarySearchTreeNode<T>* tree_predecessor(const T& elem)const;
	bool empty() const;
	void inorder_tree_traverse()const;
	BinarySearchTreeNode<T>* get_root()const { return root; }
	void transplant(BinarySearchTreeNode<T>* u, BinarySearchTreeNode<T>* v);
private:
	BinarySearchTreeNode<T>* root;
};
/*构造函数*/
template <class T>
BinarySearchTree<T>::BinarySearchTree()
{
	root = NULL;
}
/*二叉查找树插入操作实现
  实现思路：插入结点的位置对应着查找过程中查找不成功时候的结点位置，
  因此需要从根结点开始查找带插入结点位置，找到位置后插入即可
*/
template <class T>
void BinarySearchTree<T>::tree_insert(const T& elem)
{
	if (!empty())//判断二叉树是否为空，非空则找到合适节点插入
	{
		BinarySearchTreeNode<T> *pnode = root;
		BinarySearchTreeNode<T> *qnode = NULL;
		BinarySearchTreeNode<T> *newnode = new BinarySearchTreeNode<T>;//创建新节点
		newnode->key = elem;//插入节点值
		newnode->parent = NULL;//初始化双亲节点、左右孩子节点
		newnode->left = NULL;
		newnode->right = NULL;
		while (pnode)//非空，查找插入节点位置
		{
			qnode = pnode;
			if (pnode->key > elem)//当前节点值大于待插入节点值，向左子树查找
				pnode = pnode->left;
			else//当前节点值不大于待插入节点值，向右子树查找
				pnode = pnode->right;
		}
		if (qnode->key > elem)//当前节点值大于待插入节点值，则插入到左孩子节点
			qnode->left = newnode;
		else//否则插入到右孩子节点
			qnode->right = newnode;
		newnode->parent = qnode;//设置新插入节点的双亲节点
	}
	else//二叉树为空，则插入节点为根节点
	{
		root = new BinarySearchTreeNode<T>;
		root->key = elem;
		root->parent = NULL;
		root->left = NULL;
		root->right = NULL;
	}
}
/*删除节点调用的子过程transplant,用一颗子树v替换另外一颗子树u并成为其双亲的孩子节点
输入：u-被替换的子树指针，v-新替换的子树指针
输出：void
*/
template <class T>
void BinarySearchTree<T>::transplant(BinarySearchTreeNode<T>* u, BinarySearchTreeNode<T>* v)
{
	if (u->parent == NULL) root = v;
	else if (u == u->parent->left) u->parent->left=v;
	else u->parent->right = v;

	if (v != NULL) v->parent = u->parent;
}
/*节点删除实现
  输入：要删除的节点的关键字
  输出：删除成功返回0
        不存在此关键字则返回-1
*/
template <class T>
int BinarySearchTree<T>::tree_remove(const T&elem)
{
	BinarySearchTreeNode<T> *pnode;//当前节点
	BinarySearchTreeNode<T> *snode;//双亲节点、后继节点
	pnode = tree_search(elem);//查找待删除节点
	if (!pnode) return -1;//待删除节点不存在，返回-1
	if (pnode->left == NULL)//左孩子不存在，用右孩子直接替换待删除节点（这个右孩子可以是NULL，也可以不是NULL）
		transplant(pnode, pnode->right);
	else if (pnode->right == NULL)//只存在左孩子，用左孩子直接替换待删除节点
		transplant(pnode,pnode->left);
	else//左右孩子都存在
	{
		snode = tree_minmum(pnode->right);//求待删除节点的后继（因右孩子存在，所以一定是右子树中最小的节点）
		if (snode->parent != pnode)//后继不是待删除节点的右孩子，
		{
			transplant(snode, snode->right);//snode是后继节点，所以无左子树，右子树替换掉snode
			snode->right = pnode->right;//pnode的右孩子成为snode的右孩子
			snode->right->parent = snode;
		}
		transplant(pnode, snode);//snode替换掉pnode
		snode->left = pnode->left;//处理snode的左子树，及左子树的双亲关系
		snode->left->parent = snode;
	}
	return 0;
	
}
/*查找search实现
 输入：待查找的数据elem
 输出：查找成功，返回指向该节点的指针；
       待查找数值不存在，返回空指针
*/
template <class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::tree_search(const T& elem)const
{
	BinarySearchTreeNode<T> *pnode = root;//节点指针，指向根节点
	//非递归查找过程
	while (pnode)//节点非空
	{
		if (pnode->key == elem)//查找成功：指针指向节点关键值等于待查找数值，退出while
			break;
		else if (pnode->key > elem)//当前节点值大于查找的elem,则在当前节点左孩子二叉树中进行查找
			pnode = pnode->left;
		else               //当前节点值小于查找的elem,则在当前节点右孩子二叉树中进行查找
			pnode = pnode->right;
	}

	return pnode;
}

/*查找最小关键字
  输入：指向要查找的二叉树的根节点的指针
  输出：返回指向最小关键字节点的指针
*/
template <class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::tree_minmum(BinarySearchTreeNode<T>* root)const
{
	BinarySearchTreeNode<T> *pnode = root;//节点指针，指向根节点
	
	while (pnode->left)//从根结点开始，沿着各个节点的left指针查找下去，直到遇到NULL时结束
			pnode = pnode->left;
	
	return pnode;
}
/*查找最d大关键字
输入：指向要查找的二叉树的根节点的指针
输出：返回指向最大关键字节点的指针
*/
template <class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::tree_maxmum(BinarySearchTreeNode<T>* root)const
{
	BinarySearchTreeNode<T> *pnode = root;//节点指针，指向根节点

	while (pnode->right)//从根结点开始，沿着各个节点的left指针查找下去，直到遇到NULL时结束
			pnode = pnode->right;

	return pnode;
}
/*求节点后继
  输入：当前节点的值
  输出： 当前节点的后继节点的指针
*/
template <class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::tree_successor(const T& elem) const
{
	BinarySearchTreeNode<T>* pnode = tree_search(elem);//查找值为elem的节点，返回指针保存到pnode
	BinarySearchTreeNode<T>* parentnode=NULL;//定义双亲节点
	if (pnode != NULL)//当前节点存在
	{
		if (pnode->right)//当前节点存在右孩子，则后继为右子树的最小关键字节点
			return tree_minmum(pnode->right);
		parentnode = pnode->parent;//不存在右孩子，取双亲节点
		/*
		//双亲节点不为空，并且当前节点时双亲节点的右孩子时，一直寻找双亲节点，
		//直到双亲节点为空，或者当前节点是双亲节点的左孩子
		*/
		while (parentnode && pnode == parentnode->right)
		{
			pnode = parentnode;
			parentnode = parentnode->parent;
		}
		if (parentnode)//双亲节点不为空，返回
			return parentnode;
		else//为空，无后继节点
			return NULL;
	}
	return NULL;//当前节点不存在
}
/*求节点前驱
输入：当前节点的值
输出： 当前节点的前驱节点的指针
*/
template <class T>
BinarySearchTreeNode<T>* BinarySearchTree<T>::tree_predecessor(const T& elem)const
{
	BinarySearchTreeNode<T>* pnode = tree_search(elem);//查找值为elem的节点，返回指针保存到pnode
	BinarySearchTreeNode<T>* parentnode;//定义双亲节点
	if (pnode != NULL)//当前节点存在
	{
		if (pnode->right)
			return tree_maxmum(pnode->right);//当前节点存在左孩子，则后继为左子树的最大关键字节点
		parentnode = pnode->parent;//不存在左孩子，取双亲节点
		/*
		//双亲节点不为空，并且当前节点是双亲节点的左孩子时，一直寻找双亲节点，
		//直到双亲节点为空，或者当前节点是双亲节点的右孩子
		*/
		while (parentnode && pnode == parentnode->left)
		{
			pnode = parentnode;
			parentnode = pnode->parent;
		}
		if (parentnode)//双亲节点不为空，返回
			return parentnode;
		else//为空，无后继节点
			return NULL;
	}
	return NULL;
}
/*判断二叉树查找树是否为空
  输出：若为空，返回true
        非空，返回false
*/
template <class T>
bool BinarySearchTree<T>::empty() const
{
	return (NULL == root);
}
/*二叉查找树中序遍历非递归实现
 实现思路：借助栈完成
*/
template <class T>
void BinarySearchTree<T>::inorder_tree_traverse()const
{
	if (NULL != root)
	{
		stack<BinarySearchTreeNode<T>*> s;
		BinarySearchTreeNode<T> *ptmpnode;
		ptmpnode = root;//指向根节点
		while (NULL != ptmpnode || !s.empty())//当前节点不空，或者栈不空
		{
			if (NULL != ptmpnode)//当前节点不为空，入栈，置左孩子节点为当前节点
			{
				s.push(ptmpnode);//入栈
				ptmpnode = ptmpnode->left;//置左孩子节点为当前节点
			}
			else//当前节点为空，弹出栈顶元素并访问该节点，然后置右孩子节点为当前节点
			{
				ptmpnode = s.top();//弹出栈顶元素
				s.pop();
				cout << ptmpnode->key << " ";//访问该节点
				ptmpnode = ptmpnode->right; //然后置右孩子节点为当前节点
			}
		}
	}
}
