
#pragma once

#include <iostream>

using namespace std;

typedef struct _tagListNode
{
	int				iData;
	_tagListNode*	pNext;
}LISTNODE, *PLISTNODE;

typedef struct _tagList
{
	PLISTNODE	pFirst;
	PLISTNODE	pCurrent;
	int			iSize;
}LIST, *PLIST;
