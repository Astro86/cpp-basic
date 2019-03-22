
#pragma once

// c++ 11���� �����Ǵ� ����̴�. �Ϲ� �Լ��� ����Լ������͸� ���� ����� �� �ִ� ��ü��
// �������ش�.
#include <functional>
#include <assert.h>

using namespace std;

template <typename T>
class CHeapNode
{
	template <typename T>
	friend class CHeap;

private:
	CHeapNode()
	{
		m_iIndex = -1;
	}

	~CHeapNode()
	{
	}

public:
	T		m_Data;
	int		m_iIndex;
};

template <typename T>
class CHeap
{
public:
	CHeap()
	{
		m_iSize = 0;
		m_iCapacity = 100;

		m_pArray = new NODE[m_iCapacity];

		// bind�Լ��� �̿��ؼ� �Լ������͸� ��� function ��ü�� ������ش�.
		// ����Լ��� �������� ����Լ� �ּҿ� �� �Լ��� ȣ���� ��ü�� �ּҸ� �������־�� �Ѵ�.
		// ���ڰ� 2���̹Ƿ� 2���� ���� ������ �������ش�.
		m_ComFunc = bind(&CHeap::Cmp, this, placeholders::_1, placeholders::_2);
	}

	~CHeap()
	{
		delete[]	m_pArray;
	}

private:
	typedef CHeapNode<T>	NODE;
	typedef CHeapNode<T>*	PNODE;

private:
	PNODE	m_pArray;
	int		m_iSize;
	int		m_iCapacity;
	function<bool(const T&, const T&)>	m_ComFunc;

public:
	// �����Լ��� �����ؼ� ���� ���ϰ� �Ѵ�.
	void SetCmpFunction(bool(*pFunc)(const T&, const T&))
	{
		m_ComFunc = bind(pFunc, placeholders::_1, placeholders::_2);
	}

	// ����Լ��� �����ؼ� ���� ���ϰ� �Ѵ�. ���⼭�� �� �Լ������� ����ϴ� ���ø���
	// �߰��� �ϳ� �� ����Ѵ�. �ֳ��ϸ� Ŭ���� Ÿ���� �ٸ� Ŭ���� Ÿ�����ε� ��� �����ϰ�
	// �ϱ� ���ؼ��̴�.
	template <typename FuncType>
	void SetCmpFunction(bool (FuncType::*pFunc)(const T&, const T&), FuncType* pObj)
	{
		m_ComFunc = bind(pFunc, pObj, placeholders::_1, placeholders::_2);
	}

public:
	void insert(const T& data)
	{
		// ���� ������ �� á�ٸ� ���� �������ش�.
		if (m_iSize == m_iCapacity)
		{
			m_iCapacity *= 2;

			PNODE	pArray = new NODE[m_iCapacity];

			for (int i = 0; i < m_iSize; ++i)
			{
				pArray[i].m_Data = m_pArray[i].m_Data;
				pArray[i].m_iIndex = m_pArray[i].m_iIndex;
			}

			delete[]	m_pArray;

			m_pArray = pArray;
		}

		// ���� �������� �߰��� ����� ������ �־��ش�.
		m_pArray[m_iSize].m_Data = data;
		m_pArray[m_iSize].m_iIndex = m_iSize;

		// ��Ʈ�� Ÿ����鼭 ��ġ�� ����ش�.
		_insert(m_iSize);

		++m_iSize;
	}

	void clear()
	{
		m_iSize = 0;
		delete[]	m_pArray;
		
		m_iCapacity = 100;
		m_pArray = new NODE[m_iCapacity];
	}

	T pop()
	{
		if (empty())
		{
			assert(false);
		}

		// �̹� ���� �������� ��Ʈ��忡 ó������ ���� �� �����Ͱ� �� �����Ƿ� ��Ʈ����� ���� ���д�.
		T	data = m_pArray[0].m_Data;

		// ����� ���ҽ�Ų��.
		--m_iSize;

		// ���� ������ ��带 ��Ʈ�� �÷��� �Ʒ��� �������鼭 �����Ѵ�.
		m_pArray[0] = m_pArray[m_iSize];

		// ���� �÷��� �����ͷκ��� �Ʒ��� �������� �����Ѵ�.
		HeapIfy(0);

		return data;
	}

	int size()	const
	{
		return m_iSize;
	}

	int capacity()	const
	{
		return m_iCapacity;
	}

	bool empty()	const
	{
		return m_iSize == 0;
	}

	void Output(void(*pFunc)(const T& data))
	{
		for (int i = 0; i < m_iSize; ++i)
		{
			pFunc(m_pArray[i].m_Data);
		}
	}

private:
	void _insert(int iIndex)
	{
		if (iIndex <= 0)
			return;

		// �θ����� �ε����� ���Ѵ�. ���� ��� 1�϶� / 2�� �ϸ� 0�� ���ͼ� �θ� ������
		// �ε����� 2�϶� / 2�� �ϸ� 1�� �Ǿ �θ� �ȸ´�. ��, 1�� ���� �Ŀ� / 2�� ���ְ� �Ǹ�
		// ��Ȯ�ϰ� �θ� �ε����� ã�� �� �ִ�.
		int	iParent = (iIndex - 1) / 2;

		// �� ���� ���Ѵ�. �⺻ ���Լ��� �ִ����� �����ϰ� ��������ִ�.
		if (m_ComFunc(m_pArray[iIndex].m_Data, m_pArray[iParent].m_Data))
		{
			// �� ���� �����Ѵ�.
			T	temp = m_pArray[iIndex].m_Data;
			m_pArray[iIndex].m_Data = m_pArray[iParent].m_Data;
			m_pArray[iParent].m_Data = temp;

			_insert(iParent);
		}
	}

	void HeapIfy(int iIndex)
	{
		int	iLeftIndex = iIndex * 2 + 1;

		if (iLeftIndex >= m_iSize)
			return;

		// ������ �ε����� ���Ѵ�.
		int	iRightIndex = iLeftIndex + 1;

		// ���� �ڽİ� ������ �ڽ��� �ִ����̳� �ּ����̳Ŀ� ���� ��� �ڽĳ�带 �θ�� ������ �Ǵ��Ѵ�.
		int	iChildIndex = iLeftIndex;

		// ������ �ε����� ������� �۴ٸ� ������ �ڽĳ�尡 �ִٴ� �ǹ��̴�.
		if (iRightIndex < m_iSize)
		{
			// ���ʰ� ������ ���� ���Ͽ� ���� �ڽĳ���� ���� �ε����� �����Ѵ�.
			// �ٲ�� �� ��Ȳ�� �´ٸ� ������ �ڽĳ�带 �����Ѵ�. �װ� �ƴ϶�� ���� �ڽĳ�带 �����ؼ�
			// �θ�� ���ϰ� �Ѵ�.
			if (m_ComFunc(m_pArray[iRightIndex].m_Data, m_pArray[iLeftIndex].m_Data))
				iChildIndex = iRightIndex;
		}

		// �θ�� ���õ� �ڽĳ�带 ���Ѵ�.
		if (m_ComFunc(m_pArray[iChildIndex].m_Data, m_pArray[iIndex].m_Data))
		{
			// �� ���� �����Ѵ�.
			T	temp = m_pArray[iIndex].m_Data;
			m_pArray[iIndex].m_Data = m_pArray[iChildIndex].m_Data;
			m_pArray[iChildIndex].m_Data = temp;

			HeapIfy(iChildIndex);
		}
	}


private:
	// �⺻ ���Լ��� �����д�.
	bool Cmp(const T& src, const T& dest)
	{
		return src < dest;
	}
};
