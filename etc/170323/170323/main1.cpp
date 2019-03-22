
#include <iostream>
#include <time.h>

using namespace std;

int main()
{
	srand(time(0));
	/*
	�迭 : ���ӵ� ���� �������� �ϳ��� �̸����� ����� �� �ֵ��� ���ִ� ����̴�.
	��� Ÿ���� �������� �迭�� ���� �� �ִ�
	���� : ����Ÿ�� �迭��[����]; �� ���·� �����ؼ� ����� �� �ִ�.
	�迭�� Ư�� ��ҿ� �����ϱ� ���ؼ��� �ε��� ������ ���δ�.
	�ε����� 0������ �����ؼ� �迭���� - 1 ������ �����Ѵ�.
	*/
	// �Ʒ�ó�� 10���� ��� �־��ָ� ���ʴ�� 0������ 9������ 1 ~ 10�� ����
	// ���� �ȴ�.
	//int	iArray[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	// �Ʒ�ó�� 5���� ������ 0, 1, 2, 3, 4 �� �ε����� ���� ������
	// ����
	// ���� �������� 0���� �ʱ�ȭ�ȴ�.
	//int iArray[10] = { 1, 2, 3, 4, 5 };

	// �ƹ��͵� �־����� ������ ��� 0���� �ʱ�ȭ�Ѵ�.
	/*int	iArray[10] = {};

	iArray[1] = 30;

	for (int i = 0; i < 10; ++i)
	{
		iArray[i] = i + 1;
	}

	for (int i = 0; i < 10; ++i)
	{
		cout << iArray[i] << endl;
	}*/

	// Lotto Program
	int		iLotto[45];
	
	for (int i = 0; i < 45; ++i)
	{
		iLotto[i] = i + 1;
	}

	int	iLottoGame = 0;

	cout << "���Ӽ��� �Է��ϼ��� : ";
	cin >> iLottoGame;

	// ��÷��ȣ�� �̸� �����д�.
	int	iLottoNumber[7];

	int	iTemp, idx1, idx2;
	for (int j = 0; j < 100; ++j)
	{
		idx1 = rand() % 45;
		idx2 = rand() % 45;

		iTemp = iLotto[idx1];
		iLotto[idx1] = iLotto[idx2];
		iLotto[idx2] = iTemp;
	}
		
	for (int i = 0; i < 5; ++i)
	{
		for (int j = i + 1; j < 6; ++j)
		{
			if (iLotto[i] > iLotto[j])
			{
				iTemp = iLotto[i];
				iLotto[i] = iLotto[j];
				iLotto[j] = iTemp;
			}
		}
	}

	for (int i = 0; i < 7; ++i)
	{
		iLottoNumber[i] = iLotto[i];
	}

	cout << "��÷��ȣ : ";
	for (int i = 0; i < 6; ++i)
	{
		cout << iLottoNumber[i] << "\t";
	}
	cout << "/\t" << iLottoNumber[6] << endl;

	for (int i = 0; i < iLottoGame; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			idx1 = rand() % 45;
			idx2 = rand() % 45;

			iTemp = iLotto[idx1];
			iLotto[idx1] = iLotto[idx2];
			iLotto[idx2] = iTemp;
		}

		cout << i + 1 << " :\t";

		// 6���� ��÷��ȣ�� ������������ �����Ѵ�.(Bubble Sort)
		for (int j = 0; j < 5; ++j)
		{
			for (int k = j + 1; k < 6; ++k)
			{
				if (iLotto[j] > iLotto[k])
				{
					iTemp = iLotto[j];
					iLotto[j] = iLotto[k];
					iLotto[k] = iTemp;
				}
			}
		}

		for (int j = 0; j < 6; ++j)
		{
			cout << iLotto[j] << "\t";
		}

		cout << endl;

		// ��÷��ȣ�� ���Ͽ� ����� ���Ѵ�.
		int	iPairCount = 0;

		for (int j = 0; j < 6; ++j)
		{
			for (int k = 0; k < 6; ++k)
			{
				if (iLotto[j] == iLottoNumber[k])
				{
					++iPairCount;
					break;
				}
			}
		}

		switch (iPairCount)
		{
		case 6:
			cout << "1��" << endl;
			break;
		case 5:
			bool	bBonus;
			bBonus = false;
			for(int i = 0; i < 6; ++i)
			{
				if(iLotto[i] == iLottoNumber[6])
				{
					cout << "2��" << endl;
					bBonus = true;
					break;
				}
			}

			if(!bBonus)
				cout << "3��" << endl;

			break;
		case 4:
			cout << "4��" << endl;
			break;
		case 3:
			cout << "5��" << endl;
			break;
		default:	// �� ���� ���� ���
			cout << "��" << endl;
			break;
		}
	}

	int		iNumber[25];

	// �迭�� 1 ~ 25���� ���ڸ� �־��ش�.
	for (int i = 0; i < 25; ++i)
	{
		iNumber[i] = i + 1;
	}

	// 1 ~ 25 ������ ���ڸ� ���� �����ش�.(Shuffle)
	for (int i = 0; i < 100; ++i)
	{
		// ������ �ε��� 1, 2���� �����ش�.
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		// ������ ���� 2���� �ε����� ����ִ� ���� ���� �ٲ��ش�.(swap)
		iTemp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = iTemp;
	}
	
	int	iBingo = 0;

	while (true)
	{
		system("cls");

		int iNumber[25] = {};

		// �������� 5 x 5�� ����Ѵ�.
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

		cout << "Bingo : " << iBingo << endl;

		if (iBingo >= 5)
		{
			cout << "Bingo!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
			break;
		}
		cout << "���ڸ� �����ϼ���(0 : ����) : ";
		int	iInput;
		cin >> iInput;

		if (iInput == 0)
			break;

		else if (iInput < 0 || iInput > 25)
			continue;

		// �ߺ��� ���� �Է� ����
		bool	bInputCheck = true;

		// ���� ����� ������ ���ڰ� �ִ����� üũ�Ѵ�.
		for (int i = 0; i < 25; ++i)
		{
			if (iNumber[i] == iInput)
			{
				// UINT_MAX : int�� ǥ���� �� �ִ� �ִ밪�̴�.
				iNumber[i] = INT_MAX;
				bInputCheck = false;
				break;
			}
		}

		// �ߺ��� ���ڸ� �Է����� ��� �ٽ� �Է¹޴´�.
		if (bInputCheck)
			continue;

		// ���� �ټ��� üũ�Ѵ�.
		iBingo = 0;

		int		iCheck1 = 0, iCheck2 = 0;
		// ����, ���� �ټ��� üũ�Ѵ�.
		for (int i = 0; i < 5; ++i)
		{
			iCheck1 = iCheck2 = 0;
			for (int j = 0; j < 5; ++j)
			{
				// ����üũ
				if (iNumber[i * 5 + j] == INT_MAX)
					++iCheck1;

				// ����üũ
				if (iNumber[j * 5 + i] == INT_MAX)
					++iCheck2;
			}

			if (iCheck1 == 5)
				++iBingo;

			if (iCheck2 == 5)
				++iBingo;
		}

		iCheck1 = 0;

		// ���� -> ������ �밢��
		for (int i = 0; i < 25; i += 6)
		{
			if (iNumber[i] == INT_MAX)
				++iCheck1;
		}

		if (iCheck1 == 5)
			++iBingo;

		// ������ -> ���� �밢��
		iCheck1 = 0;
		for (int i = 4; i < 21; i += 4)
		{
			if (iNumber[i] == INT_MAX)
				++iCheck1;
		}

		if (iCheck1 == 5)
			++iBingo;
	}

	return 0;
}