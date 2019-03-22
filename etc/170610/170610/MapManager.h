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
	// 전방선언. Maze 클래스를 include 없이 사용 가능하다. 단, 포인터 변수만
	// 선언 가능하고 실제 사용할때는 반드시 include를 해주어야 한다.
	class CMaze**	m_ppMaze;

public:
	bool Init();
	void Run(class CPlayer* pPlayer);
	void Output();
};

