
#include <iostream>
#include <time.h>

using namespace std;

/*
열거체 : 숫자에 이름을 부여해주는 기능이다.
enum 열거체명 {}; 의 형태로 구성된다.
*/
enum SRP
{
	// 아래처럼 열거해놓으면 처음 0, 1, 2 이렇게 차례대로 값이 증가해서
	// 부여된다.
	SRP_S = 1,
	SRP_R,
	SRP_P,
	SRP_EXIT
};

int main()
{

	srand(time(0));
	/*
	   *
	  ***
	 *****
	*******
	*/
	/*for (int i = 0; i < 4; ++i)
	{
		// 공백을 출력한다.
		for (int j = 0; j < 3 - i; ++j)
		{
			cout << " ";
		}

		// *을 출력한다.
		for (int j = 0; j < i * 2 + 1; ++j)
		{
			cout << "*";
		}

		cout << endl;
	}*/

	/*
	   *
	  ***
	 *****
	*******
	 *****
	  ***
	   *
	*/
	/*int	iPivot = 0;
	for (int i = 0; i < 7; ++i)
	{
		if (i <= 3)
			iPivot = i;

		else
			iPivot = 6 - i;

		// 공백을 출력한다.
		for (int j = 0; j < 3 - iPivot; ++j)
		{
			cout << " ";
		}

		// *을 출력한다.
		for (int j = 0; j < iPivot * 2 + 1; ++j)
		{
			cout << "*";
		}

		cout << endl;
	}*/

	// 가위바위보 게임
	while (true)
	{
		system("cls");
		cout << "1. 가위" << endl;
		cout << "2. 바위" << endl;
		cout << "3. 보" << endl;
		cout << "4. 종료" << endl;
		cout << "Player Turn : ";
		int	iPlayer;
		cin >> iPlayer;

		if (iPlayer == SRP_EXIT)
			break;

		// continue : 반복문의 시작점으로 다시 올라가게 해준다.
		else if (iPlayer < SRP_S || iPlayer > SRP_EXIT)
			continue;

		// AI가 선택을 한다.
		int	iAI = rand() % 3 + 1;

		// switch문도 분기문이다. if문과 다르게 조건을 비교하는 것이 아니라
		// () 안에 들어간것의 값이 무엇인지를 체크한다.
		// 값들은 case문으로 열거해놓고 사용한다.
		cout << "Player : ";
		switch (iPlayer)
		{
		case SRP_S:
			cout << "가위\t";
			break;
		case SRP_R:
			cout << "바위\t";
			break;
		case SRP_P:
			cout << "보\t";
			break;
		}

		cout << "AI : ";
		switch (iAI)
		{
		case SRP_S:
			cout << "가위" << endl;
			break;
		case SRP_R:
			cout << "바위" << endl;
			break;
		case SRP_P:
			cout << "보" << endl;
			break;
		}

		int	iResult = iPlayer - iAI;

		if (iResult == 1 || iResult == -2)
			cout << "Player Win" << endl;

		else if (iResult == 0)
			cout << "무승부" << endl;

		else
			cout << "AI Win" << endl;

		system("pause");
	}

	return 0;
}