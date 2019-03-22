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
			// Low의 값이 Pivot값과 비교하여 조건을 만족할 경우 반복하게 한다.
			// 단, Low의 값은 Right의 값을 벗어날 수 없다. Right가 가장 마지막 배열인덱스 이기 때문이다.
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
			// 피봇을 정해주고 피봇을 기준으로 분할한다.
			int	iPivot = Partition(pData, iLeft, iRight, func);

			// 왼쪽을 쪼갠다.
			QuickSort(pData, iLeft, iPivot - 1, func);
			// 오른쪽을 쪼갠다.
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

		// 왼쪽, 오른쪽으로 분할된 배열을 합한다.
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

		// 왼쪽 부분의 배열이 모두 정렬시킬 배열에 들어갔는지 판단한다.
		if (iSrcLeft > iMid)
		{
			// 오른쪽 배열의 남아있는 값을 넣어준다.
			for (int i = iSrcRight; i <= iRight; ++i)
			{
				m_pArray[iDest] = pData[i];
				++iDest;
			}
		}

		// 왼쪽 부분의 배열에 남은 값이 있으므로 그 값을 배열에 채워준다.
		else
		{
			for (int i = iSrcLeft; i <= iMid; ++i)
			{
				m_pArray[iDest] = pData[i];
				++iDest;
			}
		}

		//  정렬된 전체 데이터를 원본 배열에 넣어준다.
		for (int i = iLeft; i <= iRight; ++i)
		{
			pData[i] = m_pArray[i];
		}
	}

	static void MergeSort(T* pData, int iLeft, int iRight, const function<bool(const T&, const T&)> func)
	{
		if (iLeft < iRight)
		{
			// 가운데 인덱스를 구한다.
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
		// bind 함수는 함수포인터를 function 객체로 만들어준다.
		func = bind(pFunc, placeholders::_1, placeholders::_2);
		Sort(pData, iCount, func, eType);
	}
	
	template <typename ClassType>
	static void Sort(T* pData, int iCount, ClassType* pObj, bool(ClassType::*pFunc)(const T&, const T&), SORT_TYPE eType = ST_QUICK)
	{
		function<bool(const T&, const T&)>	func;
		// bind 함수는 함수포인터를 function 객체로 만들어준다.
		func = bind(pFunc, pObj, placeholders::_1, placeholders::_2);
		Sort(pData, iCount, func, eType);
	}
};

template <typename T>
T* CSort<T>::m_pArray = nullptr;