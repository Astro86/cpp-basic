
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

	// �����͸� ��Ƶ� ��带 �����Ѵ�.
	PLISTNODE	pNode = new LISTNODE;

	pNode->iData = iData;
	pNode->pNext = 0;

	// pFirst�� NULL�� ����� ��尡 �ƿ� �߰��Ǿ� ���� �ʴٴ� ���̴�.
	// ��, ��带 ó�� �߰��Ѵٴ� ���̴�. �׷��Ƿ� NULL���� üũ�ؼ�
	// NULL�� ��� pFirst�� ����� �ּҸ� �־��ش�.
	if (!pList->pFirst)
		pList->pFirst = pNode;

	// ����ü�� Ŭ������ ��� ������ ������ �ش� ����ü Ȥ�� Ŭ���� Ÿ����
	// �Ϲ� ������ �޸� �ּҸ� ������ ���� ��� ->�� �����ϰ� �Ǹ� ����
	// Ű�� ����� ����� �����ϴ� ���̴�.
	// (*pList).  �� pList-> �� ����.
	else
		pList->pCurrent->pNext = pNode;
	
	// ������� �߰��� �Ϸ�Ǹ� pCurrent�� ���� ������ ��带 �־
	// ������ ��带 pCurrent�� ����Ű���� �Ѵ�.
	pList->pCurrent = pNode;

	++pList->iSize;
}

void Output(PLIST pList)
{
	// pNode�� ����Ʈ�� ù��° ����� �ּҸ� ��Ƴ��´�.
	// pNode�� ������ �� ��带 �湮�ϱ� ���ؼ� �̴�.
	PLISTNODE	pNode = pList->pFirst;

	// pNode�� NULL�� �ƴ� ����� true�� ������ �Ǿ� ��� �ݺ��ȴ�.
	// �� NULL�϶����� ���ٴ� �ǹ̴� ��� ���� ��带 ���ͼ� �����ϸ�
	// ������ ����� ���� ���� 0�̹Ƿ� ������ ������ �ݺ��ϰ�
	// �Ǵ� ���̴�.
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

void Clear(PLIST pList)
{
	PLISTNODE	pNode = pList->pFirst;

	while (pNode)
	{
		PLISTNODE	pNext = pNode->pNext;
		delete	pNode;
		pNode = pNext;
	}

	pList->iSize = 0;
	pList->pFirst = 0;
	pList->pCurrent = 0;
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

	// ��带 ����� ���ؼ��� ���� ���� ���� ��尡 �ʿ��ϴ�.
	// �ֳ��ϸ� ���� ���� ���� ��带 ����Ű�� �ִµ� ��带 ����� �Ǹ�
	// ���� ����� ���� ���� ���� ����� ���� ��带 ������ �־�� �ϱ� �����̴�.
	// �׷��� ������ ������ �ȴ�.
	PLISTNODE	pNode = pList->pFirst;
	PLISTNODE	pPrev = NULL;

	// ��尡 NULL�̸� ������ ���� ������ �����Ƿ� ���̻� ��尡 ���� ������
	// �ݺ��� �����Ѵ�.
	while (pNode)
	{
		// ��带 ã�Ҵٸ� �ݺ����� ����������.
		// ���������� �Ǹ� ���� ���� pNode�� �ּҸ� ������ �ְ� �ǰ�
		// ���� ���� pPrev�� ����ȴ�. ó�� ��带 ����� �ȴٸ� ���� ���� �����Ƿ�
		// ���⼭ ù ������ �ٷ� ���������� �Ǿ� ���� ���� NULL�� ����Ǿ��ִ�.
		if (pNode->iData == iData)
			break;

		// ���� ��带 Ž���ؾ� �ϹǷ� ���� ��带 ���� ���� �����Ѵ�.
		pPrev = pNode;
		// ���� ��带 ���´�.
		pNode = pNode->pNext;
	}

	// pNode�� NULL�̶�� ������ ������ Ž���ߴµ� ���ٴ� �ǹ��̴�.
	if (!pNode)
	{
		cout << "�����͸� ã�� �� �����ϴ�." << endl;
		system("pause");
		return;
	}

	// ���� ù��° ��带 ����� �ȴٸ� ù��° ���� ���� ��尡 ����.
	// ���� ��尡 NULL�� �ƴ� ��쿡�� ���� ����� ���� ��带 ���� �����
	// ���� ���� �����Ѵ�.
	if (pPrev)
		pPrev->pNext = pNode->pNext;

	delete	pNode;
	--pList->iSize;

	cout << "��� ���� �Ϸ�" << endl;

	Output(pList);

	system("pause");
}

void _Reverse(PLIST pList)
{
	PLISTNODE	pPrev = NULL;
	PLISTNODE	pNode = pList->pFirst;
	PLISTNODE	pNext = NULL;
	PLISTNODE	pNextNext = pNode->pNext;

	while (pNode)
	{
		pNext = pNextNext;
		if (pNext)
			pNextNext = pNext->pNext;

		pNode->pNext = pPrev;

		pPrev = pNode;
		pNode = pNext;
	}

	pNode = pList->pFirst;
	pList->pFirst = pList->pCurrent;
	pList->pCurrent = pNode;
}

void Reverse(PLIST pList)
{
	system("cls");

	if (Empty(pList))
	{
		cout << "����Ʈ�� ����ֽ��ϴ�." << endl;
		system("pause");
		return;
	}

	cout << "Reverse" << endl;

	Output(pList);

	_Reverse(pList);

	Output(pList);

	system("pause");
}

void Mirror(PLIST pList)
{
	system("cls");

	cout << "Mirror" << endl;

	if (Empty(pList))
	{
		cout << "����Ʈ�� ����ֽ��ϴ�." << endl;
		system("pause");
		return;
	}

	Output(pList);

	_Reverse(pList);

	Output(pList);

	_Reverse(pList);

	system("pause");
}

int main()
{
	// ����Ʈ ������ �����Ѵ�.
	// ����Ʈ ����ü ���� first�� ù��° ����� �ּҸ� ����ִ�.
	// ��尡 ���� ��� NULL�̴�.
	// current�� �������� �߰��� ��带 �˰��ִ�.
	// ��尡 ���� ��� NULL�̰� �� current�ڿ� ���� �߰��� ��尡
	// �߰��ȴ�.
	// ù��° ��带 �˾ƾ� ��������� �ּҷ� Ÿ����鼭 ��� ��带
	// ��ȸ�� �����ϴ�. �׷��Ƿ� ����Ʈ ����ü�� ù��° ��带 ��Ƶΰ�
	// ����ϴ� ���̴�.
	LIST	tList = {};

	while (true)
	{
		system("cls");
		cout << "1. ����߰�" << endl;
		cout << "2. ������" << endl;
		cout << "3. �����ü���" << endl;
		cout << "4. ��� ������" << endl;
		cout << "5. Mirror" << endl;
		cout << "6. ����" << endl;
		int	iInput;
		cout << "�޴��� �����ϼ��� : ";
		cin >> iInput;

		if (iInput == 6)
			break;

		switch (iInput)
		{
		case 1:
			// �����͸� �Է¹޾Ƽ� ��带 �߰��Ѵ�.
			Insert(&tList);
			break;
		case 2:
			DeleteNode(&tList);
			break;
		case 3:
			OutputNode(&tList);
			break;
		case 4:
			Reverse(&tList);
			break;
		case 5:
			Mirror(&tList);
			break;
		}
	}

	Clear(&tList);

	return 0;
}