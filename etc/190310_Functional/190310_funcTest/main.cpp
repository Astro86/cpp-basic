
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

/*
함수포인터 활용시 주의사항
반드시 리턴타입과 인자의 수, 인자의 타입이 같아야 한다.
*/
class CTestFunction
{
private:
	int a;
	int b;

public:
	CTestFunction()
	{
		a = 10;
		b = 5;
	}

	~CTestFunction()
	{
	}

public:
	int Sum()
	{
		return a + b;
	}

	int Minus()
	{
		return a - b;
	}

	int Multi()
	{
		return a * b;
	}

	int Div()
	{
		return a / b;
	}

	int Mod()
	{
		return a % b;
	}
};


template <typename FuncType, typename ClassType>
class CFunctionNode
{
	template <typename T>
	friend class CFunction;

public:
	CFunctionNode()
	{
		m_pObj = nullptr;
	}

	~CFunctionNode()
	{
	}

private:
	FuncType	m_pFunc;
	ClassType*	m_pObj;
};

template <typename FuncType>
class CFunction
{
public:
	CFunction()
	{
	}

	~CFunction()
	{
	}

public:
	template <typename ClassType>
	void Bind(FuncType pFunc, ClassType* pObj)
	{
	}

	void Bind(FuncType pFunc)
	{
	}
};

int Sum(int a, int b)
{
	return a + b;
}

int Minus(int a, int b)
{
	return a - b;
}

int Multi(int a, int b)
{
	return a * b;
}

int Div(int a, int b)
{
	return a / b;
}

int Mod(int a, int b)
{
	return a % b;
}

int Output()
{
	cout << "OutputFunc" << endl;
	return 0;
}

int main()
{
	int(*pFunc[5])(int, int);
	int(*pFunc1[])(int, int) = { Sum, Minus, Multi, Div, Mod };
	int(**pFunc2)(int, int) = new (int(*[5])(int, int));

	vector<int(*)(int, int)>	vecFunc;

	vecFunc.push_back(Sum);
	vecFunc.push_back(Minus);
	vecFunc.push_back(Multi);
	vecFunc.push_back(Div);
	vecFunc.push_back(Mod);

	//pFunc1 = pFunc;
	
	pFunc[0] = Sum;
	pFunc[1] = Minus;
	pFunc[2] = Multi;
	pFunc[3] = Div;
	pFunc[4] = Mod;

	pFunc2[0] = Sum;
	pFunc2[1] = Minus;
	pFunc2[2] = Multi;
	pFunc2[3] = Div;
	pFunc2[4] = Mod;

	for (int i = 0; i < 5; ++i)
	{
		cout << pFunc1[i](10, 5) << endl;
	}

	for (int i = 0; i < 5; ++i)
	{
		cout << pFunc2[i](10, 5) << endl;
	}

	for (size_t i = 0; i < vecFunc.size(); ++i)
	{
		cout << vecFunc[i](10, 5) << endl;
	}

	vector<int(*)(int, int)>::iterator	iter;
	vector<int(*)(int, int)>::iterator	iterEnd = vecFunc.end();
	for (iter = vecFunc.begin(); iter != iterEnd; ++iter)
	{
		cout << (*iter)(10, 5) << endl;
	}

	delete[]	pFunc2;

	int(CTestFunction::*pFunc10[5])();
	pFunc10[0] = &CTestFunction::Sum;

	CTestFunction	fc;

	cout << (fc.*pFunc10[0])() << endl;

	function<int()>	func[5];

	func[0] = bind(&CTestFunction::Sum, &fc);
	func[1] = bind(&CTestFunction::Minus, &fc);
	func[2] = bind(&CTestFunction::Multi, &fc);
	func[3] = bind(&CTestFunction::Div, &fc);
	func[4] = bind(Output);

	for (int i = 0; i < 5; ++i)
	{
		cout << func[i]() << endl;
	}

	vector<function<int()>>	vecFunc11;

	vecFunc11.push_back(bind(&CTestFunction::Sum, &fc));
	vecFunc11.push_back(bind(Output));

	for (size_t i = 0; i < vecFunc11.size(); ++i)
	{
		cout << vecFunc11[i]() << endl;
	}

	return 0;
}
