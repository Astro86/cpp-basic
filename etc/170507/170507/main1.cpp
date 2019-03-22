
#include "Core.h"
#include "ItemList.h"

int main()
{
	PLAYER	tPlayer = {};

	// 원본 몬스터를 담아놓을 구조체 변수를 설정한다.
	// 몬스터는 각 사냥터마다 1마리씩만 생성해두기로 한다.
	// 배열 3개가 필요하다.
	MONSTER	tMonster[3] = {};

	ITEMLIST	tWeaponList, tArmorList;

	// 게임을 초기화한다.
	if (!Init(&tPlayer, tMonster, &tWeaponList, &tArmorList))
		return 0;

	Run(&tPlayer, tMonster, &tWeaponList, &tArmorList);

	return 0;
}