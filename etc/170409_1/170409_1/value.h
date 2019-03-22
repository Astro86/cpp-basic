
#pragma once

#include <iostream>

using namespace std;

#define	NAME_SIZE	32

typedef struct _tagStudent
{
	char	strName[NAME_SIZE];
	int		iKor;
	int		iEng;
	int		iMath;
	int		iTotal;
	float	fAvg;
	char	cScore;
}STUDENT, *PSTUDENT;

typedef struct _tagStudentContainer
{
	PSTUDENT	pStudentArr;	//���� : ������ typedef�� *PSTUDENT�� �����ص״µ� ���⼭ ����Ÿ������ * ���� PSTUDENT�� �ص� �Ǵ�����?
	int			iCount;
	int			iArraySize;
}STUDENTCONTAINER, *PSTUDENTCONTAINER;

enum MENU
{
	MENU_NONE,
	MENU_INSERT,
	MENU_DELETE,
	MENU_SEARCH,
	MENU_OUTPUT,
	MENU_EXIT
};

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

static bool InputString(char* pName, int iSize)
{
	cin.ignore(1024, '\n');
	cin.getline(pName, iSize);

	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1024, '\n');
		return false;
	}

	return true;
}