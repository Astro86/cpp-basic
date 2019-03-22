
#include <iostream>

using namespace std;

/*
템플릿 : 타입을 가변적으로 받아올 수 있는 기능이다. 정해진 타입이 아닌 매번 호출할때마다 다른 타입으로
정의되도록 만들어줄 수 있다. 함수에도 사용이 가능하고 클래스에도 사용이 가능하다. 단, 클래스 전체도 가능하지만,
클래스의 멤버 함수 하나만도 가능하다. 물론 여러개도 가능하다.
형태 : template <typename 원하는이름> 으로 지정 가능하다.
typename, class 둘중 하나를 써서 지정한다 . 여러개의 가변타입도 지정 가능하다.
template <typename T1, class T2, typename T3> 처럼 여러개도 가능하다.
*/
template <typename T>
void OutputType()
{
	// typeid 함수는 안에 들어오는 타입정보를 문자열로 표현해줄 수 있다.
	cout << typeid(T).name() << endl;
}

template <typename T>
class CTest
{
public:
	T	m_Data;
};

int main()
{
	// <타입> 을 이용해서 T에 들어갈 타입을 정의해줄 수 있다.
	OutputType<int>();
	OutputType<float>();
	OutputType<CTest<int>>();

	return 0;
}
