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

// ȯ��ť. �迭 ������� ������ �ϰ� �迭�� ũ�⸦ ����� ���
// �ٽ� ������ ���ƿͼ� �����͸� �߰��ϴ� �����̴�. �迭 ������ ������
// ���ۺ��� ���鼭 �����͸� �߰��ϰ� ���� �ϰ� �ȴ�.
// 1���� ���� �߰��� ������ ������ �ϹǷ� ���̳��� ����Ѵ�.
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
