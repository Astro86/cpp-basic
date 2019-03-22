
#include "Store.h"
#include "Info.h"

/*
인벤토리 리스트를 생성한다.
인벤토리를 상점 메뉴까지 넘겨주게 만든다.
무기나 방어구 상점에서 아이템 목록을 선택하게 만들어준다. 선택한 아이템을 인벤토리에 추가한다.
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

	// 아이템을 생성해둔다.
	ITEM	tItem = CreateItem("목검", IT_WEAPON, 10, 1000, 500);
	AddItem(pWeaponList, tItem); //참조자 이기 때문에 포인터가 아니라 값을 직접 넘겨준다.

	tItem = CreateItem("장검", IT_WEAPON, 40, 7000, 3500);
	AddItem(pWeaponList, tItem);

	tItem = CreateItem("용검", IT_WEAPON, 1500, 20000, 10000);
	AddItem(pWeaponList, tItem);

	// 방어구 목록 생성
	tItem = CreateItem("천갑옷", IT_ARMOR, 5, 1000, 500);
	AddItem(pArmorList, tItem); //참조자 이기 때문에 포인터가 아니라 값을 직접 넘겨준다.

	tItem = CreateItem("가죽갑옷", IT_ARMOR, 20, 7000, 3500);
	AddItem(pArmorList, tItem);

	tItem = CreateItem("용비늘갑옷", IT_ARMOR, 75, 20000, 10000);
	AddItem(pArmorList, tItem);

	return true;
}

void RunBuyStore(PITEMLIST pItemList, PPLAYER pPlayer, STORE_BUY_MENU eMenu)
{
	while (true)
	{
		system("cls");
		// 상점 이름을 보여주고 판매 목록을 보여준다
		switch (eMenu)
		{
		case SBM_WEAPON:
			OutputTag("무기상점");
			break;
		case SBM_ARMOR:
			OutputTag("방어구상점");
			break;
		}

		// 아이템 목록을 출력한다.
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

		cout << iCount << ". 뒤로가기" << endl;
		cout << "보유금액 : " << pPlayer->iGold << " Gold" << endl;
		
		cout << "구매할 아이템을 선택하세요 : ";
		int	iSelect;
		cin >> iSelect;

		if (iSelect == iCount)
			return;

		else if (iSelect < 1 || iSelect > iCount)
			continue;

		pNode = pItemList->pFirst;
		// 선택한 아이템을 찾는다.
		// 증감값에 , 를 이용해서 2개를 넣을 경우 2개 다 동작된다.
		for (int i = 0; i < iSelect - 1; ++i)
		{
			pNode = pNode->pNext;
		}

		// 아이템을 구매하지 못하는 경우는 돈이 부족하거나 공간이 부족할 경우
		// 구매할 수 없다.
		if (pPlayer->tInventory.iCount == INVENTORY_MAX)
		{
			cout << "인벤토리 공간이 부족합니다." << endl;
			system("pause");
			continue;
		}

		else if (pPlayer->iGold < pNode->tItem.iPrice)
		{
			cout << "보유금액이 부족합니다." << endl;
			system("pause");
			continue;
		}

		// 찾은 아이템을 인벤토리에 넣어주고 돈을 차감한다.
		pPlayer->iGold -= pNode->tItem.iPrice;
		pPlayer->tInventory.tItem[pPlayer->tInventory.iCount] =
			pNode->tItem;
		++pPlayer->tInventory.iCount;

		cout << pNode->tItem.strName << " 아이템을 구매하였습니다." << endl;
		system("pause");
	}
}

int StoreBuyMenu()
{
	system("cls");
	cout << "1. 무기상점" << endl;
	cout << "2. 방어구상점" << endl;
	cout << "3. 뒤로가기" << endl;
	cout << "상점을 선택하세요 : ";
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

	OutputTag("아이템 판매");

	for (int i = 0; i < pInventory->iCount; ++i)
	{
		cout << i + 1 << ". ";
		OutputItem(&pInventory->tItem[i]);
		cout << endl;
	}

	cout << pInventory->iCount + 1 << ". 뒤로가기" << endl;
	cout << "판매할 아이템을 선택하세요 : ";
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

		// 판매할 아이템의 판매금액을 플레이어에게 돌려준다.
		pPlayer->iGold += pPlayer->tInventory.tItem[iSell - 1].iSell;
		cout << pPlayer->tInventory.tItem[iSell - 1].iSell << " Gold를 획득하였습니다." << endl;
	
		// 판매한 아이템을 목록에서 제외한다.
		for (int i = iSell - 1; i < pPlayer->tInventory.iCount - 1; ++i)
		{
			pPlayer->tInventory.tItem[i] = pPlayer->tInventory.tItem[i + 1];
		}

		--pPlayer->tInventory.iCount;

		cout << "아이템 판매를 완려하였습니다." << endl;
		system("pause");
	}
}

int StoreMainMenu()
{
	system("cls");
	cout << "1. 구매" << endl;
	cout << "2. 판매" << endl;
	cout << "3. 뒤로가기" << endl;
	cout << "메뉴를 선택하세요 : ";
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
