#pragma once

#include "value.h"

class CMaze
{
public:
	CMaze();
	~CMaze();

private:
	char	m_Maze[20][20];
	int		m_iStartPos[2];
	int		m_iEndPos[2];

public:
	int* GetStartPos();
	int* GetEndPos();
	char GetTileInfo(int* pPos);
	bool Finish(int* pPos);

public:
	bool Load(char* pFileName);
	void Output(class CPlayer* pPlayer);
};

