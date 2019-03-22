
#pragma once

#include "Queue.h"
#include "LinkedList.h"
#include "Heap.h"
#include "Stack.h"
#include <iostream>

using namespace std;

// ����ġ�� �̵��Ϸ��� �ε��� ������ �����ϴ� ����ü�̴�.
// �� ����ü�� �̿��ؼ� �������� ���� �켱������ �����ϰ� �ȴ�.
struct _tagEdge
{
	int	iIndex;
	int	iWeight;
	int	iParent;

	_tagEdge()
	{
		iIndex = -1;
		iWeight = -1;
		iParent = -1;
	}

	bool operator > (const _tagEdge& edge)	const
	{
		return iWeight > edge.iWeight;
	}

	bool operator >= (const _tagEdge& edge)	const
	{
		return iWeight >= edge.iWeight;
	}

	bool operator < (const _tagEdge& edge)	const
	{
		return iWeight < edge.iWeight;
	}

	bool operator <= (const _tagEdge& edge)	const
	{
		return iWeight <= edge.iWeight;
	}
};

template <typename T>
class CDijkstraNode
{
private:
	template <typename T>
	friend class CDijkstra;

private:
	CDijkstraNode()
	{
		m_iEdgeCount = 0;
		m_iEdgeCapacity = 2;
		m_bVisit = false;
		m_iIndex = -1;
		m_iParentIndex = -1;

		m_pEdge = new CDijkstraNode<T>*[m_iEdgeCapacity];
		// ������ ����ġ(���) ������ �����ϱ� ���� �迭�� ������ش�.
		m_pWeightList = new unsigned int[m_iEdgeCapacity];

		// ��� ��ü�� ����ġ ������ ���� ū������ �����صд�.
		m_iNodeWeight = UINT_MAX;
	}

	~CDijkstraNode()
	{
		delete[]	m_pEdge;
		delete[]	m_pWeightList;
	}

private:
	CDijkstraNode<T>**	m_pEdge;
	unsigned int*		m_pWeightList;
	unsigned int		m_iNodeWeight;
	int					m_iEdgeCount;
	int					m_iEdgeCapacity;
	T					m_Data;
	bool				m_bVisit;
	int					m_iIndex;
	int					m_iParentIndex;

public:
	// A���� B�� �̵��ϴ� ������ ������ٶ� ����ġ(���)�� ���� ������ ���־�� �Ѵ�.
	void AddEdge(CDijkstraNode<T>* pEdge, unsigned int iWeight)
	{
		if (m_iEdgeCount == m_iEdgeCapacity)
		{
			m_iEdgeCapacity *= 2;
			CDijkstraNode<T>**	pEdge = new CDijkstraNode<T>*[m_iEdgeCapacity];

			memcpy(pEdge, m_pEdge, sizeof(CDijkstraNode<T>*) * m_iEdgeCount);

			delete[]	m_pEdge;
			m_pEdge = pEdge;

			// ������ ���Ҵ�Ǹ� ����ġ������ ���Ҵ� �ǰ� ���ش�.
			unsigned int*	pWeights = new unsigned int[m_iEdgeCapacity];
			memcpy(pWeights, m_pWeightList, sizeof(unsigned int) * m_iEdgeCount);

			delete[]	m_pWeightList;
			m_pWeightList = pWeights;
		}

		m_pEdge[m_iEdgeCount] = pEdge;
		// ���� ����� �����Ѵ�.
		m_pWeightList[m_iEdgeCount] = iWeight;
		++m_iEdgeCount;
	}

	void Disconnect()
	{
		for (int i = 0; i < m_iEdgeCount; ++i)
		{
			m_pEdge[i]->Disconnect(this);
		}
	}

	void Disconnect(CDijkstraNode<T>* pNode)
	{
		for (int i = 0; i < m_iEdgeCount; ++i)
		{
			if (m_pEdge[i] == pNode)
			{
				for (int j = i; j < m_iEdgeCount - 1; ++j)
				{
					m_pEdge[j] = m_pEdge[j + 1];
					// ����ġ ������ ������� �Ѵ�.
					m_pWeightList[j] = m_pWeightList[j + 1];
				}
				break;
			}
		}
	}
};

template <typename T>
class CDijkstra
{
public:
	CDijkstra()
	{
		m_iCount = 0;
		m_iCapacity = 2;
		m_pGraph = new PNODE[m_iCapacity];
	}
	~CDijkstra()
	{
		for (int i = 0; i < m_iCount; ++i)
		{
			delete	m_pGraph[i];
		}

		delete[]	m_pGraph;
	}

private:
	typedef CDijkstraNode<T>	NODE;
	typedef CDijkstraNode<T>*	PNODE;

private:
	PNODE * m_pGraph;
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

	void AddEdge(const T& src, const T& dest, unsigned int iWeight)
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

		pSrc->AddEdge(pDest, iWeight);
		pDest->AddEdge(pSrc, iWeight);

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

		// �湮 ���θ� ��� false�� �ʱ�ȭ�Ѵ�.
		for (int i = 0; i < m_iCount; ++i)
		{
			m_pGraph[i]->m_bVisit = false;
		}

		CQueue<int>	queue;

		queue.push(iIndex);

		while (!queue.empty())
		{
			iIndex = queue.pop();

			// ���� ���ؿ� ��带 �湮 ���·� �ٲٰ� ������ش�.
			m_pGraph[iIndex]->m_bVisit = true;
			cout << m_pGraph[iIndex]->m_Data << " -> ";

			// ����� Edge ����ŭ �ݺ��ϸ� queue�� �߰��Ѵ�.
			// ��, �湮�� ���� �����Ѵ�.
			for (int i = 0; i < m_pGraph[iIndex]->m_iEdgeCount; ++i)
			{
				if (m_pGraph[iIndex]->m_pEdge[i]->m_bVisit)
					continue;

				// queue�� �ε����� �߰��Ѵ�.
				queue.push(m_pGraph[iIndex]->m_pEdge[i]->m_iIndex);
			}
		}

		cout << endl;
	}

	// 1�� ���ڿ� list�� ���۷����� ���� ������ �� �Լ����� �ִܰŸ��� ã�� ����� �� ����Ʈ��
	// �߰��Ұ��̱� �����̴�. ����Ʈ�� ��Ƶ� ������ �������� ��� ���� �˼� ���� ������
	// ����Ʈ�� �����ߴ�.
	void Find(CLinkedList<T>& output, const T& start, const T& end)
	{
		int	iStart = -1, iEnd = -1;
		for (int i = 0; i < m_iCount; ++i)
		{
			if (m_pGraph[i]->m_Data == start)
				iStart = i;

			if (m_pGraph[i]->m_Data == end)
				iEnd = i;

			if (iStart != -1 && iEnd != -1)
				break;
		}

		// �������̳� �������� ��ã���� ��� �Լ��� �����Ѵ�.
		if (iStart == -1 || iEnd == -1)
			return;

		cout << "============= Dijkstra ==============" << endl;

		// �湮 ���θ� ��� false�� �ʱ�ȭ�Ѵ�.
		for (int i = 0; i < m_iCount; ++i)
		{
			m_pGraph[i]->m_bVisit = false;
			// ��ü ����� ����� �������� ó�����ش�.
			m_pGraph[i]->m_iNodeWeight = UINT_MAX;
			m_pGraph[i]->m_iParentIndex = -1;
		}
		
		// queue�� ���۳�带 �־��ش�.
		CHeap<_tagEdge>	heap;

		heap.SetCmpFunction<CDijkstra<T>>(&CDijkstra<T>::SortEdge, this);

		// ���۳�忡�� �� �� �ִ� ��� Edge�� ���� �߰��Ѵ�.
		for (int i = 0; i < m_pGraph[iStart]->m_iEdgeCount; ++i)
		{
			_tagEdge	tEdge = {};
			tEdge.iIndex = m_pGraph[iStart]->m_pEdge[i]->m_iIndex;
			tEdge.iWeight = m_pGraph[iStart]->m_pWeightList[i];
			tEdge.iParent = iStart;

			heap.insert(tEdge);
		}

		// ���� ����� ����� 0���� �ʱ�ȭ�Ѵ�.
		m_pGraph[iStart]->m_iNodeWeight = 0;
		m_pGraph[iStart]->m_bVisit = true;

		int	iParentIndex = iStart;

		while (!heap.empty())
		{
			_tagEdge	tEdge = heap.pop();

			iParentIndex = tEdge.iParent;

			if (tEdge.iIndex == 2)
			{
				int a = 10;
			}

			// ���� ����ġ�� ���Ѵ��� ��� �ٷ� �������൵ �ȴ�.
			if (m_pGraph[tEdge.iIndex]->m_iNodeWeight == UINT_MAX)
			{
				// ���� �̵��ؾ��� ����ġ + �θ��� ����ġ�� ���� ����ġ�� �����ش�.
				m_pGraph[tEdge.iIndex]->m_iNodeWeight = tEdge.iWeight + m_pGraph[iParentIndex]->m_iNodeWeight;
				m_pGraph[tEdge.iIndex]->m_iParentIndex = iParentIndex;

				// ���� �� ��带 �������� �̵��� �� �ִ� ��� ������ �߰��Ѵ�.
				for (int i = 0; i < m_pGraph[tEdge.iIndex]->m_iEdgeCount; ++i)
				{
					_tagEdge	tAddEdge = {};
					tAddEdge.iIndex = m_pGraph[tEdge.iIndex]->m_pEdge[i]->m_iIndex;
					tAddEdge.iWeight = m_pGraph[tEdge.iIndex]->m_pWeightList[i];
					tAddEdge.iParent = tEdge.iIndex;

					heap.insert(tAddEdge);
				}
			}

			// ���� ����ġ�� ���Ѵ밡 �ƴ϶�� ���� ����ġ�� ���Ͽ� ���������� �����Ѵ�.
			else if (m_pGraph[tEdge.iIndex]->m_iNodeWeight > tEdge.iWeight + m_pGraph[iParentIndex]->m_iNodeWeight)
			{
				// ���� �̵��ؾ��� ����ġ + �θ��� ����ġ�� ���� ����ġ�� �����ش�.
				m_pGraph[tEdge.iIndex]->m_iNodeWeight = tEdge.iWeight + m_pGraph[iParentIndex]->m_iNodeWeight;
				m_pGraph[tEdge.iIndex]->m_iParentIndex = iParentIndex;

				// ���� �� ��带 �������� �̵��� �� �ִ� ��� ������ �߰��Ѵ�.
				for (int i = 0; i < m_pGraph[tEdge.iIndex]->m_iEdgeCount; ++i)
				{
					_tagEdge	tAddEdge = {};
					tAddEdge.iIndex = m_pGraph[tEdge.iIndex]->m_pEdge[i]->m_iIndex;
					tAddEdge.iWeight = m_pGraph[tEdge.iIndex]->m_pWeightList[i];
					tAddEdge.iParent = tEdge.iIndex;

					heap.insert(tAddEdge);
				}
			}

			m_pGraph[tEdge.iIndex]->m_bVisit = true;
		}

		CStackList<int>	result;

		int	iFindIndex = iEnd;

		while (iFindIndex != -1)
		{
			result.push(iFindIndex);
			iFindIndex = m_pGraph[iFindIndex]->m_iParentIndex;
		}

		output.clear();

		// ���ÿ��� �ٽ� ���� ������ ����Ʈ�� �������ش�.
		while (!result.empty())
		{
			int	iStackIdx = result.pop();

			output.push_back(m_pGraph[iStackIdx]->m_Data);
		}

		cout << endl;
	}

	bool SortEdge(const _tagEdge& tSrc, const _tagEdge& tDest)
	{
		return tSrc > tDest;
	}
};
