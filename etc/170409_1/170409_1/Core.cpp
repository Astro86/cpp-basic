
#include "Core.h"

bool Init(PSTUDENTCONTAINER pStudentContainer)
{
	pStudentContainer->iCount = 0;
	pStudentContainer->iArraySize = 2;
	// 동적배열로 할당한다.
	pStudentContainer->pStudentArr = new STUDENT[pStudentContainer->iArraySize];

	return true;
}

void Close(PSTUDENTCONTAINER pStudentContainer)
{
	delete[]	pStudentContainer->pStudentArr;
}

int SelectMenu()
{
	system("cls");
	cout << "1. 학생등록" << endl;
	cout << "2. 학생삭제" << endl;
	cout << "3. 학생탐색" << endl;
	cout << "4. 학생출력" << endl;
	cout << "5. 종료" << endl;
	cout << "메뉴를 선택하세요 : ";
	int	iInput = InputInt();

	if (iInput <= MENU_NONE || iInput > MENU_EXIT)
		return MENU_NONE;

	return iInput;
}

void OutputTitle(char* pTitle)
{
	system("cls");
	cout << "====================== " << pTitle <<
		" ======================" << endl;
}

void Insert(PSTUDENTCONTAINER pContainer)
{
	OutputTitle("학생등록");

	// 더이상 추가할 공간이 없으므로 공간을 더 할당한다.
	if (pContainer->iCount == pContainer->iArraySize)
	{
		PSTUDENT	pStdArr = new STUDENT[pContainer->iArraySize * 2];
		pContainer->iArraySize *= 2;

		// 새로 2배만큼 공간을 할당한 곳에 기존에 들어가있는 학생
		// 정보들을 넣어준다.
		// memcpy : 메모리 Copy
		memcpy(pStdArr, pContainer->pStudentArr,
			sizeof(STUDENT) * pContainer->iCount);

		// 기존에 있는 메모리를 해제한다.
		delete[]	pContainer->pStudentArr;

		// 새로 할당한 메모리 주소를 얻어둔다.
		pContainer->pStudentArr = pStdArr;
	}

	char	strName[NAME_SIZE] = {};
	int	iKor, iEng, iMath, iTotal;
	float	fAvg;
	char	cScore;

	cout << "이름 : ";
	if (!InputString(strName, NAME_SIZE))
		return;

	cout << "국어 : ";
	iKor = InputInt();

	if (iKor == INT_MAX)
		return;

	cout << "영어 : ";
	iEng = InputInt();

	if (iEng == INT_MAX)
		return;

	cout << "수학 : ";
	iMath = InputInt();

	if (iMath == INT_MAX)
		return;

	iTotal = iKor + iEng + iMath;
	fAvg = iTotal / 3.f;

	if (fAvg > 90.f)
		cScore = 'A';

	else if (fAvg > 80.f)
		cScore = 'B';

	else if (fAvg > 70.f)
		cScore = 'C';

	else
		cScore = 'F';

	strcpy_s(pContainer->pStudentArr[pContainer->iCount].strName,
		strName);
	pContainer->pStudentArr[pContainer->iCount].iKor = iKor;
	pContainer->pStudentArr[pContainer->iCount].iEng = iEng;
	pContainer->pStudentArr[pContainer->iCount].iMath = iMath;
	pContainer->pStudentArr[pContainer->iCount].iTotal = iTotal;
	pContainer->pStudentArr[pContainer->iCount].fAvg = fAvg;
	pContainer->pStudentArr[pContainer->iCount].cScore = cScore;

	++pContainer->iCount;
}

void OutputTag()
{
	cout << "이름\t국어\t영어\t수학\t총점\t평균\t학점" << endl;
}

void OutputStudent(PSTUDENT pStudent)
{
	cout << pStudent->strName << "\t" << pStudent->iKor <<
		"\t" << pStudent->iEng << "\t" << pStudent->iMath <<
		"\t" << pStudent->iTotal << "\t" << pStudent->fAvg <<
		"\t" << pStudent->cScore << endl;
}

void Output(PSTUDENTCONTAINER pContainer)
{
	OutputTitle("학생출력");

	if (pContainer->iCount == 0)
	{
		cout << "출력할 학생이 없습니다." << endl;
		system("pause");
		return;
	}

	OutputTag();

	for (int i = 0; i < pContainer->iCount; ++i)
	{
		OutputStudent(&pContainer->pStudentArr[i]);
	}
	cout << endl;

	system("pause");
}

// 이름을 이용해서 학생컨테이너 안에 있는 학생의 배열 인덱스를 구해주는 함수이다.
int SearchIndex(PSTUDENTCONTAINER pContainer, char* pName)
{
	for (int i = 0; i < pContainer->iCount; ++i)
	{
		if (strcmp(pContainer->pStudentArr[i].strName, pName) == 0)
		{
			return i;
		}
	}

	// 여기까지 왔다는 의미는 찾을 학생이 없다는 의미이므로 -1을 리턴한다. 인덱스는 0부터 시작이기 때문에 -1은 존재하지 않으므로
	// 찾지 못했다는 의미가 된다.
	return -1;
}

void Delete(PSTUDENTCONTAINER pContainer)
{
	OutputTitle("학생삭제");

	char	strName[NAME_SIZE] = {};

	cout << "삭제할 학생의 이름을 입력하세요 : ";
	InputString(strName, NAME_SIZE);

	int	idx = SearchIndex(pContainer, strName);

	if (idx == -1)
	{
		cout << "삭제할 학생이 존재하지 않습니다." << endl;
		system("pause");
		return;
	}

	--pContainer->iCount;

	for (int i = idx; i < pContainer->iCount; ++i)
	{
		pContainer->pStudentArr[i] = pContainer->pStudentArr[i + 1];
	}

	cout << "학생 삭제 완료" << endl;
	system("pause");
}

void Search(PSTUDENTCONTAINER pContainer)
{
	OutputTitle("학생탐색");

	char	strName[NAME_SIZE] = {};

	cout << "탐색할 학생의 이름을 입력하세요 : ";
	InputString(strName, NAME_SIZE);

	int	idx = SearchIndex(pContainer, strName);

	if (idx == -1)
	{
		cout << "탐색할 학생이 존재하지 않습니다." << endl;
		system("pause");
		return;
	}

	OutputTag();
	OutputStudent(&pContainer->pStudentArr[idx]);

	system("pause");
}

void Run(PSTUDENTCONTAINER pStudentContainer)
{
	while (true)
	{
		switch (SelectMenu())
		{
		case MENU_INSERT:
			Insert(pStudentContainer);
			break;
		case MENU_DELETE:
			Delete(pStudentContainer);
			break;
		case MENU_SEARCH:
			Search(pStudentContainer);
			break;
		case MENU_OUTPUT:
			Output(pStudentContainer);
			break;
		case MENU_EXIT:
			return;
		}
	}
}
