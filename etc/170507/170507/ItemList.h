
#pragma once

#include "value.h"

typedef struct _tagItemNode
{
	ITEM	tItem;
	struct _tagItemNode*	pNext;
	struct _tagItemNode*	pPrev;
}ITEMNODE, *PITEMNODE;

typedef struct _tagItemList
{
	PITEMNODE	pFirst;
	PITEMNODE	pCurrent;
	int			iSize;
}ITEMLIST, *PITEMLIST;

ITEM CreateItem(char* pName, ITEM_TYPE eType, int iMainOption, int iPrice, int iSell);

bool InitItemList(PITEMLIST pList);
// ���۷��� : �������̴�. ���Ե� ���� �����ϴ� ������ �Ѵ�. ������ ������ �ٿ��ִ� �Ͱ� ����.
// �� �����ڸ� �̿��ؼ� �����ϴ� ����� ���� ������ �� �ִ�.
// const�� ���� �����ϴ� ���� ������ �� ����.
void AddItem(PITEMLIST pList, const ITEM& tItem);




