#include <iostream>
#include <time.h>

using namespace std;

#include "LinkedList.h"	

bool SortList(const int& _1, const int& _2)
{
	return _1 < _2;
}

int main()
{
	srand((unsigned int)time(0));

	CLinkedList<int>	listInt;

	for (int i = 0; i < 100; ++i)
	{
		listInt.push_back(rand() % 100);
	}

	listInt.sort(SortList);

	CLinkedList<int>::iterator	iter;
	CLinkedList<int>::iterator	iterEnd = listInt.end();

	for (iter = listInt.begin(); iter != iterEnd; ++iter)
	{
		cout << *iter << endl;
	}
	cout << "====================" << endl;

	CLinkedList<int>::reverse_iterator	riter;
	CLinkedList<int>::reverse_iterator	riterEnd = listInt.rend();

	listInt.erase(98);

	for (riter = listInt.rbegin(); riter != riterEnd; ++riter)
	{
		cout << *riter << endl;
	}

	return 0;
}
