
#include "Core.h"
#include "Map.h"
#include "Store.h"
#include "Inventory.h"

enum MAIN_MENU
{
	MM_NONE,
	MM_MAP,
	MM_STORE,
	MM_INVENTORY,
	MM_EXIT
};

bool InitPlayer(PPLAYER pPlayer)
{
	system("cls");
	cout << "==================== �÷��̾� ���� ====================" << endl;
	cout << "�̸��� �Է��ϼ��� : ";
	cin.getline(pPlayer->strName, NAME_SIZE - 1);

	cout << "���� ����" << endl;

	int		iJob = 0;
	while (true)
	{
		cout << "1. ���" << endl;
		cout << "2. �ü�" << endl;
		cout << "3. ������" << endl;
		cout << "������ �����ϼ��� : ";
		cin >> iJob;

		if (iJob > JOB_NONE && iJob < JOB_END)
			break;
	}

	// eJob�� JOB Ÿ�� �����̰� iJob�� intŸ�� �����̹Ƿ� ����ȯ�ؼ�
	// �־��־�� �Ѵ�.
	pPlayer->eJob = (JOB)iJob;

	switch (iJob)
	{
	case JOB_KNIGHT:
		strcpy_s(pPlayer->strJobName, "���");
		pPlayer->iAttack = 10;
		pPlayer->iArmor = 20;
		pPlayer->iHP = 500;
		pPlayer->iHPMax = 500;
		pPlayer->iMP = 100;
		pPlayer->iMPMax = 100;
		break;
	case JOB_ARCHER:
		strcpy_s(pPlayer->strJobName, "�ü�");
		pPlayer->iAttack = 15;
		pPlayer->iArmor = 15;
		pPlayer->iHP = 400;
		pPlayer->iHPMax = 400;
		pPlayer->iMP = 200;
		pPlayer->iMPMax = 200;
		break;
	case JOB_WIZARD:
		strcpy_s(pPlayer->strJobName, "������");
		pPlayer->iAttack = 20;
		pPlayer->iArmor = 10;
		pPlayer->iHP = 300;
		pPlayer->iHPMax = 300;
		pPlayer->iMP = 300;
		pPlayer->iMPMax = 300;
		break;
	}

	pPlayer->iLevel = 1;
	pPlayer->iExp = 0; 
	pPlayer->iGold = 10000;

	return true;
}

bool Init(PPLAYER pPlayer, PMONSTER pMonster, PITEMLIST pWeaponList, PITEMLIST pArmorList)
{
	// �÷��̾� �ʱ�ȭ
	if (!InitPlayer(pPlayer))
		return false;

	// ���� �ʱ�ȭ�Ѵ�.
	if (!InitMap(pMonster))
		return false;

	// ������ �ʱ�ȭ�Ѵ�.
	if (!InitStore(pWeaponList, pArmorList))
		return false;

	return true;
}

int MainMenu()
{
	system("cls");

	cout << "1. �����" << endl;
	cout << "2. ����" << endl;
	cout << "3. �κ��丮" << endl;
	cout << "4. ����" << endl;
	cout << "�޴��� �����ϼ��� : ";
	int	iMenu;
	cin >> iMenu;

	if (iMenu <= MM_NONE || iMenu > MM_EXIT)
		return MM_NONE;

	return iMenu;
}

void Run(PPLAYER pPlayer, PMONSTER pMonsterPrototype, PITEMLIST pWeaponList, PITEMLIST pArmorList)
{
	while (true)
	{
		switch (MainMenu())
		{
		case MM_MAP:
			RunMap(pPlayer, pMonsterPrototype);
			break;
		case MM_STORE:
			RunStore(pWeaponList, pArmorList, pPlayer);
			break;
		case MM_INVENTORY:
			RunInventory(pPlayer);
			break;
		case MM_EXIT:
			return;
		}
	}
}
