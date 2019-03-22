
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

		cout << "1. �л��߰�" << endl;
		cout << "2. �л�����" << endl;
		cout << "3. �л�Ž��" << endl;
		cout << "4. �л����" << endl;
		cout << "5. ����" << endl;
		cout << "�޴��� �����ϼ��� : ";
		
		int	iMenu;
		cin >> iMenu;
		
		if (iMenu == MM_EXIT)
			break;

		switch (iMenu)
		{
		case MM_INSERT:
			if (iStudentCount == STUDENT_MAX)
			{
				cout << "���̻� �߰��� �� �����ϴ�." << endl;
				break;
			}

			system("cls");

			cout << "========================== �л��߰� ==========================" << endl;
			
			// �Է¹��۴� cin���� �Է¹��� ������ ������ �ִ� �����̴�.(�������)
			// �Է¹��ۿ� EnterŰ�� ������ ��� ���� �Է��� �Ȱɷ� �νĵ� �� �ִ�.
			// �׷��� ������ ���۸� \n�� �ִ°����� ����ش�.
			cin.ignore(1024, '\n');

			cout << "�̸� : ";
			// ���ڿ��� �Է¹����� ����Ѵ�.
			cin.getline(tStudent[iStudentCount].strName, NAME_SIZE - 1);

			// ������ �Է¹޴´�.
			int	iKor, iEng, iMath;
			cout << "���� : ";
			cin >> iKor;

			cout << "���� : ";
			cin >> iEng;

			cout << "���� : ";
			cin >> iMath;

			int		iTotal;

			iTotal = iKor + iEng + iMath;

			tStudent[iStudentCount].iKor = iKor;
			tStudent[iStudentCount].iEng = iEng;
			tStudent[iStudentCount].iMath = iMath;
			tStudent[iStudentCount].iTotal = iTotal;
			tStudent[iStudentCount].fAvg = iTotal / 3.f;

			++iStudentCount;

			cout << "�л��߰� �Ϸ�" << endl;
			break;
		
		case MM_DELETE:
		{
			system("cls");
			cout << "========================== �л����� ==========================" << endl;

			// case �� �ȿ��� ����� ���ÿ� �ʱ�ȭ�� �ϸ� ������ �߻��Ѵ�.
			// ������ �� �������� {}(�ڵ��)���� �����־��� ������ ����� ����.
			char	strName[NAME_SIZE] = {};
			
			cin.ignore(1024, '\n');
			cout << "������ �̸��� �Է��ϼ��� : ";
			cin.getline(strName, NAME_SIZE - 1);

			bool	bFind = false;

			// �ݺ����鼭 ã�´�.
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
				cout << "������ ����� �����ϴ�." << endl;

			else
				cout << "���� �Ϸ�" << endl;
		}
			break;
		case MM_SEARCH:
		{
			system("cls");
			cout << "========================== �л�Ž�� ==========================" << endl;

			// case �� �ȿ��� ����� ���ÿ� �ʱ�ȭ�� �ϸ� ������ �߻��Ѵ�.
			char	strName[NAME_SIZE] = {};

			cin.ignore(1024, '\n');
			cout << "Ž���� �̸��� �Է��ϼ��� : ";
			cin.getline(strName, NAME_SIZE - 1);

			bool	bFind = false;

			// �ݺ����鼭 ã�´�.
			for (int i = 0; i < iStudentCount; ++i)
			{
				if (strcmp(strName, tStudent[i].strName) == 0)
				{
					bFind = true;
					cout << "�̸�\t����\t����\t����\t����\t���" << endl;

					cout << tStudent[i].strName << "\t" << tStudent[i].iKor << "\t" <<
						tStudent[i].iEng << "\t" << tStudent[i].iMath << "\t" <<
						tStudent[i].iTotal << "\t" << tStudent[i].fAvg << endl;
					break;
				}
			}

			if (!bFind)
				cout << "Ž���� ����� �����ϴ�." << endl;
		}
			break;
		case MM_OUTPUT:
			system("cls");
			cout << "========================== �л���� ==========================" << endl;

			cout << "�̸�\t����\t����\t����\t����\t���" << endl;
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