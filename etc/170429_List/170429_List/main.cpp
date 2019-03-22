
#include "value.h"

bool Empty(PLIST pList)
{
	return pList->iSize == 0;
}

void Insert(PLIST pList)
{
	// 추가할 데이터를 입력받는다.
	system("cls");
	cout << "추가할 데이터를 입력하세요 : ";
	int	iData;
	cin >> iData;

	// 노드를 생성한다.
	PLISTNODE	pNode = new LISTNODE;

	pNode->iData = iData;
	pNode->pNext = NULL;

	// 처음 노드가 NULL일 경우는 노드를 처음 추가하는 것이므로 첫 노드에 넣어준다.
	if (pList->pFirst == NULL)
		pList->pFirst = pNode;

	else
		pList->pCurrent->pNext = pNode;

	pList->pCurrent = pNode;

	++pList->iSize;
}

// 모든 노드를 반복하며 삭제한다.
void Clear(PLIST pList)
{
	PLISTNODE	pNode = pList->pFirst;

	// pNode가 NULL이 아닐 경우라면 반복한다.
	while (pNode)
	{
		PLISTNODE	pNext = pNode->pNext;
		delete	pNode;
		pNode = pNext;
	}

	pList->pFirst = NULL;
	pList->pCurrent = NULL;
	pList->iSize = 0;
}

void Output(PLIST pList)
{
	PLISTNODE	pNode = pList->pFirst;

	while (pNode)
	{
		cout << pNode->iData;

		if (pNode->pNext)
			cout << " -> ";

		pNode = pNode->pNext;
	}

	cout << endl;
}

void OutputNode(PLIST pList)
{
	system("cls");
	cout << "========= 노드 출력 =========" << endl;

	cout << "노드 수 : " << pList->iSize << endl;
	Output(pList);

	system("pause");
}

void DeleteNode(PLIST pList)
{
	system("cls");

	if (Empty(pList))
	{
		cout << "리스트가 비어있습니다." << endl;
		system("pause");
		return;
	}

	Output(pList);

	cout << "삭제할 데이터를 입력하세요 : ";
	int	iData;
	cin >> iData;

	PLISTNODE	pNode = pList->pFirst;
	PLISTNODE	pPrev = NULL;

	while (pNode)
	{
		if (pNode->iData == iData)
			break;

		pPrev = pNode;
		pNode = pNode->pNext;
	}

	if (!pNode)
	{
		cout << "삭제할 데이터가 없습니다." << endl;
		system("pause");
		return;
	}

	if (pPrev)
	{
		pPrev->pNext = pNode->pNext;
		delete	pNode;
	}

	// pPrev가 NULL일 경우는 첫번째 노드라는 의미이다.
	// 이 노드를 지우고 지운 노드의 다음 노드를 first로 준다.
	else
	{
		pList->pFirst = pNode->pNext;
		delete	pNode;
	}

	--pList->iSize;

	cout << "노드 삭제 완료" << endl;

	system("pause");
}

int main()
{
	LIST	tList = {};

	while (true)
	{
		system("cls");
		cout << "1. 노드추가" << endl;
		cout << "2. 노드삭제" << endl;
		cout << "3. 노드전체출력" << endl;
		cout << "4. 종료" << endl;
		int	iInput;
		cout << "메뉴를 선택하세요 : ";
		cin >> iInput;

		if (iInput == 4)
			break;

		switch (iInput)
		{
		case 1:
			Insert(&tList);
			break;
		case 2:
			DeleteNode(&tList);
			break;
		case 3:
			OutputNode(&tList);
			break;
		}
	}

	Clear(&tList);

	return 0;
}

