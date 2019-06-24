#pragma once

#include <assert.h>

template <typename T>
class CStackNode
{
	template <typename T>
	friend class CStackArray;
	template <typename T>
	friend class CStackList;

private:
	CStackNode()
	{
		m_pPrev = nullptr;
	}

	~CStackNode()
	{
	}

private:
	T		m_Data;
	CStackNode<T>*	m_pPrev;
};

// 배열기반 Stack 구현. 벡터 기반으로 해서 크기의 한계를 없애야 한다.
template <typename T>
class CStackArray
{
public:
	CStackArray()
	{
		m_iSize = 0;
		m_iCapacity = 2;
		m_pArray = new NODE[m_iCapacity];
	}

	~CStackArray()
	{
		delete[]	m_pArray;
	}

private:
	typedef CStackNode<T>	NODE;
	typedef CStackNode<T>*	PNODE;

private:
	PNODE	m_pArray;
	int		m_iCapacity;
	int		m_iSize;

public:
	void push(const T& data)
	{
		if (m_iSize == m_iCapacity)
		{
			m_iCapacity *= 2;
			PNODE	pArray = new NODE[m_iCapacity];

			memcpy(pArray, m_pArray, sizeof(NODE) * m_iSize);

			delete[]	m_pArray;

			m_pArray = pArray;
		}

		m_pArray[m_iSize].m_Data = data;
		++m_iSize;
	}

	T pop()
	{
		if (empty())
			assert(false);

		--m_iSize;
		return m_pArray[m_iSize].m_Data;
	}

	int size()	const
	{
		return m_iSize;
	}

	bool empty()	const
	{
		return m_iSize == 0;
	}
};

template <typename T>
class CStackList
{
public:
	CStackList()
	{
		m_pNode = nullptr;
		m_iSize = 0;
	}

	~CStackList()
	{
		PNODE	pNode = m_pNode;

		while (pNode)
		{
			PNODE	pNext = pNode->m_pPrev;
			delete	pNode;
			pNode = pNext;
		}
	}

private:
	typedef CStackNode<T>	NODE;
	typedef CStackNode<T>*	PNODE;

private:
	PNODE	m_pNode;
	int		m_iSize;

public:
	void push(const T& data)
	{
		PNODE	pNode = new NODE;
		pNode->m_Data = data;
		pNode->m_pPrev = m_pNode;

		m_pNode = pNode;

		++m_iSize;
	}

	T pop()
	{
		if (empty())
			assert(false);

		PNODE	pNode = m_pNode->m_pPrev;
		T	data = m_pNode->m_Data;
		delete	m_pNode;
		m_pNode = pNode;
		--m_iSize;

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
