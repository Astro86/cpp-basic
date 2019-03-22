
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
// 레퍼런스 : 참조자이다. 대입된 값을 참조하는 역할을 한다. 일종의 별명을 붙여주는 것과 같다.
// 이 참조자를 이용해서 참조하는 대상의 값을 변경할 수 있다.
// const일 경우는 참조하는 값을 변경할 수 없다.
void AddItem(PITEMLIST pList, const ITEM& tItem);




