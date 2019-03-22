
#include <iostream>
#include "Stack.h"

using namespace std;

int main()
{
	CStackArray<int>	stackInt;

	for (int i = 0; i < 10; ++i)
	{
		stackInt.push(i);
	}

	for (int i = 0; i < 10; ++i)
	{
		cout << stackInt.pop() << endl;
	}

	CStackArray<const char*>	stackString;

	stackString.push("Test");
	stackString.push("문자열");
	stackString.push("확대");
	stackString.push("수술");

	for (int i = 0; i < 4; ++i)
	{
		cout << stackString.pop() << endl;
	}

	CStackList<int>	stackListInt;

	for (int i = 0; i < 10; ++i)
	{
		stackListInt.push(i);
	}

	for (int i = 0; i < 10; ++i)
	{
		cout << stackListInt.pop() << endl;
	}

	return 0;
}
