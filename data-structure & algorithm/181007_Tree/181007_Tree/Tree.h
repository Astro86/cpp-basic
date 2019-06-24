#pragma once

#include <assert.h>

enum INSERT_TYPE
{
	IT_ROOT,
	IT_CHILD,
	IT_SIBLING
};

// �⺻ Ʈ���� Ž�� �������� �����ϴ� ���� �ƴϴ�.
// �⺻ Ʈ���� ��ü ��带 ����־���� ��帣 ��ȸ�ϸ� 
// ���������� ������ �� ���� Ȱ���Ѵ�.

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
	// Ʈ������ �ֻ��� ��带 ��Ʈ����� �Ѵ�. ��Ʈ���� �� 1���� �����Ѵ�.
	// Ʈ���� ���� ���� �ִ� ���̻� �ڽ��� ���� ��带 Leaf ����� �Ѵ�.
	PNODE	m_pRoot;
	int		m_iSize;

public:
	void insert(const T& data, const T& base, INSERT_TYPE eType)
	{
		if (eType == IT_ROOT)
		{
			PNODE	pNode = new NODE;

			pNode->m_Data = data;

			// ��Ʈ�� ��ü�ϴ� ���̹Ƿ� ���� Root�� Child�� �ش�.
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
				// ���� ������ ������ �ִ� ������ ���� ��� ���� ������ ����� ������
				// ������ ������ �ְ� ã�� ����� ������ ���� ������ ��带 �ش�.
				if (pBaseNode->m_pSibling)
					pNode->m_pSibling = pBaseNode->m_pSibling;

				pBaseNode->m_pSibling = pNode;
				break;
			case IT_CHILD:
				// ���࿡ ������ ������ �ִ� �ڽ��� �ִٸ� ���� �ڽ��� ���� ������ �����
				// ������ �ְ� �ڽ����� �߰����ش�.
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

		// ��ü ��带 ��ȸ�ϸ� ���ڷ� ���� �Լ��� ȣ���Ѵ�.
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
