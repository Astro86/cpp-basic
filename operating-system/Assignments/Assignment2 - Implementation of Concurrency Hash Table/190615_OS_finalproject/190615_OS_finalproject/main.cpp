#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <thread>
#include "LinkedList.h"
#include <windows.h>

// 실행 시간을 체크하기 위하여 define 해 두었다.
#define CHECK_TIME_START QueryPerformanceFrequency ((_LARGE_INTEGER*)&freq); QueryPerformanceCounter((_LARGE_INTEGER*)&start)
#define CHECK_TIME_END(a) QueryPerformanceCounter((_LARGE_INTEGER*)&end); a=(float)((float) (end - start)/freq)

#define HASH_NUM 10007

using namespace std;
// STL이 사용 금지라 헤더를 작성하여 직접 링크드리스트를 구현하였다.
// 그리고 벡터를 사용하여 해시테이블을 구현하였다.
CLinkedList<int> hash_table[10007];

// 정렬에 사용할 함수.
bool sort_func(const int& _1, const int& _2)
{
	return _1 < _2;
}

// 파일을 읽어들이는 함수다
void file_read(string file_name)
{
	string text_line;
	ifstream file(file_name);
	while (getline(file, text_line)) {
		char *str_buf = new char[100];
		strcpy(str_buf, text_line.c_str());
		char *key = strtok(str_buf, " ");
		char *value = strtok(nullptr, " ");
		hash_table[stoi(key) % HASH_NUM].push_back(stoi(key), stoi(value));
	}
	file.close();
}
// 쓰레드를 사용하여 초기 셋팅을 하는 함수.
void init()
{
	thread thread0(file_read, "input0.txt");
	thread thread1(file_read, "input1.txt");
	thread thread2(file_read, "input2.txt");
	thread thread3(file_read, "input3.txt");
	thread0.join();
	thread1.join();
	thread2.join();
	thread3.join();
	// push_back() 으로 입력을 하였으므로 전체를 돌며 sorting을 다시 해 주었다.
	for (int i = 0; i < HASH_NUM; ++i)
		hash_table[i].sort(sort_func);
}
// 리스트에 데이터를 집어넣는 함수
void list_insert(const int key, const int value)
{
	int hash_key = key % HASH_NUM;
	CListIterator<int> iter;
	bool flag = false;
	for (iter = hash_table[hash_key].begin(); iter != hash_table[hash_key].end(); ++iter)
	{
		if (iter->m_Key == key)
		{
			iter->m_Value = value;
			flag = true;
			break;
		}
	}

	if (!flag)
		hash_table[hash_key].push_back(key, value);
	
	// 값에 변화가 생겼다면 다시 sorting을 해줘야한다.
	hash_table[hash_key].sort(sort_func);
	
	if (!flag)
		cout << 0 << endl;
	else
		cout << 1 << endl;
}

// 인자로 들어온 값들을 찾아주는 함수
void list_find(const int key, const int value)
{
	int hash_key = key % HASH_NUM;

	// iterator를 사용하여 순회하며 값을 찾는다.
	CListIterator<int> iter;
	int iter_cnt = 0;
	bool flag = false;
	for (iter = hash_table[hash_key].begin(); iter != hash_table[hash_key].end(); ++iter)
	{
		if (iter->m_Key == key && iter->m_Value == value)
		{
			flag = true;
			break;
		}
		++iter_cnt;
	}
	if (flag)
		cout << hash_key << " " << iter_cnt << endl;
	else
		cout << -1 << endl;
}

// 삭제하는 함수
void list_delete(const int key)
{
	int hash_key = key % HASH_NUM;
	if (hash_table[hash_key].erase(key))
		cout << 0 << endl;
	else
		cout << -1 << endl;
}

// 0, 1, 2 로 들어오는 입력에 대한 처리를 담당하는 루틴
void routine()
{
	string text_line;
	ifstream file("bigin.txt");
	while (getline(file, text_line)) {
		char *str_buf = new char[100];
		strcpy(str_buf, text_line.c_str());
		int type = stoi(strtok(str_buf, " "));
		
		if (type == 0)
		{
			exit(0);
		}
		else if (type == 1)
		{
			int key = stoi(strtok(nullptr, " "));
			int value = stoi(strtok(nullptr, " "));
			list_insert(key, value);
		}
		else if (type == 2)
		{
			int key = stoi(strtok(nullptr, " "));
			int value = stoi(strtok(nullptr, " "));
			list_find(key, value);
		}
		else if (type == 3)
		{
			int key = stoi(strtok(nullptr, " "));
			list_delete(key);
		}
	}
	file.close();
}

int main()
{
	// 시간을 체크하기 위한 변수와 루틴.
	// 윈도우용 실행시간 체크 함수로 사용하였다.
	__int64 start, freq, end;
	float result_time = 0;

	CHECK_TIME_START;
	// 쓰레드를 사용하여 전체 루틴을 만들어둔다.
	init();
	CHECK_TIME_END(result_time);
	// 입력을 받아서 처리하는 루틴이다.
	routine();

	return 0;
}