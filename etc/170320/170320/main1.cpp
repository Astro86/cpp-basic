
#include <iostream>
// time.h�� �ð��� ���õ� ����� ����ִ� ��������̴�.
#include <time.h>

using namespace std;

int main()
{
	// for�� : �ݺ����� �� �����̴�. �ݺ����̶� ���ϴ� �۾��� ���� ȸ����ŭ
	// Ȥ�� �������� �ݺ��ϰ� ������ִ� ����̴�.
	// ���� : for(�ʱⰪ; ���ǽ�; ������) {} �� ���·� �����ȴ�.
	// �ʱⰪ�� ó�� �� 1���� �ʱ�ȭ�ȴ�. �� �Ŀ� ���ǽ��� üũ�ϰ� true�ϰ��
	// �ڵ�� ���� �ڵ尡 ���۵ȴ�. �� �Ŀ� ������ �ϰ� ������ �˻��ϰ� �ڵ����
	// ����, ����üũ, �ڵ������ ���ִٰ� ������ false�� ��� for���� ����ȴ�.
	for (int i = 0; i < 10; ++i)
	{
		cout << i << endl;
	}

	// ������ 2���� ����ϴ� for���� ������.
	for (int i = 1; i < 10; ++i) {
		cout << "2 * " << i << " = " << 2 * i << endl;
	}

	// ����for�� : for�� �ȿ� for���� ���� �����̴�.
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			cout << "i : " << i << " j : " << j << endl;
		}
	}

	// �������� 2�ܺ��� 9�ܱ��� ����Ͻÿ�.
	// ����� 2��	3��		4��
	//       5��		6��		7��
	//		  8��	9��		10�� ���� ��µǰ� ��������.

	/*for (int i = 2; i < 10; i += 3) {
		cout << i << "��\t\t" << i + 1 << "��\t\t" << i + 2 << "��" << endl;
		for (int j = 1; j < 10; ++j) {
			cout << i << " * " << j << " = " << i*j << "\t";
			cout << i + 1 << " * " << j << " = " << (i + 1) * j << "\t";
			cout << i + 2 << " * " << j << " = " << (i + 2) * j << endl;
		}

		cout << endl;
	}
	*/

	for (int i = 2; i < 10; i += 3) {
		cout << i << "��\t\t" << i + 1 << "��\t\t" << i + 2 << "��" << endl;
		for (int j = 1; j < 10; ++j) {
			cout << i << " * " << j << " = " << i * j << "\t";
			cout << i + 1 << " * " << j << " = " << (i + 1)*j << "\t";
			cout << i + 2 << " * " << j << " = " << (i + 2)*j << endl;
		}
	}

	/*
	*
	**
	***
	****
	*****
	*/
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < i + 1; j++) {
			cout << "*";
		}
		cout << endl;
	}

	/*
	*****
	****
	***
	**
	*
	*/
	for (int i = 5; i > 0; --i)
	{
		for (int j = 0; j < i; ++j)
		{
			cout << "*";
		}
		cout << endl;
	}



	// ������ ����ϱ� ���ؼ��� �������̺��� �������� �Ŀ� �ش� ���̺���
	// ������ ������ ������ ����̴�. ��ǻ�Ϳ��� �ǽð����� ��� ���ϴ� ����
	// �ð��̹Ƿ� �ð��� ���� ������ �߻��ϵ��� ���ش�.
	// srand �Լ��� �������̺��� ������ش�. time(0) �Լ��� �̿��ؼ� Ÿ��
	// �� �־��ְ� �ش� �ð��� �´� �������̺��� ������ְ� �ȴ�.
	srand(time(0));

	// rand() �Լ��� �̿��ؼ� �������̺��� ������ ���´�.
	// 100 ~ 200 ������ ������ ������.
	int	iRand = rand() % 101 + 100;
	cout << iRand << endl;

	// ��ȭ����.
	int		iLevel = 0;
	while (true)
	{
		// cls : clear
		system("cls");
		cout << "1. ��ȭ" << endl;
		cout << "2. ����" << endl;
		cout << "��ȭ : " << iLevel << endl;
		cout << "�޴��� �����ϼ��� : ";
		int		iInput;
		cin >> iInput;

		if (iInput == 2)
			break;

		else if (iInput == 1)
		{
			// ������ 0 ~ 3 ������ ��� 100% ����, ������ 4 ~ 6 ������ ��� 50% ����,
			// ������ 7 ~ 9 ������ ��� 20% ����, ������ 10 ~ 15 ������ ��� 5% ����
			// �׺��� ���ٸ� 1% ����
			// ��ȭ ���н� ������ 1 ���ҵȴ�.
			float fPer = 0;
			fPer = rand() % 9901 / 100.f;
			if (iLevel >= 0 && iLevel <= 3)
				iLevel = iLevel + 1;

			else if (iLevel >= 4 && iLevel <= 6)
			{
				if (fPer >= 50) {
					++iLevel;
				}
				else {
					--iLevel;
				}
			}

			else if (iLevel >= 7 && iLevel <= 9)
			{
				if (fPer < 20) {
					++iLevel;
				}
				else {
					--iLevel;
				}
			}

			else if (iLevel >= 10 && iLevel <= 15)
			{
				if (fPer < 5) {
					++iLevel;
				}
				else {
					--iLevel;
				}
			}

			else if (iLevel > 15)
			{
				if (fPer < 0.55f) {
					++iLevel;
				}
				else {
					--iLevel;
				}
			}

			cout << "Percent : " << fPer << endl;
			// pause : �Ͻ����� �����ش�.
			system("pause");
		}
	}


	return 0;
}