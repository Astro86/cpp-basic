
#include "Core.h"

int SelectMenu()
{
	system("cls");
	cout << "1. �л��߰�" << endl;
	cout << "2. �л�����" << endl;
	cout << "3. �л�Ž��" << endl;
	cout << "4. �л����" << endl;
	cout << "5. ����" << endl;
	cout << "�޴��� �����ϼ��� : ";
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
	OutputTitle("�л��߰�");

	if (*pStudentCount == STUDENT_MAX)
	{
		cout << "���̻� �߰��� �� �����ϴ�." << endl;
		return;
	}

	int	iCount = *pStudentCount;

	// �̸��� �Է¹޴´�.
	cout << "�̸��� �Է��ϼ��� : ";
	// ���� �Է� ���� ���ڸ� �Է������Ƿ� �Է��� ����ش�.
	cin.ignore(1024, '\n');
	// ���� �Է¿� �������� ��� return�Ѵ�.
	if (!InputString(pStudentArr[iCount].strName, NAME_SIZE))
		return;

	int	iKor, iEng, iMath;

	cout << "���� : ";
	iKor = InputInt();

	// �Է� ������ ��� return�Ѵ�.
	if (iKor == INT_MAX)
		return;

	cout << "���� : ";
	iEng = InputInt();

	// �Է� ������ ��� return�Ѵ�.
	if (iEng == INT_MAX)
		return;

	cout << "���� : ";
	iMath = InputInt();

	// �Է� ������ ��� return�Ѵ�.
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

	// �л� ���� ������Ų �Ŀ� ���Ž����ش�.
	*pStudentCount = iCount;
}

// �л� ������ �޾Ƽ� ��¸� �ϴ� �Լ��̴�.
void OutputStudent(STUDENT tStudent)
{
	cout << tStudent.strName << "\t" << tStudent.iKor << "\t" <<
		tStudent.iEng << "\t" << tStudent.iMath << "\t" <<
		tStudent.iTotal << "\t" << tStudent.fAvg << "\t" <<
		tStudent.cScore << endl;
}

void OutputStudentTitle()
{
	cout << "�̸�\t����\t����\t����\t����\t���\t����" << endl;
}

void OutputStudentList(PSTUDENT pStudentArr, int iCount)
{
	system("cls");
	OutputTitle("�л����");

	if (iCount == 0)
	{
		cout << "��ϵ� �л��� �����ϴ�." << endl;
		return;
	}

	cout << "��� �л��� : " << iCount << endl;
	OutputStudentTitle();
	for (int i = 0; i < iCount; ++i)
	{
		OutputStudent(pStudentArr[i]);
	}
}

// �� �Լ��� �̸��� �Է¹ް� �̸��� ���ڷ� �Ѱ��־ ���° �л�������
// ã���ִ� ����� �Ѵ�.
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
	OutputTitle("�л�Ž��");

	char	strName[NAME_SIZE] = {};

	cout << "Ž���� �̸��� �Է��ϼ��� : ";
	cin.ignore(1024, '\n');
	if (!InputString(strName, NAME_SIZE))
		return;

	int	iIndex = _Search(pStudentArr, iStudentCount, strName);

	if (iIndex == -1)
	{
		cout << "Ž���� ����� �����ϴ�." << endl;
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

	OutputTitle("�л�����");

	char	strName[NAME_SIZE] = {};

	cout << "������ �̸��� �Է��ϼ��� : ";
	cin.ignore(1024, '\n');
	if (!InputString(strName, NAME_SIZE))
		return;

	int	iIndex = _Search(pStudentArr, *pStudentCount, strName);

	if (iIndex == -1)
	{
		cout << "������ ����� �����ϴ�." << endl;
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