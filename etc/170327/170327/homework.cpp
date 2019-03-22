#include <iostream>

using namespace std;

#define NAME_SPACE 32

enum MMENU {
	MMENU_ADD = 1,
	MMENU_DELETE,
	MMENU_SEARCH,
	MMENU_PRINTALL,
	MMENU_QUIT
};
struct _tagstudent {
	char cName[NAME_SPACE] = {};
	int iKor;
	int iMath;
	int iEng;
	int total;
	float fAvg;
	char cGrade;
};

int main() {
	_tagstudent student[10] = {};
	int iCount = 0;

	while (true) {
		system("cls");
		cout << "====================�л��������α׷�====================" << endl;
		cout << "1.�л��߰�\t2.�л�����\t3.�л�Ž��\t4.������\t5.����" << endl;
		cout << "�����Ϸ��� �۾��� �Է��ϼ���. : ";
		bool bTrue = true;
		bool bFalse = false;
		cout << bTrue << endl;
		cout << bFalse << endl;
		int iMnum = 0;
		cin >> iMnum;

		if (iMnum == 5) {
			break;
		}
		if (iMnum > 5 || iMnum < 1) {
			continue;
		}

		switch (iMnum) {
		case MMENU_ADD:
		{
			if (iCount >= 10) {
				cout << "���̻� �Է��� �� �����ϴ�." << endl;
				break;
			}
			cout << "==========�л��߰�==========" << endl;
			cin.ignore(1024, '\n');

			cout << "�̸� : ";
			cin.getline(student[iCount].cName, NAME_SPACE - 1);

			cout << "���� : ";
			cin >> student[iCount].iKor;
			cout << "���� : ";
			cin >> student[iCount].iEng;
			cout << "���� : ";
			cin >> student[iCount].iMath;

			student[iCount].total = student[iCount].iKor + student[iCount].iEng + student[iCount].iMath;
			student[iCount].fAvg = student[iCount].total / 3.f;

			++iCount;

			if (student[iCount].fAvg >= 90) {
				student[iCount].cGrade = 'A';
			}
			else if (student[iCount].fAvg >= 80) {
				student[iCount].cGrade = 'B';
			}
			else if (student[iCount].fAvg >= 70) {
				student[iCount].cGrade = 'C';
			}
			else if (student[iCount].fAvg >= 60) {
				student[iCount].cGrade = 'D';
			}
			else {
				student[iCount].cGrade = 'F';
			}

			cout << "�л��߰� �Ϸ�" << endl;

			system("pause");
		}
			break;

		case MMENU_DELETE:
		{
			cout << "===== ===== �л����� ===== =====" << endl;
			char cName[NAME_SPACE] = {};
			cin.ignore(1024, '\n');
			cout << "������ �л��� �̸��� �Է��Ͻÿ�" << endl;
			cin.getline(cName, NAME_SPACE - 1);

			bool bFind = false;

			for (int i = 0; i < iCount; ++i) {
				if (strcmp(cName, student[i].cName) == 0) {
					bFind = true;
					for (int j = i; j < iCount - 1; ++j) {
						student[j] = student[j + 1];
					}
					--iCount;
					break;
				}
			}

			if (!bFind) {
				cout << "��ġ�ϴ� ����� �����ϴ�" << endl;
			}
			else 
				cout << "���� �Ϸ�" << endl;
		}
			break;

		case MMENU_SEARCH:

			break;

		case MMENU_PRINTALL:

			break;

		}

	}
	return 0;
}