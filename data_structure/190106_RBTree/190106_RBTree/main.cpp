
#include <iostream>
#include <string>

using namespace std;

#include "CRBBTree.h"

int main()
{
	CRBBTree<int, string>	tree;

	tree.insert(10, "티모");
	tree.insert(20, "야스오");
	tree.insert(30, "제드");
	tree.insert(40, "우르곳");
	tree.insert(50, "베인");
	tree.insert(60, "마이");
	tree.insert(70, "우디르");
	tree.insert(80, "윤성");
	tree.insert(90, "김동성");

	CRBBTree<int, string>::iterator	iter;
	iter = tree.find(60);

	cout << "key : " << iter->first << " value : " << iter->second << endl;

	iter = tree.erase(80);
	cout << "key : " << iter->first << " value : " << iter->second << endl;

	for (iter = tree.begin(); iter != tree.end(); ++iter)
	{
		cout << "key : " << iter->first << " value : " << iter->second << endl;
	}

	return 0;
}
