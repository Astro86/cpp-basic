#pragma once

#include "value.h"

class CMapManager
{
private:
	static CMapManager*	m_pInst;

public:
	static CMapManager* GetInst()
	{
		if (!m_pInst)
			m_pInst = new CMapManager;
		return m_pInst;
	}

	static void DestroyInst()
	{
		if (m_pInst)
		{
			delete	m_pInst;
			m_pInst = NULL;
		}
	}

private:
	CMapManager();
	~CMapManager();

private:
	char	**m_ppMapList;
	int		m_iMapCount;
	// ���漱��. Maze Ŭ������ include ���� ��� �����ϴ�. ��, ������ ������
	// ���� �����ϰ� ���� ����Ҷ��� �ݵ�� include�� ���־�� �Ѵ�.
	class CMaze**	m_ppMaze;

public:
	bool Init();
	void Run(class CPlayer* pPlayer);
	void Output();
};

