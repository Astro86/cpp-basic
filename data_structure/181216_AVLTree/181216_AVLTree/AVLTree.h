#pragma once

#include <assert.h>

/*
AVLTree�� RedBlackTree�� ���� ������ ����Ʈ���� ��������Ʈ��
���·� �ٲ��ִ� �˰����� ����Ǳ� ������ Ž�� ������ ������
�� ������ ����� �� �� �ֱ� �����̴�.

AVLTree�� ȸ������ 2������ �ִ�.
��ȸ��, ��ȸ��.
		Q
	P		C
A		B

�� ������ Ʈ���� ���� ��� Q�� �������� ��ȸ���� �ϰԵǸ�
P�� Q�� �ڸ��� ���� �ǰ� Q�� P�� ������ �ڽ��� �ȴ�.
P�� ������ �ڽ��� B�� Q�� ���� �ڽ����� ����.
		P
	A		Q
		B		C

�� ������ Ʈ���� ���� ��� P�� �������� ��ȸ���� �ϰԵǸ�
Q�� P�� �ڸ��� ���� �ǰ� P�� Q�� ���� �ڽ��� �ȴ�.
Q�� ���� �ڽ��� B�� P�� ������ �ڽ����� ����.

ȸ������ ũ�� 4������ ��찡 �����Ѵ�.
LL : �������� ������ ���
LR : ���� -> ������ ���� ������ ���
RR : ���������� ������ ���
RL : ������ -> ���� ���� ������ ���
*/

template <typename Key, typename Value>
class CAVLTreeNode
{
	template <typename Key, typename Value>
	friend class CAVLTree;
	template <typename Key, typename Value>
	friend class CAVLTreeIterator;

private:
	CAVLTreeNode()
	{
		m_pParent = nullptr;
		m_pLeft = nullptr;
		m_pRight = nullptr;
		m_pPrev = nullptr;
		m_pNext = nullptr;
	}

	~CAVLTreeNode()
	{
	}

private:
	CAVLTreeNode<Key, Value>*	m_pParent;
	CAVLTreeNode<Key, Value>*	m_pLeft;
	CAVLTreeNode<Key, Value>*	m_pRight;
	CAVLTreeNode<Key, Value>*	m_pPrev;
	CAVLTreeNode<Key, Value>*	m_pNext;

public:
	Key		first;
	Value	second;
};

template <typename Key, typename Value>
class CAVLTreeIterator
{
	template <typename Key, typename Value>
	friend class CAVLTree;
	
public:
	CAVLTreeIterator()
	{
	}

	~CAVLTreeIterator()
	{
	}

private:
	typedef CAVLTreeNode<Key, Value>*	PNODE;

private:
	PNODE	m_pNode;

public:
	bool operator == (const CAVLTreeIterator<Key, Value>& iter)	const
	{
		return m_pNode == iter.m_pNode;
	}

	bool operator != (const CAVLTreeIterator<Key, Value>& iter)	const
	{
		return m_pNode != iter.m_pNode;
	}

	// ��ġ
	CAVLTreeIterator<Key, Value>& operator ++ ()
	{
		m_pNode = m_pNode->m_pNext;
		return *this;
	}

	// ��ġ
	CAVLTreeIterator<Key, Value> operator ++ (int)
	{
		m_pNode = m_pNode->m_pNext;
		return *this;
	}

	// ��ġ
	CAVLTreeIterator<Key, Value>& operator -- ()
	{
		m_pNode = m_pNode->m_pPrev;
		return *this;
	}

	// ��ġ
	CAVLTreeIterator<Key, Value> operator -- (int)
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
class CAVLTree
{
public:
	CAVLTree()
	{
		m_pRoot = nullptr;
		m_iSize = 0;

		m_pBegin = new NODE;
		m_pEnd = new NODE;

		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;
	}

	~CAVLTree()
	{
		PNODE	pNode = m_pBegin;

		while (pNode)
		{
			PNODE	pNext = pNode->m_pNext;
			delete	pNode;
			pNode = pNext;
		}

		m_pBegin = nullptr;
		m_pEnd = nullptr;
		m_iSize = 0;
	}

private:
	typedef CAVLTreeNode<Key, Value>	NODE;
	typedef CAVLTreeNode<Key, Value>*	PNODE;

public:
	typedef CAVLTreeIterator<Key, Value>	iterator;

private:
	PNODE	m_pRoot;
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

	bool empty()	const
	{
		return m_iSize == 0;
	}

	int size()	const
	{
		return m_iSize;
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

	iterator find(const Key& key)	const
	{
		PNODE pNode = find(key, m_pRoot);
		
		if (!pNode)
			return end();
		iterator	iter;
		iter.m_pNode = pNode;
		return iter;
	}

	iterator erase(const Key& key)
	{
		if (empty())
			return end();

		iterator	iter = find(key);

		if (iter == end())
			return end();

		return erase(iter);
	}

	iterator erase(const iterator& iter)
	{
		if (empty())
			return end();

		else if (iter == end())
			return iter;

		// �⺻ ����Ʈ���� ���� ������ ���� ������ �Ѵ�.
		PNODE	pNode = iter.m_pNode;

		PNODE	pNext = erase(iter->first, pNode);

		--m_iSize;
		if (m_iSize == 0)
			m_pRoot = nullptr;

		iterator	iter1;
		iter1.m_pNode = pNext;
		return iter1;
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
			// ���̻� �����ʿ� ��尡 �����Ƿ� ��带 �����ؼ� 
			// ������ �ڽ����� �ٿ��ְ� �Լ��� �����Ų��.
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

		Balance(pNode);
	}

	int GetHeight(PNODE pNode)
	{
		if (!pNode)
			return 0;

		int	iLeft = GetHeight(pNode->m_pLeft);
		int	iRight = GetHeight(pNode->m_pRight);

		return iLeft < iRight ? iRight + 1 : iLeft + 1;
	}

	int BalanceFactor(PNODE pNode)
	{
		return GetHeight(pNode->m_pLeft) - GetHeight(pNode->m_pRight);
	}

	void Balance(PNODE pNode)
	{
		int	iBF = BalanceFactor(pNode);

		if (abs(iBF) < 2)
			return;

		// �������� ������ ���
		if (iBF > 0)
		{
			iBF = BalanceFactor(pNode->m_pLeft);

			// iBF���� +���� ���� ��� LL�̴�.
			if (iBF > 0)
			{
				pNode = RotationRight(pNode);
			}

			// �ƴϸ� LR�̴�.
			else
			{
				RotationLeft(pNode->m_pLeft);
				pNode = RotationRight(pNode);
			}
		}

		// ���������� ������ ���
		else
		{
			iBF = BalanceFactor(pNode->m_pRight);

			// iBF���� -���� ���� ��� RR�̴�.
			if (iBF < 0)
			{
				pNode = RotationLeft(pNode);
			}

			// �ƴϸ� RL�̴�.
			else
			{
				RotationRight(pNode->m_pRight);
				pNode = RotationLeft(pNode);
			}
		}
	}

	void ReBalance(PNODE pNode)
	{
		if (!pNode)
			return;

		Balance(pNode);
		ReBalance(pNode->m_pParent);
	}

	PNODE RotationLeft(PNODE pNode)
	{
		// ���س���� �θ� ���´�.
		PNODE	pParent = pNode->m_pParent;

		// ���س���� ������ �ڽ� ��带 ���´�.
		PNODE	pRight = pNode->m_pRight;

		// ������ �ڽ� ����� �θ� ���س���� �θ�� �����Ѵ�.
		pRight->m_pParent = pParent;

		// ���س�尡 �θ��� ���� �ڽ����� ������ �ڽ������� �Ǵ��Ͽ�
		// �ű⿡ pRight�� �ٿ��ش�.
		if (pParent)
		{
			if (pParent->m_pLeft == pNode)
				pParent->m_pLeft = pRight;

			else
				pParent->m_pRight = pRight;
		}

		// pRight�� ���� �ڽ��� ���س���� ������ �ڽ����� �ٿ��ش�.
		PNODE	pLeft = pRight->m_pLeft;

		pNode->m_pRight = pLeft;

		if (pLeft)
			pLeft->m_pParent = pNode;

		// pRight�� ���� �ڽ����� ���س�带 �ٿ��ش�.
		pRight->m_pLeft = pNode;
		pNode->m_pParent = pRight;

		if (pNode == m_pRoot)
			m_pRoot = pRight;

		return pRight;
	}

	PNODE RotationRight(PNODE pNode)
	{
		// ���س���� �θ� ���´�.
		PNODE	pParent = pNode->m_pParent;

		// ���س���� ���� �ڽ� ��带 ���´�.
		PNODE	pLeft = pNode->m_pLeft;

		// ���� �ڽ� ����� �θ� ���س���� �θ�� �����Ѵ�.
		pLeft->m_pParent = pParent;

		// ���س�尡 �θ��� ���� �ڽ����� ������ �ڽ������� �Ǵ��Ͽ�
		// �ű⿡ pLeft�� �ٿ��ش�.
		if (pParent)
		{
			if (pParent->m_pLeft == pNode)
				pParent->m_pLeft = pLeft;

			else
				pParent->m_pRight = pLeft;
		}

		// pLeft�� ������ �ڽ��� ���س���� ������ �ڽ����� �ٿ��ش�.
		PNODE	pRight = pLeft->m_pRight;

		pNode->m_pLeft = pRight;
		
		if (pRight)
			pRight->m_pParent = pNode;

		// pLeft�� ���� �ڽ����� ���س�带 �ٿ��ش�.
		pLeft->m_pLeft = pNode;
		pNode->m_pParent = pLeft;

		// ���� ��尡 Root�� ��� Root�� ��ü�Ѵ�.
		if (pNode == m_pRoot)
			m_pRoot = pLeft;

		return pLeft;
	}

	PNODE find(const Key& key, PNODE pNode)	const
	{
		if (!pNode)
			return nullptr;

		if (pNode->first == key)
			return pNode;

		else if (pNode->first > key)
			return find(key, pNode->m_pLeft);

		return find(key, pNode->m_pRight);
	}

	PNODE SearchMin(PNODE pNode)
	{
		if (pNode->m_pLeft)
			return SearchMin(pNode->m_pLeft);

		return pNode;
	}

	PNODE SearchMax(PNODE pNode)
	{
		if (pNode->m_pRight)
			return SearchMax(pNode->m_pRight);

		return pNode;
	}

	PNODE erase(const Key& key, PNODE pNode)
	{
		// ��������� ���
		if (!pNode->m_pLeft && !pNode->m_pRight)
		{
			// ���� ��尡 �θ��� �������� �پ����� ��� ���� ��带 nullptr�� ó���Ѵ�.
			if (pNode->m_pParent)
			{
				if (pNode->m_pParent->m_pLeft == pNode)
					pNode->m_pParent->m_pLeft = nullptr;

				else
					pNode->m_pParent->m_pRight = nullptr;
			}

			PNODE	pParent = pNode->m_pParent;

			PNODE	pNext = pNode->m_pNext;
			PNODE	pPrev = pNode->m_pPrev;

			pPrev->m_pNext = pNext;
			pNext->m_pPrev = pPrev;

			delete	pNode;

			ReBalance(pParent);
			return pNext;
		}

		PNODE	pDeleteNode = nullptr;
		PNODE	pNext = nullptr;

		if (pNode->m_pLeft)
		{
			pNext = pNode->m_pNext;
			pDeleteNode = pNode->m_pPrev;

			PNODE	pPrev = pDeleteNode->m_pPrev;
			pPrev->m_pNext = pNode;
			pNode->m_pPrev = pPrev;
		}

		else
		{
			pDeleteNode = pNode->m_pNext;
			// ���� ����� ���� ���� ��忡 ���縦 �� ���̹Ƿ� 
			// ���� ��� ��ü�� next�� �ȴ�.
			pNext = pNode;

			PNODE	pNext1 = pDeleteNode->m_pNext;
			pNode->m_pNext = pNext1;
			pNext1->m_pPrev = pNode;
		}

		// ���� ����� ���� ���� ��忡 �����Ѵ�.
		pNode->first = pDeleteNode->first;
		pNode->second = pDeleteNode->second;

		PNODE	pParent = pDeleteNode->m_pParent;

		// ���� ��尡 �θ��� �������� �پ����� ��� ���� ��带 nullptr�� ó���Ѵ�.
		if (pDeleteNode->m_pParent->m_pLeft == pDeleteNode)
			pDeleteNode->m_pParent->m_pLeft = nullptr;

		else
			pDeleteNode->m_pParent->m_pRight = nullptr;

		delete	pDeleteNode;

		ReBalance(pParent);

		return pNext;
	}
};
