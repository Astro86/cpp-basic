
#pragma once

#include "Queue.h"
#include "LinkedList.h"
#include "Heap.h"
#include "Stack.h"
#include <iostream>

using namespace std;

// 가중치와 이동하려는 인덱스 정보를 저장하는 구조체이다.
// 이 구조체를 이용해서 힙정렬을 통해 우선순위를 결정하게 된다.
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
		// 간선의 가중치(비용) 정보를 저장하기 위한 배열을 만들어준다.
		m_pWeightList = new unsigned int[m_iEdgeCapacity];

		// 노드 자체의 가중치 정보를 가장 큰값으로 설정해둔다.
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
	// A에서 B로 이동하는 간선을 만들어줄때 가중치(비용)도 같이 저장을 해주어야 한다.
	void AddEdge(CDijkstraNode<T>* pEdge, unsigned int iWeight)
	{
		if (m_iEdgeCount == m_iEdgeCapacity)
		{
			m_iEdgeCapacity *= 2;
			CDijkstraNode<T>**	pEdge = new CDijkstraNode<T>*[m_iEdgeCapacity];

			memcpy(pEdge, m_pEdge, sizeof(CDijkstraNode<T>*) * m_iEdgeCount);

			delete[]	m_pEdge;
			m_pEdge = pEdge;

			// 간선이 재할당되면 가중치정보도 재할당 되게 해준다.
			unsigned int*	pWeights = new unsigned int[m_iEdgeCapacity];
			memcpy(pWeights, m_pWeightList, sizeof(unsigned int) * m_iEdgeCount);

			delete[]	m_pWeightList;
			m_pWeightList = pWeights;
		}

		m_pEdge[m_iEdgeCount] = pEdge;
		// 간선 비용을 저장한다.
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
					// 가중치 정보도 지워줘야 한다.
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

	// 1번 인자에 list의 레퍼런스를 받은 이유는 이 함수에서 최단거리를 찾은 목록을 이 리스트에
	// 추가할것이기 때문이다. 리스트로 잡아둔 이유는 결과목록이 몇개가 될지 알수 없기 때문에
	// 리스트로 선언했다.
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

		// 도착점이나 시작점을 못찾았을 경우 함수를 종료한다.
		if (iStart == -1 || iEnd == -1)
			return;

		cout << "============= Dijkstra ==============" << endl;

		// 방문 여부를 모두 false로 초기화한다.
		for (int i = 0; i < m_iCount; ++i)
		{
			m_pGraph[i]->m_bVisit = false;
			// 전체 노드의 비용을 무한으로 처리해준다.
			m_pGraph[i]->m_iNodeWeight = UINT_MAX;
			m_pGraph[i]->m_iParentIndex = -1;
		}
		
		// queue에 시작노드를 넣어준다.
		CHeap<_tagEdge>	heap;

		heap.SetCmpFunction<CDijkstra<T>>(&CDijkstra<T>::SortEdge, this);

		// 시작노드에서 갈 수 있는 모든 Edge를 힙에 추가한다.
		for (int i = 0; i < m_pGraph[iStart]->m_iEdgeCount; ++i)
		{
			_tagEdge	tEdge = {};
			tEdge.iIndex = m_pGraph[iStart]->m_pEdge[i]->m_iIndex;
			tEdge.iWeight = m_pGraph[iStart]->m_pWeightList[i];
			tEdge.iParent = iStart;

			heap.insert(tEdge);
		}

		// 시작 노드의 비용을 0으로 초기화한다.
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

			// 만약 가중치가 무한대일 경우 바로 갱신해줘도 된다.
			if (m_pGraph[tEdge.iIndex]->m_iNodeWeight == UINT_MAX)
			{
				// 현재 이동해야할 가중치 + 부모의 가중치로 최종 가중치를 정해준다.
				m_pGraph[tEdge.iIndex]->m_iNodeWeight = tEdge.iWeight + m_pGraph[iParentIndex]->m_iNodeWeight;
				m_pGraph[tEdge.iIndex]->m_iParentIndex = iParentIndex;

				// 현재 이 노드를 기준으로 이동할 수 있는 모든 엣지를 추가한다.
				for (int i = 0; i < m_pGraph[tEdge.iIndex]->m_iEdgeCount; ++i)
				{
					_tagEdge	tAddEdge = {};
					tAddEdge.iIndex = m_pGraph[tEdge.iIndex]->m_pEdge[i]->m_iIndex;
					tAddEdge.iWeight = m_pGraph[tEdge.iIndex]->m_pWeightList[i];
					tAddEdge.iParent = tEdge.iIndex;

					heap.insert(tAddEdge);
				}
			}

			// 만약 가중치가 무한대가 아니라면 현재 가중치와 비교하여 갱신할지를 결정한다.
			else if (m_pGraph[tEdge.iIndex]->m_iNodeWeight > tEdge.iWeight + m_pGraph[iParentIndex]->m_iNodeWeight)
			{
				// 현재 이동해야할 가중치 + 부모의 가중치로 최종 가중치를 정해준다.
				m_pGraph[tEdge.iIndex]->m_iNodeWeight = tEdge.iWeight + m_pGraph[iParentIndex]->m_iNodeWeight;
				m_pGraph[tEdge.iIndex]->m_iParentIndex = iParentIndex;

				// 현재 이 노드를 기준으로 이동할 수 있는 모든 엣지를 추가한다.
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

		// 스택에서 다시 원래 순서로 리스트에 저장해준다.
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
