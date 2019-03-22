#pragma once

#include <assert.h>

// ����Ʈ�� : �ִ� 2���� �ڽĳ�带 ������.
// ��, �� ���� 0������ 2�������� ��带 ������.
// ����Ʈ���� ���� : ���� ����Ʈ��, ���� ����Ʈ��, ��ȭ ����Ʈ��


template <typename Key, typename Value>
class CBinarySearchTreeNode
{
	template <typename Key, typename Value>
	friend class CBinarySearchTree;
	template <typename Key, typename Value>
	friend class CBinarySearchTreeIterator;

private:
	CBinarySearchTreeNode()
	{
		m_pLeft = nullptr;
		m_pRight = nullptr;
		m_pParent = nullptr;
		m_pNext = nullptr;
		m_pPrev = nullptr;
	}
	~CBinarySearchTreeNode()
	{
	}

private:
	CBinarySearchTreeNode<Key, Value>*	m_pLeft;
	CBinarySearchTreeNode<Key, Value>*	m_pRight;
	CBinarySearchTreeNode<Key, Value>*	m_pParent;
	CBinarySearchTreeNode<Key, Value>*	m_pNext;
	CBinarySearchTreeNode<Key, Value>*	m_pPrev;

public:
	Key	first;
	Value second;
};

template <typename Key, typename Value>
class CBinarySearchTreeIterator
{
	template <typename Key, typename Value>
	friend class CBinarySearchTree;

public:
	CBinarySearchTreeIterator()
	{
	}

	~CBinarySearchTreeIterator()
	{
	}

private:
	typedef CBinarySearchTreeNode<Key, Value>*	PNODE;

private:
	PNODE	m_pNode;

public:
	bool operator == (const CBinarySearchTreeIterator<Key, Value>& iter)	const
	{
		return m_pNode == iter.m_pNode;
	}

	bool operator != (const CBinarySearchTreeIterator<Key, Value>& iter)	const
	{
		return m_pNode != iter.m_pNode;
	}

	// ��ġ
	CBinarySearchTreeIterator<Key, Value>& operator ++ ()
	{
		m_pNode = m_pNode->m_pNext;
		return *this;
	}

	// ��ġ
	CBinarySearchTreeIterator<Key, Value> operator ++ (int)
	{
		m_pNode = m_pNode->m_pNext;
		return *this;
	}

	// ��ġ
	CBinarySearchTreeIterator<Key, Value>& operator -- ()
	{
		m_pNode = m_pNode->m_pPrev;
		return *this;
	}

	// ��ġ
	CBinarySearchTreeIterator<Key, Value> operator -- (int)
	{
		m_pNode = m_pNode->m_pPrev;
		return *this;
	}

	PNODE operator -> ()	const
	{
		return m_pNode;
	}
};

template <typename Key, typename Value>
class CBinarySearchTree
{
public:
	CBinarySearchTree()
	{
		m_pRoot = nullptr;
		m_iSize = 0;

		m_pBegin = new NODE;
		m_pEnd = new NODE;

		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;
	}

	~CBinarySearchTree()
	{
		clear();
		delete	m_pBegin;
		delete	m_pEnd;
	}

private:
	typedef CBinarySearchTreeNode<Key, Value>	NODE;
	typedef CBinarySearchTreeNode<Key, Value>*	PNODE;
	struct _tagPair
	{
		Key	first;
		Value second;
	};

public:
	typedef _tagPair	Pair;
	typedef CBinarySearchTreeIterator<Key, Value>	iterator;

private:
	PNODE	m_pRoot;
	// ���̳��� ó���� ���� �˷��ֱ� ���� �뵵�� ����Ѵ�.
	PNODE	m_pBegin;
	PNODE	m_pEnd;
	int		m_iSize;

public:
	void insert(const Key& key, const Value& value)
	{
		if (m_pRoot == nullptr)
		{
			m_pRoot = new NODE;
			m_pRoot->first = key;
			m_pRoot->second = value;

			m_pRoot->m_pNext = m_pEnd;
			m_pEnd->m_pPrev = m_pRoot;

			m_pRoot->m_pPrev = m_pBegin;
			m_pBegin->m_pNext = m_pRoot;
		}

		else
		{
			insert(key, value, m_pRoot);
		}

		++m_iSize;
	}

	void clear()
	{
		clear(m_pRoot);
		m_iSize = 0;
		m_pRoot = nullptr;

		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;
	}

	iterator find(const Key& key)	const
	{
		if (empty())
			assert(false);

		return find(key, m_pRoot);
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

	iterator erase(const iterator& iter)
	{
		if (iter == end())
			return end();

		// ��������� ��� �׳� �����ش�.
		if (!iter.m_pNode->m_pLeft && !iter.m_pNode->m_pRight)
		{
			// ��������ε� �θ� ���� ��쿡�� ���������� ��Ʈ��带 ����� ��Ȳ�̴�.
			if (!iter.m_pNode->m_pParent)
			{
				m_pRoot = nullptr;
				delete	iter.m_pNode;
				--m_iSize;
				return end();
			}

			else
			{
				if (iter.m_pNode->m_pParent->m_pLeft == iter.m_pNode)
					iter.m_pNode->m_pParent->m_pLeft = nullptr;

				else
					iter.m_pNode->m_pParent->m_pRight = nullptr;

				PNODE	pPrev = iter.m_pNode->m_pPrev;
				PNODE	pNext = iter.m_pNode->m_pNext;

				pPrev->m_pNext = pNext;
				pNext->m_pPrev = pPrev;

				delete	iter.m_pNode;
				--m_iSize;
				iterator	iterR;
				iterR.m_pNode = pNext;
				return iterR;
			}
		}

		else
		{
			// ���� �ڽ��� ���� ��� ���� �ڽ��� ���� ū ��带 ���´�.
			PNODE	pDeleteNode = nullptr;
			bool	bLeft = true;
			
			if (iter.m_pNode->m_pLeft)
				pDeleteNode = FindMax(iter.m_pNode->m_pLeft);

			else
			{
				pDeleteNode = FindMin(iter.m_pNode->m_pRight);
				bLeft = false;
			}

			iter->first = pDeleteNode->first;
			iter->second = pDeleteNode->second;

			PNODE	pPrev = pDeleteNode->m_pPrev;
			PNODE	pNext = pDeleteNode->m_pNext;

			pPrev->m_pNext = pNext;
			pNext->m_pPrev = pPrev;

			// ���ʿ��� ������ ���
			if (bLeft)
			{
				// ���� ����� ���� �ڽ��� ���� ��� ���� �ڽ��� ���� ���� ����� ��ġ�� �÷��ش�.
				if (pDeleteNode->m_pLeft)
				{
					pDeleteNode->m_pParent->m_pRight = pDeleteNode->m_pLeft;
				}

				else
				{
					pDeleteNode->m_pParent->m_pRight = nullptr;
				}
			}

			// �����ʿ��� ������ ���
			else
			{
				// ���� ����� ���� �ڽ��� ���� ��� ���� �ڽ��� ���� ���� ����� ��ġ�� �÷��ش�.
				if (pDeleteNode->m_pRight)
				{
					pDeleteNode->m_pParent->m_pLeft = pDeleteNode->m_pRight;
				}

				else
				{
					pDeleteNode->m_pParent->m_pLeft = nullptr;
				}
			}

			delete	pDeleteNode;
			--m_iSize;
			iterator	iterR;
			iterR.m_pNode = pNext;
			return iterR;
		}

		return end();
	}

	bool empty()	const
	{
		return m_iSize == 0;
	}

	int size()	const
	{
		return m_iSize;
	}

	// ���� ��ȸ
	void PreOrder(void (*pFunc)(const Key&, const Value&))
	{
		PreOrder(pFunc, m_pRoot);
	}

	// ���� ��ȸ
	void InOrder(void(*pFunc)(const Key&, const Value&))
	{
		InOrder(pFunc, m_pRoot);
	}

	// ���� ��ȸ
	void PostOrder(void(*pFunc)(const Key&, const Value&))
	{
		PostOrder(pFunc, m_pRoot);
	}

private:
	void insert(const Key& key, const Value& value, PNODE pNode)
	{
		if (!pNode)
			return;

		if (pNode->first > key)
		{
			if (!pNode->m_pLeft)
			{
				PNODE	pNewNode = new NODE;
				pNewNode->first = key;
				pNewNode->second = value;

				pNode->m_pLeft = pNewNode;
				pNewNode->m_pParent = pNode;

				pNewNode->m_pNext = pNode;
				pNewNode->m_pPrev = pNode->m_pPrev;

				pNode->m_pPrev->m_pNext = pNewNode;
				pNode->m_pPrev = pNewNode;
			}

			else
				insert(key, value, pNode->m_pLeft);
		}

		else if (pNode->first <= key)
		{
			// ���̻� �����ʿ� ��尡 �����Ƿ� ��带 �����ؼ� ������ �ڽ����� �ٿ��ְ�
			// �Լ��� �����Ų��.
			if (!pNode->m_pRight)
			{
				PNODE	pNewNode = new NODE;

				pNewNode->first = key;
				pNewNode->second = value;

				pNode->m_pRight = pNewNode;
				pNewNode->m_pParent = pNode;

				pNewNode->m_pPrev = pNode;
				pNewNode->m_pNext = pNode->m_pNext;

				pNode->m_pNext->m_pPrev = pNewNode;
				pNode->m_pNext = pNewNode;
			}

			else
				insert(key, value, pNode->m_pRight);
		}
	}

	void clear(PNODE pNode)
	{
		if (!pNode)
			return;

		clear(pNode->m_pLeft);
		clear(pNode->m_pRight);

		delete	pNode;
	}

	iterator find(const Key& key, PNODE pNode)	const
	{
		if (!pNode)
			return end();			// ������ ȣ��

		if (pNode->first == key)
		{
			iterator	iter;
			iter.m_pNode = pNode;
			return iter;
		}

		else if (pNode->first > key)
			return find(key, pNode->m_pLeft);

		return find(key, pNode->m_pRight);
	}

	void PreOrder(void(*pFunc)(const Key&, const Value&), PNODE pNode)
	{
		if (!pNode)
			return;

		pFunc(pNode->first, pNode->second);
		PreOrder(pFunc, pNode->m_pLeft);
		PreOrder(pFunc, pNode->m_pRight);
	}

	void InOrder(void(*pFunc)(const Key&, const Value&), PNODE pNode)
	{
		if (!pNode)
			return;

		InOrder(pFunc, pNode->m_pLeft);
		pFunc(pNode->first, pNode->second);
		InOrder(pFunc, pNode->m_pRight);
	}

	void PostOrder(void(*pFunc)(const Key&, const Value&), PNODE pNode)
	{
		if (!pNode)
			return;

		PostOrder(pFunc, pNode->m_pLeft);
		PostOrder(pFunc, pNode->m_pRight);
		pFunc(pNode->first, pNode->second);
	}

	PNODE FindMin(PNODE pNode)
	{
		if (!pNode->m_pLeft)
			return pNode;

		return FindMin(pNode->m_pLeft);
	}

	PNODE FindMax(PNODE pNode)
	{
		if (!pNode->m_pRight)
			return pNode;

		return FindMax(pNode->m_pRight);
	}
};
