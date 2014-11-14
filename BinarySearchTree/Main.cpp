#include"BinarySearchTree.h"
int main()
{
	BinarySearchTree<int> bstree;
	BinarySearchTreeNode<int>* ptnode, *proot;
	bstree.tree_insert(32);
	bstree.tree_insert(21);
	bstree.tree_insert(46);
	bstree.tree_insert(54);
	bstree.tree_insert(16);
	bstree.tree_insert(38);
	bstree.tree_insert(70);
	cout << "inorder tree walk is: ";
	bstree.inorder_tree_traverse();
	proot = bstree.get_root();
	cout << "\nmax value is: " << bstree.tree_maxmum(proot)->key << endl;
	cout << "min value is: " << bstree.tree_minmum(proot)->key<< endl;
	ptnode = bstree.tree_search(38);
	if (ptnode)
		cout << "the element 38 is exist in the binary tree.\n";
	else
		cout << "the element 38 is not exist in the binary tree.\n";
	cout << "the successor of 38 is: " << bstree.tree_successor(38)->key << endl;
	cout << "the predecessor of 38 is:" << bstree.tree_predecessor(38)->key << endl;
	if (bstree.tree_remove(46) == 0)
		cout << "delete 46 successfully" << endl;
	else
		cout << "delete 46 failed" << endl;
	cout << "inorder tree walk is: ";
	bstree.inorder_tree_traverse();
	exit(0);
}
