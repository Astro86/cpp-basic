#include <iostream>
#include <time.h>

using namespace std;

int main()
{
	srand(time(0));

	int	iNumber[9] = {};

	for (int i = 0; i < 9; ++i)
	{
		iNumber[i] = i + 1;
	}

	int	iTemp, idx1, idx2;

	for (int i = 0; i < 100; ++i)
	{
		idx1 = rand() % 9;
		idx2 = rand() % 9;

		iTemp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = iTemp;
	}

	cout << iNumber[0] << "\t" << iNumber[1] << "\t" << iNumber[2] << endl;

	int	iStrike = 0, iBall = 0;

	while (true)
	{
		cout << "숫자를 입력하세요(0 : 종료) : ";
		int	iInput[3] = {};
		cin >> iInput[0] >> iInput[1] >> iInput[2];

		if (iInput[0] == 0 || iInput[1] == 0 || iInput[2] == 0)
			break;

		iStrike = 0;
		iBall = 0;

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				if (iNumber[i] == iInput[j])
				{
					if (i == j)
						++iStrike;

					else
						++iBall;
				}
			}
		}

		if (iStrike == 3)
		{
			cout << "숫자를 맞췄습니다." << endl;
			break;
		}

		else if (iStrike == 0 && iBall == 0)
			cout << "Out" << endl;

		else
			cout << iStrike << " Strike " << iBall << " Ball" << endl;
	}

	return 0;
}

