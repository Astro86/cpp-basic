
#include <iostream>

using namespace std;

// ����Լ� : �ڱ� �ڽ� ���ο��� �ڱ� �ڽ��� �� ȣ���ϴ� �Լ��� ���Ѵ�.
// ��������� ����ؼ� �ڱ��ڽ��� ȣ���ϱ� ������ ���ÿ� �޸𸮰� ��� ���δ�.
// �׷��� ������ �ʹ� ���� ��͸� ȣ���ϰ� �Ǹ� Segment Fault�� ��µǸ鼭
// ������ �߻��Ѵ�. Stack�� �� á�� �����̴�.
int Factorial(int iNum)
{
	if (iNum == 1)
		return 1;

	return iNum * Factorial(iNum - 1);
}

int main()
{
	cout << Factorial(5) << endl;

	// ���� ����� : ������ ����� �о���� ����� �����Ѵ�.
	// C��� ����� fopen�� �̿��ؼ� �ϰ� C++����� ifstream ,ofstream��
	// �̿��ؼ� �Ѵ�.
	FILE*	pFile = NULL;
	
	//���� : �����̶�� ����ü �Ǵ� Ŭ������ ���־�Ʃ�������
	//�������ִ� ������? iostream ���� ������ �Ǿ��ִ°�����?

	while (true)
	{
		system("cls");
		cout << "1. ���ϸ����" << endl;
		cout << "2. �����б�" << endl;
		cout << "3. ����" << endl;
		cout << "�޴��� �����ϼ��� : ";
		int	iMenu;
		cin >> iMenu;

		if (iMenu == 3)
			break;

		if (iMenu == 1)
		{
			char	strFileName[256] = {};
			cin.clear();
			cin.ignore(1024, '\n');

			cout << "���� �̸��� �Է��ϼ��� : ";
			cin.getline(strFileName, 256);

			// fopen_s �Լ��� �̿��ؼ� ������ ����� �о�� �� �ִ�.
			// 1�� ���ڴ� ������ ���������Ͱ� ���� ���������� ������ �ƴٸ�
			// �� FILE*�� ������ش�.
			// 2�� ���ڴ� ������ ��ΰ� ����.
			// 3�� ���ڴ� ���� ��尡 ����.
			// r : �б� w : ���� a : �а���
			// t : �ؽ�Ʈ���� b : ���̳ʸ�����
			// 2���� �����ؼ� ����.
			// wb : ���̳ʸ� ������ �����. rb : ���̳ʸ� ������ �д´�.
			// wt : �ؽ�Ʈ ������ �����. �̷����̴�.
			fopen_s(&pFile, strFileName, "wt");

			// ���� ������ File*�� NULL�̶�� ���� ����� ���д�.
			if (pFile)
			{
				// ���Ͽ� ���� �۾��� �Ҷ��� fwrite �Լ��� �̿��ؼ� ���Ͽ�
				// ���ϴ� ������ �� �� �ִ�.
				char	str[256] = {};
				cout << "���Ͽ� �� ������ �Է��ϼ��� : ";
				cin.getline(str, 256);

				int	iLength = strlen(str);

				// 1�� ���ڴ� �����ϰ��� �ϴ� �������� �޸� �ּҸ� �Ѱ��ش�.
				// 2�� ���ڴ� Ÿ���� ũ�⸦ �����Ѵ�.
				// 3�� ���ڴ� ������ �����Ѵ�.
				// 4�� ���ڴ� File* �� �־��ش�.
				fwrite(&iLength, 4, 1, pFile);
				fwrite(str, 1, iLength, pFile);

				// �� ������ �ݵ�� �ݾ��־�� �Ѵ�.
				fclose(pFile);
			}
		}

		else if (iMenu == 2)
		{
			char	strFileName[256] = {};
			cin.clear();
			cin.ignore(1024, '\n');

			cout << "���� �̸��� �Է��ϼ��� : ";
			cin.getline(strFileName, 256);

			fopen_s(&pFile, strFileName, "rt");
			
			//���� : ��Ʈ��(���ڿ�) �� �ƴ� ���ڷ� �̷���� �ڷḦ �ۼ� �Ǵ� ��������
			//���� fopen_s �Լ��� ����ϴ���??

			if (pFile)
			{
				// �о�ö��� �ش� ������ ���� ������� �о�;� �Ѵ�.
				// �ֳ��ϸ� �����Ͱ� ���鶧 �־��� ������� ����Ǿ� �ֱ�
				// �����̴�.
				int	iLength;
				fread(&iLength, 4, 1, pFile);
				char	str[256] = {};
				fread(str, 1, iLength, pFile);

				cout << "Content : " << str << endl;

				fclose(pFile);

				system("pause");
			}
		}
	}

	return 0;
}


