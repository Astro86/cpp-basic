#pragma once

#include <assert.h>

/*
더블링크드리스트 : 노드를 양방향으로 연결시켜 놓은 리스트를 말한다.
*/

template <typename T>
class CListNode
{
	// 리스트 클래스를 friend 처리를 해두어서 리스트 클래스에서 노드클래스의
	// private 에 접근할 수 있게 만들어준다.
	template <typename T>
	friend class CLinkedList;
	template <typename T>
	friend class CListIterator;
	template <typename T>
	friend class CListReverseIterator;

private:
	CListNode()
	{
		m_pNext = nullptr;
		m_pPrev = nullptr;
	}

	~CListNode()
	{
	}

private:
	T		m_Data;
	CListNode<T>*	m_pNext;
	CListNode<T>*	m_pPrev;
};

template <typename T>
class CListIterator
{
	template <typename T>
	friend class CLinkedList;

public:
	CListIterator()
	{
	}

	~CListIterator()
	{
	}

private:
	typedef CListNode<T>*	PNODE;
	
private:
	PNODE		m_pNode;

public:
	bool operator == (const CListIterator& iter)	const
	{
		return m_pNode == iter.m_pNode;
	}

	bool operator != (const CListIterator& iter)	const
	{
		return m_pNode != iter.m_pNode;
	}

	CListIterator& operator ++ ()
	{
		m_pNode = m_pNode->m_pNext;
		return *this;
	}

	CListIterator& operator -- ()
	{
		m_pNode = m_pNode->m_pPrev;
		return *this;
	}

	T operator * ()	const
	{
		return m_pNode->m_Data;
	}
};

template <typename T>
class CListReverseIterator
{
	template <typename T>
	friend class CLinkedList;

public:
	CListReverseIterator()
	{
	}

	~CListReverseIterator()
	{
	}

private:
	typedef CListNode<T>*	PNODE;

private:
	PNODE	m_pNode;

public:
	bool operator == (const CListReverseIterator& iter)	const
	{
		return m_pNode == iter.m_pNode;
	}

	bool operator != (const CListReverseIterator& iter)	const
	{
		return m_pNode != iter.m_pNode;
	}
	
	CListReverseIterator& operator ++ ()
	{
		m_pNode = m_pNode->m_pPrev;
		return *this;
	}

	CListReverseIterator& operator -- ()
	{
		m_pNode = m_pNode->m_pNext;
		return *this;
	}

	T operator * ()	const
	{
		return m_pNode->m_Data;
	}
};

template <typename T>
class CLinkedList
{
public:
	CLinkedList()
	{
		m_pBegin = new NODE;
		m_pEnd = new NODE;

		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;

		m_iSize = 0;
	}

	~CLinkedList()
	{
		clear();
		delete	m_pBegin;
		delete	m_pEnd;
	}

private:
	typedef CListNode<T>	NODE;
	typedef CListNode<T>*	PNODE;

public:
	typedef CListIterator<T>		iterator;
	typedef CListReverseIterator<T>	reverse_iterator;

private:
	// Begin과 End노드는 더미노드이다. 실제 데이터를 저장하는 노드가 아니고 리스트에
	// 데이터를 쉽게 추가하기 위한 더미노드로 처음과 가장 끝 노드를 의미한다.
	// 실제 데이터를 가지는 노드들은 Begin과 End 사이에 추가되어야 한다.
	PNODE	m_pBegin;
	PNODE	m_pEnd;
	int		m_iSize;

public:
	void push_back(const T& data)
	{
		PNODE	pNode = new NODE;
		pNode->m_Data = data;

		PNODE	pPrev = m_pEnd->m_pPrev;

		pPrev->m_pNext = pNode;
		pNode->m_pPrev = pPrev;

		pNode->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = pNode;

		++m_iSize;
	}

	void push_front(const T& data)
	{
		PNODE	pNode = new NODE;
		pNode->m_Data = data;

		PNODE	pNext = m_pBegin->m_pNext;

		pNode->m_pNext = pNext;
		pNext->m_pPrev = pNode;

		pNode->m_pPrev = m_pBegin;
		m_pBegin->m_pNext = pNode;
		
		++m_iSize;
	}

	void clear()
	{
		PNODE	pNode = m_pBegin->m_pNext;

		while (pNode != m_pEnd)
		{
			PNODE	pNext = pNode->m_pNext;
			delete	pNode;
			pNode = pNext;
		}

		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;

		m_iSize = 0;
	}

	int size()	const
	{
		return m_iSize;
	}

	bool empty()	const
	{
		return m_iSize == 0;
	}

	void pop_back()
	{
		// assert : false가 들어가면 경고창을 출력하고 프로그램을 종료시켜
		// 버린다.
		if (empty())
			assert(false);

		PNODE	pDeleteNode = m_pEnd->m_pPrev;
		PNODE	pPrev = pDeleteNode->m_pPrev;

		pPrev->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = pPrev;

		delete	pDeleteNode;

		--m_iSize;
	}

	void pop_front()
	{
		if (empty())
			assert(false);

		PNODE	pDeleteNode = m_pBegin->m_pNext;
		PNODE	pNext = pDeleteNode->m_pNext;

		m_pBegin->m_pNext = pNext;
		pNext->m_pPrev = m_pBegin;

		delete	pDeleteNode;

		--m_iSize;
	}

	T front()	const
	{
		if (empty())
			assert(false);

		return m_pBegin->m_pNext->m_Data;
	}

	T back()	const
	{
		if (empty())
			assert(false);

		return m_pEnd->m_pPrev->m_Data;
	}

	iterator begin()	const
	{
		iterator	iter;
		iter.m_pNode = m_pBegin->m_pNext;
		return iter;
	}

	iterator end()	const
	{
		iterator	iter;
		iter.m_pNode = m_pEnd;
		return iter;
	}

	reverse_iterator rbegin()	const
	{
		reverse_iterator	iter;
		iter.m_pNode = m_pEnd->m_pPrev;
		return iter;
	}

	reverse_iterator rend()	const
	{
		reverse_iterator	iter;
		iter.m_pNode = m_pBegin;
		return iter;
	}

	void erase(const T& data)
	{
		if (empty())
			assert(false);

		PNODE	pNode = m_pBegin->m_pNext;

		while (pNode != m_pEnd)
		{
			if (pNode->m_Data == data)
			{
				PNODE	pPrev = pNode->m_pPrev;
				PNODE	pNext = pNode->m_pNext;

				pPrev->m_pNext = pNext;
				pNext->m_pPrev = pPrev;

				delete	pNode;

				--m_iSize;

				break;
			}

			pNode = pNode->m_pNext;
		}
	}

	iterator erase(const iterator& iter)
	{
		PNODE	pPrev = iter.m_pNode->m_pPrev;
		PNODE	pNext = iter.m_pNode->m_pNext;

		pPrev->m_pNext = pNext;
		pNext->m_pPrev = pPrev;

		delete	iter.m_pNode;

		iterator	iter1;
		iter1.m_pNode = pNext;

		--m_iSize;

		return iter1;
	}

	void sort(bool(*pFunc)(const T&, const T&))
	{
		if (m_iSize < 2)
			return;

		PNODE	pNode = m_pBegin->m_pNext;

		for (; pNode != m_pEnd->m_pPrev; pNode = pNode->m_pNext) 
		{
			PNODE	pNode1 = pNode->m_pNext;

			for (; pNode1 != m_pEnd; pNode1 = pNode1->m_pNext)
			{
				if (!pFunc(pNode->m_Data, pNode1->m_Data))
				{
					T	data = pNode->m_Data;
					pNode->m_Data = pNode1->m_Data;
					pNode1->m_Data = data;
				}
			}
		}
	}

	template <typename ClassType>
	void sort(bool (ClassType::*pFunc)(const T&, const T&), ClassType* pObj)
	{
		if (m_iSize < 2)
			return;

		PNODE	pNode = m_pBegin->m_pNext;

		for (; pNode != m_pEnd->m_pPrev; pNode = pNode->m_pNext)
		{
			PNODE	pNode1 = pNode->m_pNext;

			for (; pNode1 != m_pEnd; pNode1 = pNode1->m_pNext)
			{
				if (!pObj->pFunc(pNode->m_Data, pNode1->m_Data))
				{
					T	data = pNode->m_Data;
					pNode->m_Data = pNode1->m_Data;
					pNode1->m_Data = data;
				}
			}
		}
	}
};
