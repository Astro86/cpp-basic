#include <iostream>
#include <string>

using namespace std;

class QueueNode
{
public : 
	QueueNode()
	{
	}
	~QueueNode()
	{
	}

public : 
	string	m_Menu;
	int		m_iPrice;
};

class CircleQueue
{
public:
	CircleQueue()
	{
		m_pArr = new NODE[50 + 1];
		m_iSize = 0;
		m_iCapacity = 50 + 1;
	}
	~CircleQueue()
	{
		delete[]	m_pArr;
	}

	int size()	const
	{
		return m_iSize;
	}

	void insertOrder(string menu, int price)
	{
		if (m_iSize == m_iCapacity)
		{
			return;
		}

		m_pArr[m_iSize].m_Menu = menu;
		m_pArr[m_iSize].m_iPrice = price;
		
		++m_iSize;
	}

	bool deleteOrder(string& menu, int& iPrice)
	{
		if (m_iSize == 0)
			return false;

		menu = m_pArr[0].m_Menu;
		iPrice = m_pArr[0].m_iPrice;

		for (int i = 0; i < m_iSize - 1; ++i)
		{
			m_pArr[i] = m_pArr[i + 1];
		}

		--m_iSize;

		return true;
	}

	bool deleteOrder(const string& menu)
	{
		if (m_iSize == 0)
			return false;

		for (int i = 0; i < m_iSize; ++i)
		{
			if (m_pArr[i].m_Menu == menu)
			{
				for (int j = i; j < m_iSize - 1; ++j)
				{
					m_pArr[j] = m_pArr[j + 1];
				}
				--m_iSize;

				return true;
			}
		}

		return false;
	}
	void atOrder(int idx)
	{
		cout << m_pArr[idx].m_Menu << " " << m_pArr[idx].m_iPrice << endl;
	}
	void setOrder(int idx, string menu, int price)
	{
		cout << "prev order : " << m_pArr[idx].m_Menu << " " << m_pArr[idx].m_iPrice << endl;
		m_pArr[idx].m_Menu = menu;
		m_pArr[idx].m_iPrice = price;

		cout << "new order : " << m_pArr[idx].m_Menu << " " << m_pArr[idx].m_iPrice << endl;
	}

private : 
	typedef QueueNode	NODE;
	typedef QueueNode*	PNODE;

public : 
	PNODE	m_pArr;
	int		m_iSize;
	int		m_iCapacity;
};

int main()
{ 
	int iQuery;
	cin >> iQuery;
	CircleQueue CQ;

	while (true)
	{
		if (!iQuery)
			break;

		string iUserInput;
		cin >> iUserInput;

		if (iUserInput == "insert")
		{
			string	inputMenu;
			int		inputPrice;

			cin >> inputMenu >> inputPrice;
			CQ.insertOrder(inputMenu, inputPrice);
			
		}
		else if (iUserInput == "delete")
		{
			string deleteMenu;
			cin >> deleteMenu;
			CQ.deleteOrder(deleteMenu);
		}
		else if (iUserInput == "at")
		{
			int iInputIdx;
			cin >> iInputIdx;
			CQ.atOrder(iInputIdx);
		}
		else if (iUserInput == "set")
		{
			int iInputIdx;
			string	newMenu;
			int		iNewPrice;
			cin >> iInputIdx >> newMenu >> iNewPrice;
			CQ.setOrder(iInputIdx, newMenu, iNewPrice);
		}


		--iQuery;
	}

	for (int i = 0; i < CQ.size(); ++i) 
	{
		CQ.atOrder(i);
	}

	return 0;
}