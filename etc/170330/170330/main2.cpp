
#include <iostream>
#include <string>

using namespace std;

/*
�Լ� : ����� ������ش�. Ư�� ����� �Լ��� ������ְ� ���ο��� �ҷ��� ����� �� �ִ�.
���� : ����Ÿ�� �Լ���(����) {} �� ���·� �����ȴ�.
����Ÿ���� �� �Լ��� ����� ��ȯ�ϴ� Ÿ���̴�.
�Լ����� ������ �Լ��� ������ �°� ������ش�.
���ڴ� �� �Լ����� �䱸�ϴ� ���� �Ѱ��ٶ� ����Ѵ�.
*/
// �Ʒ� �Լ��� ����Ÿ���� intŸ���� �������ش�.
// ���ڷ� intŸ�� ���� 2���� �ް��ִ�.
int Sum(int a, int b)
{
	// ����Ÿ���� int�̹Ƿ� ������ �ݵ�� ��ȯ���־�� �Ѵ�.
	return a + b;
}

float Minus(float a, float b)
{
	return a - b;
}

// ���ڰ� ��� �ȴ�.
char GetChar()
{
	return 'a';
}

char* GetText()
{							
	return "Test Text";		
}

string GetString()
{
	string	str = "String Test";
	return str;
}

int GetLength(char* pString)
{
	int	iLength = 0;
	while (pString[iLength])
	{
		++iLength;
	}
	return iLength;
}

void StringCopy(char* pSrc, char* pDest)
{
	int	iLength = GetLength(pDest);

	for (int i = 0; i < iLength; ++i)
	{
		pSrc[i] = pDest[i];
	}

	pSrc[iLength] = 0;
}

int main()
{
	// �Լ��� ȣ�� : Ư�� �Լ��� ����� ȣ���Ͽ� ���⼭ �������� �� �ִ�.
	// Sum�Լ��� ���ڸ� intŸ�� ������ 2���� �ް� �ǹǷ� �ݵ�� ȣ���Ҷ� ���� �Ѱ��־�� �Ѵ�.
	// �� �Լ������� ���ڷ� �Ѱܹ��� ���� ���� ���ؼ� ��ȯ���ְ� �ȴ�. �׷��Ƿ� 30��
	// ��ȯ�Ǿ� ��µȴ�.
	cout << Sum(10, 20) << endl;
	cout << Minus(3.14f, 2.55f) << endl;
	cout << GetChar() << endl;
	cout << GetText() << endl;
	cout << GetString() << endl;
	cout << GetLength("Test") << endl;

	char	strText[64] = {};

	StringCopy(strText, "���ڿ�����");

	cout << strText << endl;
	
	return 0;
}