
#include "Inventory.h"
#include "Info.h"

void RunInventory(PPLAYER pPlayer)
{
	while (true)
	{
		system("cls");

		// �÷��̾� ���� ���
		OutputPlayer(pPlayer);
		cout << endl;

		OutputTag("������ ���");
		for (int i = 0; i < pPlayer->tInventory.iCount; ++i)
		{
			cout << i + 1 << ". ";
			OutputItem(&pPlayer->tInventory.tItem[i]);
			cout << endl;
		}

		cout << pPlayer->tInventory.iCount + 1 << ". �ڷΰ���" << endl;
		int	iSelect;
		cout << "������ �������� �����ϼ��� : ";
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

			// �κ��丮���� ������ �������� ���ܽ�Ų��.
			// �ڿ� �ִ� ��� �������� 1ĭ�� ������ �����ش�.
			for (int i = iSelect - 1; i < pPlayer->tInventory.iCount - 1; ++i)
			{
				pPlayer->tInventory.tItem[i] = pPlayer->tInventory.tItem[i + 1];
			}

			--pPlayer->tInventory.iCount;
		}

		pPlayer->bEquip[eq] = true;

		cout << pPlayer->tEquip[eq].strName << " �������� �����Ͽ����ϴ�." << endl;
		system("pause");
	}
}
