
#include "Store.h"
#include "Info.h"

/*
�κ��丮 ����Ʈ�� �����Ѵ�.
�κ��丮�� ���� �޴����� �Ѱ��ְ� �����.
���⳪ �� �������� ������ ����� �����ϰ� ������ش�. ������ �������� �κ��丮�� �߰��Ѵ�.
*/

enum STORE_MAIN_MENU
{
	SMM_NONE,
	SMM_BUY,
	SMM_SELL,
	SMM_BACK
};

enum STORE_BUY_MENU
{
	SBM_NONE,
	SBM_WEAPON,
	SBM_ARMOR,
	SBM_BACK
};

bool InitStore(PITEMLIST pWeaponList, PITEMLIST pArmorList)
{
	InitItemList(pWeaponList);
	InitItemList(pArmorList);

	// �������� �����صд�.
	ITEM	tItem = CreateItem("���", IT_WEAPON, 10, 1000, 500);
	AddItem(pWeaponList, tItem); //������ �̱� ������ �����Ͱ� �ƴ϶� ���� ���� �Ѱ��ش�.

	tItem = CreateItem("���", IT_WEAPON, 40, 7000, 3500);
	AddItem(pWeaponList, tItem);

	tItem = CreateItem("���", IT_WEAPON, 1500, 20000, 10000);
	AddItem(pWeaponList, tItem);

	// �� ��� ����
	tItem = CreateItem("õ����", IT_ARMOR, 5, 1000, 500);
	AddItem(pArmorList, tItem); //������ �̱� ������ �����Ͱ� �ƴ϶� ���� ���� �Ѱ��ش�.

	tItem = CreateItem("���װ���", IT_ARMOR, 20, 7000, 3500);
	AddItem(pArmorList, tItem);

	tItem = CreateItem("���ð���", IT_ARMOR, 75, 20000, 10000);
	AddItem(pArmorList, tItem);

	return true;
}

void RunBuyStore(PITEMLIST pItemList, PPLAYER pPlayer, STORE_BUY_MENU eMenu)
{
	while (true)
	{
		system("cls");
		// ���� �̸��� �����ְ� �Ǹ� ����� �����ش�
		switch (eMenu)
		{
		case SBM_WEAPON:
			OutputTag("�������");
			break;
		case SBM_ARMOR:
			OutputTag("������");
			break;
		}

		// ������ ����� ����Ѵ�.
		PITEMNODE	pNode = pItemList->pFirst;

		int		iCount = 1;

		while (pNode)
		{
			cout << iCount << ". ";
			OutputItem(&pNode->tItem);
			cout << endl;
			++iCount;
			pNode = pNode->pNext;
		}

		cout << iCount << ". �ڷΰ���" << endl;
		cout << "�����ݾ� : " << pPlayer->iGold << " Gold" << endl;
		
		cout << "������ �������� �����ϼ��� : ";
		int	iSelect;
		cin >> iSelect;

		if (iSelect == iCount)
			return;

		else if (iSelect < 1 || iSelect > iCount)
			continue;

		pNode = pItemList->pFirst;
		// ������ �������� ã�´�.
		// �������� , �� �̿��ؼ� 2���� ���� ��� 2�� �� ���۵ȴ�.
		for (int i = 0; i < iSelect - 1; ++i)
		{
			pNode = pNode->pNext;
		}

		// �������� �������� ���ϴ� ���� ���� �����ϰų� ������ ������ ���
		// ������ �� ����.
		if (pPlayer->tInventory.iCount == INVENTORY_MAX)
		{
			cout << "�κ��丮 ������ �����մϴ�." << endl;
			system("pause");
			continue;
		}

		else if (pPlayer->iGold < pNode->tItem.iPrice)
		{
			cout << "�����ݾ��� �����մϴ�." << endl;
			system("pause");
			continue;
		}

		// ã�� �������� �κ��丮�� �־��ְ� ���� �����Ѵ�.
		pPlayer->iGold -= pNode->tItem.iPrice;
		pPlayer->tInventory.tItem[pPlayer->tInventory.iCount] =
			pNode->tItem;
		++pPlayer->tInventory.iCount;

		cout << pNode->tItem.strName << " �������� �����Ͽ����ϴ�." << endl;
		system("pause");
	}
}

int StoreBuyMenu()
{
	system("cls");
	cout << "1. �������" << endl;
	cout << "2. ������" << endl;
	cout << "3. �ڷΰ���" << endl;
	cout << "������ �����ϼ��� : ";
	int	iStore;
	cin >> iStore;

	if (iStore <= SBM_NONE || iStore > SBM_BACK)
		return SBM_NONE;
	return iStore;
}

void RunBuy(PITEMLIST pWeaponList, PITEMLIST pArmorList, PPLAYER pPlayer)
{
	while (true)
	{
		switch (StoreBuyMenu())
		{
		case SBM_WEAPON:
			RunBuyStore(pWeaponList, pPlayer, SBM_WEAPON);
			break;
		case SBM_ARMOR:
			RunBuyStore(pArmorList, pPlayer, SBM_ARMOR);
			break;
		case SBM_BACK:
			return;
		}
	}
}

int StoreSellMenu(PINVENTORY pInventory)
{
	system("cls");

	OutputTag("������ �Ǹ�");

	for (int i = 0; i < pInventory->iCount; ++i)
	{
		cout << i + 1 << ". ";
		OutputItem(&pInventory->tItem[i]);
		cout << endl;
	}

	cout << pInventory->iCount + 1 << ". �ڷΰ���" << endl;
	cout << "�Ǹ��� �������� �����ϼ��� : ";
	int	iSelect;
	cin >> iSelect;

	if (iSelect < 1 || iSelect > pInventory->iCount + 1)
		return -1;

	return iSelect;
}

void RunSell(PPLAYER pPlayer)
{
	while (true)
	{
		int	iSell = StoreSellMenu(&pPlayer->tInventory);

		if (iSell == pPlayer->tInventory.iCount + 1)
			return;

		else if (iSell == -1)
			continue;

		// �Ǹ��� �������� �Ǹűݾ��� �÷��̾�� �����ش�.
		pPlayer->iGold += pPlayer->tInventory.tItem[iSell - 1].iSell;
		cout << pPlayer->tInventory.tItem[iSell - 1].iSell << " Gold�� ȹ���Ͽ����ϴ�." << endl;
	
		// �Ǹ��� �������� ��Ͽ��� �����Ѵ�.
		for (int i = iSell - 1; i < pPlayer->tInventory.iCount - 1; ++i)
		{
			pPlayer->tInventory.tItem[i] = pPlayer->tInventory.tItem[i + 1];
		}

		--pPlayer->tInventory.iCount;

		cout << "������ �ǸŸ� �Ϸ��Ͽ����ϴ�." << endl;
		system("pause");
	}
}

int StoreMainMenu()
{
	system("cls");
	cout << "1. ����" << endl;
	cout << "2. �Ǹ�" << endl;
	cout << "3. �ڷΰ���" << endl;
	cout << "�޴��� �����ϼ��� : ";
	int	iMenu;
	cin >> iMenu;

	if (iMenu <= SMM_NONE || iMenu > SMM_BACK)
		return SMM_NONE;

	return iMenu;
}

void RunStore(PITEMLIST pWeaponList, PITEMLIST pArmorList, PPLAYER pPlayer)
{
	while (true)
	{
		switch (StoreMainMenu())
		{
		case SMM_BUY:
			RunBuy(pWeaponList, pArmorList, pPlayer);
			break;
		case SMM_SELL:
			RunSell(pPlayer);
			break;
		case SMM_BACK:
			return;
		}
	}
}
