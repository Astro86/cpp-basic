
#pragma once

#include "ItemList.h"

// 함수는 선언과 정의 부분으로 나눌 수 있다.
// 헤더파일에는 이 함수의 선언 부분을 만들어 주고
// cpp파일에 실제 정의 부분을 만들어준다.
bool Init(PPLAYER pPlayer, PMONSTER pMonster, PITEMLIST pWeaponList, PITEMLIST pArmorList);
void Run(PPLAYER pPlayer, PMONSTER pMonsterPrototype, PITEMLIST pWeaponList, PITEMLIST pArmorList);
