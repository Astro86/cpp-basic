
#include <iostream>
#include <string>

using namespace std;

#include "Tree.h"
#include "BinarySearchTree.h"

// ����Ʈ���� ��ȸ ����� 3������ �ִ�.
// ������ȸ, ������ȸ, ������ȸ�� �ִ�.
// ������ȸ�� ������ȸ, ������ȸ�� BinarySearchTree Ŭ������ �Լ����� ���� �����غ���.

// ���� : Ű���� �־ �����ϴ� erase �Լ��� ������.


void Output(int& iData)
{
	cout << iData << " ";
}

void OutputOrder(const int& key, const string& value)
{
	cout << "Key : " << key << " Value : " << value << " -> ";
}

int main()
{
	CTree<int>	tree;

	tree.insert(10, 0, IT_ROOT);
	tree.insert(20, 10, IT_CHILD);
	tree.insert(30, 20, IT_SIBLING);
	tree.insert(40, 30, IT_SIBLING);
	tree.insert(50, 30, IT_CHILD);
	tree.insert(60, 50, IT_SIBLING);
	tree.insert(70, 40, IT_CHILD);
	tree.insert(80, 20, IT_CHILD);
	tree.insert(90, 80, IT_CHILD);
	tree.insert(100, 90, IT_SIBLING);

	tree.Visit(Output);
	cout << endl;

	CBinarySearchTree<int, string>	tree1;

	tree1.insert(10, "ö��");
	tree1.insert(5, "����");
	tree1.insert(15, "����");
	tree1.insert(2, "����Ʋ");
	tree1.insert(1, "����Ʋ1");
	tree1.insert(7, "����Ʋ2");
	tree1.insert(6, "����Ʋ3");
	tree1.insert(9, "����Ʋ4");
	tree1.insert(12, "����Ʋ5");
	tree1.insert(13, "����Ʋ6");
	tree1.insert(16, "����Ʋ7");
	tree1.insert(18, "����Ʋ8");

	CBinarySearchTree<int, string>::iterator	iter1;
	iter1 = tree1.find(15);

	cout << "first : " << iter1->first << " second : " << iter1->second << endl;

	iter1 = tree1.erase(iter1);

	cout << "================= PreOrder =================" << endl;
	tree1.PreOrder(OutputOrder);
	cout << endl << endl;

	cout << "================= InOrder =================" << endl;
	tree1.InOrder(OutputOrder);
	cout << endl << endl;

	cout << "================= PostOrder =================" << endl;
	tree1.PostOrder(OutputOrder);
	cout << endl << endl;

	cout << "================= iterator =================" << endl;

	CBinarySearchTree<int, string>::iterator	iter;
	CBinarySearchTree<int, string>::iterator	iterEnd = tree1.end();
	
	for (iter = tree1.begin(); iter != iterEnd; ++iter)
	{
		OutputOrder(iter->first, iter->second);
		cout << endl;
	}


	return 0;
}
