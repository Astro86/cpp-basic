
#include <iostream>
#include <time.h>

using namespace std;

int main()
{
	srand(time(0));
	/*
	배열 : 연속된 여러 변수들을 하나의 이름으로 사용할 수 있도록 해주는 기능이다.
	모든 타입의 변수들은 배열을 만들 수 있다
	형태 : 변수타입 배열명[개수]; 의 형태로 선언해서 사용할 수 있다.
	배열의 특정 요소에 접근하기 위해서는 인덱스 개념이 쓰인다.
	인덱스는 0번부터 시작해서 배열개수 - 1 까지가 존재한다.
	*/
	// 아래처럼 10개를 모두 넣어주면 차례대로 0번부터 9번까지 1 ~ 10의 값이
	// 들어가게 된다.
	//int	iArray[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	// 아래처럼 5개만 넣으면 0, 1, 2, 3, 4 번 인덱스에 각각 지정한
	// 값이
	// 들어가고 나머지는 0으로 초기화된다.
	//int iArray[10] = { 1, 2, 3, 4, 5 };

	// 아무것도 넣어주지 않으면 모두 0으로 초기화한다.
	/*int	iArray[10] = {};

	iArray[1] = 30;

	for (int i = 0; i < 10; ++i)
	{
		iArray[i] = i + 1;
	}

	for (int i = 0; i < 10; ++i)
	{
		cout << iArray[i] << endl;
	}*/

	// Lotto Program
	int		iLotto[45];
	
	for (int i = 0; i < 45; ++i)
	{
		iLotto[i] = i + 1;
	}

	int	iLottoGame = 0;

	cout << "게임수를 입력하세요 : ";
	cin >> iLottoGame;

	// 당첨번호를 미리 만들어둔다.
	int	iLottoNumber[7];

	int	iTemp, idx1, idx2;
	for (int j = 0; j < 100; ++j)
	{
		idx1 = rand() % 45;
		idx2 = rand() % 45;

		iTemp = iLotto[idx1];
		iLotto[idx1] = iLotto[idx2];
		iLotto[idx2] = iTemp;
	}
		
	for (int i = 0; i < 5; ++i)
	{
		for (int j = i + 1; j < 6; ++j)
		{
			if (iLotto[i] > iLotto[j])
			{
				iTemp = iLotto[i];
				iLotto[i] = iLotto[j];
				iLotto[j] = iTemp;
			}
		}
	}

	for (int i = 0; i < 7; ++i)
	{
		iLottoNumber[i] = iLotto[i];
	}

	cout << "당첨번호 : ";
	for (int i = 0; i < 6; ++i)
	{
		cout << iLottoNumber[i] << "\t";
	}
	cout << "/\t" << iLottoNumber[6] << endl;

	for (int i = 0; i < iLottoGame; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			idx1 = rand() % 45;
			idx2 = rand() % 45;

			iTemp = iLotto[idx1];
			iLotto[idx1] = iLotto[idx2];
			iLotto[idx2] = iTemp;
		}

		cout << i + 1 << " :\t";

		// 6개의 당첨번호를 오름차순으로 정렬한다.(Bubble Sort)
		for (int j = 0; j < 5; ++j)
		{
			for (int k = j + 1; k < 6; ++k)
			{
				if (iLotto[j] > iLotto[k])
				{
					iTemp = iLotto[j];
					iLotto[j] = iLotto[k];
					iLotto[k] = iTemp;
				}
			}
		}

		for (int j = 0; j < 6; ++j)
		{
			cout << iLotto[j] << "\t";
		}

		cout << endl;

		// 당첨번호와 비교하여 등수를 정한다.
		int	iPairCount = 0;

		for (int j = 0; j < 6; ++j)
		{
			for (int k = 0; k < 6; ++k)
			{
				if (iLotto[j] == iLottoNumber[k])
				{
					++iPairCount;
					break;
				}
			}
		}

		switch (iPairCount)
		{
		case 6:
			cout << "1등" << endl;
			break;
		case 5:
			bool	bBonus;
			bBonus = false;
			for(int i = 0; i < 6; ++i)
			{
				if(iLotto[i] == iLottoNumber[6])
				{
					cout << "2등" << endl;
					bBonus = true;
					break;
				}
			}

			if(!bBonus)
				cout << "3등" << endl;

			break;
		case 4:
			cout << "4등" << endl;
			break;
		case 3:
			cout << "5등" << endl;
			break;
		default:	// 그 외의 값일 경우
			cout << "꽝" << endl;
			break;
		}
	}

	int		iNumber[25];

	// 배열에 1 ~ 25까지 숫자를 넣어준다.
	for (int i = 0; i < 25; ++i)
	{
		iNumber[i] = i + 1;
	}

	// 1 ~ 25 사이의 숫자를 골고루 섞어준다.(Shuffle)
	for (int i = 0; i < 100; ++i)
	{
		// 랜덤한 인덱스 1, 2번을 구해준다.
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		// 위에서 구한 2개의 인덱스에 들어있는 값을 서로 바꿔준다.(swap)
		iTemp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = iTemp;
	}
	
	int	iBingo = 0;

	while (true)
	{
		system("cls");

		int iNumber[25] = {};

		// 숫자판을 5 x 5로 출력한다.
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

		cout << "Bingo : " << iBingo << endl;

		if (iBingo >= 5)
		{
			cout << "Bingo!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
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

		// 빙고 줄수를 체크한다.
		iBingo = 0;

		int		iCheck1 = 0, iCheck2 = 0;
		// 가로, 세로 줄수를 체크한다.
		for (int i = 0; i < 5; ++i)
		{
			iCheck1 = iCheck2 = 0;
			for (int j = 0; j < 5; ++j)
			{
				// 가로체크
				if (iNumber[i * 5 + j] == INT_MAX)
					++iCheck1;

				// 세로체크
				if (iNumber[j * 5 + i] == INT_MAX)
					++iCheck2;
			}

			if (iCheck1 == 5)
				++iBingo;

			if (iCheck2 == 5)
				++iBingo;
		}

		iCheck1 = 0;

		// 왼쪽 -> 오른쪽 대각선
		for (int i = 0; i < 25; i += 6)
		{
			if (iNumber[i] == INT_MAX)
				++iCheck1;
		}

		if (iCheck1 == 5)
			++iBingo;

		// 오른쪽 -> 왼쪽 대각선
		iCheck1 = 0;
		for (int i = 4; i < 21; i += 4)
		{
			if (iNumber[i] == INT_MAX)
				++iCheck1;
		}

		if (iCheck1 == 5)
			++iBingo;
	}

	return 0;
}