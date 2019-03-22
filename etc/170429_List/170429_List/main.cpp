
#include "value.h"

bool Empty(PLIST pList)
{
	return pList->iSize == 0;
}

void Insert(PLIST pList)
{
	// �߰��� �����͸� �Է¹޴´�.
	system("cls");
	cout << "�߰��� �����͸� �Է��ϼ��� : ";
	int	iData;
	cin >> iData;

	// ��带 �����Ѵ�.
	PLISTNODE	pNode = new LISTNODE;

	pNode->iData = iData;
	pNode->pNext = NULL;

	// ó�� ��尡 NULL�� ���� ��带 ó�� �߰��ϴ� ���̹Ƿ� ù ��忡 �־��ش�.
	if (pList->pFirst == NULL)
		pList->pFirst = pNode;

	else
		pList->pCurrent->pNext = pNode;

	pList->pCurrent = pNode;

	++pList->iSize;
}

// ��� ��带 �ݺ��ϸ� �����Ѵ�.
void Clear(PLIST pList)
{
	PLISTNODE	pNode = pList->pFirst;

	// pNode�� NULL�� �ƴ� ����� �ݺ��Ѵ�.
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
	cout << "========= ��� ��� =========" << endl;

	cout << "��� �� : " << pList->iSize << endl;
	Output(pList);

	system("pause");
}

void DeleteNode(PLIST pList)
{
	system("cls");

	if (Empty(pList))
	{
		cout << "����Ʈ�� ����ֽ��ϴ�." << endl;
		system("pause");
		return;
	}

	Output(pList);

	cout << "������ �����͸� �Է��ϼ��� : ";
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
		cout << "������ �����Ͱ� �����ϴ�." << endl;
		system("pause");
		return;
	}

	if (pPrev)
	{
		pPrev->pNext = pNode->pNext;
		delete	pNode;
	}

	// pPrev�� NULL�� ���� ù��° ����� �ǹ��̴�.
	// �� ��带 ����� ���� ����� ���� ��带 first�� �ش�.
	else
	{
		pList->pFirst = pNode->pNext;
		delete	pNode;
	}

	--pList->iSize;

	cout << "��� ���� �Ϸ�" << endl;

	system("pause");
}

int main()
{
	LIST	tList = {};

	while (true)
	{
		system("cls");
		cout << "1. ����߰�" << endl;
		cout << "2. ������" << endl;
		cout << "3. �����ü���" << endl;
		cout << "4. ����" << endl;
		int	iInput;
		cout << "�޴��� �����ϼ��� : ";
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

