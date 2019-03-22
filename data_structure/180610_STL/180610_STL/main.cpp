
#include <iostream>
//STL
#include <vector>
#include <list>
#include <unordered_map>	// �ؽ����� ����Ѵ�. �Ϲ� �ʺ��� ������ ������.

using namespace std;

/*
������ ������ : Ŭ������ ����ü�� �����ڸ� ������ִ� ����̴�.
�⺻ ������ ����� �ƴ϶� ���� ���� �����ڷ� ������ �� �� �ְ� ����� ���̴�.
������ �Լ� �������̵��� ����ϴ�. �����ڵ� �Լ��̴�.
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
	// a��ü�� + �Լ��� ȣ�����ش�.
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

	// vector : �����迭�� ����ϱ� ���� �����س��� STL�̴�.
	vector<int>		vecInt;

	// push_back �Լ��� �ڿ� �߰��ϴ� ���̴�. �迭�� Ư���� �տ� �߰��ϸ� ���ɿ� �ǿ����� �ִ�.
	// �׷��� push_back ��ɸ� �����Ѵ�.
	vecInt.push_back(10);
	vecInt.push_back(20);
	vecInt.push_back(30);

	cout << endl;

	// vector�� �ε��� ������ �����Ѵ�.
	cout << vecInt[1] << endl;

	cout << vecInt.front() << endl;
	cout << vecInt.back() << endl;

	vecInt.pop_back();

	for (size_t i = 0; i < vecInt.size(); ++i)
	{
		cout << vecInt[i] << endl;
	}

	// iterator : �ݺ����̴�. vector �� iterator �� �����߱� ������ int�� Ÿ������ ����
	// vector�� ��� ��带 �湮�� �� �ִ�.
	vector<int>::iterator	iter;

	// begin() : ù ����� iterator �� ���´�.
	// end() : ���� ������ ����� �� ���� End��带 ���´�. end���� ��������� ���� ǥ���ϱ�
	// ���ؼ� ���������.
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

	// ���� ��ġ�� iterator�� �ش��ϴ� ��带 �����Ѵ�.
	intList.erase(iter1);

	for (iter1 = intList.begin(); iter1 != intList.end(); ++iter1)
	{
		cout << *iter1 << endl;
	}

	// ���� Ž���� ����ȭ�Ǿ� �ִ� �˰����̴�. ���������� ����� ����Ʈ���� �����Ǿ� �ִ�.
	// ���� key, value�� �����Ǿ� �ִ�.
	// key�� �̿��ؼ� ���ϴ� ��带 Ž���ϰ� value�� ���ϴ� �����͸� �����Ѵ�.
	unordered_map<int, float>	mapFloat;

	// make_pair �Լ��� �̿��Ͽ� key, value�� ��� �ϳ��� ���� ������ش�.
	mapFloat.insert(make_pair(10, 3.14f));
	mapFloat.insert(make_pair(20, 5.334f));

	unordered_map<int, float>::iterator	iter2 = mapFloat.find(20);

	// first : key second : value
	cout << "key : " << iter2->first << " Value : " << iter2->second << endl;

	mapFloat.erase(iter2);

	// ���� Ž���ߴµ� ���ٸ� end�� �����Ѵ�.
	iter2 = mapFloat.find(3040);

	if (iter2 == mapFloat.end())
		cout << "Ž������" << endl;

	for (iter2 = mapFloat.begin(); iter2 != mapFloat.end(); ++iter2)
	{
		cout << "key : " << iter2->first << " Value : " << iter2->second << endl;
	}

	return 0;
}
