
#include <iostream>

using namespace std;

// 함수 오버로딩 : 함수 이름은 같지만 인자가 다른것을 말한다.
// 같은 이름으로 다른 인자의 여러 함수를 만들어줄 때 사용한다.
// 리턴타입은 함수 오버로딩에 영향을 주지 않는다.
void Output()
{
	cout << "Output Blank" << endl;
}

void Output(int iNumber)
{
	cout << "Output(int iNumber) : "<<iNumber << endl;
}

void Output(float fNumber)
{
	cout << "Output(float fNumber) : "<<fNumber << endl;
}

void Output(int iNumber, int iNumber1)
{
	cout << "Output(int iNumber, int iNumber1) : "<<iNumber << "\t" << iNumber1 << endl;
}

void Default(int iNum = 100)
{
	cout << "Default : "<<iNum << endl;
}

int main()
{
	Output();
	Output(10);
	Output(3.14f);
	Output(10, 20);

	Default();
	Default(1234);		


	// 동적 할당 : 메모리 할당을 내가 원하는 시점에 동적으로 할당
	// 한다. 일반적인 지역변수는 해당 코드블럭으로 실행흐름이 이동
	// 할때 메모리에 할당된다. 전역변수는 프로그램이 시작될때
	// 할당된다. 하지만 동적할당을 하면 내가 원하는 시점에 메모리
	// 를 할당할 수 있다. 동적할당한 메모리는 힙에 할당된다.
	// new 키워드를 이용해서 메모리를 동적할당 할 수 있다.
	// 흔히 착각하기 쉬운게 아래처럼 동적할당을 하면 pNumber에
	// 메모리를 할당하는 것으로 착각한다. 하지만 이 의미는 아니다.
	// new int를 하게 되는 순간 메모리 힙영역의 어딘가에 int의
	// 크기만큼(4byte) 할당을 하고 할당된 메모리 주소를 리턴한다.
	// 그렇게 되면 int*변수인 pNumber에 그 주소를 갖고있고
	// 주소를 알고있으므로 힙에 할당된 메모리공간에 원하는 값을
	// 넣고 쓸 수 있다.
	int*	pNumber = new int;
	*pNumber = 300;		//질문 : *pNumber가 의미하는게 
						//pNumber가 가르키는 주소의 4바이트 영역에 300이라는 내용물을 대입한다는 소리?
	cout << *pNumber << endl;

	// 힙에 동적할당을 하면 반드시 delete 키워드를 이용해서
	// 메모리를 해제해 주어야 한다. 해제하지 않으면 메모리가
	// 남게 되는데 이런 현상을 메모리 Leak이라고 한다.
	delete	pNumber;

	// 동적 배열 : 동적으로 배열을 선언하는 것이다.
	int		iNum = 300;
	int*	pArray = new int[iNum];
	int		iArray[300];
	delete[]	pArray;

	return 0;
}
