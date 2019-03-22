#include <iostream>
#include <time.h>
using namespace std;


int main()
{
	srand(time(0));
	int player;
	int AI;

	while (true) {
		system("cls");
		cout << "가위, 바위, 보 중 하나를 골라주세요" << endl;
		cout << "0. 가위" << endl;
		cout << "1. 바위" << endl;
		cout << "2. 보" << endl;
		cout << "3. 종료" << endl;
		cin >> player;

		int	iAI = rand() % 3;

		if (player == 0) {
			if (iAI % 3 == 2) {
				cout << "player : 가위, AI : 보" << endl;
				cout << "승자 : player" << endl;
			}
			else if (iAI % 3 == 1) {
				cout << "player : 가위, AI : 바위" << endl;
				cout << "승자 : AI" << endl;
			}
			else if (iAI % 3 == 0) {
				cout << "player : 가위, AI : 가위" << endl;
				cout << "무승부" << endl;
			}
		}
		else if (player == 1) {
			if (iAI % 3 == 2) {
				cout << "player : 바위, AI : 보" << endl;
				cout << "승자 : AI" << endl;
			}
			else if (iAI % 3 == 1) {
				cout << "player : 바위, AI : 바위" << endl;
				cout << "무승부" << endl;
			}
			else if (iAI % 3 == 0) {
				cout << "player : 바위, AI : 가위" << endl;
				cout << "player" << endl;
			}
		}
		else if (player == 2) {
			if (iAI % 3 == 2) {
				cout << "player : 보, AI : 보" << endl;
				cout << "무승부" << endl;
			}
			else if (iAI % 3 == 1) {
				cout << "player : 보, AI : 바위" << endl;
				cout << "승자 : player" << endl;
			}
			else if (iAI % 3 == 0) {
				cout << "player : 보, AI : 가위" << endl;
				cout << "승자 : AI" << endl;
			}

		}

		else if (player == 3)
			break;
	}
}

