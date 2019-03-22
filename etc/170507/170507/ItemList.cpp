
#include "ItemList.h"

ITEM CreateItem(char * pName, ITEM_TYPE eType, int iMainOption, int iPrice, int iSell)
{
	ITEM	tItem = {};
	strcpy_s(tItem.strName, pName);
	tItem.eType = eType;
	tItem.iMainOption = iMainOption;
	tItem.iPrice = iPrice;
	tItem.iSell = iSell;

	return tItem;
}

bool InitItemList(PITEMLIST pList)
{
	pList->iSize = 0;
	pList->pFirst = 0;
	pList->pCurrent = 0;

	return true;
}

void AddItem(PITEMLIST pList, const ITEM & tItem)
{
	PITEMNODE	pNode = new ITEMNODE;

	pNode->tItem = tItem;
	pNode->pNext = NULL;
	pNode->pPrev = NULL;

	if (pList->pFirst == NULL)
		pList->pFirst = pNode;

	else
	{
		pNode->pPrev = pList->pCurrent;
		pList->pCurrent->pNext = pNode;
	}

	pList->pCurrent = pNode;

	++pList->iSize;
}
