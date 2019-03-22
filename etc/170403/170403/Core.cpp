
#include "Core.h"

int SelectMenu()
{
	system("cls");
	cout << "1. 학생추가" << endl;
	cout << "2. 학생삭제" << endl;
	cout << "3. 학생탐색" << endl;
	cout << "4. 학생출력" << endl;
	cout << "5. 종료" << endl;
	cout << "메뉴를 선택하세요 : ";
	int	iInput = InputInt();

	if (iInput == INT_MAX || iInput <= MENU_NONE || iInput > MENU_EXIT)
		return MENU_NONE;

	return iInput;
}

void OutputTitle(char* pTitle)
{
	cout << "=================== " << pTitle << " ===================" << endl;
}

void Insert(PSTUDENT pStudentArr, int* pStudentCount)
{
	system("cls");
	OutputTitle("학생추가");

	if (*pStudentCount == STUDENT_MAX)
	{
		cout << "더이상 추가할 수 없습니다." << endl;
		return;
	}

	int	iCount = *pStudentCount;

	// 이름을 입력받는다.
	cout << "이름을 입력하세요 : ";
	// 문자 입력 전에 숫자를 입력했으므로 입력일 비워준다.
	cin.ignore(1024, '\n');
	// 문자 입력에 실패했을 경우 return한다.
	if (!InputString(pStudentArr[iCount].strName, NAME_SIZE))
		return;

	int	iKor, iEng, iMath;

	cout << "국어 : ";
	iKor = InputInt();

	// 입력 실패일 경우 return한다.
	if (iKor == INT_MAX)
		return;

	cout << "영어 : ";
	iEng = InputInt();

	// 입력 실패일 경우 return한다.
	if (iEng == INT_MAX)
		return;

	cout << "수학 : ";
	iMath = InputInt();

	// 입력 실패일 경우 return한다.
	if (iMath == INT_MAX)
		return;

	pStudentArr[iCount].iKor = iKor;
	pStudentArr[iCount].iEng = iEng;
	pStudentArr[iCount].iMath = iMath;
	pStudentArr[iCount].iTotal = iKor + iEng + iMath;
	pStudentArr[iCount].fAvg = pStudentArr[iCount].iTotal / 3.f;

	if (pStudentArr[iCount].fAvg >= 90.f)
		pStudentArr[iCount].cScore = 'A';

	else if (pStudentArr[iCount].fAvg >= 80.f)
		pStudentArr[iCount].cScore = 'B';

	else if (pStudentArr[iCount].fAvg >= 70.f)
		pStudentArr[iCount].cScore = 'C';

	else
		pStudentArr[iCount].cScore = 'F';

	++iCount;

	// 학생 수를 증가시킨 후에 갱신시켜준다.
	*pStudentCount = iCount;
}

// 학생 정보를 받아서 출력만 하는 함수이다.
void OutputStudent(STUDENT tStudent)
{
	cout << tStudent.strName << "\t" << tStudent.iKor << "\t" <<
		tStudent.iEng << "\t" << tStudent.iMath << "\t" <<
		tStudent.iTotal << "\t" << tStudent.fAvg << "\t" <<
		tStudent.cScore << endl;
}

void OutputStudentTitle()
{
	cout << "이름\t국어\t영어\t수학\t총점\t평균\t학점" << endl;
}

void OutputStudentList(PSTUDENT pStudentArr, int iCount)
{
	system("cls");
	OutputTitle("학생목록");

	if (iCount == 0)
	{
		cout << "등록된 학생이 없습니다." << endl;
		return;
	}

	cout << "등록 학생수 : " << iCount << endl;
	OutputStudentTitle();
	for (int i = 0; i < iCount; ++i)
	{
		OutputStudent(pStudentArr[i]);
	}
}

// 이 함수는 이름을 입력받고 이름을 인자로 넘겨주어서 몇번째 학생인지를
// 찾아주는 기능을 한다.
int _Search(PSTUDENT pStudentArr, int iStudentCount, char* pName)
{
	for (int i = 0; i < iStudentCount; ++i)
	{
		if (strcmp(pStudentArr[i].strName, pName) == 0)
			return i;
	}

	return -1;
}

void Search(PSTUDENT pStudentArr, int iStudentCount)
{
	system("cls");
	OutputTitle("학생탐색");

	char	strName[NAME_SIZE] = {};

	cout << "탐색할 이름을 입력하세요 : ";
	cin.ignore(1024, '\n');
	if (!InputString(strName, NAME_SIZE))
		return;

	int	iIndex = _Search(pStudentArr, iStudentCount, strName);

	if (iIndex == -1)
	{
		cout << "탐색할 대상이 없습니다." << endl;
		return;
	}

	OutputStudentTitle();
	OutputStudent(pStudentArr[iIndex]);
}

void PressStudent(PSTUDENT pStudentArr, int iStudentCount, int iStart)
{
	for (int i = iStart; i < iStudentCount - 1; ++i)
	{
		pStudentArr[i] = pStudentArr[i + 1];
	}
}

void Delete(PSTUDENT pStudentArr, int* pStudentCount)
{
	system("cls");

	OutputTitle("학생삭제");

	char	strName[NAME_SIZE] = {};

	cout << "삭제할 이름을 입력하세요 : ";
	cin.ignore(1024, '\n');
	if (!InputString(strName, NAME_SIZE))
		return;

	int	iIndex = _Search(pStudentArr, *pStudentCount, strName);

	if (iIndex == -1)
	{
		cout << "삭제할 대상이 없습니다." << endl;
		return;
	}

	PressStudent(pStudentArr, *pStudentCount, iIndex);

	--(*pStudentCount);
}

void Run(PSTUDENT pStudentArr, int iStudentCount)
{
	while (true)
	{
		switch (SelectMenu())
		{
		case MENU_INSERT:
			Insert(pStudentArr, &iStudentCount);
			break;
		case MENU_DELETE:
			Delete(pStudentArr, &iStudentCount);
			break;
		case MENU_SEARCH:
			Search(pStudentArr, iStudentCount);
			break;
		case MENU_OUTPUT:
			OutputStudentList(pStudentArr, iStudentCount);
			break;
		case MENU_EXIT:
			return;
		}
		system("pause");
	}
}