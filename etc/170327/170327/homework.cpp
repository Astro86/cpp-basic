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
		cout << "====================학생관리프로그램====================" << endl;
		cout << "1.학생추가\t2.학생삭제\t3.학생탐색\t4.모두출력\t5.종료" << endl;
		cout << "실행하려는 작업을 입력하세요. : ";
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
				cout << "더이상 입력할 수 없습니다." << endl;
				break;
			}
			cout << "==========학생추가==========" << endl;
			cin.ignore(1024, '\n');

			cout << "이름 : ";
			cin.getline(student[iCount].cName, NAME_SPACE - 1);

			cout << "국어 : ";
			cin >> student[iCount].iKor;
			cout << "영어 : ";
			cin >> student[iCount].iEng;
			cout << "수학 : ";
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

			cout << "학생추가 완료" << endl;

			system("pause");
		}
			break;

		case MMENU_DELETE:
		{
			cout << "===== ===== 학생제거 ===== =====" << endl;
			char cName[NAME_SPACE] = {};
			cin.ignore(1024, '\n');
			cout << "제거할 학생의 이름을 입력하시오" << endl;
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
				cout << "일치하는 대상이 없습니다" << endl;
			}
			else 
				cout << "삭제 완료" << endl;
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