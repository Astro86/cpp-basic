
#include "Inventory.h"
#include "Info.h"

void RunInventory(PPLAYER pPlayer)
{
	while (true)
	{
		system("cls");

		// 플레이어 정보 출력
		OutputPlayer(pPlayer);
		cout << endl;

		OutputTag("아이템 목록");
		for (int i = 0; i < pPlayer->tInventory.iCount; ++i)
		{
			cout << i + 1 << ". ";
			OutputItem(&pPlayer->tInventory.tItem[i]);
			cout << endl;
		}

		cout << pPlayer->tInventory.iCount + 1 << ". 뒤로가기" << endl;
		int	iSelect;
		cout << "장착할 아이템을 선택하세요 : ";
		cin >> iSelect;

		if (iSelect == pPlayer->tInventory.iCount + 1)
			return;

		else if (iSelect < 1 || iSelect > pPlayer->tInventory.iCount + 1)
			continue;

		EQUIP	eq;
		switch (pPlayer->tInventory.tItem[iSelect - 1].eType)
		{
		case IT_WEAPON:
			eq = EQ_WEAPON;
			break;
		case IT_ARMOR:
			eq = EQ_ARMOR;
			break;
		}


		if (pPlayer->bEquip[eq])
		{
			ITEM	tItem = pPlayer->tEquip[eq];
			pPlayer->tEquip[eq] = pPlayer->tInventory.tItem[iSelect - 1];
			pPlayer->tInventory.tItem[iSelect - 1] = tItem;
		}

		else
		{
			pPlayer->tEquip[eq] = pPlayer->tInventory.tItem[iSelect - 1];

			// 인벤토리에서 장착한 아이템을 제외시킨다.
			// 뒤에 있는 모든 아이템을 1칸씩 앞으로 땡겨준다.
			for (int i = iSelect - 1; i < pPlayer->tInventory.iCount - 1; ++i)
			{
				pPlayer->tInventory.tItem[i] = pPlayer->tInventory.tItem[i + 1];
			}

			--pPlayer->tInventory.iCount;
		}

		pPlayer->bEquip[eq] = true;

		cout << pPlayer->tEquip[eq].strName << " 아이템을 장착하였습니다." << endl;
		system("pause");
	}
}
