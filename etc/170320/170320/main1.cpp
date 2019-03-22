
#include <iostream>
// time.h는 시간에 관련된 기능을 담고있는 헤더파일이다.
#include <time.h>

using namespace std;

int main()
{
	// for문 : 반복문의 한 종류이다. 반복문이란 원하는 작업을 일정 회수만큼
	// 혹은 무한으로 반복하게 만들어주는 기능이다.
	// 형태 : for(초기값; 조건식; 증감값) {} 의 형태로 구성된다.
	// 초기값은 처음 딱 1번만 초기화된다. 그 후에 조건식을 체크하고 true일경우
	// 코드블럭 안의 코드가 동작된다. 그 후에 증감을 하고 조건을 검사하고 코드실행
	// 증감, 조건체크, 코드실행을 해주다가 조건이 false일 경우 for문이 종료된다.
	for (int i = 0; i < 10; ++i)
	{
		cout << i << endl;
	}

	// 구구단 2단을 출력하는 for문을 만들어보자.
	for (int i = 1; i < 10; ++i) {
		cout << "2 * " << i << " = " << 2 * i << endl;
	}

	// 이중for문 : for문 안에 for문이 들어가는 형태이다.
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			cout << "i : " << i << " j : " << j << endl;
		}
	}

	// 구구단을 2단부터 9단까지 출력하시오.
	// 출력을 2단	3단		4단
	//       5단		6단		7단
	//		  8단	9단		10단 으로 출력되게 변경한자.

	/*for (int i = 2; i < 10; i += 3) {
		cout << i << "단\t\t" << i + 1 << "단\t\t" << i + 2 << "단" << endl;
		for (int j = 1; j < 10; ++j) {
			cout << i << " * " << j << " = " << i*j << "\t";
			cout << i + 1 << " * " << j << " = " << (i + 1) * j << "\t";
			cout << i + 2 << " * " << j << " = " << (i + 2) * j << endl;
		}

		cout << endl;
	}
	*/

	for (int i = 2; i < 10; i += 3) {
		cout << i << "단\t\t" << i + 1 << "단\t\t" << i + 2 << "단" << endl;
		for (int j = 1; j < 10; ++j) {
			cout << i << " * " << j << " = " << i * j << "\t";
			cout << i + 1 << " * " << j << " = " << (i + 1)*j << "\t";
			cout << i + 2 << " * " << j << " = " << (i + 2)*j << endl;
		}
	}

	/*
	*
	**
	***
	****
	*****
	*/
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < i + 1; j++) {
			cout << "*";
		}
		cout << endl;
	}

	/*
	*****
	****
	***
	**
	*
	*/
	for (int i = 5; i > 0; --i)
	{
		for (int j = 0; j < i; ++j)
		{
			cout << "*";
		}
		cout << endl;
	}



	// 난수를 사용하기 위해서는 난수테이블을 만들어놓은 후에 해당 테이블에서
	// 임의의 난수를 얻어오는 방식이다. 컴퓨터에서 실시간으로 계속 변하는 것은
	// 시간이므로 시간에 따라서 난수가 발생하도록 해준다.
	// srand 함수는 난수테이블을 만들어준다. time(0) 함수를 이용해서 타임
	// 을 넣어주고 해당 시간에 맞는 난수테이블을 만들어주게 된다.
	srand(time(0));

	// rand() 함수를 이용해서 난수테이블에서 난수를 얻어온다.
	// 100 ~ 200 사이의 난수를 얻어오자.
	int	iRand = rand() % 101 + 100;
	cout << iRand << endl;

	// 강화게임.
	int		iLevel = 0;
	while (true)
	{
		// cls : clear
		system("cls");
		cout << "1. 강화" << endl;
		cout << "2. 종료" << endl;
		cout << "강화 : " << iLevel << endl;
		cout << "메뉴를 선택하세요 : ";
		int		iInput;
		cin >> iInput;

		if (iInput == 2)
			break;

		else if (iInput == 1)
		{
			// 레벨이 0 ~ 3 사이일 경우 100% 성공, 레벨이 4 ~ 6 사이일 경우 50% 성공,
			// 레벨이 7 ~ 9 사이일 경우 20% 성공, 레벨이 10 ~ 15 사이일 경우 5% 성공
			// 그보다 높다면 1% 성공
			// 강화 실패시 레벨이 1 감소된다.
			float fPer = 0;
			fPer = rand() % 9901 / 100.f;
			if (iLevel >= 0 && iLevel <= 3)
				iLevel = iLevel + 1;

			else if (iLevel >= 4 && iLevel <= 6)
			{
				if (fPer >= 50) {
					++iLevel;
				}
				else {
					--iLevel;
				}
			}

			else if (iLevel >= 7 && iLevel <= 9)
			{
				if (fPer < 20) {
					++iLevel;
				}
				else {
					--iLevel;
				}
			}

			else if (iLevel >= 10 && iLevel <= 15)
			{
				if (fPer < 5) {
					++iLevel;
				}
				else {
					--iLevel;
				}
			}

			else if (iLevel > 15)
			{
				if (fPer < 0.55f) {
					++iLevel;
				}
				else {
					--iLevel;
				}
			}

			cout << "Percent : " << fPer << endl;
			// pause : 일시정지 시켜준다.
			system("pause");
		}
	}


	return 0;
}