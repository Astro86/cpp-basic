#pragma once

#include <assert.h>

enum NODE_COLOR
{
	RED,
	BLACK
};

template <typename Key, typename Value>
class CRBBTreeNode
{
	template <typename Key, typename Value>
	friend class CRBBTree;
	template <typename Key, typename Value>
	friend class CRBBTreeIterator;

private:
	CRBBTreeNode()
	{
		m_pParent = nullptr;
		m_pLeft = nullptr;
		m_pRight = nullptr;
		m_pPrev = nullptr;
		m_pNext = nullptr;
		m_eColor = RED;
	}
	~CRBBTreeNode()
	{
	}

private:
	CRBBTreeNode<Key, Value>*	m_pParent;
	CRBBTreeNode<Key, Value>*	m_pLeft;
	CRBBTreeNode<Key, Value>*	m_pRight;
	CRBBTreeNode<Key, Value>*	m_pPrev;
	CRBBTreeNode<Key, Value>*	m_pNext;
	NODE_COLOR					m_eColor;

public:
	Key		first;
	Value	second;
};

template <typename Key, typename Value>
class CRBBTreeIterator
{
	template <typename Key, typename Value>
	friend class CRBBTree;

public:
	CRBBTreeIterator()
	{
	}

	~CRBBTreeIterator()
	{
	}

private:
	typedef CRBBTreeNode<Key, Value>*	PNODE;

private:
	PNODE	m_pNode;

public:
	bool operator == (const CRBBTreeIterator<Key, Value>& iter)	const
	{
		return m_pNode == iter.m_pNode;
	}

	bool operator != (const CRBBTreeIterator<Key, Value>& iter)	const
	{
		return m_pNode != iter.m_pNode;
	}

	// 전치
	CRBBTreeIterator<Key, Value>& operator ++ ()
	{
		m_pNode = m_pNode->m_pNext;
		return *this;
	}

	// 후치
	CRBBTreeIterator<Key, Value> operator ++ (int)
	{
		m_pNode = m_pNode->m_pNext;
		return *this;
	}

	// 전치
	CRBBTreeIterator<Key, Value>& operator -- ()
	{
		m_pNode = m_pNode->m_pPrev;
		return *this;
	}

	// 후치
	CRBBTreeIterator<Key, Value> operator -- (int)
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
class CRBBTree
{
public:
	CRBBTree()
	{
		m_pRoot = nullptr;
		m_iSize = 0;

		// 더미노드 생성
		Nil = new NODE;
		Nil->m_eColor = BLACK;

		m_pBegin = new NODE;
		m_pEnd = new NODE;

		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;
	}

	~CRBBTree()
	{
		clear();
		delete	Nil;
		delete	m_pBegin;
		delete	m_pEnd;
	}

private:
	typedef CRBBTreeNode<Key, Value>	NODE;
	typedef CRBBTreeNode<Key, Value>*	PNODE;

public:
	typedef CRBBTreeIterator<Key, Value>	iterator;

private:
	PNODE		m_pRoot;
	int			m_iSize;
	PNODE		Nil;
	PNODE		m_pBegin;
	PNODE		m_pEnd;

public:
	void insert(const Key& first, const Value& second)
	{
		if (!m_pRoot)
		{
			m_pRoot = new NODE;

			m_pRoot->m_eColor = BLACK;
			m_pRoot->first = first;
			m_pRoot->second = second;

			m_pRoot->m_pLeft = Nil;
			m_pRoot->m_pRight = Nil;

			m_pBegin->m_pNext = m_pRoot;
			m_pRoot->m_pPrev = m_pBegin;

			m_pRoot->m_pNext = m_pEnd;
			m_pEnd->m_pPrev = m_pRoot;
		}

		else
		{
			PNODE	pNode = insert(first, second, m_pRoot);

			Balance(pNode);

			m_pRoot->m_eColor = BLACK;
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

	bool empty()	const
	{
		return m_iSize == 0;
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

	iterator erase(const Key& key)
	{
		iterator	iter = find(key);

		if (iter == end())
			return end();

		return erase(iter);
	}

	iterator erase(iterator& iter)
	{
		if (iter == end())
			return end();

		// 리프노드일 경우라면 그냥 지우면 된다.
		if (iter.m_pNode->m_pLeft == Nil && iter.m_pNode->m_pRight)
		{
			// 리프노드인데 부모가 없다면 Root노드 딱 1개만 추가되어 있는 상태인 것이다.
			if (!iter.m_pNode->m_pParent)
			{
				m_pRoot = nullptr;
				delete	iter.m_pNode;
				--m_iSize;
				return end();
			}

			else
			{
				// 지울 노드의 부모로부터 현재 지울 노드의 연결을 끊어준다.
				if (iter.m_pNode->m_pParent->m_pLeft == iter.m_pNode)
					iter.m_pNode->m_pParent->m_pLeft = Nil;

				else
					iter.m_pNode->m_pParent->m_pRight = Nil;

				// 지울 노드의 이전노드와 다음노드를 연결한다.
				PNODE	pPrev = iter.m_pNode->m_pPrev;
				PNODE	pNext = iter.m_pNode->m_pNext;

				pPrev->m_pNext = pNext;
				pNext->m_pPrev = pPrev;

				delete	iter.m_pNode;
				--m_iSize;
				iter.m_pNode = pNext;
				return iter;
			}
		}

		// 리프노드가 아닐 경우
		bool	bLeft = false;
		PNODE	pDeleteNode = nullptr;

		// 왼쪽 노드가 있을 경우 왼쪽에서 가장 큰 노드를 찾는다.
		if (iter.m_pNode->m_pLeft != Nil)
		{
			bLeft = true;
			pDeleteNode = FindLeftMax(iter.m_pNode->m_pLeft);
		}

		else
			pDeleteNode = FindRightMin(iter.m_pNode->m_pRight);

		// 지울 노드의 Color를 미리 받아둔다.
		NODE_COLOR	eDeleteColor = pDeleteNode->m_eColor;

		// 찾아온 노드의 값으로 지울 노드의 값을 대체한다.
		iter.m_pNode->first = pDeleteNode->first;
		iter.m_pNode->second = pDeleteNode->second;

		if (iter.m_pNode->m_eColor == BLACK)
			iter.m_pNode->m_eColor = BLACK;

		else
			iter.m_pNode->m_eColor = pDeleteNode->m_eColor;

		iterator	iterResult;
		iterResult.m_pNode = iter.m_pNode;

		// 만약 왼쪽에서 가장 큰 노드를 찾아왔다면 지울 노드의 다음 노드를 얻어와서 iterator를 만들어주고
		// 반환해야 한다.
		if (bLeft)
			iterResult.m_pNode = iter.m_pNode->m_pNext;

		PNODE	pDeleteChild = nullptr;

		// 왼쪽에서 가장 큰 노드를 얻어올 경우 오른쪽 자식은 Nil이겠지만 왼쪽자식은 있을 수도 있다.
		// 반대의 경우도 마찬가지다.
		if (bLeft)
		{
			if (pDeleteNode->m_pLeft != Nil)
				pDeleteChild = pDeleteNode->m_pLeft;
		}

		else if(pDeleteNode->m_pRight != Nil)
			pDeleteChild = pDeleteNode->m_pRight;

		if (pDeleteChild)
		{
			// 현재 얻어온 노드의 부모를 지울 노드의 부모로 지정한다.
			pDeleteChild->m_pParent = pDeleteNode->m_pParent;

			// 지울 노드가 부모의 왼쪽인지 오른쪽인지에 따라 자식으로 붙여준다.
			if (pDeleteNode->m_pParent->m_pLeft == pDeleteNode)
				pDeleteNode->m_pParent->m_pLeft = pDeleteChild;

			else
				pDeleteNode->m_pParent->m_pRight = pDeleteChild;
		}

		else
		{
			// 지울 노드가 부모의 왼쪽인지 오른쪽인지에 따라 자식으로 붙여준다.
			if (pDeleteNode->m_pParent->m_pLeft == pDeleteNode)
				pDeleteNode->m_pParent->m_pLeft = Nil;

			else
				pDeleteNode->m_pParent->m_pRight = Nil;
		}

		// 삭제할 노드가 검은색일 경우 이중흑색노드가 된다.
		if (eDeleteColor == BLACK)
		{
			_erase(iter.m_pNode);
		}

		PNODE	pPrev = pDeleteNode->m_pPrev;
		PNODE	pNext = pDeleteNode->m_pNext;

		pPrev->m_pNext = pNext;
		pNext->m_pPrev = pPrev;

		delete	pDeleteNode;
		--m_iSize;
		return iterResult;
	}

private:
	PNODE insert(const Key& first, const Value& second, PNODE pNode)
	{
		if(pNode == Nil)
			return Nil;

		if (pNode->first > first)
		{
			if (pNode->m_pLeft == Nil)
			{
				PNODE	pNewNode = new NODE;

				pNewNode->m_pLeft = Nil;
				pNewNode->m_pRight = Nil;

				pNewNode->first = first;
				pNewNode->second = second;

				pNewNode->m_pParent = pNode;

				PNODE	pPrev = pNode->m_pPrev;

				pNewNode->m_pNext = pNode;
				pNewNode->m_pPrev = pPrev;

				pPrev->m_pNext = pNewNode;
				pNode->m_pPrev = pNewNode;

				pNode->m_pLeft = pNewNode;

				return pNewNode;
			}

			else
				return insert(first, second, pNode->m_pLeft);
		}

		else
		{
			if (pNode->m_pRight == Nil)
			{
				PNODE	pNewNode = new NODE;

				pNewNode->m_pLeft = Nil;
				pNewNode->m_pRight = Nil;

				pNewNode->first = first;
				pNewNode->second = second;

				pNewNode->m_pParent = pNode;

				PNODE	pNext = pNode->m_pNext;

				pNewNode->m_pNext = pNext;
				pNewNode->m_pPrev = pNode;

				pNode->m_pNext = pNewNode;
				pNext->m_pPrev = pNewNode;

				pNode->m_pRight = pNewNode;

				return pNewNode;
			}

			else
				return insert(first, second, pNode->m_pRight);
		}

		return Nil;
	}

	void Balance(PNODE pNode)
	{
		if (!pNode)
			return;

		else if (!pNode->m_pParent)
			return;

		else if (pNode->m_pParent->m_eColor == BLACK)
			return;

		// 만약 조부노드가 없다면 탐색 종료한다.
		PNODE	pPParent = pNode->m_pParent->m_pParent;

		if (!pPParent)
			return;

		// 부모노드가 조부노드의 왼쪽인지 오른쪽인지를 판단한다.
		if (pPParent->m_pLeft == pNode->m_pParent)
		{
			PNODE	pUncle = pPParent->m_pRight;

			// case 1. 삼촌노드가 RED일 경우
			if (pUncle->m_eColor == RED)
			{
				// 부모노드와 삼촌노드를 BLACK으로 칠한다.
				pUncle->m_eColor = BLACK;
				pNode->m_pParent->m_eColor = BLACK;

				// 조부노드를 빨간색으로 칠한다.
				pPParent->m_eColor = RED;

				// 조부노드를 기준노드로 해서 다시 탐색을 시작한다.
				Balance(pPParent);
			}

			// 삼촌노드가 BLACK일 경우
			else
			{
				// case 2. 새로 삽입한 노드가 부모의 오른쪽 자식일 경우
				if (pNode == pNode->m_pParent->m_pRight)
				{
					// 부모노드를 기준으로 좌회전하여 case3번으로 변경해준다.
					pNode = RotationLeft(pNode->m_pParent);
				}

				// case 3. 새로 삽입한 노드가 부모의 왼쪽 자식일 경우
				// 부모를 BLACK, 조부를 RED로 칠한다.
				pNode->m_pParent->m_eColor = BLACK;
				pPParent->m_eColor = RED;

				// 조부를 기준으로 오른쪽으로 회전시킨다.
				pNode = RotationRight(pPParent);

				// 조부노드를 기준으로 재귀호출한다.
				// 조부는 회전되서 아래로 내려갔으므로 여기서는 조부를 찾아서 넣어준다.
				Balance(pNode->m_pParent->m_pParent);
			}
		}

		// 부모노드가 조부노드의 오른쪽 자식일 경우
		else
		{
			PNODE	pUncle = pPParent->m_pLeft;

			// case 1. 삼촌노드가 RED일 경우
			if (pUncle->m_eColor == RED)
			{
				// 부모노드와 삼촌노드를 BLACK으로 칠한다.
				pUncle->m_eColor = BLACK;
				pNode->m_pParent->m_eColor = BLACK;

				// 조부노드를 빨간색으로 칠한다.
				pPParent->m_eColor = RED;

				// 조부노드를 기준노드로 해서 다시 탐색을 시작한다.
				Balance(pPParent);
			}

			// 삼촌노드가 BLACK일 경우
			else
			{
				// case 2. 새로 삽입한 노드가 부모의 왼쪽 자식일 경우
				if (pNode == pNode->m_pParent->m_pLeft)
				{
					// 부모노드를 기준으로 우회전하여 case3번으로 변경해준다.
					pNode = RotationRight(pNode->m_pParent);
				}

				// case 3. 새로 삽입한 노드가 부모의 오른쪽 자식일 경우
				// 부모를 BLACK, 조부를 RED로 칠한다.
				pNode->m_pParent->m_eColor = BLACK;
				pPParent->m_eColor = RED;

				// 조부를 기준으로 왼쪽으로 회전시킨다.
				pNode = RotationLeft(pPParent);

				// 조부노드를 기준으로 재귀호출한다.
				// 조부는 회전되서 아래로 내려갔으므로 여기서는 조부를 찾아서 넣어준다.
				Balance(pNode->m_pParent->m_pParent);
			}
		}
	}

	PNODE RotationLeft(PNODE pNode)
	{
		// 기준노드의 오른쪽 노드를 얻어온다.
		PNODE	pRight = pNode->m_pRight;

		// 오른쪽 노드의 왼쪽 자식을 얻어온다.
		PNODE	pRightChildL = pRight->m_pLeft;

		// 기준노드를 오른쪽 자식의 왼쪽 자식으로 준다.
		pRight->m_pLeft = pNode;

		// 기준노드가 부모의 왼쪽 자식인지 오른쪽 자식인지를 판단해서 기준노드의 부모의 자식으로
		// 오른쪽 노드를 준다.
		if (pNode->m_pParent)
		{
			if (pNode->m_pParent->m_pLeft == pNode)
				pNode->m_pParent->m_pLeft = pRight;

			else
				pNode->m_pParent->m_pRight = pRight;
		}

		// 기준노드가 Root일 경우 기존 m_pRoot를 pRight로 교체해준다.
		else
			m_pRoot = pRight;

		// 오른쪽 노드의 부모를 기준노드의 부모로 준다.
		pRight->m_pParent = pNode->m_pParent;
		pNode->m_pParent = pRight;

		// 오른쪽 노드의 왼쪽 자식을 기준노드의 오른쪽 자식으로 준다.
		pNode->m_pRight = pRightChildL;
		pRightChildL->m_pParent = pNode;

		// 회전을 하고 나면 기준노드가 바뀌므로 리턴해준다.
		return pNode;
	}

	PNODE RotationRight(PNODE pNode)
	{
		// 기준노드의 왼쪽 노드를 얻어온다.
		PNODE	pLeft = pNode->m_pLeft;

		// 왼쪽 노드의 오른쪽 자식을 얻어온다.
		PNODE	pLeftChildR = pLeft->m_pRight;

		// 기준노드를 오른쪽 자식의 왼쪽 자식으로 준다.
		pLeft->m_pRight = pNode;

		// 기준노드가 부모의 왼쪽 자식인지 오른쪽 자식인지를 판단해서 기준노드의 부모의 자식으로
		// 오른쪽 노드를 준다.
		if (pNode->m_pParent)
		{
			if (pNode->m_pParent->m_pLeft == pNode)
				pNode->m_pParent->m_pLeft = pLeft;

			else
				pNode->m_pParent->m_pRight = pLeft;
		}

		// 기준노드가 Root일 경우 기존 m_pRoot를 pLeft로 교체해준다.
		else
			m_pRoot = pLeft;

		// 왼쪽 노드의 부모를 기준노드의 부모로 준다.
		pLeft->m_pParent = pNode->m_pParent;
		pNode->m_pParent = pLeft;

		// 왼쪽 노드의 오른쪽 자식을 기준노드의 왼쪽 자식으로 준다.
		pNode->m_pLeft = pLeftChildR;
		pLeftChildR->m_pParent = pNode;

		// 회전을 하고 나면 기준노드가 바뀌므로 리턴해준다.
		return pNode;
	}

	void clear(PNODE pNode)
	{
		if (!pNode || pNode == Nil)
			return;

		clear(pNode->m_pLeft);
		clear(pNode->m_pRight);

		delete	pNode;
	}
	
	iterator find(const Key& key, PNODE pNode)	const
	{
		if (pNode == Nil)
			return end();			// 생성자 호출

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

	void _erase(PNODE pNode)
	{
		if (pNode == m_pRoot || pNode->m_eColor == RED)
			return;

		PNODE	pSibling = nullptr;

		// 이중 흑색노드가 부모의 왼쪽 자식일 경우
		if (pNode == pNode->m_pParent->m_pLeft)
		{
			// 형제노드를 얻어온다.
			pSibling = pNode->m_pParent->m_pRight;

			// case change. 이중흑색노드의 형제가 RED인 경우
			if (pSibling->m_eColor == RED)
			{
				pSibling->m_eColor = BLACK;
				pNode->m_pParent->m_eColor = RED;

				// 부모노드를 좌회전한다.
				RotationLeft(pNode->m_pParent);

				// 형제가 바뀌었으므로 형제를 다시 얻어온다.
				pSibling = pNode->m_pParent->m_pRight;
			}

			// case a. 이중흑색노드의 형제가 BLACK이고 양쪽 자식 모두 BLACK인 경우
			if (pSibling->m_pLeft->m_eColor == BLACK && pSibling->m_pRight->m_eColor == BLACK)
			{
				// 형제를 레드로 바꾼다.
				if (pSibling != Nil)
					pSibling->m_eColor = RED;

				// 이중흑색노드 검은색 1개를 부모에게 전달한다.
				// 빨간색일 경우에는 검은색으로 칠하고 탐색을 종료한다.
				if (pNode->m_pParent->m_eColor == RED)
				{
					pNode->m_pParent->m_eColor = BLACK;
					return;
				}

				// 부모가 검은색일 경우에는 부모 기준으로 다시 검사를 시작한다.
				_erase(pNode->m_pParent);
			}

			// case b. 이중흑색노드의 형제가 BLACK이고 형제의 왼쪽 자식이 RED인 경우
			else if (pSibling->m_pLeft->m_eColor == RED)
			{
				// 형제를 빨간색으로 칠한다.
				if (pSibling != Nil)
					pSibling->m_eColor = RED;

				// 형제의 왼쪽 자식을 검은색으로 칠한다.
				pSibling->m_pLeft->m_eColor = BLACK;

				// 형제노드 기준으로 우회전한다.
				RotationRight(pSibling);

				_erase(pNode);
			}

			// case c. 이중흑색노드의 형제가 BLACK이고 형제의 오른쪽 자식이 RED인 경우
			else if (pSibling->m_pRight->m_eColor == RED)
			{
				// 부모의 색을 형제에게 넘긴다.
				if (pSibling != Nil)
					pSibling->m_eColor = pNode->m_pParent->m_eColor;

				// 부모노드와 형제의 오른쪽 자식을 검은색으로 칠한다.
				pNode->m_pParent->m_eColor = BLACK;
				pSibling->m_pRight->m_eColor = BLACK;

				// 부모노드 기준으로 좌회전한다.
				RotationLeft(pNode->m_pParent);
			}
		}

		// 이중 흑색노드가 부모의 오른쪽 자식일 경우
		else
		{
			// 형제노드를 얻어온다.
			pSibling = pNode->m_pParent->m_pLeft;

			// case change. 이중흑색노드의 형제가 RED인 경우
			if (pSibling->m_eColor == RED)
			{
				pSibling->m_eColor = BLACK;
				pNode->m_pParent->m_eColor = RED;

				// 부모노드를 우회전한다.
				RotationRight(pNode->m_pParent);

				// 형제가 바뀌었으므로 형제를 다시 얻어온다.
				pSibling = pNode->m_pParent->m_pLeft;
			}

			// case a. 이중흑색노드의 형제가 BLACK이고 양쪽 자식 모두 BLACK인 경우
			if (pSibling->m_pLeft->m_eColor == BLACK && pSibling->m_pRight->m_eColor == BLACK)
			{
				// 형제를 레드로 바꾼다.
				if (pSibling != Nil)
					pSibling->m_eColor = RED;

				// 이중흑색노드 검은색 1개를 부모에게 전달한다.
				// 빨간색일 경우에는 검은색으로 칠하고 탐색을 종료한다.
				if (pNode->m_pParent->m_eColor == RED)
				{
					pNode->m_pParent->m_eColor = BLACK;
					return;
				}

				// 부모가 검은색일 경우에는 부모 기준으로 다시 검사를 시작한다.
				_erase(pNode->m_pParent);
			}

			// case b. 이중흑색노드의 형제가 BLACK이고 형제의 오른쪽 자식이 RED인 경우
			else if (pSibling->m_pRight->m_eColor == RED)
			{
				// 형제를 빨간색으로 칠한다.
				if (pSibling != Nil)
					pSibling->m_eColor = RED;

				// 형제의 왼쪽 자식을 검은색으로 칠한다.
				pSibling->m_pRight->m_eColor = BLACK;

				// 형제노드 기준으로 좌회전한다.
				RotationLeft(pSibling);

				_erase(pNode);
			}

			// case c. 이중흑색노드의 형제가 BLACK이고 형제의 왼쪽 자식이 RED인 경우
			else if (pSibling->m_pLeft->m_eColor == RED)
			{
				// 부모의 색을 형제에게 넘긴다.
				if (pSibling != Nil)
					pSibling->m_eColor = pNode->m_pParent->m_eColor;

				// 부모노드와 형제의 왼쪽 자식을 검은색으로 칠한다.
				pNode->m_pParent->m_eColor = BLACK;
				pSibling->m_pLeft->m_eColor = BLACK;

				// 부모노드 기준으로 우회전한다.
				RotationRight(pNode->m_pParent);
			}
		}
	}

	PNODE FindLeftMax(PNODE pNode)	const
	{
		if (pNode->m_pRight == Nil)
			return pNode;

		return FindLeftMax(pNode->m_pRight);
	}

	PNODE FindRightMin(PNODE pNode)	const
	{
		if (pNode->m_pLeft == Nil)
			return pNode;

		return FindRightMin(pNode->m_pLeft);
	}
};
