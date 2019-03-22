
#pragma once

#include <iostream>

using namespace std;

#define	NAME_SIZE	32
#define	LEVEL_MAX	10

const unsigned int	g_iLvUpTable[LEVEL_MAX]	=
{
	10000, 15000, 22000, 32000, 45000, 63000, 83000, 110000, 150000, 200000
};

enum JOB
{
	JOB_NONE,
	JOB_KNIGHT,
	JOB_ARCHER,
	JOB_WIZARD,
	JOB_END
};

// Item Type
enum ITEM_TYPE
{
	IT_WEAPON,
	IT_ARMOR,
	IT_END
};

enum EQUIP
{
	EQ_WEAPON,
	EQ_ARMOR,
	EQ_END
};

// Item
typedef struct _tagItem
{
	char	strName[NAME_SIZE];
	ITEM_TYPE	eType;
	int		iMainOption;
	int		iPrice;
	int		iSell;
}ITEM, *PITEM;

#define	INVENTORY_MAX	10

// Inventory
typedef struct _tagInventory
{
	ITEM	tItem[INVENTORY_MAX];
	int		iCount;
}INVENTORY, *PINVENTORY;

// Player
typedef struct _tagPlayer
{
	char	strName[NAME_SIZE];
	// enum문 변수를 생성할 수도 있다.
	JOB		eJob;
	char	strJobName[NAME_SIZE];
	int		iAttack;
	int		iArmor;
	int		iHP;
	int		iHPMax;
	int		iMP;
	int		iMPMax;
	int		iExp;
	int		iGold;
	int		iLevel;
	INVENTORY	tInventory;
	ITEM		tEquip[EQ_END];
	bool		bEquip[EQ_END];
}PLAYER, *PPLAYER;

// Monster
typedef struct _tagMonster
{
	char	strName[NAME_SIZE];
	int		iAttack;
	int		iArmor;
	int		iHP;
	int		iHPMax;
	int		iMP;
	int		iMPMax;
	int		iExp;
	int		iGold;
	int		iLevel;
}MONSTER, *PMONSTER;
