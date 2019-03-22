
#include <iostream>

using namespace std;

int main()
{
	/*
	쉬프트 연산자
	<<, >> 2가지로 구성되어 있다.
	이 연산자도 2진수로 연산하는 연산자이다.
	10 << 2 = 40
	10을 2진수로 변환한다. 1010 이다.
	1010을 <<(왼쪽으로) 2만큼 이동시키는 연산이다.
	오른쪽에 0을 2개 붙이는 것과 같다.
	결과는 101000 이 된다. 10진수로 40이 되는것이다.
	이 결과를 보면 10에 2의 2승을 곱한 것과 같다.
	10 << 3 = 80
	1010000 이 되고 80이 된다. 10에 2의 3승을 곱한것과 같다.
	2의 n승단위의 곱을 처리할 수도 있다. 그래서 빠른 곱하기 라고도 부른다.
	10 >> 2 = 2
	1010 을 오른쪽으로 2칸 이동시킨다. 오른쪽 2개를 지우는 것과 같다.
	10이 되고 2가 된다.
	2의 2승을 나눈것과 같다. 빠른 나누기라고도 부른다.
	*/
	cout << "10 << 2 = " << (10 << 2) << endl;
	cout << "10 >> 2 = " << (10 >> 2) << endl;

	unsigned char	r, g, b, a;
	r = 255;
	g = 100;
	b = 183;
	a = 207;

	// int에 argb 순으로 넣어준다.
	int	iColor = 0;
	// iColor = iColor | a; 연산자 축약형이다.
	iColor |= a;
	cout << "iColor = " << iColor << endl;
	// iColor = iColor << 8;
	iColor <<= 8;

	iColor |= r;

	iColor <<= 8;

	iColor |= g;

	iColor <<= 8;

	iColor |= b;

	cout << "a : " << (iColor >> 24 & 0xff) << endl;
	cout << "r : " << (iColor >> 16 & 0xff) << endl;
	cout << "g : " << (iColor >> 8 & 0xff) << endl;
	cout << "b : " << (iColor & 0xff) << endl;
	//할당된 a, r, g, b 값만을 뽑아내기위해 16진수 ff를 2진수 변환시 11111111
	//16진수 한자리는 2진수 4자리에 해당.


/*
증감연산자 : ++, -- 2가지가 존재한다. 1증가 1감소이다.
이 연산을 앞에 붙이냐 뒤에 붙이냐에 따라서 전치, 후치로 나뉜다.
전치는 먼저 값을 증가시키고 후에 다른 일을 처리한다.
후치는 먼저 다른 일을 처리하고 후에 값을 증가시킨다.
*/
	int	iNumber = 10;
	cout << "++iNumber : " << ++iNumber << endl;
	cout << "iNumber++ : " << iNumber++ << endl;
	cout << "iNumber : " << iNumber << endl;

	/*
	if문 : 분기문의 한 종류이다. 분기문이란 여러 분기중 하나만 선택해서 동작되도록
	만들어주는 기능이다.
	형태 : if(조건식) {}(코드블럭)의 형태로 구성된다.
	조건식이 true일 경우 코드블럭 안의 코드가 동작되고 false일 경우 동작하지
	않는다. if문 내의 코드가 1줄일 경우 코드블럭을 생략할 수 있다.
	else : else는 독립적으로 사용할 수 없고 반드시 if문과 쌍으로 존재해야 한다.
	else는 if의 조건이 false일 경우 동작되는 구문을 정의한다.
	분기문은 몇개의 분기든 정의해놓고 그중 하나만 처리가 가능하도록 할 수 있다.
	그래서 else if를 제공해준다.
	형태 : else if(조건식) {} 의 형태로 구성된다.
	else if도 else와 마찬가지로 독립적으로 할 수 없고 반드시 if와 쌍으로
	사용해야 한다. 몇개든지 사용할 수 있고 위에서부터 차례대로 조건을 체크하여
	true일 경우 동작시키는 방식이다.
	*/
	// 입력받은 숫자가 10 ~ 20 사이의 숫자일 경우 출력을 해준다.
	cout << "숫자를 입력하세요 : ";
	cin >> iNumber;

	if (iNumber >= 10 && iNumber <= 20)
		cout << "10 ~ 20" << endl;

	else if (iNumber > 20 && iNumber <= 30)
		cout << "21 ~ 30" << endl;

	else if (iNumber > 30 && iNumber <= 40)
		cout << "31 ~ 40" << endl;

	else
		cout << "Fail" << endl;

	if (true)
		cout << "true" << endl;

	else
		cout << "false" << endl;

	int	iKor, iEng, iMath, iTotal;
	float	fAvg;

	cout << "국어 : ";
	cin >> iKor;

	cout << "영어 : ";
	cin >> iEng;

	cout << "수학 : ";
	cin >> iMath;

	iTotal = iKor + iEng + iMath;
	fAvg = iTotal / 3.f;

	cout << "국어\t영어\t수학\t총점\t평균\t학점" << endl;
	cout << iKor << "\t" << iEng << "\t" << iMath << "\t" << iTotal << "\t" <<
		fAvg << "\t";

	if (fAvg >= 90.f)
		cout << "A" << endl;

	else if (fAvg >= 80.f)
		cout << "B" << endl;

	else if (fAvg >= 70.f)
		cout << "C" << endl;

	else
		cout << "F" << endl;

	return 0;
}

