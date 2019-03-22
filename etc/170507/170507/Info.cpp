
#include "Info.h"

void OutputTag(char * pName)
{
	cout << "========================= " << pName << " =========================" << endl;
}

void OutputPlayer(const PPLAYER pPlayer)
{
	cout << "이름 : " << pPlayer->strName << "\t직업 : " << pPlayer->strJobName << endl;
	cout << "레벨 : " << pPlayer->iLevel << "\t경험치 : " << pPlayer->iExp << endl;
	cout << "공격력 : " << pPlayer->iAttack;
	if (pPlayer->bEquip[EQ_WEAPON])
		cout << " + " << pPlayer->tEquip[EQ_WEAPON].iMainOption;
	cout << "\t방어력 : " << pPlayer->iArmor;
	if (pPlayer->bEquip[EQ_ARMOR])
		cout << " + " << pPlayer->tEquip[EQ_ARMOR].iMainOption;
	cout << endl;
	cout << "체력 : " << pPlayer->iHP << " / " << pPlayer->iHPMax << "\t마나 : " <<
		pPlayer->iMP << " / " << pPlayer->iMPMax << endl;
	cout << "보유골드 : " << pPlayer->iGold << " Gold" << endl;
	cout << "장착무기 : ";
	if (pPlayer->bEquip[EQ_WEAPON])
		cout << pPlayer->tEquip[EQ_WEAPON].strName << "\t";
	else
		cout << "없음\t";

	cout << "장착방어구 : ";
	if (pPlayer->bEquip[EQ_ARMOR])
		cout << pPlayer->tEquip[EQ_ARMOR].strName << endl;
	else
		cout << "없음" << endl;
}

void OutputMonster(const PMONSTER pMonster)
{
	cout << "이름 : " << pMonster->strName << endl;
	cout << "레벨 : " << pMonster->iLevel << "\t획득경험치 : " << pMonster->iExp << endl;
	cout << "공격력 : " << pMonster->iAttack << "\t방어력 : " << pMonster->iArmor << endl;
	cout << "체력 : " << pMonster->iHP << " / " << pMonster->iHPMax << "\t마나 : " <<
		pMonster->iMP << " / " << pMonster->iMPMax << endl;
	cout << "획득골드 : " << pMonster->iGold << " Gold" << endl;
}

void OutputItem(const PITEM pItem)
{
	cout << "이름 : " << pItem->strName << "\t종류 : ";
	switch (pItem->eType)
	{
	case IT_WEAPON:
		cout << "무기" << endl;
		cout << "공격력 : ";
		break;
	case IT_ARMOR:
		cout << "방어구" << endl;
		cout << "방어력 : ";
		break;
	}

	cout << pItem->iMainOption << endl;
	cout << "구매가격 : " << pItem->iPrice << "\t판매가격 : " << pItem->iSell << endl;
}
