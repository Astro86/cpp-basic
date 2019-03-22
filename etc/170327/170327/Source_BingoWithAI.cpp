
#include <iostream>
#include <time.h>
#include <conio.h>

using namespace std;

int main()
{
	srand(time(0));

	int		iNumber[25] = {};
	int		iAINumber[25] = {};

	// 배열에 1 ~ 25까지 숫자를 넣어준다.
	for (int i = 0; i < 25; ++i)
	{
		iNumber[i] = i + 1;
		iAINumber[i] = i + 1;
	}

	// 1 ~ 25 사이의 숫자를 골고루 섞어준다.(Shuffle)
	int	iTemp, idx1, idx2;
	for (int i = 0; i < 100; ++i)
	{
		// (Player)랜덤한 인덱스 1, 2번을 구해준다.
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		// 위에서 구한 2개의 인덱스에 들어있는 값을 서로 바꿔준다.(swap)
		iTemp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = iTemp;

		// (AI)랜덤한 인덱스 1, 2번을 구해준다.
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		// 위에서 구한 2개의 인덱스에 들어있는 값을 서로 바꿔준다.(swap)
		iTemp = iAINumber[idx1];
		iAINumber[idx1] = iAINumber[idx2];
		iAINumber[idx2] = iTemp;
	}

	// 선택 안된 숫자 목록을 저장하기 위한 배열을 만든다.
	int	iNoneSelect[25] = {};
	int	iNoneSelectCount = 0;

	int	iBingo = 0, iAIBingo = 0;

	while (true)
	{
		system("cls");

		// 숫자판을 5 x 5로 출력한다.
		cout << "================ Player ================" << endl;
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (iNumber[i * 5 + j] == INT_MAX)
					cout << "*\t";
				else
					cout << iNumber[i * 5 + j] << "\t";
			}

			cout << endl;
		}

		cout << "Bingo : " << iBingo << endl << endl;

		cout << "================ AI ================" << endl;
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (iAINumber[i * 5 + j] == INT_MAX)
					cout << "*\t";
				else
					cout << iAINumber[i * 5 + j] << "\t";
			}

			cout << endl;
		}

		cout << "Bingo : " << iAIBingo << endl << endl;

		if (iBingo >= 5)
		{
			cout << "Bingo!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
			break;
		}

		else if (iAIBingo >= 5)
		{
			cout << "AI Bingo!!!!!!!!!!!!!!!" << endl;
			break;
		}

		cout << "숫자를 선택하세요(0 : 종료) : ";
		int	iInput;
		cin >> iInput;

		if (iInput == 0)
			break;

		else if (iInput < 0 || iInput > 25)
			continue;

		// 중복된 숫자 입력 방지
		bool	bInputCheck = true;

		// 숫자 목록중 선택한 숫자가 있는지를 체크한다.
		for (int i = 0; i < 25; ++i)
		{
			if (iNumber[i] == iInput)
			{
				// UINT_MAX : int로 표현할 수 있는 최대값이다.
				iNumber[i] = INT_MAX;
				bInputCheck = false;
				break;
			}
		}

		// 중복된 숫자를 입력했을 경우 다시 입력받는다.
		if (bInputCheck)
			continue;

		// AI의 숫자를 변경한다.
		for (int i = 0; i < 25; ++i)
		{
			if (iAINumber[i] == iInput)
			{
				iAINumber[i] = INT_MAX;
				break;
			}
		}

		// AI가 선택한다. 선택안된 숫자중 랜덤한 수를 선택해야 한다.
		// 선택안한 목록을 만들어준다.
		iNoneSelectCount = 0;
		for (int i = 0; i < 25; ++i)
		{
			if (iAINumber[i] != INT_MAX)
			{
				iNoneSelect[iNoneSelectCount] = iAINumber[i];
				++iNoneSelectCount;
			}
		}

		int	iRand = rand() % iNoneSelectCount;
		iInput = iNoneSelect[iRand];

		// AI가 선택한 숫자를 이용해서 플레이어와 AI의 숫자를 *로 만들어준다.
		for (int i = 0; i < 25; ++i)
		{
			if (iNumber[i] == iInput)
			{
				iNumber[i] = INT_MAX;
				break;
			}
		}

		for (int i = 0; i < 25; ++i)
		{
			if (iAINumber[i] == iInput)
			{
				iAINumber[i] = INT_MAX;
				break;
			}
		}

		// 빙고 줄수를 체크한다.
		iBingo = 0;
		iAIBingo = 0;

		int		iCheck1 = 0, iCheck2 = 0;
		int		iAICheck1 = 0, iAICheck2 = 0;
		// 가로, 세로 줄수를 체크한다.
		for (int i = 0; i < 5; ++i)
		{
			iCheck1 = iCheck2 = 0;
			iAICheck1 = iAICheck2 = 0;
			for (int j = 0; j < 5; ++j)
			{
				// 가로체크
				if (iNumber[i * 5 + j] == INT_MAX)
					++iCheck1;

				// 세로체크
				if (iNumber[j * 5 + i] == INT_MAX)
					++iCheck2;

				// AI Check
				if (iAINumber[i * 5 + j] == INT_MAX)
					++iAICheck1;

				if (iAINumber[j * 5 + i] == INT_MAX)
					++iAICheck2;
			}

			if (iCheck1 == 5)
				++iBingo;

			if (iCheck2 == 5)
				++iBingo;

			if (iAICheck1 == 5)
				++iAIBingo;

			if (iAICheck2 == 5)
				++iAIBingo;
		}

		iCheck1 = 0;
		iAICheck1 = 0;

		// 왼쪽 -> 오른쪽 대각선
		for (int i = 0; i < 25; i += 6)
		{
			if (iNumber[i] == INT_MAX)
				++iCheck1;

			if (iAINumber[i] == INT_MAX)
				++iAICheck1;
		}

		if (iCheck1 == 5)
			++iBingo;

		if (iAICheck1 == 5)
			++iAIBingo;

		// 오른쪽 -> 왼쪽 대각선
		iCheck1 = 0;
		iAICheck1 = 0;
		for (int i = 4; i < 21; i += 4)
		{
			if (iNumber[i] == INT_MAX)
				++iCheck1;

			if (iAINumber[i] == INT_MAX)
				++iAICheck1;
		}

		if (iCheck1 == 5)
			++iBingo;

		if (iAICheck1 == 5)
			++iAIBingo;
	}

	return 0;
}

