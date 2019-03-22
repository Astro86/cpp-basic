
#include <iostream>

using namespace std;

int main()
{
	/*
	사칙연산자 : +, -, *, /, %
	% : 나머지 연산자이다. mod 연산자라고 한다. 이 연산자는 반드시 정수 대
	정수로 연산해야 한다.
	나눗셈 연산을 할때 주의사항
	정수 / 정수를 하게되면 무조건 정수가 나온다. 결과가 소수점자리가 존재할 경우
	소수점자리가 짤린다.
	결과로 실수를 얻고 싶다면 반드시 둘중 하나라도 실수로 만들어 주어야 한다.
	*/
	float	fNumber1 = 10 / 3.f;
	float fNumber2;
	cout << "fNumber1 : " << fNumber1 << endl;

	// 변수의 형변환(Type Casting)
	// 변수를 일시적으로 다른 타입으로 변환하는 기능을 제공해준다.
	int		iNum1, iNum2;
	iNum1 = 10;
	iNum2 = 3;
	fNumber2 = iNum1 / iNum2;
	// 아래의 경우 결과는 3.33333 이지만 int변수에 대입해주므로
	// 소수점 자리가 짤리고 3만 들어간다. 암시적 형변환이라고 한다.
	int	iNum3 = iNum1 / (float)iNum2;

	cout << "fNumber2 : " << fNumber2 << endl;
	cout << "iNum3 : " << iNum3 << endl;

	int iNum4 = 100 % 3;
	cout << "iNum4 : "<< iNum4 << endl;
	// 나머지 연산자를 안쓰고 사칙연산만을 활용해서 나머지를 구해보자.
	iNum3 = 100 - 100 / 3 * 3;
	cout << iNum3 << endl;
	iNum3 = 37 - 37 / 7 * 7;
	cout << iNum3 << endl;

	/*
	관계연산자
	<, >, <=, >=, ==, !=
	위의 6가지 연산자를 제공해준다. 관계연산자는 피연산자가 값으로 구성되고
	이 값들을 비교하여 조건이 맞는지 true, false의 형태로 반환해준다.
	*/
	bool	bResult = 10 < 3;
	cout << "10 < 3 = " << bResult << endl;

	bResult = 10 > 3;
	cout << "10 > 3 = " << bResult << endl;

	/*
	논리연산자
	AND, OR, NOT으로 구성되어 있는 연산자이다. 논리연산은 참/거짓 : 참/거짓
	을 연산해주는 연산자이다.
	A	B	AND	OR
	0	0	0	0
	1	0	0	1
	0	1	0	1
	1	1	1	1
	AND는 피연산자 둘 모두 참일 경우 참이고 나머지는 거짓이다.
	OR는 피연산자 둘 모두 거짓일 경우 거짓이고 나머지는 참이다.
	A	NOT
	0	1
	1	0
	NOT은 피연산자 하나만 연산한다. 부정의 의미로 거짓일때 참, 참일때 거짓이다.
	기호 : AND(&&), OR(||), NOT(!)
	*/
	cout << "false && false = " << (false && false) << endl;
	cout << "true && false = " << (true && false) << endl;
	cout << "false && true = " << (false && true) << endl;
	cout << "true && true = " << (true && true) << endl;

	cout << "false || false = " << (false || false) << endl;
	cout << "true || false = " << (true || false) << endl;
	cout << "false || true = " << (false || true) << endl;
	cout << "true || true = " << (true || true) << endl;

	cout << "!false = " << !false << endl;
	cout << "!true = " << !true << endl;

	// 입력받은 숫자가 10 ~ 20 사이의 숫자인지를 체크한다.
	cout << "숫자를 입력하세요 : ";
	cin >> iNum3;
	bResult = 10 <= iNum3 && iNum3 <= 20;
	cout << bResult << endl;

	/*
	진수변환
	컴퓨터가 사용하는 수 개념은 2진수, 8진수, 10진수, 16진수가 있다.
	그런데 보통 2진수, 10진수, 16진수를 많이 활용한다.
	각 수는 다른 진수로 변환이 가능하다.
	16진수는 0 ~ 9까지 이고 10 ~ 15 까지는 a ~ f로 표현한다.
	10진수 89라는 숫자를 2진수나 16진수로 변환해보자.
	먼저 2진수로 변환한다. 2로 계속 나누면서 나머지값을 적어둔다.
	89 / 2 = 44 ---- 1
	44 / 2 = 22 ---- 0
	22 / 2 = 11 ---- 0
	11 / 2 = 5 ----- 1
	5 / 2 = 2 ------ 1
	2 / 2 = 1 ------ 0
	이렇게 구한 후에 역순으로 읽는다.
	89 : 2진수 1011001이 된다.
	변환한 2진수를 16진수로 변환해보자. 2진수를 오른쪽부터 4자리씩 끊어준다.
	101 1001
	101은 0101과 같다.
	0101 1001
	각 자리별로 오른쪽으로부터 1, 2, 4, 8을 부여하고 1인 부분의 숫자들을 더한다.
	4 + 1, 8 + 1이므로 16진수 59가 나오게 된다. 16진수는 표기할때 앞에 0x를
	붙여서 0x59 로 표시한다.
	
	비트단위 논리 연산자
	논리연산자의 한 종류로 일반 논리연산자와 다르게 결과가 값으로 나오게 된다.
	비트단위 논리연산자는 어떤 수를 2진수로 변환한 후에 2진수의
	각 자리별로 논리연산을 진행한다. 기호는 AND(&), OR(|), NOT(~)로 표시한다.
	
	89 & 57 = 25
	57 / 2 = 28 ---- 1
	28 / 2 = 14 ---- 0
	14 / 2 = 7 ----- 0
	7 / 2 = 3 ------ 1
	3 / 2 = 1 ------ 1
	89 : 1011001
	57 : 0111001
	각 자리별로 논리연산을 한다.
	0011001 이 된다. 25가 된다.
	
	89 | 57 = 121
	89 : 1011001
	57 : 0111001
	각 자리별로 |연산을 한다.
	1111001
	*/
	
	cout << "(89 & 57) : " << (89 & 57) << endl;
	cout << "(89 | 57) : " << (89 | 57) << endl;
	
	// const : 상수를 만들어주는 기능이다. 상수란 변하지 않는 수이다. 값을
	// 바꿀 수 없다는 것이다.
	const int	iAttack = 0x1;		//     1
	const int	iArmor = 0x2;		//    10
	const int	iHPUP = 0x4;		//   100
	const int	iMPUP = 0x8;		//  1000
	const int	iCritical = 0x10;	// 10000

	// 10101
	int	iBuf = iAttack | iHPUP | iCritical;
	cout << "iBuf : " << iBuf << endl;
	// XOR : A와 B가 다를때 참 같을때 거짓이다.
	// iBuf = iBuf ^ iHPUP;이다. ^는 XOR 기호이다.
	// 10101 ^ 00100 을 하면 10001
	
	iBuf ^= iHPUP;
	cout << "iBuf : " << iBuf << endl;

	// 10001 & 00001 = 1
	cout << "Attack : " << (iBuf & iAttack) << endl;
	// 10001 & 00010 = 0
	cout << "Armor : " << (iBuf & iArmor) << endl;
	// 10001 & 00100 = 0
	cout << "HP : " << (iBuf & iHPUP) << endl;
	// 10001 & 01000 = 0
	cout << "MP : " << (iBuf & iMPUP) << endl;
	// 10001 & 10000 = 10000
	cout << "Critical : " << (iBuf & iCritical) << endl;

	return 0;
}