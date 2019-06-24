#pragma once

#include <assert.h>

/*
����ũ�帮��Ʈ : ��带 ��������� ������� ���� ����Ʈ�� ���Ѵ�.
*/

template <typename T>
class CListNode
{
	// ����Ʈ Ŭ������ friend ó���� �صξ ����Ʈ Ŭ�������� ���Ŭ������
	// private �� ������ �� �ְ� ������ش�.
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
	// Begin�� End���� ���̳���̴�. ���� �����͸� �����ϴ� ��尡 �ƴϰ� ����Ʈ��
	// �����͸� ���� �߰��ϱ� ���� ���̳��� ó���� ���� �� ��带 �ǹ��Ѵ�.
	// ���� �����͸� ������ ������ Begin�� End ���̿� �߰��Ǿ�� �Ѵ�.
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
		// assert : false�� ���� ���â�� ����ϰ� ���α׷��� �������
		// ������.
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
