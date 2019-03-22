
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
	cout << "==================== 플레이어 설정 ====================" << endl;
	cout << "이름을 입력하세요 : ";
	cin.getline(pPlayer->strName, NAME_SIZE - 1);

	cout << "직업 선택" << endl;

	int		iJob = 0;
	while (true)
	{
		cout << "1. 기사" << endl;
		cout << "2. 궁수" << endl;
		cout << "3. 마법사" << endl;
		cout << "직업을 선택하세요 : ";
		cin >> iJob;

		if (iJob > JOB_NONE && iJob < JOB_END)
			break;
	}

	// eJob은 JOB 타입 변수이고 iJob은 int타입 변수이므로 형변환해서
	// 넣어주어야 한다.
	pPlayer->eJob = (JOB)iJob;

	switch (iJob)
	{
	case JOB_KNIGHT:
		strcpy_s(pPlayer->strJobName, "기사");
		pPlayer->iAttack = 10;
		pPlayer->iArmor = 20;
		pPlayer->iHP = 500;
		pPlayer->iHPMax = 500;
		pPlayer->iMP = 100;
		pPlayer->iMPMax = 100;
		break;
	case JOB_ARCHER:
		strcpy_s(pPlayer->strJobName, "궁수");
		pPlayer->iAttack = 15;
		pPlayer->iArmor = 15;
		pPlayer->iHP = 400;
		pPlayer->iHPMax = 400;
		pPlayer->iMP = 200;
		pPlayer->iMPMax = 200;
		break;
	case JOB_WIZARD:
		strcpy_s(pPlayer->strJobName, "마법사");
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
	// 플레이어 초기화
	if (!InitPlayer(pPlayer))
		return false;

	// 맵을 초기화한다.
	if (!InitMap(pMonster))
		return false;

	// 상점을 초기화한다.
	if (!InitStore(pWeaponList, pArmorList))
		return false;

	return true;
}

int MainMenu()
{
	system("cls");

	cout << "1. 사냥터" << endl;
	cout << "2. 상점" << endl;
	cout << "3. 인벤토리" << endl;
	cout << "4. 종료" << endl;
	cout << "메뉴를 선택하세요 : ";
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
