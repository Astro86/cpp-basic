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
		cout << "����, ����, �� �� �ϳ��� ����ּ���" << endl;
		cout << "0. ����" << endl;
		cout << "1. ����" << endl;
		cout << "2. ��" << endl;
		cout << "3. ����" << endl;
		cin >> player;

		int	iAI = rand() % 3;

		if (player == 0) {
			if (iAI % 3 == 2) {
				cout << "player : ����, AI : ��" << endl;
				cout << "���� : player" << endl;
			}
			else if (iAI % 3 == 1) {
				cout << "player : ����, AI : ����" << endl;
				cout << "���� : AI" << endl;
			}
			else if (iAI % 3 == 0) {
				cout << "player : ����, AI : ����" << endl;
				cout << "���º�" << endl;
			}
		}
		else if (player == 1) {
			if (iAI % 3 == 2) {
				cout << "player : ����, AI : ��" << endl;
				cout << "���� : AI" << endl;
			}
			else if (iAI % 3 == 1) {
				cout << "player : ����, AI : ����" << endl;
				cout << "���º�" << endl;
			}
			else if (iAI % 3 == 0) {
				cout << "player : ����, AI : ����" << endl;
				cout << "player" << endl;
			}
		}
		else if (player == 2) {
			if (iAI % 3 == 2) {
				cout << "player : ��, AI : ��" << endl;
				cout << "���º�" << endl;
			}
			else if (iAI % 3 == 1) {
				cout << "player : ��, AI : ����" << endl;
				cout << "���� : player" << endl;
			}
			else if (iAI % 3 == 0) {
				cout << "player : ��, AI : ����" << endl;
				cout << "���� : AI" << endl;
			}

		}

		else if (player == 3)
			break;
	}
}

