#include <iostream>
#include <time.h>
#include <conio.h>

using namespace std;

int main()
{
	srand(time(0));

	int	iNumber[25] = {};

	for (int i = 0; i < 24; ++i)
	{
		iNumber[i] = i + 1;
	}

	iNumber[24] = INT_MAX;	//*�� Ư���� ���ڸ� �Ҵ��Ͽ� Ȥ�ø� ������ ���ϱ����� INT_MAX �� ��.

	// ���� *�� ����ִ� �ε����� �����صд�.
	int	iStarIndex = 24;

	// *�� ������ ������ 1 ~ 24 ������ ���ڸ� ���� �����ش�.
	int	iTemp, idx1, idx2;
	for (int i = 0; i < 100; ++i)
	{
		idx1 = rand() % 24;
		idx2 = rand() % 24;

		iTemp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = iTemp;
	}

	while (true)
	{
		system("cls");
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (iNumber[i * 5 + j] == INT_MAX)
					cout << "*\t";

				else
					cout << iNumber[i * 5 + j] << "\t";
			}
			cout << endl;
		}

		bool	bWin = true;

		for (int i = 0; i < 24; ++i)
		{
			if (iNumber[i] != i + 1)
			{
				bWin = false;
				break;
			}
		}

		if (bWin)
		{
			cout << "��� ������ϴ�." << endl;
			break;
		}

		cout << "w : �� s : �� a : �� d : �� q : ���� : ";
		// _getch() �Լ��� ���ڸ� �Է¹޴� �Լ��̴�. �� �Լ��� ���ڸ� �Է����ڸ���
		// �ٷ� ���۵ȴ�. ���ڸ� �Է��ϰ� EnterŰ�� ���ĵ� �ȴ�.
		char	cInput = _getch();

		if (cInput == 'q' || cInput == 'Q')
			break;

		switch (cInput)
		{
			// case������ break�� ������ ������ ��� �Ʒ��� ��������.
			// �Ʒ�ó�� �ϸ� w, W �Ѵ� ���� ������ �ϰ� �ȴ�.
		case 'w':
		case 'W':
			// ���� �̵��� �Ҷ� ���� *�� ���� ���ٿ� ���� ��� ���̻� �̵��� �� ����.
			if (iStarIndex > 4)
			{
				iTemp = iNumber[iStarIndex];
				iNumber[iStarIndex] = iNumber[iStarIndex - 5];
				iNumber[iStarIndex - 5] = iTemp;

				// ���� �ִ� ��ġ�� �����Ѵ�.
				iStarIndex -= 5;
			}
			break;
		case 's':
		case 'S':
			// �Ʒ��� �̵��� �Ҷ� ���� *�� ���� �Ʒ��� ���� ��� ���̻� �̵��� �� ����.
			if (iStarIndex < 20)
			{
				iTemp = iNumber[iStarIndex];
				iNumber[iStarIndex] = iNumber[iStarIndex + 5];
				iNumber[iStarIndex + 5] = iTemp;

				iStarIndex += 5;
			}
			break;
		case 'a':
		case 'A':
			// �������� �̵��� �Ҷ� ���� *�� ���� ���ʿ� ���� ��� ���̻� �̵��� �� ����.
			if (iStarIndex % 5 != 0)
			{
				iTemp = iNumber[iStarIndex];
				iNumber[iStarIndex] = iNumber[iStarIndex - 1];
				iNumber[iStarIndex - 1] = iTemp;

				--iStarIndex;
			}
			break;
		case 'd':
		case 'D':
			// ���������� �̵��� �Ҷ� ���� *�� ���� �����ʿ� ���� ��� �̵��� �� ����.
			if (iStarIndex % 5 != 4)
			{
				iTemp = iNumber[iStarIndex];
				iNumber[iStarIndex] = iNumber[iStarIndex + 1];
				iNumber[iStarIndex + 1] = iTemp;

				++iStarIndex;
			}
			break;
		}
	}

	return 0;
}