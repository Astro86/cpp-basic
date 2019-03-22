#pragma once

#include "Queue.h"
#include "Stack.h"
#include <iostream>

using namespace std;

template <typename T>
class CGraphNode
{
private:
	template <typename T>
	friend class CGraph;

private:
	CGraphNode()
	{
		m_iEdgeCount = 0;
		m_iEdgeCapacity = 2;
		m_bVisit = false;
		m_iIndex = -1;

		m_pEdge = new CGraphNode<T>*[m_iEdgeCapacity];
	}

	~CGraphNode()
	{
		delete[]	m_pEdge;
	}

private:
	CGraphNode<T>**	m_pEdge;
	int				m_iEdgeCount;
	int				m_iEdgeCapacity;
	T				m_Data;
	bool			m_bVisit;
	int				m_iIndex;

public:
	void AddEdge(CGraphNode<T>* pEdge)
	{
		if (m_iEdgeCount == m_iEdgeCapacity)
		{
			m_iEdgeCapacity *= 2;
			CGraphNode<T>**	pEdge = new CGraphNode<T>*[m_iEdgeCapacity];

			memcpy(pEdge, m_pEdge, sizeof(CGraphNode<T>*) * m_iEdgeCount);

			delete[]	m_pEdge;
			m_pEdge = pEdge;
		}

		m_pEdge[m_iEdgeCount] = pEdge;
		++m_iEdgeCount;
	}

	void Disconnect()
	{
		for (int i = 0; i < m_iEdgeCount; ++i)
		{
			m_pEdge[i]->Disconnect(this);
		}
	}

	void Disconnect(CGraphNode<T>* pNode)
	{
		for (int i = 0; i < m_iEdgeCount; ++i)
		{
			if (m_pEdge[i] == pNode)
			{
				for (int j = i; j < m_iEdgeCount - 1; ++j)
				{
					m_pEdge[j] = m_pEdge[j + 1];
				}
				break;
			}
		}
	}
};

template <typename T>
class CGraph
{
public:
	CGraph()
	{
		m_iCount = 0;
		m_iCapacity = 2;
		m_pGraph = new PNODE[m_iCapacity];
	}
	~CGraph()
	{
		for (int i = 0; i < m_iCount; ++i)
		{
			delete	m_pGraph[i];
		}

		delete[]	m_pGraph;
	}

private:
	typedef CGraphNode<T>	NODE;
	typedef CGraphNode<T>*	PNODE;

private:
	PNODE*	m_pGraph;
	int		m_iCount;
	int		m_iCapacity;

public:
	void AddVertex(const T& data)
	{
		if (m_iCount == m_iCapacity)
		{
			m_iCapacity *= 2;
			PNODE* pGraph = new PNODE[m_iCapacity];
			memcpy(pGraph, m_pGraph, sizeof(PNODE) * m_iCount);
			delete[]	m_pGraph;
			m_pGraph = pGraph;
		}

		PNODE	pNode = new NODE;

		pNode->m_Data = data;
		pNode->m_iIndex = m_iCount;

		cout << "Add " << data << " Vertex" << endl;

		m_pGraph[m_iCount] = pNode;
		++m_iCount;
	}

	void AddEdge(const T& src, const T& dest)
	{
		PNODE	pSrc = nullptr;
		PNODE	pDest = nullptr;

		for (int i = 0; i < m_iCount; ++i)
		{
			if (m_pGraph[i]->m_Data == src && !pSrc)
				pSrc = m_pGraph[i];

			else if (m_pGraph[i]->m_Data == dest && !pDest)
				pDest = m_pGraph[i];

			if (pSrc && pDest)
				break;
		}

		if (!pSrc || !pDest)
			return;

		pSrc->AddEdge(pDest);
		pDest->AddEdge(pSrc);

		cout << pSrc->m_Data << " -> " << pDest->m_Data << " Edge" << endl;
		cout << pDest->m_Data << " -> " << pSrc->m_Data << " Edge" << endl;
	}

	void DeleteVertex(const T& data)
	{
		PNODE	pNode = nullptr;
		int	iStartIndex = -1;
		for (int i = 0; i < m_iCount; ++i)
		{
			if (m_pGraph[i]->m_Data == data)
			{
				iStartIndex = i;
				pNode = m_pGraph[i];
				break;
			}
		}

		if (!pNode)
			return;

		pNode->Disconnect();

		delete	pNode;
		for (int i = iStartIndex; i < m_iCount - 1; ++i)
		{
			m_pGraph[i] = m_pGraph[i + 1];
		}

		--m_iCount;
	}

	void BFS(const T& start)
	{
		int	iIndex = -1;
		for (int i = 0; i < m_iCount; ++i)
		{
			if (m_pGraph[i]->m_Data == start)
			{
				iIndex = i;
				break;
			}
		}

		if (iIndex == -1)
			return;

		cout << "============= BFS ==============" << endl;

		// 방문 여부를 모두 false로 초기화한다.
		for (int i = 0; i < m_iCount; ++i)
		{
			m_pGraph[i]->m_bVisit = false;
		}

		CQueue<int>	queue;

		queue.push(iIndex);

		while (!queue.empty())
		{
			iIndex = queue.pop();

			// 현재 구해온 노드를 방문 상태로 바꾸고 출력해준다.
			m_pGraph[iIndex]->m_bVisit = true;
			cout << m_pGraph[iIndex]->m_Data << " -> ";

			// 연결된 Edge 수만큼 반복하며 queue에 추가한다.
			// 단, 방문한 노드는 제외한다.
			for (int i = 0; i < m_pGraph[iIndex]->m_iEdgeCount; ++i)
			{
				if (m_pGraph[iIndex]->m_pEdge[i]->m_bVisit)
					continue;

				// queue에 인덱스를 추가한다.
				queue.push(m_pGraph[iIndex]->m_pEdge[i]->m_iIndex);
			}
		}

		cout << endl;
	}

	void DFS(const T& start)
	{
		int	iIndex = -1;
		for (int i = 0; i < m_iCount; ++i)
		{
			if (m_pGraph[i]->m_Data == start)
			{
				iIndex = i;
				break;
			}
		}

		if (iIndex == -1)
			return;

		cout << "============= DFS ==============" << endl;

		// 방문 여부를 모두 false로 초기화한다.
		for (int i = 0; i < m_iCount; ++i)
		{
			m_pGraph[i]->m_bVisit = false;
		}

		CStackList<int>	stack;

		stack.push(iIndex);

		while (!stack.empty())
		{
			iIndex = stack.pop();

			// 현재 구해온 노드를 방문 상태로 바꾸고 출력해준다.
			m_pGraph[iIndex]->m_bVisit = true;
			cout << m_pGraph[iIndex]->m_Data << " -> ";

			for (int i = 0; i < m_pGraph[iIndex]->m_iEdgeCount; ++i)
			{
				if (m_pGraph[iIndex]->m_pEdge[i]->m_bVisit)
					continue;

				stack.push(m_pGraph[iIndex]->m_pEdge[i]->m_iIndex);
			}
		}

		cout << endl;
	}
};
