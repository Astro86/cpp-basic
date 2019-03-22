#include "MapManager.h"
#include "Maze.h"
#include "Player.h"

CMapManager* CMapManager::m_pInst = NULL;

CMapManager::CMapManager()	:
	m_ppMaze(NULL)
{
}

CMapManager::~CMapManager()
{
	for (int i = 0; i < m_iMapCount; ++i)
	{
		delete[]	m_ppMapList[i];
		delete m_ppMaze[i];
	}
	
	delete[]	m_ppMaze;
	delete[]	m_ppMapList;
}

bool CMapManager::Init()
{
	// �� ����� �о�´�.
	FILE*	pFile = NULL;

	fopen_s(&pFile, "MapList.txt", "rt");

	if (pFile)
	{
		// ��� ���� �о�´�.
		char	cMapCount;
		//fread �Լ��� ���� �����ŭ ����Ŀ���� �̵���Ų��.
		fread(&cMapCount, 1, 1, pFile);

		// ���ڷ� �� ���ڸ� �Ϲ� ���ڷ� ��ȯ���ش�.
		m_iMapCount = atoi(&cMapCount);

		// ���� ���ڸ� �д´�.
		fread(&cMapCount, 1, 1, pFile);

		// ���� ����ŭ ���ڿ��� �����迭�� �Ҵ��Ѵ�.
		m_ppMapList = new char*[m_iMapCount];

		// ���� ��� ����ŭ �ݺ��ϸ� ���� ����� �о�´�.
		for (int i = 0; i < m_iMapCount; ++i)
		{
			m_ppMapList[i] = new char[256];
			memset(m_ppMapList[i], 0, 256);

			int		iNameCount = 0;

			// ���ڸ� �ϳ��� �о \n�� ���ö� ���� �����̴�.
			while (true)
			{
				fread(&cMapCount, 1, 1, pFile);

				if (cMapCount == '\n' || feof(pFile) != 0)
					break;

				m_ppMapList[i][iNameCount] = cMapCount;
				++iNameCount;
			}
		}

		fclose(pFile);
	}

	// ���� ��� ����ŭ ���� �ε��Ѵ�.
	m_ppMaze = new CMaze*[m_iMapCount];

	for (int i = 0; i < m_iMapCount; ++i)
	{
		m_ppMaze[i] = new CMaze;
		m_ppMaze[i]->Load(m_ppMapList[i]);
	}

	return true;
}

void CMapManager::Run(class CPlayer* pPlayer)
{
	while (true)
	{
		system("cls");
		for (int i = 0; i < m_iMapCount; ++i)
		{
			cout << i + 1 << ". " << m_ppMapList[i] << endl;
		}

		cout << m_iMapCount + 1 << ". ����" << endl;
		cout << "�̷θ� �����ϼ��� : ";
		int	iInput = InputInt();

		if (iInput < 1 || iInput > m_iMapCount + 1)
			continue;

		else if (iInput == m_iMapCount + 1)
			break;

		int	iSelectMap = iInput - 1;

		// InGame�� �����ϱ� ���� �÷��̾��� ��ġ�� �̷��� ���� ��ġ�� �����Ѵ�. 
		pPlayer->SetPos(m_ppMaze[iSelectMap]->GetStartPos());

		while (true)
		{
			system("cls");
			// ���� ����Ѵ�.
			m_ppMaze[iSelectMap]->Output(pPlayer);

			if (m_ppMaze[iSelectMap]->Finish(pPlayer->GetPos()))
			{
				cout << "�̷�Ż��!!" << endl;
				system("pause");
				break;
			}

			char	cInput = 'l';
			
			while (cInput != 'w' && cInput != 's' && cInput != 'a' && cInput != 'd' &&
				cInput != 'q')
			{
				cInput = pPlayer->Input();
			}

			if (cInput == 'q' || cInput == 'Q')
				break;

			switch (cInput)
			{
			case 'w':
			case 'W':
				if (pPlayer->GetPos()[0] > 0)
				{
					int	iPos[2];
					iPos[0] = pPlayer->GetPos()[0] - 1;
					iPos[1] = pPlayer->GetPos()[1];
					char	cBlock = m_ppMaze[iSelectMap]->GetTileInfo(iPos);

					// ���� �ִ� ���� ��쿡�� �����δ�.
					if (cBlock != '0')
					{
						pPlayer->Up();
					}
				}
				break;
			case 's':
			case 'S':
				if (pPlayer->GetPos()[0] < 19)
				{
					int	iPos[2];
					iPos[0] = pPlayer->GetPos()[0] + 1;
					iPos[1] = pPlayer->GetPos()[1];
					char	cBlock = m_ppMaze[iSelectMap]->GetTileInfo(iPos);

					// ���� �ִ� ���� ��쿡�� �����δ�.
					if (cBlock != '0')
					{
						pPlayer->Down();
					}
				}
				break;
			case 'a':
			case 'A':
				if (pPlayer->GetPos()[1] > 0)
				{
					int	iPos[2];
					iPos[0] = pPlayer->GetPos()[0];
					iPos[1] = pPlayer->GetPos()[1] - 1;
					char	cBlock = m_ppMaze[iSelectMap]->GetTileInfo(iPos);

					// ���� �ִ� ���� ��쿡�� �����δ�.
					if (cBlock != '0')
					{
						pPlayer->Left();
					}
				}
				break;
			case 'd':
			case 'D':
				if (pPlayer->GetPos()[1] < 19)
				{
					int	iPos[2];
					iPos[0] = pPlayer->GetPos()[0];
					iPos[1] = pPlayer->GetPos()[1] + 1;
					char	cBlock = m_ppMaze[iSelectMap]->GetTileInfo(iPos);

					// ���� �ִ� ���� ��쿡�� �����δ�.
					if (cBlock != '0')
					{
						pPlayer->Right();
					}
				}
				break;
			}

			Sleep(33);
		}
	}
}

void CMapManager::Output()
{
}
