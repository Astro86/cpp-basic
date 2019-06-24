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

	// ��ġ
	CRBBTreeIterator<Key, Value>& operator ++ ()
	{
		m_pNode = m_pNode->m_pNext;
		return *this;
	}

	// ��ġ
	CRBBTreeIterator<Key, Value> operator ++ (int)
	{
		m_pNode = m_pNode->m_pNext;
		return *this;
	}

	// ��ġ
	CRBBTreeIterator<Key, Value>& operator -- ()
	{
		m_pNode = m_pNode->m_pPrev;
		return *this;
	}

	// ��ġ
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

		// ���̳�� ����
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

		// ��������� ����� �׳� ����� �ȴ�.
		if (iter.m_pNode->m_pLeft == Nil && iter.m_pNode->m_pRight)
		{
			// ��������ε� �θ� ���ٸ� Root��� �� 1���� �߰��Ǿ� �ִ� ������ ���̴�.
			if (!iter.m_pNode->m_pParent)
			{
				m_pRoot = nullptr;
				delete	iter.m_pNode;
				--m_iSize;
				return end();
			}

			else
			{
				// ���� ����� �θ�κ��� ���� ���� ����� ������ �����ش�.
				if (iter.m_pNode->m_pParent->m_pLeft == iter.m_pNode)
					iter.m_pNode->m_pParent->m_pLeft = Nil;

				else
					iter.m_pNode->m_pParent->m_pRight = Nil;

				// ���� ����� �������� ������带 �����Ѵ�.
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

		// ������尡 �ƴ� ���
		bool	bLeft = false;
		PNODE	pDeleteNode = nullptr;

		// ���� ��尡 ���� ��� ���ʿ��� ���� ū ��带 ã�´�.
		if (iter.m_pNode->m_pLeft != Nil)
		{
			bLeft = true;
			pDeleteNode = FindLeftMax(iter.m_pNode->m_pLeft);
		}

		else
			pDeleteNode = FindRightMin(iter.m_pNode->m_pRight);

		// ���� ����� Color�� �̸� �޾Ƶд�.
		NODE_COLOR	eDeleteColor = pDeleteNode->m_eColor;

		// ã�ƿ� ����� ������ ���� ����� ���� ��ü�Ѵ�.
		iter.m_pNode->first = pDeleteNode->first;
		iter.m_pNode->second = pDeleteNode->second;

		if (iter.m_pNode->m_eColor == BLACK)
			iter.m_pNode->m_eColor = BLACK;

		else
			iter.m_pNode->m_eColor = pDeleteNode->m_eColor;

		iterator	iterResult;
		iterResult.m_pNode = iter.m_pNode;

		// ���� ���ʿ��� ���� ū ��带 ã�ƿԴٸ� ���� ����� ���� ��带 ���ͼ� iterator�� ������ְ�
		// ��ȯ�ؾ� �Ѵ�.
		if (bLeft)
			iterResult.m_pNode = iter.m_pNode->m_pNext;

		PNODE	pDeleteChild = nullptr;

		// ���ʿ��� ���� ū ��带 ���� ��� ������ �ڽ��� Nil�̰����� �����ڽ��� ���� ���� �ִ�.
		// �ݴ��� ��쵵 ����������.
		if (bLeft)
		{
			if (pDeleteNode->m_pLeft != Nil)
				pDeleteChild = pDeleteNode->m_pLeft;
		}

		else if(pDeleteNode->m_pRight != Nil)
			pDeleteChild = pDeleteNode->m_pRight;

		if (pDeleteChild)
		{
			// ���� ���� ����� �θ� ���� ����� �θ�� �����Ѵ�.
			pDeleteChild->m_pParent = pDeleteNode->m_pParent;

			// ���� ��尡 �θ��� �������� ������������ ���� �ڽ����� �ٿ��ش�.
			if (pDeleteNode->m_pParent->m_pLeft == pDeleteNode)
				pDeleteNode->m_pParent->m_pLeft = pDeleteChild;

			else
				pDeleteNode->m_pParent->m_pRight = pDeleteChild;
		}

		else
		{
			// ���� ��尡 �θ��� �������� ������������ ���� �ڽ����� �ٿ��ش�.
			if (pDeleteNode->m_pParent->m_pLeft == pDeleteNode)
				pDeleteNode->m_pParent->m_pLeft = Nil;

			else
				pDeleteNode->m_pParent->m_pRight = Nil;
		}

		// ������ ��尡 �������� ��� ���������尡 �ȴ�.
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

		// ���� ���γ�尡 ���ٸ� Ž�� �����Ѵ�.
		PNODE	pPParent = pNode->m_pParent->m_pParent;

		if (!pPParent)
			return;

		// �θ��尡 ���γ���� �������� ������������ �Ǵ��Ѵ�.
		if (pPParent->m_pLeft == pNode->m_pParent)
		{
			PNODE	pUncle = pPParent->m_pRight;

			// case 1. ���̳�尡 RED�� ���
			if (pUncle->m_eColor == RED)
			{
				// �θ���� ���̳�带 BLACK���� ĥ�Ѵ�.
				pUncle->m_eColor = BLACK;
				pNode->m_pParent->m_eColor = BLACK;

				// ���γ�带 ���������� ĥ�Ѵ�.
				pPParent->m_eColor = RED;

				// ���γ�带 ���س��� �ؼ� �ٽ� Ž���� �����Ѵ�.
				Balance(pPParent);
			}

			// ���̳�尡 BLACK�� ���
			else
			{
				// case 2. ���� ������ ��尡 �θ��� ������ �ڽ��� ���
				if (pNode == pNode->m_pParent->m_pRight)
				{
					// �θ��带 �������� ��ȸ���Ͽ� case3������ �������ش�.
					pNode = RotationLeft(pNode->m_pParent);
				}

				// case 3. ���� ������ ��尡 �θ��� ���� �ڽ��� ���
				// �θ� BLACK, ���θ� RED�� ĥ�Ѵ�.
				pNode->m_pParent->m_eColor = BLACK;
				pPParent->m_eColor = RED;

				// ���θ� �������� ���������� ȸ����Ų��.
				pNode = RotationRight(pPParent);

				// ���γ�带 �������� ���ȣ���Ѵ�.
				// ���δ� ȸ���Ǽ� �Ʒ��� ���������Ƿ� ���⼭�� ���θ� ã�Ƽ� �־��ش�.
				Balance(pNode->m_pParent->m_pParent);
			}
		}

		// �θ��尡 ���γ���� ������ �ڽ��� ���
		else
		{
			PNODE	pUncle = pPParent->m_pLeft;

			// case 1. ���̳�尡 RED�� ���
			if (pUncle->m_eColor == RED)
			{
				// �θ���� ���̳�带 BLACK���� ĥ�Ѵ�.
				pUncle->m_eColor = BLACK;
				pNode->m_pParent->m_eColor = BLACK;

				// ���γ�带 ���������� ĥ�Ѵ�.
				pPParent->m_eColor = RED;

				// ���γ�带 ���س��� �ؼ� �ٽ� Ž���� �����Ѵ�.
				Balance(pPParent);
			}

			// ���̳�尡 BLACK�� ���
			else
			{
				// case 2. ���� ������ ��尡 �θ��� ���� �ڽ��� ���
				if (pNode == pNode->m_pParent->m_pLeft)
				{
					// �θ��带 �������� ��ȸ���Ͽ� case3������ �������ش�.
					pNode = RotationRight(pNode->m_pParent);
				}

				// case 3. ���� ������ ��尡 �θ��� ������ �ڽ��� ���
				// �θ� BLACK, ���θ� RED�� ĥ�Ѵ�.
				pNode->m_pParent->m_eColor = BLACK;
				pPParent->m_eColor = RED;

				// ���θ� �������� �������� ȸ����Ų��.
				pNode = RotationLeft(pPParent);

				// ���γ�带 �������� ���ȣ���Ѵ�.
				// ���δ� ȸ���Ǽ� �Ʒ��� ���������Ƿ� ���⼭�� ���θ� ã�Ƽ� �־��ش�.
				Balance(pNode->m_pParent->m_pParent);
			}
		}
	}

	PNODE RotationLeft(PNODE pNode)
	{
		// ���س���� ������ ��带 ���´�.
		PNODE	pRight = pNode->m_pRight;

		// ������ ����� ���� �ڽ��� ���´�.
		PNODE	pRightChildL = pRight->m_pLeft;

		// ���س�带 ������ �ڽ��� ���� �ڽ����� �ش�.
		pRight->m_pLeft = pNode;

		// ���س�尡 �θ��� ���� �ڽ����� ������ �ڽ������� �Ǵ��ؼ� ���س���� �θ��� �ڽ�����
		// ������ ��带 �ش�.
		if (pNode->m_pParent)
		{
			if (pNode->m_pParent->m_pLeft == pNode)
				pNode->m_pParent->m_pLeft = pRight;

			else
				pNode->m_pParent->m_pRight = pRight;
		}

		// ���س�尡 Root�� ��� ���� m_pRoot�� pRight�� ��ü���ش�.
		else
			m_pRoot = pRight;

		// ������ ����� �θ� ���س���� �θ�� �ش�.
		pRight->m_pParent = pNode->m_pParent;
		pNode->m_pParent = pRight;

		// ������ ����� ���� �ڽ��� ���س���� ������ �ڽ����� �ش�.
		pNode->m_pRight = pRightChildL;
		pRightChildL->m_pParent = pNode;

		// ȸ���� �ϰ� ���� ���س�尡 �ٲ�Ƿ� �������ش�.
		return pNode;
	}

	PNODE RotationRight(PNODE pNode)
	{
		// ���س���� ���� ��带 ���´�.
		PNODE	pLeft = pNode->m_pLeft;

		// ���� ����� ������ �ڽ��� ���´�.
		PNODE	pLeftChildR = pLeft->m_pRight;

		// ���س�带 ������ �ڽ��� ���� �ڽ����� �ش�.
		pLeft->m_pRight = pNode;

		// ���س�尡 �θ��� ���� �ڽ����� ������ �ڽ������� �Ǵ��ؼ� ���س���� �θ��� �ڽ�����
		// ������ ��带 �ش�.
		if (pNode->m_pParent)
		{
			if (pNode->m_pParent->m_pLeft == pNode)
				pNode->m_pParent->m_pLeft = pLeft;

			else
				pNode->m_pParent->m_pRight = pLeft;
		}

		// ���س�尡 Root�� ��� ���� m_pRoot�� pLeft�� ��ü���ش�.
		else
			m_pRoot = pLeft;

		// ���� ����� �θ� ���س���� �θ�� �ش�.
		pLeft->m_pParent = pNode->m_pParent;
		pNode->m_pParent = pLeft;

		// ���� ����� ������ �ڽ��� ���س���� ���� �ڽ����� �ش�.
		pNode->m_pLeft = pLeftChildR;
		pLeftChildR->m_pParent = pNode;

		// ȸ���� �ϰ� ���� ���س�尡 �ٲ�Ƿ� �������ش�.
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

	void _erase(PNODE pNode)
	{
		if (pNode == m_pRoot || pNode->m_eColor == RED)
			return;

		PNODE	pSibling = nullptr;

		// ���� �����尡 �θ��� ���� �ڽ��� ���
		if (pNode == pNode->m_pParent->m_pLeft)
		{
			// ������带 ���´�.
			pSibling = pNode->m_pParent->m_pRight;

			// case change. ������������ ������ RED�� ���
			if (pSibling->m_eColor == RED)
			{
				pSibling->m_eColor = BLACK;
				pNode->m_pParent->m_eColor = RED;

				// �θ��带 ��ȸ���Ѵ�.
				RotationLeft(pNode->m_pParent);

				// ������ �ٲ�����Ƿ� ������ �ٽ� ���´�.
				pSibling = pNode->m_pParent->m_pRight;
			}

			// case a. ������������ ������ BLACK�̰� ���� �ڽ� ��� BLACK�� ���
			if (pSibling->m_pLeft->m_eColor == BLACK && pSibling->m_pRight->m_eColor == BLACK)
			{
				// ������ ����� �ٲ۴�.
				if (pSibling != Nil)
					pSibling->m_eColor = RED;

				// ���������� ������ 1���� �θ𿡰� �����Ѵ�.
				// �������� ��쿡�� ���������� ĥ�ϰ� Ž���� �����Ѵ�.
				if (pNode->m_pParent->m_eColor == RED)
				{
					pNode->m_pParent->m_eColor = BLACK;
					return;
				}

				// �θ� �������� ��쿡�� �θ� �������� �ٽ� �˻縦 �����Ѵ�.
				_erase(pNode->m_pParent);
			}

			// case b. ������������ ������ BLACK�̰� ������ ���� �ڽ��� RED�� ���
			else if (pSibling->m_pLeft->m_eColor == RED)
			{
				// ������ ���������� ĥ�Ѵ�.
				if (pSibling != Nil)
					pSibling->m_eColor = RED;

				// ������ ���� �ڽ��� ���������� ĥ�Ѵ�.
				pSibling->m_pLeft->m_eColor = BLACK;

				// ������� �������� ��ȸ���Ѵ�.
				RotationRight(pSibling);

				_erase(pNode);
			}

			// case c. ������������ ������ BLACK�̰� ������ ������ �ڽ��� RED�� ���
			else if (pSibling->m_pRight->m_eColor == RED)
			{
				// �θ��� ���� �������� �ѱ��.
				if (pSibling != Nil)
					pSibling->m_eColor = pNode->m_pParent->m_eColor;

				// �θ���� ������ ������ �ڽ��� ���������� ĥ�Ѵ�.
				pNode->m_pParent->m_eColor = BLACK;
				pSibling->m_pRight->m_eColor = BLACK;

				// �θ��� �������� ��ȸ���Ѵ�.
				RotationLeft(pNode->m_pParent);
			}
		}

		// ���� �����尡 �θ��� ������ �ڽ��� ���
		else
		{
			// ������带 ���´�.
			pSibling = pNode->m_pParent->m_pLeft;

			// case change. ������������ ������ RED�� ���
			if (pSibling->m_eColor == RED)
			{
				pSibling->m_eColor = BLACK;
				pNode->m_pParent->m_eColor = RED;

				// �θ��带 ��ȸ���Ѵ�.
				RotationRight(pNode->m_pParent);

				// ������ �ٲ�����Ƿ� ������ �ٽ� ���´�.
				pSibling = pNode->m_pParent->m_pLeft;
			}

			// case a. ������������ ������ BLACK�̰� ���� �ڽ� ��� BLACK�� ���
			if (pSibling->m_pLeft->m_eColor == BLACK && pSibling->m_pRight->m_eColor == BLACK)
			{
				// ������ ����� �ٲ۴�.
				if (pSibling != Nil)
					pSibling->m_eColor = RED;

				// ���������� ������ 1���� �θ𿡰� �����Ѵ�.
				// �������� ��쿡�� ���������� ĥ�ϰ� Ž���� �����Ѵ�.
				if (pNode->m_pParent->m_eColor == RED)
				{
					pNode->m_pParent->m_eColor = BLACK;
					return;
				}

				// �θ� �������� ��쿡�� �θ� �������� �ٽ� �˻縦 �����Ѵ�.
				_erase(pNode->m_pParent);
			}

			// case b. ������������ ������ BLACK�̰� ������ ������ �ڽ��� RED�� ���
			else if (pSibling->m_pRight->m_eColor == RED)
			{
				// ������ ���������� ĥ�Ѵ�.
				if (pSibling != Nil)
					pSibling->m_eColor = RED;

				// ������ ���� �ڽ��� ���������� ĥ�Ѵ�.
				pSibling->m_pRight->m_eColor = BLACK;

				// ������� �������� ��ȸ���Ѵ�.
				RotationLeft(pSibling);

				_erase(pNode);
			}

			// case c. ������������ ������ BLACK�̰� ������ ���� �ڽ��� RED�� ���
			else if (pSibling->m_pLeft->m_eColor == RED)
			{
				// �θ��� ���� �������� �ѱ��.
				if (pSibling != Nil)
					pSibling->m_eColor = pNode->m_pParent->m_eColor;

				// �θ���� ������ ���� �ڽ��� ���������� ĥ�Ѵ�.
				pNode->m_pParent->m_eColor = BLACK;
				pSibling->m_pLeft->m_eColor = BLACK;

				// �θ��� �������� ��ȸ���Ѵ�.
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
