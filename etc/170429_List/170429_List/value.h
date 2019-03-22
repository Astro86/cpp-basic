
#pragma once

#include <iostream>

using namespace std;

/*
Linked List : �迭�� �迭 ������ŭ ��带 ���ӵǰ� ��Ƴ��� �����͸� �����Ѵ�.
����Ʈ�� ������ ��带 ���� �Ҵ��ϰ� �� ��忡 �����͸� ������ �Ŀ� ���� ��带
����Ű�� ������ش�.
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
