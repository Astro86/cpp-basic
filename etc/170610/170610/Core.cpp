#include "Core.h"
#include "MapManager.h"
#include "Player.h"

//스태틱 멤버변수를 사용하겠다는 선언.
CCore* CCore::m_pInst = NULL;

CCore::CCore()	:
	m_pPlayer(NULL)
{
}

CCore::~CCore()
{
	if (m_pPlayer)
		delete	m_pPlayer;
	CMapManager::DestroyInst();
}

bool CCore::Init()
{
	// 플레이어를 할당한다.
	m_pPlayer = new CPlayer;

	// 맵 관리자 초기화
	if (!CMapManager::GetInst()->Init())
		return false;

	return true;
}

void CCore::Run()
{
	CMapManager::GetInst()->Run(m_pPlayer);
}
