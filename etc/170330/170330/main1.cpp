
#include <iostream>

using namespace std;

#define	NAME_SIZE	32
#define	STUDENT_MAX	10

struct _tagStudent
{
	char	strName[NAME_SIZE];
	int		iKor;
	int		iEng;
	int		iMath;
	int		iTotal;
	float	fAvg;
};

int main()
{
	/*
	포인터 : 모든 변수타입은 포인터타입을 가질 수 있다. 포인터타입을 이용하여 생성한 변수는
	해당 타입으로 생성한 변수의 메모리 주소를 값으로 가지게 된다. 메모리 주소를 알고 있다면
	그 주소에 접근하여 값을 변경하거나 가져다 사용할 수 있다.
	포인터 변수는 자기 스스로는 아무것도 할 수 없다. 반드시 어떤 변수의 메모리주소를 갖고있고
	그 주소를 참조해야만 일을 할 수 있다.
	포인터는 메모리 주소를 값으로 갖게 되기 때문에 타입에 상관없이 무조건 4byte이다.
	왜냐하면 메모리 주소체계는 16진수 8자리로 구성된다. 즉 16진수 1자리는 2진수 4자리이고
	2진수 1자리는 1bit이므로 4bit * 8 = 32bit가 되서 4byte이다.
	형태 : 변수타입 *변수명;으로 하게된다.
	예) int iNumber = 100;
	// & 주소를 리턴한다.
	int *pNumber = &iNumber;
	*/

	// 컴파일을 64비트용으로 하게 되면 8바이트가 나온다.
	cout << sizeof(int*) << endl;
	cout << sizeof(char*) << endl;

	int	iNumber = 100;
	int	*pNumber = &iNumber;

	// 역참조 : 포인터변수가 어떤 변수의 메모리 주소를 담고있을 경우 해당 주소에 접근하여
	// 값을 바꿀 수 있는 기능을 말한다. 포인터 변수 앞에 *을 붙여서 접근한다.
	// 아래는 pNumber앞에 *을 붙였으므로 pNumber가 가리키는 대상의 값을 의미한다.
	// pNumber는 iNumber의 주소를 갖고 있으므로 iNumber를 가리키고 *pNumber는
	// iNumber의 값을 의미한다.
	*pNumber = 200;

	cout << "iNumber : " << iNumber << endl;
	cout << "iNumber의 주소 : " << &iNumber << endl;
	cout << "pNumber : " << pNumber << endl;
	cout << "pNumber의 주소 : " << &pNumber << endl;

	// 포인터의 const
	// const 키워드는 변수타입 전이나 변수타입 뒤에 붙여줄 수 있다.
	const int *cpNumber = &iNumber;

	// cpNumber는 const를 변수 앞에 붙여주었기 때문에 가리키는 대상의 값을
	// 변경할 수 없다. 하지만 가리키는 대상 자체를 변경하는 것은 가능하다.
	//*cpNumber = 300;
	int		iNumber1 = 500;
	cpNumber = &iNumber1;

	cout << *cpNumber << endl;

	// const 를 변수타입 뒤에 붙여주게 되면 가리키는 대상을 변경할 수 없다.
	// 가리키는 대상의 값은 변경이 가능하다.
	int* const pcNumber = &iNumber;

	*pcNumber = 1234;

	//pcNumber = &iNumber1;

	cout << iNumber << endl;

	// 둘다 붙여주면 2개의 특징을 모두 갖게 된다. 즉 가리키는 대상도 변경할 수 없고
	// 가리키는 대상의 값도 변경할 수 없다.
	const int* const cpcNumber = &iNumber;

	//*cpcNumber = 11223;
	//cpcNumber = &iNumber1;
	//const int	iAttack = 0x1;

	// "" 문자열을 쓰게 되면 const char* 이다. 문자열 상수들을 저장하는 메모리 공간에
	// 테스트 <== 문자열이 저장되고 그 주소를 리턴받아서 저장해둔다.
	// pText는 저 문자열 상수의 주소를 갖게되고 그 주소를 참조하여 출력하게 된다.
	// const이기 때문에 값의 변경은 불가능하다.
	char*	pText = "테스트";

	cout << pText << endl;
	cout << (int*)pText << endl;

			//질문 : (int*)를 붙여서 강제형변환 해서 출력된 값은 pText의 주소값??

	// 사용자정의 타입들도 변수타입이다. 그러므로 포인터 변수를 생성할 수 있다.
	_tagStudent		tStudent = {};

	_tagStudent	*pStudent = &tStudent;

	cout << "_tagStudent : " << sizeof(pStudent) << endl;

	(*pStudent).iKor = 100;
	// 구조체 포인터를 이용하여 가리키는 대상의 값에 접근할때는 위의 방법과 아래의 방법 모두
	// 사용할 수 있다.
	pStudent->iKor = 200;

	cout << tStudent.iKor << endl;
	cout << "tStudent의 주소 : " << &tStudent << endl;
	cout << "pStudent : " << pStudent << endl;
	cout << "pStudent의 주소 : " << &pStudent << endl;

	// 포인터의 배열의 관계
	// 중요) 배열명은 포인터다. 배열은 연속된 메모리 블록에 할당된다.
	// 배열명은 해당 배열의 시작 메모리 주소를 가지고 있다.
	
	int	iArray[10] = {};
	// 배열명은 배열의 시작 메모리 주소이므로 &을 붙여주지 않아도 주소이기 때문에
	// 포인터 변수에 대입이 가능하다.
	int	*pArray = iArray;
	// ++을 해주게 되면 iArray[1] 의 메모리 주소를 갖게된다.
	pArray++;
	// 그러므로 여기서 1번 인덱스는 iArray기준으로 2번인덱스가 된다.
	pArray[1] = 1234;
	//포인터가 배열을 가르키면 인덱스를 이용해서 해당 배열에 접근이 가능하다
			//질문 : pArray 는 iArray 배열의 시작주소를 갖는 포인터 변수인데
			//		포인터 변수인 pArray[1] 이 표현의 의미가 무엇인지?

	// 원래 인덱스로 접근하는 의미는 아래처럼 연산이 일어난다.
	cout <<"pArray : " <<pArray << endl;
	cout << "pArray[0] : " << pArray[0] << endl; //pArray는 포인터 변수이지 배열이 아닌데 pArray[0]값에 0이 들어가있는 이유 ( 쓰레기값이 아니라) 
	cout << "pArray[1] : "<<pArray[1] << endl;
	cout << "*(pArray + 1) : " <<*(pArray + 1) << endl;//pArray는 iArray[0]의 주소값. 그 주소값에 4를(int타입 이기에) 더한 주소에 해당하는 값을 호출??
													   //결국 iArray[1]의 값을 호출?
	cout << "*pArray + 1 : "<<*pArray + 1 << endl;	//pArray의 역참조 = 0 따라서 0+1 = 1
	cout << "iArray[1] : "<<iArray[1] << endl;		//iArray의 1번 인덱스값 = pArray[0]
	cout << "iArray[2] : "<<iArray[2] << endl;

	// 포인터의 연산 : +, -연산만 존재한다.
	// ++을 할 경우 1증가인데 포인터변수에 ++을 하게 된다면 단순히 1 증가가 아니다.
	// 포인터는 메모리 주소를 갖고 있는 변수이다.
	// 해당 포인터타입의 크기만큼 증가한다.
	// 만약 int* 라면 4만큼 증가하게 되는것이다.
	
	cout << "pArray : " << pArray << endl;
	cout << "pArray + 1 : " << pArray + 1 << endl;

	char	str[10] = {};

	char	*pStr = str;

	cout << "(int*)pStr : "<<(int*)pStr << endl;
	cout << "(int*)(pStr + 1) : " << (int*)(pStr + 1) << endl;

	_tagStudent	tStdArr[STUDENT_MAX] = {};
	_tagStudent	*pStdArr = tStdArr;

	cout << "pStdArr : " <<pStdArr << endl;
	cout << "pStdArr + 1 : " <<pStdArr + 1 << endl;

	return 0;
}