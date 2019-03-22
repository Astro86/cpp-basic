
#include <iostream>
#include <time.h>

using namespace std;

// 숫자를 1 ~ 25 사이의 숫자로 지정하는 함수를 만들어준다.
void SetNumber(int* pNumber)
{
	for (int i = 0; i < 25; ++i)
	{
		pNumber[i] = i + 1;
	}
}

// 숫자를 섞어주는 함수이다.
void Shuffle(int* pNumber)
{
	int	iTemp, idx1, idx2;
	for (int i = 0; i < 100; ++i)
	{
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		iTemp = pNumber[idx1];
		pNumber[idx1] = pNumber[idx2];
		pNumber[idx2] = iTemp;
	}
}

void Output(int* pNumber, int iBingo)
{
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

	cout << "Bingo : " << iBingo << endl;
}

int InputNumber()
{
	int		iInput;
	cout << "숫자를 입력하세요(0 : 종료) : ";
	cin >> iInput;

	return iInput;
}

bool ChangeNumber(int* pNumber, int iInput)
{
	for (int i = 0; i < 25; ++i)
	{
		if (pNumber[i] == iInput)
		{
			pNumber[i] = INT_MAX;
			return false;
		}
	}

	return true;
}

int CheckVH(int* pNumber)
{
	int	iBingo = 0;
	for (int i = 0; i < 5; ++i)
	{
		int	iCheck1 = 0, iCheck2 = 0;
		for (int j = 0; j < 5; ++j)
		{
			// 가로체크
			if (pNumber[i * 5 + j] == INT_MAX)
				++iCheck1;

			// 세로체크
			if (pNumber[j * 5 + i] == INT_MAX)
				++iCheck2;
		}

		if (iCheck1 == 5)
			++iBingo;

		if (iCheck2 == 5)
			++iBingo;
	}

	return iBingo;
}

int CheckDigonal(int* pNumber)
{
	int	iCheck = 0;
	int	iBingo = 0;

	for (int i = 0; i < 25; i += 6)
	{
		if (pNumber[i] == INT_MAX)
			++iCheck;
	}

	if (iCheck == 5)
		++iBingo;

	iCheck = 0;
	for (int i = 4; i <= 20; i += 4)
	{
		if (pNumber[i] == INT_MAX)
			++iCheck;
	}

	if (iCheck == 5)
		++iBingo;

	return iBingo;
}

// 선택되지 않은 숫자목록을 만들어준다.
int CreateNoneSelectNumber(int* pNumber, int* pNoneSelect)
{
	int	iCount = 0;
	for (int i = 0; i < 25; ++i)
	{
		if (pNumber[i] != INT_MAX)
		{
			pNoneSelect[iCount] = pNumber[i];
			++iCount;
		}
	}

	return iCount;
}

enum WIN
{
	WIN_NONE,
	WIN_PLAYER,
	WIN_AI
};


WIN CheckWin(int iBingo, int iAIBingo)
{
	if (iBingo >= 5)
		return WIN_PLAYER;

	else if (iAIBingo >= 5)
		return WIN_AI;

	return WIN_NONE;
}



int main()
{
	srand(time(0));

	int		iNumber[25] = {};
	int		iAINumber[25] = {};

	// 숫자를 1 ~ 25로 넣어준다.
	SetNumber(iNumber);
	SetNumber(iAINumber);
			
	// 숫자를 섞어준다.
	Shuffle(iNumber);
	Shuffle(iAINumber);


	int	iBingo = 0, iAIBingo = 0;

	int	iNoneSelect[25] = {};

	while (true)
	{
		system("cls");
		// 번호판을 출력한다.
		cout << "===================== Player =====================" << endl;
		Output(iNumber, iBingo);
		cout << endl;

		cout << "===================== AI =====================" << endl;
		Output(iAINumber, iAIBingo);
		cout << endl;

		WIN win = CheckWin(iBingo, iAIBingo);

		if (win == WIN_PLAYER)
		{
			cout << "Player 승리" << endl;
			break;
		}

		else if (win == WIN_AI)
		{
			cout << "AI 승리" << endl;
			break;
		}

		// 입력을 받는다.
		int iInput = InputNumber();

		if (iInput == 0)
			break;

		else if (iInput < 0 || iInput > 25)
			continue;

		if (ChangeNumber(iNumber, iInput))
			continue;

		// AI 숫자도 *로 변경해준다.
		ChangeNumber(iAINumber, iInput);

		// AI Turn
		// 선택되지 않은 숫자목록을 만들어준다.
		int iNoneSelectCount = CreateNoneSelectNumber(iAINumber, iNoneSelect);

		// 선택되지 않은 목록에서 숫자를 선택한다.
		iInput = iNoneSelect[rand() % iNoneSelectCount];

		// 플레이어와 AI의 숫자를 *로 변경한다.
		ChangeNumber(iNumber, iInput);
		ChangeNumber(iAINumber, iInput);

		iBingo = 0;
		iBingo += CheckVH(iNumber);
		iBingo += CheckDigonal(iNumber);

		iAIBingo = 0;
		iAIBingo += CheckVH(iAINumber);
		iAIBingo += CheckDigonal(iAINumber);
	}

	return 0;
}
