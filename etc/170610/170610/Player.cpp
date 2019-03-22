#include "Player.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::SetPos(int * pPos)
{
	m_iPos[0] = pPos[0];
	m_iPos[1] = pPos[1];
}

char CPlayer::Input()
{
	//cout << "w : 위 s : 아래 a : 왼쪽 d : 오른쪽 q : 종료 : ";
	//char	cInput = _getch();
	char	cInput = 'l';

	// Windows 키 입력 함수 : GetAsyncKeyState 함수는 윈도우 키 입력 함수이다.
	// 입력 대기를 하지 않는다. 이 함수는 인자로 키플래그를 넘겨주면 해당 키가 안눌렸을 경우
	// 0을 리턴하고 눌렀을 경우 0x8000을 리턴한다. 단, 누르고 있을 경우0x8000 에 0x1을 OR 연산해서
	// 넘겨준다.
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		cInput = 'w';
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		cInput = 's';
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		cInput = 'a';
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		cInput = 'd';
	}

	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		cInput = 'q';
	}

	return cInput;
}

void CPlayer::Up()
{
	m_iPos[0]--;
}

void CPlayer::Down()
{
	m_iPos[0]++;
}

void CPlayer::Left()
{
	m_iPos[1]--;
}

void CPlayer::Right()
{
	m_iPos[1]++;
}

int * CPlayer::GetPos()
{
	return m_iPos;
}
