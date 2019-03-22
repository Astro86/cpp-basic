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
	//cout << "w : �� s : �Ʒ� a : ���� d : ������ q : ���� : ";
	//char	cInput = _getch();
	char	cInput = 'l';

	// Windows Ű �Է� �Լ� : GetAsyncKeyState �Լ��� ������ Ű �Է� �Լ��̴�.
	// �Է� ��⸦ ���� �ʴ´�. �� �Լ��� ���ڷ� Ű�÷��׸� �Ѱ��ָ� �ش� Ű�� �ȴ����� ���
	// 0�� �����ϰ� ������ ��� 0x8000�� �����Ѵ�. ��, ������ ���� ���0x8000 �� 0x1�� OR �����ؼ�
	// �Ѱ��ش�.
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
