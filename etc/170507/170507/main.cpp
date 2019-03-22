
#include <iostream>

using namespace std;

// 재귀함수 : 자기 자신 내부에서 자기 자신을 또 호출하는 함수를 말한다.
// 재귀적으로 계속해서 자기자신을 호출하기 때문에 스택에 메모리가 계속 쌓인다.
// 그렇기 때문에 너무 많이 재귀를 호출하게 되면 Segment Fault가 출력되면서
// 에러가 발생한다. Stack이 꽉 찼기 때문이다.
int Factorial(int iNum)
{
	if (iNum == 1)
		return 1;

	return iNum * Factorial(iNum - 1);
}

int main()
{
	cout << Factorial(5) << endl;

	// 파일 입출력 : 파일을 만들고 읽어오는 기능을 제공한다.
	// C언어 방식은 fopen을 이용해서 하고 C++방식은 ifstream ,ofstream을
	// 이용해서 한다.
	FILE*	pFile = NULL;
	
	//질문 : 파일이라는 구조체 또는 클래스가 비주얼스튜디오에서
	//제공해주는 것인지? iostream 내에 저장이 되어있는것인지?

	while (true)
	{
		system("cls");
		cout << "1. 파일만들기" << endl;
		cout << "2. 파일읽기" << endl;
		cout << "3. 종료" << endl;
		cout << "메뉴를 선택하세요 : ";
		int	iMenu;
		cin >> iMenu;

		if (iMenu == 3)
			break;

		if (iMenu == 1)
		{
			char	strFileName[256] = {};
			cin.clear();
			cin.ignore(1024, '\n');

			cout << "파일 이름을 입력하세요 : ";
			cin.getline(strFileName, 256);

			// fopen_s 함수를 이용해서 파일을 만들고 읽어올 수 있다.
			// 1번 인자는 파일의 이중포인터가 들어가서 정상적으로 수행이 됐다면
			// 이 FILE*를 만들어준다.
			// 2번 인자는 파일의 경로가 들어간다.
			// 3번 인자는 파일 모드가 들어간다.
			// r : 읽기 w : 쓰기 a : 읽고쓰기
			// t : 텍스트파일 b : 바이너리파일
			// 2개를 조합해서 쓴다.
			// wb : 바이너리 파일을 만든다. rb : 바이너리 파일을 읽는다.
			// wt : 텍스트 파일을 만든다. 이런식이다.
			fopen_s(&pFile, strFileName, "wt");

			// 만약 생성된 File*가 NULL이라면 파일 만들기 실패다.
			if (pFile)
			{
				// 파일에 쓰는 작업을 할때는 fwrite 함수를 이용해서 파일에
				// 원하는 내용을 쓸 수 있다.
				char	str[256] = {};
				cout << "파일에 쓸 내용을 입력하세요 : ";
				cin.getline(str, 256);

				int	iLength = strlen(str);

				// 1번 인자는 저장하고자 하는 데이터의 메모리 주소를 넘겨준다.
				// 2번 인자는 타입의 크기를 지정한다.
				// 3번 인자는 개수를 지정한다.
				// 4번 인자는 File* 를 넣어준다.
				fwrite(&iLength, 4, 1, pFile);
				fwrite(str, 1, iLength, pFile);

				// 다 썼으면 반드시 닫아주어야 한다.
				fclose(pFile);
			}
		}

		else if (iMenu == 2)
		{
			char	strFileName[256] = {};
			cin.clear();
			cin.ignore(1024, '\n');

			cout << "파일 이름을 입력하세요 : ";
			cin.getline(strFileName, 256);

			fopen_s(&pFile, strFileName, "rt");
			
			//질문 : 스트링(문자열) 이 아닌 숫자로 이루어진 자료를 작성 또는 읽을때도
			//같은 fopen_s 함수를 사용하는지??

			if (pFile)
			{
				// 읽어올때는 해당 파일을 만든 순서대로 읽어와야 한다.
				// 왜냐하면 데이터가 만들때 넣어준 순서대로 저장되어 있기
				// 때문이다.
				int	iLength;
				fread(&iLength, 4, 1, pFile);
				char	str[256] = {};
				fread(str, 1, iLength, pFile);

				cout << "Content : " << str << endl;

				fclose(pFile);

				system("pause");
			}
		}
	}

	return 0;
}


