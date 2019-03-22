#include "Maze.h"
#include "Player.h"

CMaze::CMaze()
{
}

CMaze::~CMaze()
{
}

int * CMaze::GetStartPos()
{
	return m_iStartPos;
}

int * CMaze::GetEndPos()
{
	return m_iEndPos;
}

char CMaze::GetTileInfo(int * pPos)
{
	return m_Maze[pPos[0]][pPos[1]];
}

bool CMaze::Finish(int * pPos)
{
	if (pPos[0] == m_iEndPos[0] && pPos[1] == m_iEndPos[1])
		return true;

	return false;
}

bool CMaze::Load(char * pFileName)
{
	FILE*	pFile = NULL;

	fopen_s(&pFile, pFileName, "rt");

	if (pFile)
	{
		for (int i = 0; i < 20; ++i)
		{
			fread(m_Maze[i], 1, 20, pFile);

			if (feof(pFile) != 0)
				break;
			char	cSpace;
			fread(&cSpace, 1, 1, pFile);
		}

		for (int i = 0; i < 20; ++i)
		{
			for (int j = 0; j < 20; ++j)
			{
				if (m_Maze[i][j] == '2')
				{
					m_iStartPos[0] = i;
					m_iStartPos[1] = j;
				}

				else if (m_Maze[i][j] == '3')
				{
					m_iEndPos[0] = i;
					m_iEndPos[1] = j;
				}
			}
		}

		fclose(pFile);
	}

	return true;
}

void CMaze::Output(class CPlayer* pPlayer)
{
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			if (pPlayer->GetPos()[0] == i &&
				pPlayer->GetPos()[1] == j)
			{
				cout << "¡Ý";
			}

			else if (m_Maze[i][j] == '0')
			{
				cout << "¡á";
			}

			else if (m_Maze[i][j] == '1')
			{
				cout << "  ";
			}

			else if (m_Maze[i][j] == '2')
			{
				cout << "¡Ú";
			}

			else
			{
				cout << "£À";
			}
		}

		cout << endl;
	}
}
