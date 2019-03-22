
// #include : 앞에 #이 붙으면 전처리기이다. 전처리기란 컴파일 단계에서 처리되는것을
// 말한다. 우리가 사용하는 visual studio는 컴파일러이다. C, C++등은 언어인데 고수준
// 언어이다. 고수준 언어란 사람이 사용하기 쉬운 언어를 말한다. 하지만 컴퓨터는 이러한
// 고수준 언어를 인식하지 못한다. 왜냐하면 컴퓨터는 저수준 언어인 어셈블리어와 기계어로
// 동작하기 때문이다. 컴파일러는 번역기다. 사람이 사용하기 쉬운 고수준 언어를 번역하여
// 컴퓨터가 알아듣기 쉬운 저수준 언어로 번역해주는 역할을 한다.
// 컴파일 단계 : 컴파일(번역) -> 빌드(바이너리 코드로 변환하여 실행파일을 만들어준다.)
// include 뒤에 오는 헤더파일을 컴파일 단계에서 여기에 포함시켜준다. iostream 헤더파일
// 에는 C++의 표준 입출력 기능 및 표준으로 제공되는 다양한 기능들이 들어가있다.
// 그 기능들을 여기에서 사용하기위해서 include를 해주는 것이다.
#include <iostream>
//#include <string>

// namespace : 이름공간. C++에서는 변수 명이나 혹은 함수명 등을 같은 이름으로
// 사용할 경우 에러가 발생할 수 있다. namespace로 어떤 부분을 감싸게 되면 그
// 부분은 해당 namespace로 감싸지게 된다. c++표준 출력기능인 cout은 std namespace
// 안에 들어가있다.
// using namespace 기능은 원하는 namespace를 사용하겠다 라고 지정해주고
// std:: 이렇게 붙여주지 않아도 사용 가능하도록 선언하는 것이다.
using namespace std;

// Ctrl + Shift + B : Build를 해준다. Build를 하면 코드를 컴파일하고
// 실행파일을 만들어준다.
// Ctrl + F5 : 실행이다. 만들어진 실행파일을 실행시켜주는 역할을 한다.
// 만약 빌드가 되어 있지 않다면 빌드를 하고 실행을 시켜주게 된다.

// 아래의 int main() 은 함수이다. 어떤 프로그램이건 반드시 Entry Point가 존재
// 해야한다. C++에서는 main 이라고 이름지어진 함수를 진입점으로 인식한다.
// 우리가 만든 프로그램에서 동작을 시키려면 반드시 이 진입점 함수 내에 코드가
// 존재해야 한다.
int main()
{
	// cout이나 endl은 iostream 헤더파일에서 제공되는 C++ 표준 기능이다.
	// 그런데 이 기능들은 std 라는 namespace 안에 소속되어 있다. 그렇기 때문에
	// 자신이 소속되어 있는 namespace 명을 적어주어야 한다.
	// std::cout : std namespace 안에 있는 cout이라는 의미이다.
	// :: 스코프 연산자.
	std::cout << "Test Output" << std::endl;
	cout << "Test Output Free" << endl;

	//string	str11 = "aksjf";
	//cout << str11.c_str() << endl;
	/*
	변수 : 변하는 수. 컴퓨터에는 크게 2가지의 저장장치가 존재한다.
	주기억장치와 보조기억장치 이다. 주기억장치는 cpu가 사용하는 저장공간으로
	휘발성 메모리의 특성을 지니고 있다. 휘발성 메모리란 일회용 저장공간을 의미
	한다. 컴퓨터 부품중 RAM(메모리)가 주기억장치에 해당한다.
	보조기억장치는 비휘발성 메모리의 특성을 지니고 있다. 반영구적으로 데이터를
	저장할 수 있다. 하드디스크가 보조기억장치에 해당된다. 일반적으로 주기억장치가
	속도가 월등히 빠르다.
	변수를 사용하게 되면 해당 변수는 메모리에 공간이 할당되고 원하는 값을 저장해
	두고 사용하게 된다. 변수에는 각 특성에 맞게 각각의 타입이 존재한다.
	컴퓨터의 용량 체계 : 최소단위는 bit이다.
	1byte : 8bit
	1kbyte : 1024byte
	1mbyte	= 1024kbyte
	1gbyte	= 1024mbyte
	1tbyte	= 1024gbyte
	Type	|	종류		|	용량		|	표현범위			|	unsigned
	char	|	문자		|	1byte	|	-128~127		|	0 ~ 255
	bool	|	참/거짓		|	1byte	|	0/1				|	0 / 1
	short	|	정수		|	2byte	|	-32768~32767	|	0 ~ 65535
	int		|	정수		|	4byte	|	약 -22억~21억	|	0 ~ 약 43억
	float	|	실수		|	4byte	|	
	double	|	실수		|	8byte	|
	unsigned : 음수 부호를 양수로 변환해준다.
	*/
	// 변수의 선언 : 변수타입 변수명; 의 형태로 선언한다. ;은 마침표다.
	// 반드시 코드의 마지막에 ;을 붙여주어야 한다.
	// 변수 앞에 c를 붙여주었는데 이를 보고 헝가리안 표기법이라고 부른다.
	// 변수의 타입마다 어떤 타입인지를 구분할 수 있도록 변수명 앞에 타입을
	// 구분할 알파벳을 붙여준다. char 변수는 1byte 문자를 저장한다. 영문이나
	// 숫자를 저장할 수 있다.
	// 원래 char도 -128 ~ 127의 숫자를 저장한다. 하지만 문자를 저장하고 문자를
	// 출력할 수 있는 이유는 컴퓨터 내부적으로 가지고 있는 아스키 코드 표라는
	// 것 때문이다. 숫자가 들어가면 해당 숫자에 맞는 아스키 코드를 표에서 찾아서
	// 출력하기 때문이다.
	char	cFont1;
	char	cFont2;
	// 문자 1개를 표현할때는 ''(작은따옴표) 안에 문자를 표시한다.
	// 문자 여러개(문자열)을 표현할 때는 ""(큰따옴표) 안에 표시한다.
	cFont1 = 'd';
	cFont2 = 75;

	cout << "cFont1 : " << cFont1 << endl;
	cout << "cFont2 : " << cFont2 << endl;

	// bool변수는 true / false 둘중 하나를 저장한다. 0은 false이고 0이 아닌
	// 모든 수는 true이다.
	bool	bTest = true;

	unsigned short	sNumber = 32769;
	sNumber = 65536;

	cout << "sNumber : " << sNumber << endl;

	int		iNumber = 2100000000;
	// 64비트 인트이다.
	__int64	iNumber64 = 10000000000000;

	cout << "iNumber : " << iNumber << endl;
	cout << "__64 iNumber64 : " << iNumber64 << endl;

	// 실수를 사용할때 3.14 와 3.14f는 다르다. 
	// 3.14 로 사용하면 double 타입이 되고 뒤에 f를 붙인 3.14f는
	// float 타입이다.
	float	fNumber1 = 3.1412357568f;
	float	fNumber2 = 3.1412357568;
	/*질문1 : 위의 두개가 다르지않는데 소수점 뒤에 f를 붙히는 경우는 어떤경우이고 
			어짜피 자료형을 float으로 선언해두면 굳이 소수점 뒤에 붙히는 이유가 뭔지*/
	cout << "fNumber1 : " << fNumber1 << endl;
	cout << "fNumber2 : " << fNumber2 << endl;

	double	dNumber = 3.14324872347;
	cout << "dNumber : " << dNumber << endl;
	/*질문2 : 소수점은 무조건 5자리까지만 표현되는지, 만약 아니라면 전체 다 보이게끔 출력하는 자료형*/

	
	// sizeof : 변수나 변수 타입의 용량을 byte단위로 알아보는 함수이다.
	cout << "char size : 1?" << sizeof(char) << endl;
	cout << "bool size : 1?" << sizeof(bool) << endl;
	cout << "short size : 2?" << sizeof(short) << endl;
	cout << "int size : 4?" << sizeof(int) << endl;
	cout << "__int64 size : 8?" << sizeof(__int64) << endl;
	cout << "float size : 4?" << sizeof(float) << endl;
	cout << "double size : 8?" << sizeof(double) << endl;
	cout << "long size : 4?" << sizeof(long) << endl;
	cout << "_Longlong size : 8?" << sizeof(_Longlong) << endl;

	cout << "숫자를 입력하세요 : ";
	cin >> iNumber;

	cout << "입력한 숫자 : " << iNumber << endl;

	return 0;
}