#pragma once

#include "value.h"

class CCore
{
private:
	static CCore*	m_pInst;

public:
	// Singleton ���� : ��ü ������ ���ϴ� ������ŭ�� �����ϰ� �����Ѵ�.
	// ����, �Ҹ��ڸ� private���� �θ� �ܺο��� ������ �Ұ����ѵ� �Ʒ� �Լ���
	// �̿��ؼ� ��ü�� �����Ѵ�. static ��������� static ����Լ����� �ٷ�
	// ������ �����ϹǷ� ���⿡ NULL�϶��� ���� �Ҵ��� �ϰ� �� ���Ŀ��� �Ҵ��
	// ��ü�� ���ϸ� �Ѵ�. �� 1���� �����ȴ�.
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

