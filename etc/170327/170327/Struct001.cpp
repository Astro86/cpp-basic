
#include <iostream>

using namespace std;

// #define : 전처리기이다. define 이름을 사용하면 이름 뒤에 잇는 값이나 코드를
// 복사하는 기능이다.
#define	NAME_SIZE	32

/*
구조체는 사용자정의 타입을 만들어줄 수 있는 기능이다. 다양한 관련있는 변수들을 모아서
캡슐화 하고 구조체명을 이용해서 구조체 변수를 선언하여 멤버들을 사용할 수 있게 해준다.
구조체의 크기는 멤버크기의 총 합이다.
*/

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
	cout << sizeof(_tagStudent) << endl;
	// 구조체명은 해당 구조체 변수 타입이다. 그렇기 때문에 구조체명으로 구조체 변수를
	// 생성해서 사용한다.
	_tagStudent	tStd;

	tStd.iKor = 10;

	// 문자열 복사 : strcpy_s(src, dest) 의 형태로 구성된 함수를 이용한다.
	// dest를 src에 복사한다.
	strcpy_s(tStd.strName, "철수");
	
		//질문 : tStd.strName = "철수" 와 같이 작성하지않고 카피를 하는 이유
		//배열에 위와같이 넣는것은 불가능하다. 지원하지않는 기능임
		//따라서 철수 는 총 4바이트 이기때문에 각각에 해당하는 아스키코드값을
		//배열에 차례대로 집어넣게끔 하기위해.

	// strlen : 문자열의 길이를 구해주는 함수이다.
	// 한글은 글자 1개당 2byte를 차지한다. 영문, 숫자를 1byte이다.
	cout << "Length : " << strlen(tStd.strName) << endl;

	// strcmp : 문자열을 비교하는 함수이다. 같을 경우 0을 반환한다.
	cout << "이름 철수? : " << strcmp(tStd.strName, "철수") << endl;

	cout << tStd.strName << endl;

	return 0;
}