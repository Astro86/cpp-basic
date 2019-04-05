#pragma once

#include <assert.h>
#include <time.h>

template <typename T>
class CVectorNode
{
private:
	template <typename T>
	friend class CVector;
	template <typename T>
	friend class CVectorIterator;

private:
	CVectorNode()
	{
		m_pPrev = nullptr;
		m_pNext = nullptr;
	}

	~CVectorNode()
	{
	}

private:
	T	m_Data;
	CVectorNode<T>*	m_pPrev;
	CVectorNode<T>*	m_pNext;
};

template <typename T>
class CVectorIterator
{
	template <typename T>
	friend class CVector;

public:
	CVectorIterator()
	{
	}

	~CVectorIterator()
	{
	}

private:
	typedef CVectorNode<T>*		PNODE;

private:
	PNODE	m_pNode;

public:
	bool operator == (const CVectorIterator<T>& iter)
	{
		return m_pNode == iter.m_pNode;
	}

	bool operator != (const CVectorIterator<T>& iter)
	{
		return m_pNode != iter.m_pNode;
	}

	CVectorIterator<T>& operator ++ ()
	{
		m_pNode = m_pNode->m_pNext;
		return *this;
	}

	CVectorIterator<T>& operator -- ()
	{
		m_pNode = m_pNode->m_pPrev;
		return *this;
	}

	CVectorIterator<T> operator + (int iCount)
	{
		CVectorIterator<T>	iter;
		iter.m_pNode = m_pNode + iCount;
		return iter;
	}

	CVectorIterator<T> operator - (int iCount)
	{
		CVectorIterator<T>	iter;
		iter.m_pNode = m_pNode - iCount;
		return iter;
	}

	CVectorIterator<T>& operator += (int iCount)
	{
		m_pNode += iCount;
		return *this;
	}

	CVectorIterator<T>& operator -= (int iCount)
	{
		m_pNode -= iCount;
		return *this;
	}

	T& operator * ()
	{
		return m_pNode->m_Data;
	}
};

template <typename T>
class CVector
{
public:
	CVector()
	{
		m_iCapacity = 2;
		m_iSize = 0;
		m_pArray = new NODE[m_iCapacity];

		m_pBegin = new NODE;
		m_pEnd = new NODE;

		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;

		srand(time(0));
	}

	~CVector()
	{
		delete[]	m_pArray;
		delete m_pEnd;
		delete m_pBegin;
	}

private:
	typedef CVectorNode<T>	NODE;
	typedef CVectorNode<T>*	PNODE;

public:
	typedef CVectorIterator<T>			iterator;
	typedef const CVectorIterator<T>	const_iterator;

private:
	PNODE	m_pArray;
	PNODE	m_pBegin;
	PNODE	m_pEnd;
	int		m_iCapacity;
	int		m_iSize;

public:
	void push_back(const T& data)
	{
		if (full())
			resize(m_iCapacity * 2);

		m_pArray[m_iSize].m_Data = data;

		if (m_iSize == 0)
		{
			m_pBegin->m_pNext = m_pArray;
			m_pArray[m_iSize].m_pPrev = m_pBegin;
		}

		else
		{
			m_pArray[m_iSize].m_pPrev = &m_pArray[m_iSize - 1];
			m_pArray[m_iSize - 1].m_pNext = &m_pArray[m_iSize];
		}

		m_pEnd->m_pPrev = &m_pArray[m_iSize];
		m_pArray[m_iSize].m_pNext = m_pEnd;

		++m_iSize;
	}

	void resize(int iCapacity)
	{
		m_iCapacity = iCapacity;
		PNODE	pArray = new NODE[iCapacity];

		memcpy(pArray, m_pArray, sizeof(NODE) * m_iSize);

		delete[]	m_pArray;
		m_pArray = pArray;

		for (int i = 1; i < m_iSize - 1; ++i)
		{
			m_pArray[i].m_pPrev = &m_pArray[i - 1];
			m_pArray[i].m_pNext = &m_pArray[i + 1];

			m_pArray[i - 1].m_pNext = &m_pArray[i];
			m_pArray[i + 1].m_pPrev = &m_pArray[i];
		}

		m_pBegin->m_pNext = m_pArray;
		m_pArray[0].m_pPrev = m_pBegin;

		m_pArray[m_iSize - 1].m_pNext = m_pEnd;
		m_pEnd->m_pPrev = &m_pArray[m_iSize - 1];
	}

	void pop_back()
	{
		if (empty())
			assert(false);

		--m_iSize;

		if (m_iSize == 0)
		{
			m_pBegin->m_pNext = m_pEnd;
			m_pEnd->m_pPrev = m_pBegin;
		}

		else
		{
			m_pArray[m_iSize - 1].m_pNext = m_pEnd;
			m_pEnd->m_pPrev = &m_pArray[m_iSize - 1];
		}
	}

	bool full()	const
	{
		return m_iSize == m_iCapacity;
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

	void clear()
	{
		m_iSize = 0;

		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;
	}

	T& front()	const
	{
		if (empty())
			assert(false);

		return m_pArray[0].m_Data;
	}

	T& back()	const
	{
		if (empty())
			assert(false);

		return m_pArray[m_iSize - 1].m_Data;
	}

public:
	iterator begin()
	{
		iterator	iter;
		iter.m_pNode = m_pArray;
		return iter;
	}

	iterator end()
	{
		iterator	iter;
		iter.m_pNode = m_pEnd;
		return iter;
	}

	iterator erase(iterator& iter)
	{
		int	idx = ((int)iter.m_pNode - (int)m_pArray) / sizeof(NODE);

		for (int i = idx; i < m_iSize - 1; ++i)
		{
			m_pArray[i].m_Data = m_pArray[i + 1].m_Data;
		}

		--m_iSize;

		m_pArray[m_iSize - 1].m_pNext = m_pEnd;
		m_pEnd->m_pPrev = &m_pArray[m_iSize - 1];

		return iter;
	}

	void Shuffle()
	{
		int	idx1, idx2;
		T	temp;
		for (int i = 0; i < m_iSize * 2; ++i)
		{
			idx1 = rand() % m_iSize;
			idx2 = rand() % m_iSize;

			temp = m_pArray[idx1].m_Data;
			m_pArray[idx1].m_Data = m_pArray[idx2].m_Data;
			m_pArray[idx2].m_Data = temp;
		}
	}

	void sort(bool(*pFunc)(const T&, const T&))
	{
		for (int i = 0; i < m_iSize - 1; ++i)
		{
			for (int j = i + 1; j < m_iSize; ++j)
			{
				if (pFunc(m_pArray[i].m_Data, m_pArray[j].m_Data))
				{
					T data = m_pArray[i].m_Data;
					m_pArray[i].m_Data = m_pArray[j].m_Data;
					m_pArray[j].m_Data = data;
				}
			}
		}
	}

public:
	T & operator [] (int idx)
	{
		return m_pArray[idx].m_Data;
	}
};
