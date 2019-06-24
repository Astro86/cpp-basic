#pragma once

#include <functional>

using namespace std;

enum SORT_TYPE
{
	ST_QUICK,
	ST_MERGE,
	ST_BUBBLE
};

template <typename T>
class CSort
{
	// ================= QuickSort =================
private:
	static int Partition(T* pData, int iLeft, int iRight, const function<bool(const T&, const T&)> func)
	{
		int	iLow = iLeft;
		int	iHigh = iRight + 1;
		int	iPivot = pData[iLeft];

		do
		{
			// Low�� ���� Pivot���� ���Ͽ� ������ ������ ��� �ݺ��ϰ� �Ѵ�.
			// ��, Low�� ���� Right�� ���� ��� �� ����. Right�� ���� ������ �迭�ε��� �̱� �����̴�.
			do
			{
				++iLow;
			} while (iLow <= iRight && func(pData[iLow], iPivot));

			do
			{
				--iHigh;
			} while (iHigh >= iLeft && func(iPivot, pData[iHigh]));

			if (iLow < iHigh)
			{
				T data = pData[iLow];
				pData[iLow] = pData[iHigh];
				pData[iHigh] = data;
			}
		} while (iLow < iHigh);

		T data = pData[iLeft];
		pData[iLeft] = pData[iHigh];
		pData[iHigh] = data;

		return iHigh;
	}

	static void QuickSort(T* pData, int iLeft, int iRight, const function<bool(const T&, const T&)> func)
	{
		if (iLeft < iRight)
		{
			// �Ǻ��� �����ְ� �Ǻ��� �������� �����Ѵ�.
			int	iPivot = Partition(pData, iLeft, iRight, func);

			// ������ �ɰ���.
			QuickSort(pData, iLeft, iPivot - 1, func);
			// �������� �ɰ���.
			QuickSort(pData, iPivot + 1, iRight, func);
		}
	}

	// ================= MergeSort =================
private:
	static T*	m_pArray;

	static void Merge(T* pData, int iLeft, int iMid, int iRight, const function<bool(const T&, const T&)> func)
	{
		int	iSrcLeft = iLeft;
		int	iSrcRight = iMid + 1;
		int	iDest = iLeft;

		// ����, ���������� ���ҵ� �迭�� ���Ѵ�.
		while (iSrcLeft <= iMid && iSrcRight <= iRight)
		{
			if (func(pData[iSrcLeft], pData[iSrcRight]))
			{
				m_pArray[iDest] = pData[iSrcLeft];
				++iDest;
				++iSrcLeft;
			}

			else
			{
				m_pArray[iDest] = pData[iSrcRight];
				++iDest;
				++iSrcRight;
			}
		}

		// ���� �κ��� �迭�� ��� ���Ľ�ų �迭�� ������ �Ǵ��Ѵ�.
		if (iSrcLeft > iMid)
		{
			// ������ �迭�� �����ִ� ���� �־��ش�.
			for (int i = iSrcRight; i <= iRight; ++i)
			{
				m_pArray[iDest] = pData[i];
				++iDest;
			}
		}

		// ���� �κ��� �迭�� ���� ���� �����Ƿ� �� ���� �迭�� ä���ش�.
		else
		{
			for (int i = iSrcLeft; i <= iMid; ++i)
			{
				m_pArray[iDest] = pData[i];
				++iDest;
			}
		}

		//  ���ĵ� ��ü �����͸� ���� �迭�� �־��ش�.
		for (int i = iLeft; i <= iRight; ++i)
		{
			pData[i] = m_pArray[i];
		}
	}

	static void MergeSort(T* pData, int iLeft, int iRight, const function<bool(const T&, const T&)> func)
	{
		if (iLeft < iRight)
		{
			// ��� �ε����� ���Ѵ�.
			int	iMid = (iLeft + iRight) / 2;
			MergeSort(pData, iLeft, iMid, func);
			MergeSort(pData, iMid + 1, iRight, func);
			Merge(pData, iLeft, iMid, iRight, func);
		}
	}

private:
	static void Sort(T* pData, int iCount, const function<bool(const T&, const T&)> func, SORT_TYPE eType)
	{
		switch (eType)
		{
		case ST_QUICK:
			QuickSort(pData, 0, iCount - 1, func);
			break;
		case ST_MERGE:
			m_pArray = new T[iCount];
			MergeSort(pData, 0, iCount - 1, func);
			delete[]	m_pArray;
			m_pArray = nullptr;
			break;
		case ST_BUBBLE:
			break;
		}
	}

public:
	static void Sort(T* pData, int iCount, bool(*pFunc)(const T&, const T&), SORT_TYPE eType = ST_QUICK)
	{
		function<bool(const T&, const T&)>	func;
		// bind �Լ��� �Լ������͸� function ��ü�� ������ش�.
		func = bind(pFunc, placeholders::_1, placeholders::_2);
		Sort(pData, iCount, func, eType);
	}
	
	template <typename ClassType>
	static void Sort(T* pData, int iCount, ClassType* pObj, bool(ClassType::*pFunc)(const T&, const T&), SORT_TYPE eType = ST_QUICK)
	{
		function<bool(const T&, const T&)>	func;
		// bind �Լ��� �Լ������͸� function ��ü�� ������ش�.
		func = bind(pFunc, pObj, placeholders::_1, placeholders::_2);
		Sort(pData, iCount, func, eType);
	}
};

template <typename T>
T* CSort<T>::m_pArray = nullptr;