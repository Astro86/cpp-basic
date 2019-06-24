
#include <iostream>
#include <string>

using namespace std;

#include "CRBBTree.h"

int main()
{
	CRBBTree<int, string>	tree;

	tree.insert(10, "Ƽ��");
	tree.insert(20, "�߽���");
	tree.insert(30, "����");
	tree.insert(40, "�츣��");
	tree.insert(50, "����");
	tree.insert(60, "����");
	tree.insert(70, "���");
	tree.insert(80, "����");
	tree.insert(90, "�赿��");

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
