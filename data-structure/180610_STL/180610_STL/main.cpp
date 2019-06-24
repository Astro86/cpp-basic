
#include <iostream>
//STL
#include <vector>
#include <list>
#include <unordered_map>	// 해쉬맵을 사용한다. 일반 맵보다 성능이 빠르다.

using namespace std;

/*
연산자 재정의 : 클래스나 구조체에 연산자를 만들어주는 기능이다.
기본 연산자 기능이 아니라 내가 만든 연산자로 동작이 될 수 있게 만드는 것이다.
일종의 함수 오버라이딩과 비슷하다. 연산자도 함수이다.
*/
template <typename T>
class COperator
{
public:
	COperator()
	{
	}

	COperator(const T& data)
	{
		m_Data = data;
	}

	~COperator()
	{
	}

private:
	T	m_Data;

public:
	COperator<T> operator + (const COperator<T>& dest)
	{
		COperator<T>	result;
		result.m_Data = m_Data + dest.m_Data;
		return result;
	}

	COperator<T> operator + (int a)
	{
		COperator<T>	result;
		result.m_Data = m_Data + a;
		return result;
	}

	COperator<T> operator + (float a)
	{
		COperator<T>	result;
		result.m_Data = m_Data + a;
		return result;
	}

	void operator += (const COperator<T>& dest)
	{
		m_Data += dest.m_Data;
	}

public:
	void Print()
	{
		cout << m_Data << endl;
	}
};

class CMyString
{
public:
	CMyString()
	{
		m_iSize = 0;
		m_iCapacity = 20;
		m_pString = new char[m_iCapacity];
	}

	CMyString(const char* pString)
	{
		m_iSize = strlen(pString);
		m_iCapacity = m_iSize + 1;

		m_pString = new char[m_iCapacity];
		strcpy_s(m_pString, m_iCapacity, pString);
		m_pString[m_iSize] = 0;
	}

	~CMyString()
	{
		delete[]	m_pString;
	}

private:
	char*	m_pString;
	int		m_iSize;
	int		m_iCapacity;

public:
	void operator = (const char* pString)
	{
		delete[]	m_pString;
		m_iSize = strlen(pString);
		m_iCapacity = m_iSize + 1;

		m_pString = new char[m_iCapacity];
		strcpy_s(m_pString, m_iSize, pString);
		m_pString[m_iSize] = 0;
	}

	CMyString operator + (const char* pString)
	{
		char*	pStr = new char[m_iSize + strlen(pString) + 1];
		memset(pStr, 0, sizeof(char) * m_iSize + strlen(pString) + 1);

		//strcpy_s(pStr, m_iSize + 1, m_pString);
		//strcat_s(pStr, strlen(pString) + 1, pString);
		memcpy(pStr, m_pString, m_iSize);
		memcpy(pStr + m_iSize, pString, strlen(pString));
		CMyString	str = pStr;
		delete[]	pStr;
		return str;
	}

	CMyString operator + (const CMyString& str)
	{
		return *this + str.m_pString;
	}

	char* GetString()
	{
		return m_pString;
	}
};

int main()
{
	COperator<int>	a(10), b(20), c;
	// a객체의 + 함수를 호출해준다.
	c = a + b;

	c.Print();

	c = a + 30;
	c.Print();

	c = a + 3.14f;
	c.Print();

	c += a;
	c.Print();

	CMyString	a1("aa"), b1("bb"), c1;

	//c1 = a1 + b1;
	//c1 = a1 + "asdf";

	//cout << c1.GetString() << endl;

	// vector : 동적배열을 사용하기 쉽게 구현해놓은 STL이다.
	vector<int>		vecInt;

	// push_back 함수는 뒤에 추가하는 것이다. 배열의 특성상 앞에 추가하면 성능에 악영향이 있다.
	// 그래서 push_back 기능만 제공한다.
	vecInt.push_back(10);
	vecInt.push_back(20);
	vecInt.push_back(30);

	cout << endl;

	// vector는 인덱스 접근을 제공한다.
	cout << vecInt[1] << endl;

	cout << vecInt.front() << endl;
	cout << vecInt.back() << endl;

	vecInt.pop_back();

	for (size_t i = 0; i < vecInt.size(); ++i)
	{
		cout << vecInt[i] << endl;
	}

	// iterator : 반복자이다. vector 의 iterator 를 생성했기 때문에 int를 타입으로 갖는
	// vector의 모든 노드를 방문할 수 있다.
	vector<int>::iterator	iter;

	// begin() : 첫 노드의 iterator 를 얻어온다.
	// end() : 가장 마지막 노드의 그 다음 End노드를 얻어온다. end노드는 명시적으로 끝을 표현하기
	// 위해서 만들어졌다.
	for (iter = vecInt.begin(); iter != vecInt.end(); ++iter)
	{
		cout << *iter << endl;
	}

	list<int>	intList;

	intList.push_back(10);
	intList.push_back(20);
	intList.push_front(30);

	cout << intList.size() << endl;
	cout << intList.empty() << endl;

	list<int>::iterator	iter1 = intList.begin();
	++iter1;

	// 현재 위치의 iterator에 해당하는 노드를 삭제한다.
	intList.erase(iter1);

	for (iter1 = intList.begin(); iter1 != intList.end(); ++iter1)
	{
		cout << *iter1 << endl;
	}

	// 맵은 탐색에 최적화되어 있는 알고리즘이다. 내부적으로 레드블랙 이진트리로 구성되어 있다.
	// 맵은 key, value로 구성되어 있다.
	// key를 이용해서 원하는 노드를 탐색하고 value에 원하는 데이터를 저장한다.
	unordered_map<int, float>	mapFloat;

	// make_pair 함수를 이용하여 key, value를 묶어서 하나의 노드로 만들어준다.
	mapFloat.insert(make_pair(10, 3.14f));
	mapFloat.insert(make_pair(20, 5.334f));

	unordered_map<int, float>::iterator	iter2 = mapFloat.find(20);

	// first : key second : value
	cout << "key : " << iter2->first << " Value : " << iter2->second << endl;

	mapFloat.erase(iter2);

	// 만약 탐색했는데 없다면 end를 리턴한다.
	iter2 = mapFloat.find(3040);

	if (iter2 == mapFloat.end())
		cout << "탐색실패" << endl;

	for (iter2 = mapFloat.begin(); iter2 != mapFloat.end(); ++iter2)
	{
		cout << "key : " << iter2->first << " Value : " << iter2->second << endl;
	}

	return 0;
}
