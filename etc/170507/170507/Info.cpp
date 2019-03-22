
#include "Info.h"

void OutputTag(char * pName)
{
	cout << "========================= " << pName << " =========================" << endl;
}

void OutputPlayer(const PPLAYER pPlayer)
{
	cout << "�̸� : " << pPlayer->strName << "\t���� : " << pPlayer->strJobName << endl;
	cout << "���� : " << pPlayer->iLevel << "\t����ġ : " << pPlayer->iExp << endl;
	cout << "���ݷ� : " << pPlayer->iAttack;
	if (pPlayer->bEquip[EQ_WEAPON])
		cout << " + " << pPlayer->tEquip[EQ_WEAPON].iMainOption;
	cout << "\t���� : " << pPlayer->iArmor;
	if (pPlayer->bEquip[EQ_ARMOR])
		cout << " + " << pPlayer->tEquip[EQ_ARMOR].iMainOption;
	cout << endl;
	cout << "ü�� : " << pPlayer->iHP << " / " << pPlayer->iHPMax << "\t���� : " <<
		pPlayer->iMP << " / " << pPlayer->iMPMax << endl;
	cout << "������� : " << pPlayer->iGold << " Gold" << endl;
	cout << "�������� : ";
	if (pPlayer->bEquip[EQ_WEAPON])
		cout << pPlayer->tEquip[EQ_WEAPON].strName << "\t";
	else
		cout << "����\t";

	cout << "������ : ";
	if (pPlayer->bEquip[EQ_ARMOR])
		cout << pPlayer->tEquip[EQ_ARMOR].strName << endl;
	else
		cout << "����" << endl;
}

void OutputMonster(const PMONSTER pMonster)
{
	cout << "�̸� : " << pMonster->strName << endl;
	cout << "���� : " << pMonster->iLevel << "\tȹ�����ġ : " << pMonster->iExp << endl;
	cout << "���ݷ� : " << pMonster->iAttack << "\t���� : " << pMonster->iArmor << endl;
	cout << "ü�� : " << pMonster->iHP << " / " << pMonster->iHPMax << "\t���� : " <<
		pMonster->iMP << " / " << pMonster->iMPMax << endl;
	cout << "ȹ���� : " << pMonster->iGold << " Gold" << endl;
}

void OutputItem(const PITEM pItem)
{
	cout << "�̸� : " << pItem->strName << "\t���� : ";
	switch (pItem->eType)
	{
	case IT_WEAPON:
		cout << "����" << endl;
		cout << "���ݷ� : ";
		break;
	case IT_ARMOR:
		cout << "��" << endl;
		cout << "���� : ";
		break;
	}

	cout << pItem->iMainOption << endl;
	cout << "���Ű��� : " << pItem->iPrice << "\t�ǸŰ��� : " << pItem->iSell << endl;
}
