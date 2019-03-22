
#include "value.h"

bool Empty(PLIST pList)
{
	return pList->iSize == 0;
}

void Insert(PLIST pList)
{
	// 추가할 데이터를 입력받는다.
	system("cls");

	STUDENT	tStd = {};

	cout << "이름 : ";

	cin.clear();
	cin.ignore(1024, '\n');
	cin.getline(tStd.strName, NAME_SIZE);

	cout << "국어 : ";
	cin >> tStd.iKor;

	cout << "영어 : ";
	cin >> tStd.iEng;

	cout << "수학 : ";
	cin >> tStd.iMath;

	tStd.iTotal = tStd.iKor + tStd.iEng + tStd.iMath;

	tStd.fAvg = tStd.iTotal / 3.f;

	// 데이터를 담아둘 노드를 생성한다.
	PLISTNODE	pNode = new LISTNODE;

	pNode->tStudent = tStd;
	pNode->pNext = 0;

	// pFirst가 NULL일 경우라면 노드가 아예 추가되어 있지 않다는 것이다.
	// 즉, 노드를 처음 추가한다는 것이다. 그러므로 NULL인지 체크해서
	// NULL일 경우 pFirst에 노드의 주소를 넣어준다.
	if (!pList->pFirst)
		pList->pFirst = pNode;

	// 구조체나 클래스의 경우 포인터 변수가 해당 구조체 혹은 클래스 타입의
	// 일반 변수의 메모리 주소를 가지고 있을 경우 ->로 접근하게 되면 가리
	// 키는 대상의 멤버에 접근하는 것이다.
	// (*pList).  과 pList-> 는 같다.
	else
		pList->pCurrent->pNext = pNode;

	// 다음노드 추가가 완료되면 pCurrent에 현재 생성한 노드를 주어서
	// 마지막 노드를 pCurrent가 가리키도록 한다.
	pList->pCurrent = pNode;

	++pList->iSize;
}

void OutputStudent(PSTUDENT pStudent)
{
	cout << pStudent->strName << "\t" << pStudent->iKor << "\t" <<
		pStudent->iEng << "\t" << pStudent->iMath << "\t" << pStudent->iTotal <<
		"\t" << pStudent->fAvg << endl;
}

void Output(PLIST pList)
{
	// pNode에 리스트의 첫번째 노드의 주소를 담아놓는다.
	// pNode의 역할은 각 노드를 방문하기 위해서 이다.
	PLISTNODE	pNode = pList->pFirst;

	// pNode가 NULL이 아닐 경우라면 true가 나오게 되어 계속 반복된다.
	// 즉 NULL일때까지 돈다는 의미는 계속 다음 노드를 얻어와서 설정하면
	// 마지막 노드의 다음 노드는 0이므로 마지막 노드까지 반복하게
	// 되는 것이다.
	cout << "이름\t국어\t영어\t수학\t총점\t평균" << endl;

	while (pNode)
	{
		OutputStudent(&pNode->tStudent);
		pNode = pNode->pNext;
	}

	cout << endl;
}

void OutputNode(PLIST pList)
{
	system("cls");
	cout << "========= 학생 출력 =========" << endl;

	cout << "노드 수 : " << pList->iSize << endl;

	Output(pList);

	system("pause");
}

void Clear(PLIST pList)
{
	PLISTNODE	pNode = pList->pFirst;

	while (pNode)
	{
		PLISTNODE	pNext = pNode->pNext;
		delete	pNode;
		pNode = pNext;
	}

	pList->iSize = 0;
	pList->pFirst = 0;
	pList->pCurrent = 0;
}

void DeleteNode(PLIST pList)
{
	system("cls");

	if (Empty(pList))
	{
		cout << "리스트가 비어있습니다." << endl;
		system("pause");
		return;
	}

	Output(pList);

	cout << "삭제할 이름을 입력하세요 : ";
	char	strName[NAME_SIZE] = {};

	cin.clear();
	cin.ignore(1024, '\n');
	cin.getline(strName, NAME_SIZE);

	// 노드를 지우기 위해서는 지울 노드와 이전 노드가 필요하다.
	// 왜냐하면 이전 노드는 지울 노드를 가리키고 있는데 노드를 지우게 되면
	// 지운 노드의 이전 노드와 지운 노드의 다음 노드를 연결해 주어야 하기 때문이다.
	// 그래야 연결이 유지가 된다.
	PLISTNODE	pNode = pList->pFirst;
	PLISTNODE	pPrev = NULL;

	// 노드가 NULL이면 마지막 다음 노드까지 왔으므로 더이상 노드가 없기 때문에
	// 반복을 종료한다.
	while (pNode)
	{
		// 노드를 찾았다면 반복문을 빠져나간다.
		// 빠져나가게 되면 지울 노드는 pNode가 주소를 가지고 있게 되고
		// 이전 노드는 pPrev에 저장된다. 처음 노드를 지우게 된다면 이전 노드는 없으므로
		// 여기서 첫 노드부터 바로 빠져나가게 되어 이전 노드는 NULL로 저장되어있다.
		if (strcmp(pNode->tStudent.strName, strName) == 0)
			break;

		// 다음 노드를 탐색해야 하므로 이전 노드를 현재 노드로 지정한다.
		pPrev = pNode;
		// 다음 노드를 얻어온다.
		pNode = pNode->pNext;
	}

	// pNode가 NULL이라면 마지막 노드까지 탐색했는데 없다는 의미이다.
	if (!pNode)
	{
		cout << "데이터를 찾을 수 없습니다." << endl;
		system("pause");
		return;
	}

	// 만약 첫번째 노드를 지우게 된다면 첫번째 노드는 이전 노드가 없다.
	// 이전 노드가 NULL이 아닌 경우에만 이전 노드의 다음 노드를 지울 노드의
	// 다음 노드로 설정한다.
	if (pPrev)
		pPrev->pNext = pNode->pNext;

	delete	pNode;
	--pList->iSize;

	cout << "노드 삭제 완료" << endl;

	Output(pList);

	system("pause");
}

PLISTNODE _ReverseRecursive(PLISTNODE pNode, PLISTNODE* pFirst)
{
	if (!pNode->pNext)
	{
		// 이중 포인터는 포인터 변수의 메모리 주소를 담는 변수이다. 일반 변수의 메모리 주소를 일반 포인터가
		// 알고 있다면 그 메모리에 접근하여 값을 변경하는 것이 가능한 것처럼 이중 포인터는 포인터변수의
		// 메모리 주소를 알고 있다면 그 포인터변수가 가지고 있는 일반 변수의 메모리 주소를 변경해줄 수 있다.
		// 즉 포인터가 가리키는 대상을 변경 가능해지는 것이다.
		*pFirst = pNode;
		return pNode;
	}

	PLISTNODE pRec = _ReverseRecursive(pNode->pNext, pFirst);

	pRec->pNext = pNode;

	return pNode;
}

void ReverseRecursive(PLIST pList)
{
	PLISTNODE	pNode = _ReverseRecursive(pList->pFirst, &pList->pFirst);
	pNode->pNext = 0;

	pList->pCurrent = pNode;
}

void _Reverse(PLIST pList)
{
	PLISTNODE	pPrev = NULL;
	PLISTNODE	pNode = pList->pFirst;
	PLISTNODE	pNext = NULL;
	PLISTNODE	pNextNext = pNode->pNext;

	while (pNode)
	{
		pNext = pNextNext;
		if (pNext)
			pNextNext = pNext->pNext;

		pNode->pNext = pPrev;

		pPrev = pNode;
		pNode = pNext;
	}

	pNode = pList->pFirst;
	pList->pFirst = pList->pCurrent;
	pList->pCurrent = pNode;
}

void Reverse(PLIST pList)
{
	system("cls");

	if (Empty(pList))
	{
		cout << "리스트가 비어있습니다." << endl;
		system("pause");
		return;
	}

	cout << "Reverse" << endl;

	Output(pList);

	//_Reverse(pList);
	ReverseRecursive(pList);

	Output(pList);

	system("pause");
}

void Mirror(PLIST pList)
{
	system("cls");

	cout << "Mirror" << endl;

	if (Empty(pList))
	{
		cout << "리스트가 비어있습니다." << endl;
		system("pause");
		return;
	}

	Output(pList);

	_Reverse(pList);

	Output(pList);

	_Reverse(pList);

	system("pause");
}

int main()
{
	// 리스트 변수를 생성한다.
	// 리스트 구조체 안의 first는 첫번째 노드의 주소를 담고있다.
	// 노드가 없을 경우 NULL이다.
	// current는 마지막에 추가한 노드를 알고있다.
	// 노드가 없을 경우 NULL이고 이 current뒤에 새로 추가된 노드가
	// 추가된다.
	// 첫번째 노드를 알아야 다음노드의 주소로 타고들어가면서 모든 노드를
	// 순회가 가능하다. 그러므로 리스트 구조체에 첫번째 노드를 담아두고
	// 사용하는 것이다.
	LIST	tList = {};

	while (true)
	{
		system("cls");
		cout << "1. 학생추가" << endl;
		cout << "2. 학생삭제" << endl;
		cout << "3. 학생전체출력" << endl;
		cout << "4. 리스트 뒤집기" << endl;
		cout << "5. Mirror" << endl;
		cout << "6. 종료" << endl;
		int	iInput;
		cout << "메뉴를 선택하세요 : ";
		cin >> iInput;

		if (iInput == 6)
			break;

		switch (iInput)
		{
		case 1:
			// 데이터를 입력받아서 노드를 추가한다.
			Insert(&tList);
			break;
		case 2:
			DeleteNode(&tList);
			break;
		case 3:
			OutputNode(&tList);
			break;
		case 4:
			Reverse(&tList);
			break;
		case 5:
			Mirror(&tList);
			break;
		}
	}

	Clear(&tList);

	return 0;
}