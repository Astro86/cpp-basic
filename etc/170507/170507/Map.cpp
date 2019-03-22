
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
	// �� ����ͺ� ���͸� �����Ѵ�.
	pMonster[0] = CreateMonster("����ȣ", 25, 5, 100, 10, 1000, 2000, 1);
	pMonster[1] = CreateMonster("�̻���", 60, 40, 1000, 100, 6000, 10000, 5);
	pMonster[2] = CreateMonster("�����", 150, 100, 3000, 3000, 15000, 40000, 10);

	return true;
}

int MapMenu()
{
	system("cls");
	cout << "================ ����� ================" << endl;
	cout << "1. �ʺ�" << endl;
	cout << "2. �߼�" << endl;
	cout << "3. ���" << endl;
	cout << "4. �ڷΰ���" << endl;
	cout << "�޴��� �����ϼ��� : ";
	int	iMenu;
	cin >> iMenu;

	if (iMenu <= MAP_NONE || iMenu > MAP_BACK)
		return MAP_NONE;

	return iMenu;
}

bool BattleAttack(PPLAYER pPlayer, PMONSTER pMonster)
{
	// Damage�� ���Ѵ�.
	int	iDamage = pPlayer->iAttack - pMonster->iArmor;

	if (pPlayer->bEquip[EQ_WEAPON])
		iDamage += pPlayer->tEquip[EQ_WEAPON].iMainOption;

	iDamage = iDamage < 1 ? 1 : iDamage;

	pMonster->iHP -= iDamage;

	cout << pPlayer->strName << " �� " << pMonster->strName << " ���� " << iDamage <<
		" ���ظ� �־����ϴ�." << endl;

	if (pMonster->iHP <= 0)
	{
		cout << pMonster->strName << " ���Ͱ� ����Ͽ����ϴ�." << endl;
		cout << pMonster->iExp << " ����ġ�� ȹ���Ͽ����ϴ�." << endl;
		cout << pMonster->iGold << " Gold�� ȹ���Ͽ����ϴ�." << endl;
		pPlayer->iExp += pMonster->iExp;
		pPlayer->iGold += pMonster->iGold;

		if (pPlayer->iExp >= g_iLvUpTable[pPlayer->iLevel - 1])
		{
			pPlayer->iExp -= g_iLvUpTable[pPlayer->iLevel - 1];
			++pPlayer->iLevel;
			cout << pPlayer->iLevel << " ���� �޼�" << endl;

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

	// ���Ͱ� �÷��̾ �����Ѵ�.
	iDamage = pMonster->iAttack - pPlayer->iArmor;

	if (pPlayer->bEquip[EQ_ARMOR])
		iDamage -= pPlayer->tEquip[EQ_ARMOR].iMainOption;

	iDamage = iDamage < 1 ? 1 : iDamage;

	pPlayer->iHP -= iDamage;

	cout << pMonster->strName << " �� " << pPlayer->strName << " ���� " << iDamage <<
		" ���ظ� �־����ϴ�." << endl;

	if (pPlayer->iHP <= 0)
	{
		cout << pPlayer->strName << " �÷��̾ ����Ͽ����ϴ�." << endl;
		cout << pPlayer->iExp * 0.1f << " ����ġ�� �Ҿ����ϴ�." << endl;
		cout << pPlayer->iGold * 0.1f << " Gold�� �Ҿ����ϴ�." << endl;
		pPlayer->iExp *= 0.9f;
		pPlayer->iGold *= 0.9f;

		pPlayer->iHP = pPlayer->iHPMax;
		pPlayer->iMP = pPlayer->iMPMax;
	}

	return false;
}

int BattleMenu()
{
	cout << "1. ����" << endl;
	cout << "2. ��������" << endl;
	cout << "�޴��� �����ϼ��� : ";
	int	iInput;
	cin >> iInput;

	if (iInput <= BM_NONE || iInput > BM_BACK)
		return BM_NONE;

	return iInput;
}


void RunBattle(PPLAYER pPlayer, PMONSTER pMonsterPrototype, MAP_MENU eMenu)
{
	// ���� ���̵��� �´� ���͸� �������ش�.
	MONSTER	tMonster = pMonsterPrototype[eMenu - 1];

	while (true)
	{
		system("cls");
		// �÷��̾� ������ ����Ѵ�.
		OutputTag("Player");
		OutputPlayer(pPlayer);
		cout << endl;

		// ���� ������ ����Ѵ�.
		OutputTag("Monster");
		OutputMonster(&tMonster);
		cout << endl;

		switch (BattleMenu())
		{
		case BM_ATTACK:
			if (BattleAttack(pPlayer, &tMonster))
			{
				// ���Ͱ� �׾��� ��� ������ �ٽ� �����Ѵ�.
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
