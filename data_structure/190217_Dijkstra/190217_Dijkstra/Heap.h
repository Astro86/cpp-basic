
#pragma once

// c++ 11부터 지원되는 기능이다. 일반 함수나 멤버함수포인터를 쉽게 사용할 수 있는 객체를
// 지원해준다.
#include <functional>
#include <assert.h>

using namespace std;

template <typename T>
class CHeapNode
{
	template <typename T>
	friend class CHeap;

private:
	CHeapNode()
	{
		m_iIndex = -1;
	}

	~CHeapNode()
	{
	}

public:
	T		m_Data;
	int		m_iIndex;
};

template <typename T>
class CHeap
{
public:
	CHeap()
	{
		m_iSize = 0;
		m_iCapacity = 100;

		m_pArray = new NODE[m_iCapacity];

		// bind함수를 이용해서 함수포인터를 묶어서 function 객체를 만들어준다.
		// 멤버함수를 넣을때는 멤버함수 주소와 이 함수를 호출할 객체의 주소를 지정해주어야 한다.
		// 인자가 2개이므로 2개의 인자 순서를 지정해준다.
		m_ComFunc = bind(&CHeap::Cmp, this, placeholders::_1, placeholders::_2);
	}

	~CHeap()
	{
		delete[]	m_pArray;
	}

private:
	typedef CHeapNode<T>	NODE;
	typedef CHeapNode<T>*	PNODE;

private:
	PNODE	m_pArray;
	int		m_iSize;
	int		m_iCapacity;
	function<bool(const T&, const T&)>	m_ComFunc;

public:
	// 전역함수를 지정해서 값을 비교하게 한다.
	void SetCmpFunction(bool(*pFunc)(const T&, const T&))
	{
		m_ComFunc = bind(pFunc, placeholders::_1, placeholders::_2);
	}

	// 멤버함수를 지정해서 값을 비교하게 한다. 여기서는 이 함수에서만 사용하는 템플릿을
	// 추가로 하나 더 사용한다. 왜냐하면 클래스 타입을 다른 클래스 타입으로도 사용 가능하게
	// 하기 위해서이다.
	template <typename FuncType>
	void SetCmpFunction(bool (FuncType::*pFunc)(const T&, const T&), FuncType* pObj)
	{
		m_ComFunc = bind(pFunc, pObj, placeholders::_1, placeholders::_2);
	}

public:
	void insert(const T& data)
	{
		// 만약 공간이 꽉 찼다면 새로 복사해준다.
		if (m_iSize == m_iCapacity)
		{
			m_iCapacity *= 2;

			PNODE	pArray = new NODE[m_iCapacity];

			for (int i = 0; i < m_iSize; ++i)
			{
				pArray[i].m_Data = m_pArray[i].m_Data;
				pArray[i].m_iIndex = m_pArray[i].m_iIndex;
			}

			delete[]	m_pArray;

			m_pArray = pArray;
		}

		// 가장 마지막에 추가할 노드의 정보를 넣어준다.
		m_pArray[m_iSize].m_Data = data;
		m_pArray[m_iSize].m_iIndex = m_iSize;

		// 루트로 타고들어가면서 위치를 잡아준다.
		_insert(m_iSize);

		++m_iSize;
	}

	void clear()
	{
		m_iSize = 0;
		delete[]	m_pArray;
		
		m_iCapacity = 100;
		m_pArray = new NODE[m_iCapacity];
	}

	T pop()
	{
		if (empty())
		{
			assert(false);
		}

		// 이미 정렬 기준으로 루트노드에 처음으로 빼야 할 데이터가 들어가 있으므로 루트노드의 값을 얻어둔다.
		T	data = m_pArray[0].m_Data;

		// 사이즈를 감소시킨다.
		--m_iSize;

		// 가장 마지막 노드를 루트로 올려서 아래로 내려가면서 정렬한다.
		m_pArray[0] = m_pArray[m_iSize];

		// 위로 올려준 데이터로부터 아래로 내려가며 정렬한다.
		HeapIfy(0);

		return data;
	}

	int size()	const
	{
		return m_iSize;
	}

	int capacity()	const
	{
		return m_iCapacity;
	}

	bool empty()	const
	{
		return m_iSize == 0;
	}

	void Output(void(*pFunc)(const T& data))
	{
		for (int i = 0; i < m_iSize; ++i)
		{
			pFunc(m_pArray[i].m_Data);
		}
	}

private:
	void _insert(int iIndex)
	{
		if (iIndex <= 0)
			return;

		// 부모노드의 인덱스를 구한다. 예를 들어 1일때 / 2를 하면 0이 나와서 부모가 맞지만
		// 인덱스가 2일때 / 2를 하면 1이 되어서 부모가 안맞다. 즉, 1을 빼준 후에 / 2를 해주게 되면
		// 정확하게 부모 인덱스를 찾을 수 있다.
		int	iParent = (iIndex - 1) / 2;

		// 두 값을 비교한다. 기본 비교함수는 최대힙을 구성하게 만들어져있다.
		if (m_ComFunc(m_pArray[iIndex].m_Data, m_pArray[iParent].m_Data))
		{
			// 두 값을 변경한다.
			T	temp = m_pArray[iIndex].m_Data;
			m_pArray[iIndex].m_Data = m_pArray[iParent].m_Data;
			m_pArray[iParent].m_Data = temp;

			_insert(iParent);
		}
	}

	void HeapIfy(int iIndex)
	{
		int	iLeftIndex = iIndex * 2 + 1;

		if (iLeftIndex >= m_iSize)
			return;

		// 오른쪽 인덱스를 구한다.
		int	iRightIndex = iLeftIndex + 1;

		// 왼쪽 자식과 오른쪽 자식중 최대힙이냐 최소힙이냐에 따라 어느 자식노드를 부모와 비교할지 판단한다.
		int	iChildIndex = iLeftIndex;

		// 오른쪽 인덱스가 사이즈보다 작다면 오른쪽 자식노드가 있다는 의미이다.
		if (iRightIndex < m_iSize)
		{
			// 왼쪽과 오른쪽 값을 비교하여 비교할 자식노드의 최종 인덱스를 결정한다.
			// 바꿔야 할 상황이 온다면 오른쪽 자식노드를 선택한다. 그게 아니라면 왼쪽 자식노드를 선택해서
			// 부모와 비교하게 한다.
			if (m_ComFunc(m_pArray[iRightIndex].m_Data, m_pArray[iLeftIndex].m_Data))
				iChildIndex = iRightIndex;
		}

		// 부모와 선택된 자식노드를 비교한다.
		if (m_ComFunc(m_pArray[iChildIndex].m_Data, m_pArray[iIndex].m_Data))
		{
			// 두 값을 변경한다.
			T	temp = m_pArray[iIndex].m_Data;
			m_pArray[iIndex].m_Data = m_pArray[iChildIndex].m_Data;
			m_pArray[iChildIndex].m_Data = temp;

			HeapIfy(iChildIndex);
		}
	}


private:
	// 기본 비교함수를 만들어둔다.
	bool Cmp(const T& src, const T& dest)
	{
		return src < dest;
	}
};
