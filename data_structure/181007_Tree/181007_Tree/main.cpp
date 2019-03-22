
#include <iostream>
#include <string>

using namespace std;

#include "Tree.h"
#include "BinarySearchTree.h"

// 이진트리의 순회 방법은 3가지가 있다.
// 전위순회, 중위순회, 후위순회가 있다.
// 전위순회와 중위순회, 후위순회를 BinarySearchTree 클래스에 함수들을 만들어서 구현해보자.

// 숙제 : 키값을 넣어서 삭제하는 erase 함수를 만들어보자.


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

	tree1.insert(10, "철수");
	tree1.insert(5, "영희");
	tree1.insert(15, "윤성");
	tree1.insert(2, "빵셔틀");
	tree1.insert(1, "빵셔틀1");
	tree1.insert(7, "빵셔틀2");
	tree1.insert(6, "빵셔틀3");
	tree1.insert(9, "빵셔틀4");
	tree1.insert(12, "빵셔틀5");
	tree1.insert(13, "빵셔틀6");
	tree1.insert(16, "빵셔틀7");
	tree1.insert(18, "빵셔틀8");

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
