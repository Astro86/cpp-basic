
#include "Core.h"

void SetNumber(int* pNumber)
{
	for (int i = 0; i < 24; ++i)
	{
		pNumber[i] = i + 1;
	}

	pNumber[24] = INT_MAX;
}

void Shuffle(int* pNumber)
{
	int	iTemp, idx1, idx2;
	for (int i = 0; i < 100; ++i)
	{
		idx1 = rand() % 24;
		idx2 = rand() % 24;

		iTemp = pNumber[idx1];
		pNumber[idx1] = pNumber[idx2];
		pNumber[idx2] = iTemp;
	}
}

bool Init(int * pNumber)
{
	srand(time(0));

	SetNumber(pNumber);

	Shuffle(pNumber);

	return true;
}

void Output(int* pNumber)
{
	system("cls");
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (pNumber[i * 5 + j] == INT_MAX)
				cout << "*\t";

			else
				cout << pNumber[i * 5 + j] << "\t";
		}

		cout << endl;
	}
}

char Input()
{
	cout << "w(¡è) s(¡é) a(¡ç) d(¡æ) q(Á¾·á) : ";
	return _getch();
}

void Move(int* pNumber, int* pStarIndex,
	char cDir)
{
	int	iStarIndex = *pStarIndex;
	int	iTemp = 0;
	switch (cDir)
	{
	case 'w':
	case 'W':
		if (iStarIndex > 4)
		{
			iTemp = pNumber[iStarIndex];
			pNumber[iStarIndex] = pNumber[iStarIndex - 5];
			pNumber[iStarIndex - 5] = iTemp;
			iStarIndex -= 5;
		}
		break;
	case 's':
	case 'S':
		if (iStarIndex < 20)
		{
			iTemp = pNumber[iStarIndex];
			pNumber[iStarIndex] = pNumber[iStarIndex + 5];
			pNumber[iStarIndex + 5] = iTemp;
			iStarIndex += 5;
		}
		break;
	case 'a':
	case 'A':
		if (iStarIndex % 5 != 0)
		{
			iTemp = pNumber[iStarIndex];
			pNumber[iStarIndex] = pNumber[iStarIndex - 1];
			pNumber[iStarIndex - 1] = iTemp;
			iStarIndex -= 1;
		}
		break;
	case 'd':
	case 'D':
		if (iStarIndex % 5 != 4)
		{
			iTemp = pNumber[iStarIndex];
			pNumber[iStarIndex] = pNumber[iStarIndex + 1];
			pNumber[iStarIndex + 1] = iTemp;
			iStarIndex += 1;
		}
		break;
	}

	*pStarIndex = iStarIndex;
}

void Run(int* pNumber)
{
	int		iStarIndex = 24;
	while (true)
	{
		Output(pNumber);
		char	cInput = Input();

		if (cInput == 'q' || cInput == 'Q')
		{
			cout << endl;
			return;
		}

		Move(pNumber, &iStarIndex, cInput);
	}
}