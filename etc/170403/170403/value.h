
// #pragma once : 이 헤더파일을 딱 1번만 포함시키겠다는 의미이다.
// value 헤더는 공통적으로 사용되는 내용들을 모아서 선언해 놓는 용도로
// 사용한다.
#pragma once

#include <iostream>

using namespace std;

// 등록 학생의 최대치를 만들어둔다.
#define	STUDENT_MAX		10
#define	NAME_SIZE		32

// typedef : 타입을 제정의한다.
// 예) typedef int MyInt; 해주게 되면 
// MyInt  i = 0; 이렇게 int변수를 선언해줄 수 있다.
typedef struct _tagStudent
{
	char	strName[NAME_SIZE];
	int		iKor;
	int		iEng;
	int		iMath;
	int		iTotal;
	float	fAvg;
	char	cScore;
}STUDENT, *PSTUDENT;
// _tagStudent 대신에 STUDENT 로 타입을 쓸 수 있다.
// PSTUDENT는 앞에 *이 붙어 있기 때문에 포인터타입 변수를 선언할 수 있다.

// MENU
enum MENU
{
	MENU_NONE,
	MENU_INSERT,
	MENU_DELETE,
	MENU_SEARCH,
	MENU_OUTPUT,
	MENU_EXIT
};

// 헤더파일에 함수를 구현부분까지 직접 만들어주기 위해서는 일반함수로
// 처리하는것이 불가능하다.
// 함수 앞에 static을 붙여주게 되면 이 함수는 각각의 cpp마다
// 서로 다른 함수로 인식이 된다. 그렇기 때문에 중복참조가 아닌
// 각각 하나씩 가지고 참조가 되게된다.
static int InputInt()
{
	int	iInput;
	cin >> iInput;

	// 입력에 실패했을 경우 true를 리턴한다.
	if (cin.fail())
	{
		// 입력의 에러비트를 모두 초기화한다.
		cin.clear();
		// \n을 찾아내어 입력버퍼를 비워준다.
		cin.ignore(1024, '\n');
		return INT_MAX;	// 입력 실패시 특수값을 INT_MAX로 잡아두었다.
	}

	return iInput;
}

static bool InputString(char* pText, int iCount)
{
	cin.getline(pText, iCount);

	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1024, '\n');
		pText[0] = 0;
		return false;
	}

	return true;
}