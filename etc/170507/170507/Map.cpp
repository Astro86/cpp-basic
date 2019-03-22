
#include "Map.h"
#include "Info.h"

enum MAP_MENU
{
	MAP_NONE,
	MAP_EASY,
	MAP_NORMAL,
	MAP_HARD,
	MAP_BACK
};

enum BATTLE_MENU
{
	BM_NONE,
	BM_ATTACK,
	BM_BACK
};

MONSTER CreateMonster(char* pName, int iAttack, int iArmor,
	int iHP, int iMP, int iExp, int iGold, int iLevel)
{
	MONSTER	tMonster = {};
	strcpy_s(tMonster.strName, pName);
	tMonster.iAttack = iAttack;
	tMonster.iArmor = iArmor;
	tMonster.iHP = iHP;
	tMonster.iHPMax = iHP;
	tMonster.iMP = iMP;
	tMonster.iMPMax = iMP;
	tMonster.iExp = iExp;
	tMonster.iGold = iGold;
	tMonster.iLevel = iLevel;
	return tMonster;
}

bool InitMap(PMONSTER pMonster)
{
	// 각 사냥터별 몬스터를 설정한다.
	pMonster[0] = CreateMonster("송준호", 25, 5, 100, 10, 1000, 2000, 1);
	pMonster[1] = CreateMonster("이상진", 60, 40, 1000, 100, 6000, 10000, 5);
	pMonster[2] = CreateMonster("최재관", 150, 100, 3000, 3000, 15000, 40000, 10);

	return true;
}

int MapMenu()
{
	system("cls");
	cout << "================ 사냥터 ================" << endl;
	cout << "1. 초보" << endl;
	cout << "2. 중수" << endl;
	cout << "3. 고수" << endl;
	cout << "4. 뒤로가기" << endl;
	cout << "메뉴를 선택하세요 : ";
	int	iMenu;
	cin >> iMenu;

	if (iMenu <= MAP_NONE || iMenu > MAP_BACK)
		return MAP_NONE;

	return iMenu;
}

bool BattleAttack(PPLAYER pPlayer, PMONSTER pMonster)
{
	// Damage를 구한다.
	int	iDamage = pPlayer->iAttack - pMonster->iArmor;

	if (pPlayer->bEquip[EQ_WEAPON])
		iDamage += pPlayer->tEquip[EQ_WEAPON].iMainOption;

	iDamage = iDamage < 1 ? 1 : iDamage;

	pMonster->iHP -= iDamage;

	cout << pPlayer->strName << " 가 " << pMonster->strName << " 에게 " << iDamage <<
		" 피해를 주었습니다." << endl;

	if (pMonster->iHP <= 0)
	{
		cout << pMonster->strName << " 몬스터가 사망하였습니다." << endl;
		cout << pMonster->iExp << " 경험치를 획득하였습니다." << endl;
		cout << pMonster->iGold << " Gold를 획득하였습니다." << endl;
		pPlayer->iExp += pMonster->iExp;
		pPlayer->iGold += pMonster->iGold;

		if (pPlayer->iExp >= g_iLvUpTable[pPlayer->iLevel - 1])
		{
			pPlayer->iExp -= g_iLvUpTable[pPlayer->iLevel - 1];
			++pPlayer->iLevel;
			cout << pPlayer->iLevel << " 레벨 달성" << endl;

			float	fAttack, fArmor, fHP, fMP;
			switch (pPlayer->eJob)
			{
			case JOB_KNIGHT:
				fAttack = 0.1f;
				fArmor = 0.2f;
				fHP = 0.2f;
				fMP = 0.1f;
				break;
			case JOB_ARCHER:
				fAttack = 0.15f;
				fArmor = 0.15f;
				fHP = 0.15f;
				fMP = 0.15f;
				break;
			case JOB_WIZARD:
				fAttack = 0.2f;
				fArmor = 0.1f;
				fHP = 0.1f;
				fMP = 0.2f;
				break;
			}

			float	fOption = pPlayer->iAttack * fAttack;
			int		iOption = (int)fOption;
			if (fOption < 1.f)
				iOption = 1;
			pPlayer->iAttack += iOption;

			fOption = pPlayer->iArmor * fArmor;
			iOption = (int)fOption;
			if (fOption < 1.f)
				iOption = 1;
			pPlayer->iArmor += iOption;

			fOption = pPlayer->iHPMax * fHP;
			iOption = (int)fOption;
			if (fOption < 1.f)
				iOption = 1;
			pPlayer->iHPMax += iOption;
			pPlayer->iHP = pPlayer->iHPMax;

			fOption = pPlayer->iMPMax * fMP;
			iOption = (int)fOption;
			if (fOption < 1.f)
				iOption = 1;
			pPlayer->iMPMax += iOption;
			pPlayer->iMP = pPlayer->iMPMax;
		}

		return true;
	}

	// 몬스터가 플레이어를 공격한다.
	iDamage = pMonster->iAttack - pPlayer->iArmor;

	if (pPlayer->bEquip[EQ_ARMOR])
		iDamage -= pPlayer->tEquip[EQ_ARMOR].iMainOption;

	iDamage = iDamage < 1 ? 1 : iDamage;

	pPlayer->iHP -= iDamage;

	cout << pMonster->strName << " 가 " << pPlayer->strName << " 에게 " << iDamage <<
		" 피해를 주었습니다." << endl;

	if (pPlayer->iHP <= 0)
	{
		cout << pPlayer->strName << " 플레이어가 사망하였습니다." << endl;
		cout << pPlayer->iExp * 0.1f << " 경험치를 잃었습니다." << endl;
		cout << pPlayer->iGold * 0.1f << " Gold를 잃었습니다." << endl;
		pPlayer->iExp *= 0.9f;
		pPlayer->iGold *= 0.9f;

		pPlayer->iHP = pPlayer->iHPMax;
		pPlayer->iMP = pPlayer->iMPMax;
	}

	return false;
}

int BattleMenu()
{
	cout << "1. 공격" << endl;
	cout << "2. 도망가기" << endl;
	cout << "메뉴를 선택하세요 : ";
	int	iInput;
	cin >> iInput;

	if (iInput <= BM_NONE || iInput > BM_BACK)
		return BM_NONE;

	return iInput;
}


void RunBattle(PPLAYER pPlayer, PMONSTER pMonsterPrototype, MAP_MENU eMenu)
{
	// 현재 난이도에 맞는 몬스터를 생성해준다.
	MONSTER	tMonster = pMonsterPrototype[eMenu - 1];

	while (true)
	{
		system("cls");
		// 플레이어 정보를 출력한다.
		OutputTag("Player");
		OutputPlayer(pPlayer);
		cout << endl;

		// 몬스터 정보를 출력한다.
		OutputTag("Monster");
		OutputMonster(&tMonster);
		cout << endl;

		switch (BattleMenu())
		{
		case BM_ATTACK:
			if (BattleAttack(pPlayer, &tMonster))
			{
				// 몬스터가 죽엇을 경우 정보를 다시 복사한다.
				tMonster = pMonsterPrototype[eMenu - 1];
			}
			system("pause");
			break;
		case BM_BACK:
			return;
		}
	}
}

void RunMap(PPLAYER pPlayer, PMONSTER pMonsterPrototype)
{
	while (true)
	{
		switch (MapMenu())
		{
		case MAP_EASY:
			RunBattle(pPlayer, pMonsterPrototype, MAP_EASY);
			break;
		case MAP_NORMAL:
			RunBattle(pPlayer, pMonsterPrototype, MAP_NORMAL);
			break;
		case MAP_HARD:
			RunBattle(pPlayer, pMonsterPrototype, MAP_HARD);
			break;
		case MAP_BACK:
			return;
		}
	}
}
