
#pragma once

#include <iostream>

using namespace std;

/*
Linked List : 배열은 배열 개수만큼 노드를 연속되게 잡아놓고 데이터를 저장한다.
리스트는 각각의 노드를 따로 할당하고 그 노드에 데이터를 저장한 후에 다음 노드를
가리키게 만들어준다.
*/
typedef struct _tagListNode
{
	int		iData;
	_tagListNode*	pNext;
}LISTNODE, *PLISTNODE;

typedef struct _tagList
{
	PLISTNODE	pFirst;
	PLISTNODE	pCurrent;
	int			iSize;
}LIST, *PLIST;
