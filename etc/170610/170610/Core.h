#pragma once

#include "value.h"

class CCore
{
private:
	static CCore*	m_pInst;

public:
	// Singleton 패턴 : 객체 생성을 원하는 개수만큼만 생성하게 제어한다.
	// 생성, 소멸자를 private으로 두면 외부에서 접근이 불가능한데 아래 함수를
	// 이용해서 객체를 생성한다. static 멤버변수는 static 멤버함수에서 바로
	// 접근이 가능하므로 여기에 NULL일때만 동적 할당을 하고 그 이후에는 할당된
	// 객체를 리턴만 한다. 즉 1개만 생성된다.
	static CCore* GetInst()
	{
		if (!m_pInst)
			m_pInst = new CCore;
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
	CCore();
	~CCore();

private:
	class CPlayer*	m_pPlayer;

public:
	bool Init();
	void Run();
};

