#pragma once

#include <assert.h>

template <typename T>
class CQueueNode
{
	template <typename T>
	friend class CQueue;
	template <typename T, int SIZE>
	friend class CCircleQueue;

private:
	CQueueNode()
	{
		m_pNext = nullptr;
	}

	~CQueueNode()
	{
	}

private:
	T		m_Data;
	CQueueNode<T>*	m_pNext;
};

template <typename T>
class CQueue
{
public:
	CQueue()
	{
		m_iSize = 0;
		m_pFirst = nullptr;
		m_pLast = nullptr;
	}

	~CQueue()
	{
		PNODE	pNode = m_pFirst;

		while (pNode)
		{
			PNODE	pNext = pNode->m_pNext;
			delete	pNode;
			pNode = pNext;
		}
	}

private:
	typedef CQueueNode<T>	NODE;
	typedef CQueueNode<T>*	PNODE;

private:
	PNODE	m_pFirst;
	PNODE	m_pLast;
	int		m_iSize;

public:
	void push(const T& data)
	{
		PNODE	pNode = new NODE;

		pNode->m_Data = data;
		
		if (!m_pFirst)
			m_pFirst = pNode;

		if (m_pLast)
			m_pLast->m_pNext = pNode;

		m_pLast = pNode;
		++m_iSize;
	}

	T pop()
	{
		if (empty())
			assert(false);

		T	data = m_pFirst->m_Data;

		PNODE	pNext = m_pFirst->m_pNext;

		delete	m_pFirst;
		m_pFirst = pNext;

		--m_iSize;

		if (empty())
			m_pLast = nullptr;

		return data;
	}

	bool empty()	const
	{
		return m_iSize == 0;
	}

	int size()	const
	{
		return m_iSize;
	}
};

// 환형큐. 배열 기반으로 구현을 하고 배열의 크기를 벗어났을 경우
// 다시 앞으로 돌아와서 데이터를 추가하는 개념이다. 배열 사이즈 내에서
// 빙글빙글 돌면서 데이터를 추가하고 빼고 하게 된다.
// 1개의 노드는 추가와 삭제가 만나야 하므로 더미노드로 사용한다.
template <typename T, int SIZE = 100>
class CCircleQueue
{
public:
	CCircleQueue()
	{
		m_iCapacity = SIZE + 1;
		m_iSize = 0;
		m_iHead = 0;
		m_iTail = 0;
	}

	~CCircleQueue()
	{
	}

private:
	typedef CQueueNode<T>	NODE;
	typedef CQueueNode<T>*	PNODE;

private:
	NODE	m_Array[SIZE + 1];
	int		m_iCapacity;
	int		m_iSize;
	int		m_iHead;
	int		m_iTail;

public:
	void push(const T& data)
	{
		if (full())
			return;

		int	iTail = (m_iTail + 1) % m_iCapacity;

		m_Array[iTail].m_Data = data;
		++m_iSize;

		m_iTail = iTail;
	}

	T pop()
	{
		if (empty())
			assert(false);

		int	iHead = (m_iHead + 1) % m_iCapacity;

		T	data = m_Array[iHead].m_Data;
		--m_iSize;

		m_iHead = iHead;
		return data;
	}

	bool full()	const
	{
		return m_iSize == m_iCapacity - 1;
	}

	bool empty()	const
	{
		return m_iSize == 0;
	}

	int size()	const
	{
		return m_iSize;
	}

	int capacity()	const
	{
		return m_iCapacity;
	}
};
