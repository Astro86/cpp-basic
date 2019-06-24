
#include <iostream>

using namespace std;

#include "AVLTree.h"

int main()
{
	CAVLTree<int, const char*>	avlTree;

	avlTree.insert(1, "aa");
	avlTree.insert(2, "bb");
	avlTree.insert(3, "cc");
	avlTree.insert(4, "dd");
	avlTree.insert(5, "ee");
	avlTree.insert(6, "ff");
	avlTree.insert(7, "gg");
	avlTree.insert(8, "hh");
	avlTree.insert(9, "ii");

	CAVLTree<int, const char*>::iterator	iter;
	CAVLTree<int, const char*>::iterator	iterEnd = avlTree.end();

	for (iter = avlTree.begin(); iter != iterEnd; ++iter)
	{
		cout << "Key : " << iter->first << " Value : " << iter->second << endl;
	}

	cout << "========= find ===========" << endl;

	iter = avlTree.find(8);
	cout << "Key : " << iter->first << " Value : " << iter->second << endl;

	iter = avlTree.find(30);

	if (iter == avlTree.end())
		cout << "Fail" << endl;

	else
		cout << "Key : " << iter->first << " Value : " << iter->second << endl;

	cout << "========= erase ===========" << endl;

	iter = avlTree.erase(7);

	if (iter == avlTree.end())
		cout << "Fail" << endl;

	else
		cout << "Key : " << iter->first << " Value : " << iter->second << endl;

	iter = avlTree.erase(20);

	if (iter == avlTree.end())
		cout << "Fail" << endl;

	else
		cout << "Key : " << iter->first << " Value : " << iter->second << endl;

	iter = avlTree.erase(6);

	cout << "=========== Loop ============" << endl;
	iterEnd = avlTree.end();

	for (iter = avlTree.begin(); iter != iterEnd; ++iter)
	{
		cout << "Key : " << iter->first << " Value : " << iter->second << endl;
	}

	return 0;
}
