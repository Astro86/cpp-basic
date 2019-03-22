#include <iostream>
#include <time.h>
#include <conio.h>

using namespace std;

int main()
{
	srand(time(0));

	int	iNumber[25] = {};

	for (int i = 0; i < 24; ++i)
	{
		iNumber[i] = i + 1;
	}

	iNumber[24] = INT_MAX;	//*에 특수한 숫자를 할당하여 혹시모를 오류를 피하기위해 INT_MAX 를 둠.

	// 현재 *이 들어있는 인덱스를 저장해둔다.
	int	iStarIndex = 24;

	// *을 제외한 나머지 1 ~ 24 사이의 숫자를 골고루 섞어준다.
	int	iTemp, idx1, idx2;
	for (int i = 0; i < 100; ++i)
	{
		idx1 = rand() % 24;
		idx2 = rand() % 24;

		iTemp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = iTemp;
	}

	while (true)
	{
		system("cls");
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

		bool	bWin = true;

		for (int i = 0; i < 24; ++i)
		{
			if (iNumber[i] != i + 1)
			{
				bWin = false;
				break;
			}
		}

		if (bWin)
		{
			cout << "모두 맞췄습니다." << endl;
			break;
		}

		cout << "w : ↑ s : ↓ a : ← d : → q : 종료 : ";
		// _getch() 함수는 문자를 입력받는 함수이다. 이 함수는 문자를 입력하자마자
		// 바로 동작된다. 문자를 입력하고 Enter키를 안쳐도 된다.
		char	cInput = _getch();

		if (cInput == 'q' || cInput == 'Q')
			break;

		switch (cInput)
		{
			// case구문은 break를 만나기 전까지 계속 아래로 내려간다.
			// 아래처럼 하면 w, W 둘다 같은 동작을 하게 된다.
		case 'w':
		case 'W':
			// 위로 이동을 할때 만약 *이 가장 윗줄에 있을 경우 더이상 이동할 수 없다.
			if (iStarIndex > 4)
			{
				iTemp = iNumber[iStarIndex];
				iNumber[iStarIndex] = iNumber[iStarIndex - 5];
				iNumber[iStarIndex - 5] = iTemp;

				// 별이 있는 위치를 변경한다.
				iStarIndex -= 5;
			}
			break;
		case 's':
		case 'S':
			// 아래로 이동을 할때 만약 *이 가장 아래에 있을 경우 더이상 이동할 수 없다.
			if (iStarIndex < 20)
			{
				iTemp = iNumber[iStarIndex];
				iNumber[iStarIndex] = iNumber[iStarIndex + 5];
				iNumber[iStarIndex + 5] = iTemp;

				iStarIndex += 5;
			}
			break;
		case 'a':
		case 'A':
			// 왼쪽으로 이동을 할때 만약 *이 가장 왼쪽에 있을 경우 더이상 이동할 수 없다.
			if (iStarIndex % 5 != 0)
			{
				iTemp = iNumber[iStarIndex];
				iNumber[iStarIndex] = iNumber[iStarIndex - 1];
				iNumber[iStarIndex - 1] = iTemp;

				--iStarIndex;
			}
			break;
		case 'd':
		case 'D':
			// 오른쪽으로 이동을 할때 만약 *이 가장 오른쪽에 있을 경우 이동할 수 없다.
			if (iStarIndex % 5 != 4)
			{
				iTemp = iNumber[iStarIndex];
				iNumber[iStarIndex] = iNumber[iStarIndex + 1];
				iNumber[iStarIndex + 1] = iTemp;

				++iStarIndex;
			}
			break;
		}
	}

	return 0;
}