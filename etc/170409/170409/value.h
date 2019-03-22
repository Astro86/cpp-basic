
#pragma once

#include <iostream>
#include <time.h>
#include <conio.h>

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

static char InputChar()
{
	char	cInput;
	cin >> cInput;

	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1024, '\n');
		return UCHAR_MAX;
	}

	return cInput;
}
