
#include <iostream>
#include <time.h>
#include "Sort.h"

using namespace std;

bool SortNumber(const int& iSrc, const int& iDest)
{
	return iSrc < iDest;
}

int main()
{
	srand(time(0));
	int	iArray[20] = {};

	for (int i = 0; i < 20; ++i)
	{
		iArray[i] = rand();
		cout << iArray[i] << endl;
	}

	CSort<int>::Sort(iArray, 20, SortNumber, ST_MERGE);

	cout << "=============== Sort ===============" << endl;

	for (int i = 0; i < 20; ++i)
	{
		cout << iArray[i] << endl;
	}

	return 0;
}
