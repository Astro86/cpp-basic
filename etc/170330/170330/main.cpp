
#include <iostream>

using namespace std;

// Main Menu
enum MAIN_MENU
{
	MM_NONE,
	MM_INSERT,
	MM_DELETE,
	MM_SEARCH,
	MM_OUTPUT,
	MM_EXIT
};

#define		NAME_SIZE	32
#define		STUDENT_MAX	10

struct _tagStudent
{
	char	strName[NAME_SIZE];
	int		iKor;
	int		iEng;
	int		iMath;
	int		iTotal;
	float	fAvg;
};

int main()
{
	_tagStudent	tStudent[STUDENT_MAX] = {};
	int		iStudentCount = 0;

	while (true)
	{
		system("cls");

		cout << "1. 학생추가" << endl;
		cout << "2. 학생삭제" << endl;
		cout << "3. 학생탐색" << endl;
		cout << "4. 학생출력" << endl;
		cout << "5. 종료" << endl;
		cout << "메뉴를 선택하세요 : ";
		
		int	iMenu;
		cin >> iMenu;
		
		if (iMenu == MM_EXIT)
			break;

		switch (iMenu)
		{
		case MM_INSERT:
			if (iStudentCount == STUDENT_MAX)
			{
				cout << "더이상 추가할 수 없습니다." << endl;
				break;
			}

			system("cls");

			cout << "========================== 학생추가 ==========================" << endl;
			
			// 입력버퍼는 cin에서 입력받은 내용을 가지고 있는 버퍼이다.(저장공간)
			// 입력버퍼에 Enter키가 들어가있을 경우 문자 입력이 된걸로 인식될 수 있다.
			// 그렇기 때문에 버퍼를 \n이 있는곳까지 비워준다.
			cin.ignore(1024, '\n');

			cout << "이름 : ";
			// 문자열을 입력받을때 사용한다.
			cin.getline(tStudent[iStudentCount].strName, NAME_SIZE - 1);

			// 점수를 입력받는다.
			int	iKor, iEng, iMath;
			cout << "국어 : ";
			cin >> iKor;

			cout << "영어 : ";
			cin >> iEng;

			cout << "수학 : ";
			cin >> iMath;

			int		iTotal;

			iTotal = iKor + iEng + iMath;

			tStudent[iStudentCount].iKor = iKor;
			tStudent[iStudentCount].iEng = iEng;
			tStudent[iStudentCount].iMath = iMath;
			tStudent[iStudentCount].iTotal = iTotal;
			tStudent[iStudentCount].fAvg = iTotal / 3.f;

			++iStudentCount;

			cout << "학생추가 완료" << endl;
			break;
		
		case MM_DELETE:
		{
			system("cls");
			cout << "========================== 학생삭제 ==========================" << endl;

			// case 문 안에서 선언과 동시에 초기화를 하면 에러가 발생한다.
			// 하지만 이 구문들을 {}(코드블럭)으로 감싸주었기 때문에 상관이 없다.
			char	strName[NAME_SIZE] = {};
			
			cin.ignore(1024, '\n');
			cout << "삭제할 이름을 입력하세요 : ";
			cin.getline(strName, NAME_SIZE - 1);

			bool	bFind = false;

			// 반복돌면서 찾는다.
			for (int i = 0; i < iStudentCount; ++i)
			{
				if (strcmp(strName, tStudent[i].strName) == 0)
				{
					bFind = true;
					for (int j = i; j < iStudentCount - 1; ++j)
					{
						tStudent[j] = tStudent[j + 1];
					}

					--iStudentCount;

					break;
				}
			}

			if (!bFind)
				cout << "삭제할 대상이 없습니다." << endl;

			else
				cout << "삭제 완료" << endl;
		}
			break;
		case MM_SEARCH:
		{
			system("cls");
			cout << "========================== 학생탐색 ==========================" << endl;

			// case 문 안에서 선언과 동시에 초기화를 하면 에러가 발생한다.
			char	strName[NAME_SIZE] = {};

			cin.ignore(1024, '\n');
			cout << "탐색할 이름을 입력하세요 : ";
			cin.getline(strName, NAME_SIZE - 1);

			bool	bFind = false;

			// 반복돌면서 찾는다.
			for (int i = 0; i < iStudentCount; ++i)
			{
				if (strcmp(strName, tStudent[i].strName) == 0)
				{
					bFind = true;
					cout << "이름\t국어\t영어\t수학\t총점\t평균" << endl;

					cout << tStudent[i].strName << "\t" << tStudent[i].iKor << "\t" <<
						tStudent[i].iEng << "\t" << tStudent[i].iMath << "\t" <<
						tStudent[i].iTotal << "\t" << tStudent[i].fAvg << endl;
					break;
				}
			}

			if (!bFind)
				cout << "탐색할 대상이 없습니다." << endl;
		}
			break;
		case MM_OUTPUT:
			system("cls");
			cout << "========================== 학생출력 ==========================" << endl;

			cout << "이름\t국어\t영어\t수학\t총점\t평균" << endl;
			for (int i = 0; i < iStudentCount; ++i)
			{
				cout << tStudent[i].strName << "\t" << tStudent[i].iKor << "\t" <<
					tStudent[i].iEng << "\t" << tStudent[i].iMath << "\t" <<
					tStudent[i].iTotal << "\t" << tStudent[i].fAvg << endl;
			}
			break;
		}

		system("pause");
	}

	return 0;
}