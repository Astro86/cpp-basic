#pragma once

#include <assert.h>

/*
AVLTree나 RedBlackTree를 쓰는 이유는 편향트리를 완전이진트리
형태로 바꿔주는 알고리즘이 적용되기 때문에 탐색 성능이 언제나
잘 나오게 만들어 줄 수 있기 때문이다.

AVLTree의 회전에는 2가지가 있다.
좌회전, 우회전.
		Q
	P		C
A		B

위 형태의 트리가 있을 경우 Q를 기준으로 우회전을 하게되면
P가 Q의 자리로 가게 되고 Q는 P의 오른쪽 자식이 된다.
P의 오른쪽 자식인 B가 Q의 왼쪽 자식으로 들어간다.
		P
	A		Q
		B		C

위 형태의 트리가 있을 경우 P르 기준으로 좌회전을 하게되면
Q가 P의 자리로 가게 되고 P는 Q의 왼쪽 자식이 된다.
Q의 왼쪽 자식인 B가 P의 오른쪽 자식으로 들어간다.

회전에는 크게 4가지의 경우가 존재한다.
LL : 왼쪽으로 무너진 경우
LR : 왼쪽 -> 오른쪽 으로 무너진 경우
RR : 오른쪽으로 무너진 경우
RL : 오른쪽 -> 왼쪽 으로 무너진 경우
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

	// 전치
	CAVLTreeIterator<Key, Value>& operator ++ ()
	{
		m_pNode = m_pNode->m_pNext;
		return *this;
	}

	// 후치
	CAVLTreeIterator<Key, Value> operator ++ (int)
	{
		m_pNode = m_pNode->m_pNext;
		return *this;
	}

	// 전치
	CAVLTreeIterator<Key, Value>& operator -- ()
	{
		m_pNode = m_pNode->m_pPrev;
		return *this;
	}

	// 후치
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

		// 기본 이진트리의 삭제 방법대로 먼저 삭제를 한다.
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
			// 더이상 오른쪽에 노드가 없으므로 노드를 생성해서 
			// 오른쪽 자식으로 붙여주고 함수를 종료시킨다.
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

		// 왼쪽으로 무너진 경우
		if (iBF > 0)
		{
			iBF = BalanceFactor(pNode->m_pLeft);

			// iBF값이 +값이 나올 경우 LL이다.
			if (iBF > 0)
			{
				pNode = RotationRight(pNode);
			}

			// 아니면 LR이다.
			else
			{
				RotationLeft(pNode->m_pLeft);
				pNode = RotationRight(pNode);
			}
		}

		// 오른쪽으로 무너진 경우
		else
		{
			iBF = BalanceFactor(pNode->m_pRight);

			// iBF값이 -값이 나올 경우 RR이다.
			if (iBF < 0)
			{
				pNode = RotationLeft(pNode);
			}

			// 아니면 RL이다.
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
		// 기준노드의 부모를 얻어온다.
		PNODE	pParent = pNode->m_pParent;

		// 기준노드의 오른쪽 자식 노드를 얻어온다.
		PNODE	pRight = pNode->m_pRight;

		// 오른쪽 자식 노드의 부모를 기준노드의 부모로 지정한다.
		pRight->m_pParent = pParent;

		// 기준노드가 부모의 왼쪽 자식인지 오른쪽 자식인지를 판단하여
		// 거기에 pRight를 붙여준다.
		if (pParent)
		{
			if (pParent->m_pLeft == pNode)
				pParent->m_pLeft = pRight;

			else
				pParent->m_pRight = pRight;
		}

		// pRight의 왼쪽 자식을 기준노드의 오른쪽 자식으로 붙여준다.
		PNODE	pLeft = pRight->m_pLeft;

		pNode->m_pRight = pLeft;

		if (pLeft)
			pLeft->m_pParent = pNode;

		// pRight의 왼쪽 자식으로 기준노드를 붙여준다.
		pRight->m_pLeft = pNode;
		pNode->m_pParent = pRight;

		if (pNode == m_pRoot)
			m_pRoot = pRight;

		return pRight;
	}

	PNODE RotationRight(PNODE pNode)
	{
		// 기준노드의 부모를 얻어온다.
		PNODE	pParent = pNode->m_pParent;

		// 기준노드의 왼쪽 자식 노드를 얻어온다.
		PNODE	pLeft = pNode->m_pLeft;

		// 왼쪽 자식 노드의 부모를 기준노드의 부모로 지정한다.
		pLeft->m_pParent = pParent;

		// 기준노드가 부모의 왼쪽 자식인지 오른쪽 자식인지를 판단하여
		// 거기에 pLeft를 붙여준다.
		if (pParent)
		{
			if (pParent->m_pLeft == pNode)
				pParent->m_pLeft = pLeft;

			else
				pParent->m_pRight = pLeft;
		}

		// pLeft의 오른쪽 자식을 기준노드의 오른쪽 자식으로 붙여준다.
		PNODE	pRight = pLeft->m_pRight;

		pNode->m_pLeft = pRight;
		
		if (pRight)
			pRight->m_pParent = pNode;

		// pLeft의 왼쪽 자식으로 기준노드를 붙여준다.
		pLeft->m_pLeft = pNode;
		pNode->m_pParent = pLeft;

		// 기준 노드가 Root일 경우 Root를 교체한다.
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
		// 리프노드일 경우
		if (!pNode->m_pLeft && !pNode->m_pRight)
		{
			// 지울 노드가 부모의 왼쪽으로 붙어있을 경우 왼쪽 노드를 nullptr로 처리한다.
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
			// 지울 노드의 값을 현재 노드에 복사를 할 것이므로 
			// 현재 노드 자체가 next가 된다.
			pNext = pNode;

			PNODE	pNext1 = pDeleteNode->m_pNext;
			pNode->m_pNext = pNext1;
			pNext1->m_pPrev = pNode;
		}

		// 지울 노드의 값을 현재 노드에 복사한다.
		pNode->first = pDeleteNode->first;
		pNode->second = pDeleteNode->second;

		PNODE	pParent = pDeleteNode->m_pParent;

		// 지울 노드가 부모의 왼쪽으로 붙어있을 경우 왼쪽 노드를 nullptr로 처리한다.
		if (pDeleteNode->m_pParent->m_pLeft == pDeleteNode)
			pDeleteNode->m_pParent->m_pLeft = nullptr;

		else
			pDeleteNode->m_pParent->m_pRight = nullptr;

		delete	pDeleteNode;

		ReBalance(pParent);

		return pNext;
	}
};
