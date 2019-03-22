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
	// 맵 목록을 읽어온다.
	FILE*	pFile = NULL;

	fopen_s(&pFile, "MapList.txt", "rt");

	if (pFile)
	{
		// 목록 수를 읽어온다.
		char	cMapCount;
		//fread 함수는 읽은 사이즈만큼 파일커서를 이동시킨다.
		fread(&cMapCount, 1, 1, pFile);

		// 문자로 된 숫자를 일반 숫자로 변환해준다.
		m_iMapCount = atoi(&cMapCount);

		// 개행 문자를 읽는다.
		fread(&cMapCount, 1, 1, pFile);

		// 파일 수만큼 문자열을 동적배열로 할당한다.
		m_ppMapList = new char*[m_iMapCount];

		// 파일 목록 수만큼 반복하며 파일 목록을 읽어온다.
		for (int i = 0; i < m_iMapCount; ++i)
		{
			m_ppMapList[i] = new char[256];
			memset(m_ppMapList[i], 0, 256);

			int		iNameCount = 0;

			// 문자를 하나씩 읽어서 \n이 나올때 라인 종료이다.
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

	// 파일 목록 수만큼 맵을 로드한다.
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

		cout << m_iMapCount + 1 << ". 종료" << endl;
		cout << "미로를 선택하세요 : ";
		int	iInput = InputInt();

		if (iInput < 1 || iInput > m_iMapCount + 1)
			continue;

		else if (iInput == m_iMapCount + 1)
			break;

		int	iSelectMap = iInput - 1;

		// InGame을 시작하기 전에 플레이어의 위치를 미로의 시작 위치로 변경한다. 
		pPlayer->SetPos(m_ppMaze[iSelectMap]->GetStartPos());

		while (true)
		{
			system("cls");
			// 맵을 출력한다.
			m_ppMaze[iSelectMap]->Output(pPlayer);

			if (m_ppMaze[iSelectMap]->Finish(pPlayer->GetPos()))
			{
				cout << "미로탈출!!" << endl;
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

					// 갈수 있는 블럭일 경우에만 움직인다.
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

					// 갈수 있는 블럭일 경우에만 움직인다.
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

					// 갈수 있는 블럭일 경우에만 움직인다.
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

					// 갈수 있는 블럭일 경우에만 움직인다.
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
