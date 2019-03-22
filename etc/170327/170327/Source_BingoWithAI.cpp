
#include <iostream>
#include <time.h>
#include <conio.h>

using namespace std;

int main()
{
	srand(time(0));

	int		iNumber[25] = {};
	int		iAINumber[25] = {};

	// �迭�� 1 ~ 25���� ���ڸ� �־��ش�.
	for (int i = 0; i < 25; ++i)
	{
		iNumber[i] = i + 1;
		iAINumber[i] = i + 1;
	}

	// 1 ~ 25 ������ ���ڸ� ���� �����ش�.(Shuffle)
	int	iTemp, idx1, idx2;
	for (int i = 0; i < 100; ++i)
	{
		// (Player)������ �ε��� 1, 2���� �����ش�.
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		// ������ ���� 2���� �ε����� ����ִ� ���� ���� �ٲ��ش�.(swap)
		iTemp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = iTemp;

		// (AI)������ �ε��� 1, 2���� �����ش�.
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		// ������ ���� 2���� �ε����� ����ִ� ���� ���� �ٲ��ش�.(swap)
		iTemp = iAINumber[idx1];
		iAINumber[idx1] = iAINumber[idx2];
		iAINumber[idx2] = iTemp;
	}

	// ���� �ȵ� ���� ����� �����ϱ� ���� �迭�� �����.
	int	iNoneSelect[25] = {};
	int	iNoneSelectCount = 0;

	int	iBingo = 0, iAIBingo = 0;

	while (true)
	{
		system("cls");

		// �������� 5 x 5�� ����Ѵ�.
		cout << "================ Player ================" << endl;
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

		cout << "Bingo : " << iBingo << endl << endl;

		cout << "================ AI ================" << endl;
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (iAINumber[i * 5 + j] == INT_MAX)
					cout << "*\t";
				else
					cout << iAINumber[i * 5 + j] << "\t";
			}

			cout << endl;
		}

		cout << "Bingo : " << iAIBingo << endl << endl;

		if (iBingo >= 5)
		{
			cout << "Bingo!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
			break;
		}

		else if (iAIBingo >= 5)
		{
			cout << "AI Bingo!!!!!!!!!!!!!!!" << endl;
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

		// AI�� ���ڸ� �����Ѵ�.
		for (int i = 0; i < 25; ++i)
		{
			if (iAINumber[i] == iInput)
			{
				iAINumber[i] = INT_MAX;
				break;
			}
		}

		// AI�� �����Ѵ�. ���þȵ� ������ ������ ���� �����ؾ� �Ѵ�.
		// ���þ��� ����� ������ش�.
		iNoneSelectCount = 0;
		for (int i = 0; i < 25; ++i)
		{
			if (iAINumber[i] != INT_MAX)
			{
				iNoneSelect[iNoneSelectCount] = iAINumber[i];
				++iNoneSelectCount;
			}
		}

		int	iRand = rand() % iNoneSelectCount;
		iInput = iNoneSelect[iRand];

		// AI�� ������ ���ڸ� �̿��ؼ� �÷��̾�� AI�� ���ڸ� *�� ������ش�.
		for (int i = 0; i < 25; ++i)
		{
			if (iNumber[i] == iInput)
			{
				iNumber[i] = INT_MAX;
				break;
			}
		}

		for (int i = 0; i < 25; ++i)
		{
			if (iAINumber[i] == iInput)
			{
				iAINumber[i] = INT_MAX;
				break;
			}
		}

		// ���� �ټ��� üũ�Ѵ�.
		iBingo = 0;
		iAIBingo = 0;

		int		iCheck1 = 0, iCheck2 = 0;
		int		iAICheck1 = 0, iAICheck2 = 0;
		// ����, ���� �ټ��� üũ�Ѵ�.
		for (int i = 0; i < 5; ++i)
		{
			iCheck1 = iCheck2 = 0;
			iAICheck1 = iAICheck2 = 0;
			for (int j = 0; j < 5; ++j)
			{
				// ����üũ
				if (iNumber[i * 5 + j] == INT_MAX)
					++iCheck1;

				// ����üũ
				if (iNumber[j * 5 + i] == INT_MAX)
					++iCheck2;

				// AI Check
				if (iAINumber[i * 5 + j] == INT_MAX)
					++iAICheck1;

				if (iAINumber[j * 5 + i] == INT_MAX)
					++iAICheck2;
			}

			if (iCheck1 == 5)
				++iBingo;

			if (iCheck2 == 5)
				++iBingo;

			if (iAICheck1 == 5)
				++iAIBingo;

			if (iAICheck2 == 5)
				++iAIBingo;
		}

		iCheck1 = 0;
		iAICheck1 = 0;

		// ���� -> ������ �밢��
		for (int i = 0; i < 25; i += 6)
		{
			if (iNumber[i] == INT_MAX)
				++iCheck1;

			if (iAINumber[i] == INT_MAX)
				++iAICheck1;
		}

		if (iCheck1 == 5)
			++iBingo;

		if (iAICheck1 == 5)
			++iAIBingo;

		// ������ -> ���� �밢��
		iCheck1 = 0;
		iAICheck1 = 0;
		for (int i = 4; i < 21; i += 4)
		{
			if (iNumber[i] == INT_MAX)
				++iCheck1;

			if (iAINumber[i] == INT_MAX)
				++iAICheck1;
		}

		if (iCheck1 == 5)
			++iBingo;

		if (iAICheck1 == 5)
			++iAIBingo;
	}

	return 0;
}

