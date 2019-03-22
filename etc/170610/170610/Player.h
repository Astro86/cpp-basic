#pragma once

#include "value.h"

class CPlayer
{
public:
	CPlayer();
	~CPlayer();

private:
	int		m_iPos[2];

public:
	void SetPos(int* pPos);
	char Input();
	void Up();
	void Down();
	void Left();
	void Right();

public:
	int* GetPos();
};

