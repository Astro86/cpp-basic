
#include <iostream>
#include "Vector.h"

using namespace std;

bool Sort(const int& src, const int& dest)
{
	return src > dest;
}

int main()
{
	CVector<int>	vecInt;

	for (int i = 0; i < 100; ++i)
	{
		vecInt.push_back(i + 1);
	}

	vecInt.Shuffle();

	/*for (int i = 0; i < vecInt.size(); ++i)
	{
		cout << vecInt[i] << endl;
	}*/

	CVector<int>::iterator	iter;
	CVector<int>::iterator	iterEnd = vecInt.end();

	iter = vecInt.begin() + 10;

	cout << "begin + 10 : " << *iter << endl;

	iter = vecInt.erase(iter);

	cout << "erase : " << *iter << endl;

	for (iter = vecInt.begin(); iter != iterEnd; ++iter)
	{
		cout << *iter << endl;
	}

	cout << "Size : " << vecInt.size() << endl;

	vecInt.pop_back();

	cout << "Size : " << vecInt.size() << endl;

	vecInt.sort(Sort);

	for (int i = 0; i < vecInt.size(); ++i)
	{
		cout << vecInt[i] << endl;
	}

	return 0;
}
