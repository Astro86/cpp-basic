
#include <iostream>
#include <string>

using namespace std;

/*
함수 : 기능을 만들어준다. 특정 기능을 함수로 만들어주고 메인에서 불러다 사용할 수 있다.
형태 : 리턴타입 함수명(인자) {} 의 형태로 구성된다.
리턴타입은 이 함수가 결과를 반환하는 타입이다.
함수명은 가급적 함수의 목적에 맞게 만들어준다.
인자는 이 함수에서 요구하는 값을 넘겨줄때 사용한다.
*/
// 아래 함수는 리턴타입은 int타입을 리턴해준다.
// 인자로 int타입 변수 2개를 받고있다.
int Sum(int a, int b)
{
	// 리턴타입이 int이므로 정수를 반드시 반환해주어야 한다.
	return a + b;
}

float Minus(float a, float b)
{
	return a - b;
}

// 인자가 없어도 된다.
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
	// 함수의 호출 : 특정 함수의 기능을 호출하여 여기서 실행해줄 수 있다.
	// Sum함수는 인자를 int타입 값으로 2개를 받게 되므로 반드시 호출할때 값을 넘겨주어야 한다.
	// 이 함수에서는 인자로 넘겨받은 값을 서로 더해서 반환해주게 된다. 그러므로 30이
	// 반환되어 출력된다.
	cout << Sum(10, 20) << endl;
	cout << Minus(3.14f, 2.55f) << endl;
	cout << GetChar() << endl;
	cout << GetText() << endl;
	cout << GetString() << endl;
	cout << GetLength("Test") << endl;

	char	strText[64] = {};

	StringCopy(strText, "문자열복사");

	cout << strText << endl;
	
	return 0;
}