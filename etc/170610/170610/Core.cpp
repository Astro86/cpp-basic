#include "Core.h"
#include "MapManager.h"
#include "Player.h"

//����ƽ ��������� ����ϰڴٴ� ����.
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
	// �÷��̾ �Ҵ��Ѵ�.
	m_pPlayer = new CPlayer;

	// �� ������ �ʱ�ȭ
	if (!CMapManager::GetInst()->Init())
		return false;

	return true;
}

void CCore::Run()
{
	CMapManager::GetInst()->Run(m_pPlayer);
}
