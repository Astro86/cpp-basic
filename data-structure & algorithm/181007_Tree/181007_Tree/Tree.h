#pragma once

#include <assert.h>

enum INSERT_TYPE
{
	IT_ROOT,
	IT_CHILD,
	IT_SIBLING
};

// 기본 트리는 탐색 목적으로 구현하는 것은 아니다.
// 기본 트리는 전체 노드를 집어넣어놓고 노드르 순회하며 
// 계층구조를 구성할 때 많이 활용한다.

template <typename T>
class CTreeNode
{
	template <typename T>
	friend class CTree;

private:
	CTreeNode()
	{
		m_pChild = nullptr;
		m_pSibling = nullptr;
	}

	~CTreeNode()
	{
	}

private:
	CTreeNode<T>*	m_pChild;
	CTreeNode<T>*	m_pSibling;
	T				m_Data;
};

template <typename T>
class CTree
{
public:
	CTree()
	{
		m_pRoot = nullptr;
		m_iSize = 0;
	}

	~CTree()
	{
		clear();
	}

private:
	typedef CTreeNode<T>	NODE;
	typedef CTreeNode<T>*	PNODE;

private:
	// 트리에서 최상위 노드를 루트노드라고 한다. 루트노드는 딱 1개만 존재한다.
	// 트리의 가장 끝에 있는 더이상 자식이 없는 노드를 Leaf 노드라고 한다.
	PNODE	m_pRoot;
	int		m_iSize;

public:
	void insert(const T& data, const T& base, INSERT_TYPE eType)
	{
		if (eType == IT_ROOT)
		{
			PNODE	pNode = new NODE;

			pNode->m_Data = data;

			// 루트를 교체하는 것이므로 기존 Root를 Child로 준다.
			pNode->m_pChild = m_pRoot;

			m_pRoot = pNode;
		}

		else
		{
			PNODE	pBaseNode = FindNode(base, m_pRoot);

			if (!pBaseNode)
				return;

			PNODE	pNode = new NODE;
			pNode->m_Data = data;

			switch (eType)
			{
			case IT_SIBLING:
				// 만약 기존에 가지고 있는 형제가 있을 경우 새로 생성한 노드의 형제로
				// 기존의 형제를 주고 찾은 노드의 형제로 새로 생성한 노드를 준다.
				if (pBaseNode->m_pSibling)
					pNode->m_pSibling = pBaseNode->m_pSibling;

				pBaseNode->m_pSibling = pNode;
				break;
			case IT_CHILD:
				// 만약에 기존에 가지고 있는 자식이 있다면 기존 자식을 새로 생성한 노드의
				// 형제로 주고 자식으로 추가해준다.
				if (pBaseNode->m_pChild)
					pNode->m_pSibling = pBaseNode->m_pChild;

				pBaseNode->m_pChild = pNode;
				break;
			}
		}

		++m_iSize;
	}

	void Visit(void(*pFunc)(T&))
	{
		if (empty())
			assert(false);

		// 전체 노드를 순회하며 인자로 들어온 함수를 호출한다.
		Visit(pFunc, m_pRoot);
	}

	void clear()
	{
		clear(m_pRoot);
		m_iSize = 0;
		m_pRoot = nullptr;
	}

	bool empty()	const
	{
		return m_iSize == 0;
	}

	int size()	const
	{
		return m_iSize;
	}

private:
	PNODE FindNode(const T& data, PNODE pNode)
	{
		if (!pNode)
			return nullptr;

		if (pNode->m_Data == data)
			return pNode;

		PNODE	pFindNode = nullptr;

		pFindNode = FindNode(data, pNode->m_pSibling);

		if (!pFindNode)
			pFindNode = FindNode(data, pNode->m_pChild);

		return pFindNode;
	}

	void Visit(void (*pFunc)(T&), PNODE pNode)
	{
		if (!pNode)
			return;

		pFunc(pNode->m_Data);

		Visit(pFunc, pNode->m_pSibling);
		Visit(pFunc, pNode->m_pChild);
	}

	void clear(PNODE pNode)
	{
		if (!pNode)
			return;

		clear(pNode->m_pSibling);
		clear(pNode->m_pChild);

		delete	pNode;
	}
};
