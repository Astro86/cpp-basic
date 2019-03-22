
#pragma once

#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

static int InputInt()
{
	int	iInput;
	cin >> iInput;

	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1024, '\n');
		return INT_MAX;
	}

	return iInput;
}
