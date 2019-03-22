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
}STUDENT, *PSTUDENT;

typedef struct _tagListNode
{
	STUDENT			tStudent;
	_tagListNode*	pNext;
}LISTNODE, *PLISTNODE;

typedef struct _tagList
{
	PLISTNODE	pFirst;
	PLISTNODE	pCurrent;
	int			iSize;
}LIST, *PLIST;
