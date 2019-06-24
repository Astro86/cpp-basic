#include <mutex>

std::mutex m;

// 처음 구현시 링크드리스트 내에 링크드리스트를 인자로 하여 
// 사용할 목적으로 템플릿을 사용하여 구현하였다가 
// 배열의 인자로 링크드리스트를 넣어주게 되며 템플릿을 사용한 의미가
// 없어졌지만 다시 변경하기 번거로워서 그대로 사용하였다.
template <typename T>
class CListNode
{
	// 리스트 클래스를 friend 처리를 해두어서 리스트 클래스에서 노드클래스의
	// private 에 접근할 수 있게 만들어준다.
	template <typename T>
	friend class CLinkedList;
	template <typename T>
	friend class CListIterator;

private:
	CListNode()
	{
		m_pNext = nullptr;
		m_pPrev = nullptr;
	}

	~CListNode()
	{
	}

public:
	T		m_Key;
	T		m_Value;
	CListNode<T>*	m_pNext;
	CListNode<T>*	m_pPrev;
};

template <typename T>
class CListIterator
{
	template <typename T>
	friend class CListNode;
	
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

// iterator를 사용하여 비교 등의 연산을 수행하기위해 
// 연산자 오버로딩을 정의해주었다.
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

	PNODE operator -> ()	const
	{
		return m_pNode;
	}
};
// 링크드리스트를 구현하였다.
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
		delete	m_pBegin;
		delete	m_pEnd;
	}

private:
	typedef CListNode<T>	NODE;
	typedef CListNode<T>*	PNODE;

public:
	typedef CListIterator<T>		iterator;

private:
	// Begin과 End노드는 더미노드로 구현하여 삽입과 삭제를 용이하게
	// 하게끔 하였다.
	PNODE	m_pBegin;
	PNODE	m_pEnd;
	int		m_iSize;

public:
	void push_back(const T& key, const T& value)
	{
		m.lock();
		PNODE	pNode = new NODE;
		pNode->m_Key = key;
		pNode->m_Value = value;

		PNODE	pPrev = m_pEnd->m_pPrev;

		pPrev->m_pNext = pNode;
		pNode->m_pPrev = pPrev;

		pNode->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = pNode;

		++m_iSize;
		m.unlock();
	}

	int size()	const
	{
		return m_iSize;
	}

	bool empty()	const
	{
		return m_iSize == 0;
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

	bool erase(const T& key)
	{
		if (empty())
			return false;

		PNODE	pNode = m_pBegin->m_pNext;

		while (pNode != m_pEnd)
		{
			if (pNode->m_Key == key)
			{
				PNODE	pPrev = pNode->m_pPrev;
				PNODE	pNext = pNode->m_pNext;

				pPrev->m_pNext = pNext;
				pNext->m_pPrev = pPrev;

				delete	pNode;

				--m_iSize;

				return true;
			}

			pNode = pNode->m_pNext;
		}
		return false;
	}

	// sort 함수는 함수포인터를 인자로 받아오게끔 하여
	// 오름차순 및 내림차순 등의 추가적인 정렬을 가능토록
	// 구현하였다.
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
				if (!pFunc(pNode->m_Value, pNode1->m_Value))
				{
					T	key = pNode->m_Key;
					T	value = pNode->m_Value;
					pNode->m_Key = pNode1->m_Key;
					pNode->m_Value = pNode1->m_Value;
					pNode1->m_Key = key;
					pNode1->m_Value = value;
				}
			}
		}
	}
};