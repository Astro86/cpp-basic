
#include <iostream>
#include <time.h>

using namespace std;

/*
����ü : ���ڿ� �̸��� �ο����ִ� ����̴�.
enum ����ü�� {}; �� ���·� �����ȴ�.
*/
enum SRP
{
	// �Ʒ�ó�� �����س����� ó�� 0, 1, 2 �̷��� ���ʴ�� ���� �����ؼ�
	// �ο��ȴ�.
	SRP_S = 1,
	SRP_R,
	SRP_P,
	SRP_EXIT
};

int main()
{

	srand(time(0));
	/*
	   *
	  ***
	 *****
	*******
	*/
	/*for (int i = 0; i < 4; ++i)
	{
		// ������ ����Ѵ�.
		for (int j = 0; j < 3 - i; ++j)
		{
			cout << " ";
		}

		// *�� ����Ѵ�.
		for (int j = 0; j < i * 2 + 1; ++j)
		{
			cout << "*";
		}

		cout << endl;
	}*/

	/*
	   *
	  ***
	 *****
	*******
	 *****
	  ***
	   *
	*/
	/*int	iPivot = 0;
	for (int i = 0; i < 7; ++i)
	{
		if (i <= 3)
			iPivot = i;

		else
			iPivot = 6 - i;

		// ������ ����Ѵ�.
		for (int j = 0; j < 3 - iPivot; ++j)
		{
			cout << " ";
		}

		// *�� ����Ѵ�.
		for (int j = 0; j < iPivot * 2 + 1; ++j)
		{
			cout << "*";
		}

		cout << endl;
	}*/

	// ���������� ����
	while (true)
	{
		system("cls");
		cout << "1. ����" << endl;
		cout << "2. ����" << endl;
		cout << "3. ��" << endl;
		cout << "4. ����" << endl;
		cout << "Player Turn : ";
		int	iPlayer;
		cin >> iPlayer;

		if (iPlayer == SRP_EXIT)
			break;

		// continue : �ݺ����� ���������� �ٽ� �ö󰡰� ���ش�.
		else if (iPlayer < SRP_S || iPlayer > SRP_EXIT)
			continue;

		// AI�� ������ �Ѵ�.
		int	iAI = rand() % 3 + 1;

		// switch���� �б⹮�̴�. if���� �ٸ��� ������ ���ϴ� ���� �ƴ϶�
		// () �ȿ� ������ ���� ���������� üũ�Ѵ�.
		// ������ case������ �����س��� ����Ѵ�.
		cout << "Player : ";
		switch (iPlayer)
		{
		case SRP_S:
			cout << "����\t";
			break;
		case SRP_R:
			cout << "����\t";
			break;
		case SRP_P:
			cout << "��\t";
			break;
		}

		cout << "AI : ";
		switch (iAI)
		{
		case SRP_S:
			cout << "����" << endl;
			break;
		case SRP_R:
			cout << "����" << endl;
			break;
		case SRP_P:
			cout << "��" << endl;
			break;
		}

		int	iResult = iPlayer - iAI;

		if (iResult == 1 || iResult == -2)
			cout << "Player Win" << endl;

		else if (iResult == 0)
			cout << "���º�" << endl;

		else
			cout << "AI Win" << endl;

		system("pause");
	}

	return 0;
}