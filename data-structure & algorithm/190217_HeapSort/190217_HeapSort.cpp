
#include <iostream>

using namespace std;

#include "Heap.h"
#include <time.h>

class CTestSort
{
public:
	CTestSort()
	{
	}

	~CTestSort()
	{
	}

public:
	bool Sort(const int& iSrc, const int& iDest)
	{
		return iSrc < iDest;
	}
};

bool CmpFunc(const int& iSrc, const int& iDest)
{
	return iSrc < iDest;
}

void Output(const int& iData)
{
	cout << iData << endl;
}

int main()
{
	srand(time(0));

	// 기본 생성자에서는 이 힙 클래스에 만들어져있는 기본 비교 함수를 이용해서 정렬하게 된다.
	CHeap<int>	heap;

	// 정렬 함수를 변경한다.
	heap.SetCmpFunction(CmpFunc);
	// 멤버함수 지정방법
	//CTestSort	sort;
	//heap.SetCmpFunction<CTestSort>(&CTestSort::Sort, &sort);

	for (int i = 0; i < 10; ++i)
	{
		int	iNumber = rand() % 10000;
		heap.insert(iNumber);
		cout << iNumber << endl;
	}

	cout << "============= Sort ==============" << endl;

	// 하나씩 빼와서 처리해야한다.
	for (int i = 0; i < 10; ++i)
	{
		cout << heap.pop() << endl;
	}

    return 0;
}

