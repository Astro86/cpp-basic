
#include <iostream>

using namespace std;

/*
클래스 : C++은 객체지향 언어이다. 객체 지향이란 객체들을 생성해서 조립하여 완성된
프로그램을 만들어나가는 프로그래밍 방식이다. C++에서 객체지향 프로그래밍을 위해
제공되는 수단이 클래스이다. 클래스는 구조체와 마찬가지로 사용자정의 변수 타입을
만들 수 있다. 여러 변수들을 묶어서 생성이 가능하고 변수 뿐만 아니라 함수도
멤버로 가질 수 있는 기능을 제공한다.

클래스의 4가지 속성
캡슐화 : 여러 데이터 및 함수를 묶어서 하나의 인터페이스로 제공하는 기능을
말한다.

은닉화 : 데이터를 외부로부터 숨길 수 있는 기능을 제공한다.
public : 클래스 내부 뿐만 아니라 외부에 모두 공개하는 키워드이다.
protected : 클래스 외부에서는 접근이 불가능하고 내부 및 상속관계에서 자식의 내부에서는
접근이 허용된다.
private : 클래스 내부에서만 접근이 가능하고 외부 및 자식에서는 접근이 불가능하다.

상속성 : 클래스는 부모와 자식의 관계를 형성할 수 있는 기능을 제공한다. 이를 상속이라고
한다. 상속을 받게되면 자식은 부모의 멤버를 사용할 수 있게 된다.

다형성 : RTTI(Real Time Type Information) 다형성은 상속관계에 있는 클래스간에
서로 형변환이 가능한 속성을 말한다.

클래스의 형태
class 클래스명 {}; 의 형태로 구성이 된다. 구조체와 비슷하다.
클래스명을 이용해서 변수를 생성할 수 있다.
*/

typedef class CStudent
{
	// 멤버변수 위에 아무것도 붙여주지 않을 경우 기본으로 private이다.
	// 구조체는 기본으로 public이다.
public:	// 접근 지정자는 한번 써놓으면 다른걸 쓰기 전까지 이 아래로는 모두 적용된다.
	int		m_iKor;
	int		m_iEng;
	int		m_iMath;
	int		m_iTotal;
	float	m_fAvg;
	int*	m_pData;

public:
	// 일반 멤버변수는 생성한 각 객체마다 메모리가 할당되고 처리가 된다.
	// static 멤버 변수는 이 클래스를 이용해서 생성한 모든 객체가 공유하는
	// 하나의 메모리만 만들어지게 된다.
	static int	m_iStaticTest;

public:																			
																				
	// 멤버함수 : 이 클래스를 이용해서 생성한 객체가 사용할 수 있는 함수이다.
	void Output()
	{
		/*
		this : 자기 자신에 대한 포인터이다. 멤버함수를 호출할때 특정 객체의
		함수를 .을 이용해서 호출을 하게 된다. 이럴 경우 내부적으로 this에 호출한
		호출자의 포인터를 갖게 만들어준다. 즉 std1.Output() 함수를 호출하면
		std1에 대한 포인터를 this 에 넣고 호출을 해준다. 그렇기 때문에 this가
		호출자이므로 멤버변수에 접근할때 해당 객체의 메모리로 접근하게 된다.
		this->m_iKor 로 써야 맞는데 this->가 생략된 것이다.
		*/
		cout << "국어 : " << this->m_iKor << endl;
		cout << "영어 : " << m_iEng << endl;
	}

	// static 멤버함수 : static 멤버함수도 딱 1개만 할당된다. 모든 객체들이
	// 공유해서 사용하는 함수이다. 그렇기 때문에 this가 맵핑이 안된다.
	// 즉 일반 멤버변수는 이곳에서 사용이 불가능하다는 것이다.

	static void StaticFunction()
	{
		// static 멤버 함수 안에서는 static 멤버변수만 사용 가능하다.
		//m_iKor = 100;
		int	iKor;													
		static int	iEng = 300;
		cout << "Static Function" << endl;
	}

public:
	/*
	클래스에는 특수한 함수를 제공해주는데 생성자와 소멸자이다.

	생성자란 이 클래스를 이용해서 객체를 생성할때 호출되는 함수를 말한다.
	객체 멤버들의 초기화에 적합한 함수이다.

	소멸자란 이 클래스를 이용해서 생성한 객체가 메모리에서 해제될때 호출되는
	함수이다. 객체의 정리작업에 적합하다.
	*/
	CStudent()	: // Initializer : 변수 선언과 동시에 초기화를 해야할때 사용한다.
		m_iKor(100),
		m_iEng(95),
		m_iMath(98)
	{
		m_iMath = 93;
		m_pData = new int;
		*m_pData = 300;
	}

	CStudent(int iKor, int iEng, int iMath)	:
		m_iKor(iKor),
		m_iEng(iEng),
		m_iMath(iMath)
	{
		m_iTotal = iKor + iEng + iMath;
		m_fAvg = m_iTotal / 3.f;

		m_pData = new int;
		*m_pData = 300;
	}

	CStudent(const CStudent & std)						
	{													
		m_iKor = std.m_iKor;							
		m_iEng = std.m_iEng;
		m_iMath = std.m_iMath;							
		m_iTotal = std.m_iTotal;						
		m_fAvg = std.m_fAvg;
		// 메모리를 공유하게 된다.
		//m_pData = std.m_pData;						
														
		// 깊은복사 : 공간도 새로 할당하고 값만 복사한다.
		m_pData = new int;
		*m_pData = *std.m_pData;
	}

	~CStudent()
	{
		delete	m_pData;
	}
}CSTUDENT, *PCSTUDENT;

// static 멤버변수는 반드시 사용하겠다고 정의해주어야 한다.
int	CStudent::m_iStaticTest = 0;						
														
//typedef CStudent	STUDENT;

/*
함수포인터 : 함수도 메모리 공간에 할당되게 된다.
일반 전역 함수는 딱 1개만 존재하고 함수명 자체가 함수의 포인터이다.
*/
void FunctionPointer()
{
	cout << "Function Pointer" << endl;
}

void FuncTest1(int a)
{
	cout << a << endl;
}

void FuncTest2(int a, int b)
{
	cout << a << "\t" << b << endl;
}

int FuncTest3(int a, int b)
{
	return a + b;
}

int main()
{
	CStudent	std1, std2;
	CSTUDENT	std3;

	std1.m_iKor = 100;

	PCSTUDENT	pStudent = &std1;

	pStudent->m_iEng = 90;

	cout << std1.m_iMath << endl;
	cout << std2.m_iMath << endl;
	cout << std3.m_iMath << endl;

	std1.Output();
	std2.Output();
	std3.Output();

	// 일반 전역함수는 함수명 자체가 해당 함수의 메모리 주소이다.
	// 함수포인터 변수선언 : 리턴타입 (*변수명)(인자타입); 으로 선언 가능하다.
	void(*pFuncPointer)() = FunctionPointer;

	pFuncPointer();

	void(*pFuncTest1)(int) = FuncTest1;
	pFuncTest1(10);

	void(*pFuncTest2)(int, int) = FuncTest2;
	pFuncTest2(10, 20);

	int(*pFuncTest3)(int, int) = FuncTest3;
	cout << pFuncTest3(10, 20) << endl;

	/*
	멤버함수 포인터 : 멤버함수도 딱 1개만 메모리에 할당된다.
	그런데 멤버함수 같은 경우에는 this가 맵핑 되어야 하기 때문에 반드시 호출자를
	지정해 주어야 한다.
	변수타입 형태 : 리턴타입 (클래스명::*변수명)(인자); 의 형태로 구성된다.
	*/
	void(CStudent::*pFunc)() = &CStudent::Output;
	(std1.*pFunc)();

	std1.m_iStaticTest = 100;
	std2.m_iStaticTest = 200;
	std3.m_iStaticTest = 300;
	CStudent::m_iStaticTest = 400;

	cout << std1.m_iStaticTest << endl;
	cout << std2.m_iStaticTest << endl;
	cout << std3.m_iStaticTest << endl;

	CStudent::StaticFunction();

	// static 멤버함수는 일반 함수 포인터처럼 사용이 가능하다.
	void (*pFuncStatic)() = CStudent::StaticFunction;

	pFuncStatic();

	CStudent	std4(10, 20, 30);
	// 복사 생성자를 호출한다. 복사 생성자는 똑같은 타입의 객체를 받아서
	// 그 객체의 값을 새로 생성하는 객체에 복사해주는 생성자이다.
	// 복사 방식에는 2가지 방식이 있다. Deep Copy, Shallow Copy
	// 일반 값만 복사하는 경우 얕은 복사이다.
	// 값 뿐만 아니라 메모리 공간까지 새로 할당해야 할 경우 깊은 복사이다.
	// 복사생성자를 만들어주지 않을 경우 디폴트 복사생성자가 호출된다.
	// 얕은 복사를 한다.
	CStudent	std5(std4);

	return 0;
}
