
#include "Core.h"

bool Init(PSTUDENTCONTAINER pStudentContainer)
{
	pStudentContainer->iCount = 0;
	pStudentContainer->iArraySize = 2;
	// �����迭�� �Ҵ��Ѵ�.
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
	cout << "1. �л����" << endl;
	cout << "2. �л�����" << endl;
	cout << "3. �л�Ž��" << endl;
	cout << "4. �л����" << endl;
	cout << "5. ����" << endl;
	cout << "�޴��� �����ϼ��� : ";
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
	OutputTitle("�л����");

	// ���̻� �߰��� ������ �����Ƿ� ������ �� �Ҵ��Ѵ�.
	if (pContainer->iCount == pContainer->iArraySize)
	{
		PSTUDENT	pStdArr = new STUDENT[pContainer->iArraySize * 2];
		pContainer->iArraySize *= 2;

		// ���� 2�踸ŭ ������ �Ҵ��� ���� ������ ���ִ� �л�
		// �������� �־��ش�.
		// memcpy : �޸� Copy
		memcpy(pStdArr, pContainer->pStudentArr,
			sizeof(STUDENT) * pContainer->iCount);

		// ������ �ִ� �޸𸮸� �����Ѵ�.
		delete[]	pContainer->pStudentArr;

		// ���� �Ҵ��� �޸� �ּҸ� ���д�.
		pContainer->pStudentArr = pStdArr;
	}

	char	strName[NAME_SIZE] = {};
	int	iKor, iEng, iMath, iTotal;
	float	fAvg;
	char	cScore;

	cout << "�̸� : ";
	if (!InputString(strName, NAME_SIZE))
		return;

	cout << "���� : ";
	iKor = InputInt();

	if (iKor == INT_MAX)
		return;

	cout << "���� : ";
	iEng = InputInt();

	if (iEng == INT_MAX)
		return;

	cout << "���� : ";
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
	cout << "�̸�\t����\t����\t����\t����\t���\t����" << endl;
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
	OutputTitle("�л����");

	if (pContainer->iCount == 0)
	{
		cout << "����� �л��� �����ϴ�." << endl;
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

// �̸��� �̿��ؼ� �л������̳� �ȿ� �ִ� �л��� �迭 �ε����� �����ִ� �Լ��̴�.
int SearchIndex(PSTUDENTCONTAINER pContainer, char* pName)
{
	for (int i = 0; i < pContainer->iCount; ++i)
	{
		if (strcmp(pContainer->pStudentArr[i].strName, pName) == 0)
		{
			return i;
		}
	}

	// ������� �Դٴ� �ǹ̴� ã�� �л��� ���ٴ� �ǹ��̹Ƿ� -1�� �����Ѵ�. �ε����� 0���� �����̱� ������ -1�� �������� �����Ƿ�
	// ã�� ���ߴٴ� �ǹ̰� �ȴ�.
	return -1;
}

void Delete(PSTUDENTCONTAINER pContainer)
{
	OutputTitle("�л�����");

	char	strName[NAME_SIZE] = {};

	cout << "������ �л��� �̸��� �Է��ϼ��� : ";
	InputString(strName, NAME_SIZE);

	int	idx = SearchIndex(pContainer, strName);

	if (idx == -1)
	{
		cout << "������ �л��� �������� �ʽ��ϴ�." << endl;
		system("pause");
		return;
	}

	--pContainer->iCount;

	for (int i = idx; i < pContainer->iCount; ++i)
	{
		pContainer->pStudentArr[i] = pContainer->pStudentArr[i + 1];
	}

	cout << "�л� ���� �Ϸ�" << endl;
	system("pause");
}

void Search(PSTUDENTCONTAINER pContainer)
{
	OutputTitle("�л�Ž��");

	char	strName[NAME_SIZE] = {};

	cout << "Ž���� �л��� �̸��� �Է��ϼ��� : ";
	InputString(strName, NAME_SIZE);

	int	idx = SearchIndex(pContainer, strName);

	if (idx == -1)
	{
		cout << "Ž���� �л��� �������� �ʽ��ϴ�." << endl;
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
