
#include "Core.h"
#include "ItemList.h"

int main()
{
	PLAYER	tPlayer = {};

	// ���� ���͸� ��Ƴ��� ����ü ������ �����Ѵ�.
	// ���ʹ� �� ����͸��� 1�������� �����صα�� �Ѵ�.
	// �迭 3���� �ʿ��ϴ�.
	MONSTER	tMonster[3] = {};

	ITEMLIST	tWeaponList, tArmorList;

	// ������ �ʱ�ȭ�Ѵ�.
	if (!Init(&tPlayer, tMonster, &tWeaponList, &tArmorList))
		return 0;

	Run(&tPlayer, tMonster, &tWeaponList, &tArmorList);

	return 0;
}