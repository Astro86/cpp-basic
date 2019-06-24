# 과제 내용 및 제한 사항

![img3](https://user-images.githubusercontent.com/35681772/59994741-ef40c580-968f-11e9-83a2-f9cab8b10ed6.png)

![img4](https://user-images.githubusercontent.com/35681772/59994767-097aa380-9690-11e9-92a2-14ae4bfd6caa.png)

---

# 과제 구현 결과

## 1. 개요
설계의 목적, 요구사항, 개발환경 등 기본 사항들을 정리
(개발환경은 학생 개개인의 개발환경을 작성하되, 구현은 채점서버에 맞게 구현해야 함)

### 1-1. 설계의 목적

Thread를 사용하여 input값을 읽어 들이고 Hash table을 구현하여 그 뒤의 적절한 입력에 따른 처리가 이뤄지도록 하였다.

### 1-2. 요구사항

STL 사용이 금지였기 때문에 직접 구현하였다. 또한 Windows 에서 C++을 사용하였고 첨부된 주의사항을 모두 준수하였다.

### 1-3. 개발환경

>OS : Windows 10 Pro<br>
Processor : Intel(R) Core(TM) i7-5557 CPU @ 3.10GHz<br>
RAM : 16GB<br>
IDE : Microsoft Visual Studio Community 2017 ver 15.9.9<br>
Language : Visual C++ 2017

---

## 2. 자료구조 및 기능

### 2-1. 자료구조

STL 사용이 불가능하여 linked list를 직접 구현하여 사용하였다. 최초엔 linked list 내에 linked list를 두는 방식으로 Hash table 을 구현하려고 c++ template을 사용하여 구현하였으나, 나중에 배열로 바꾸면서 의미가 없어지게 되었다. 다시 int 형으로 수정하려니 번거로워서 template을 사용한 채 그대로 두었다.

Hash table의 max key value가 10007 이기 때문에 배열의 크기는 10007을 넘어가지 않는다. 따라서 10007 크기를 가진 배열 내에 링크드리스트를 두어 Hash table을 구현하였다.

### 2-2. 기능

문제의 요구사항을 구현하는 데에 있어 필요한 기능은 다음과 같다.
1)	삽입 : push_back() 을 구현하여 사용하였다.
2)	탐색 : iterator를 구현하여 iterator가 순회하며 적절한 값이 있는지 없는지에 대한 수행을 할 수 있도록 하였다.
3)	삭제 : erase 함수를 linked list class 내에 구현하여 사용하였다.

---

## 3. 기능별 알고리즘 명세

### 3-1. main()
```c++
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
```

### 3-2. sort_func() & file_read()
```c++
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
```

Sort_func 함수는 정렬에 사용할 함수를 따로 만들어 함수포인터로 넘김으로써 오름차순 및 내림차순 등 외부에서 인자로 넘기게 하여 사용 편의성을 높혔다. Key와 value 모두 정렬할 생각으로 구현해 두었으나 문제의 요구조건상 value만 정렬하면 충분했다.

File_read 함수는 쓰레드가 실행할 함수이다. 쓰레드에서 각 함수를 받아 처리하게 된다.


### 3-3. init()
```c++
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
```
Init() 함수는 쓰레드를 이용하여 txt 파일로 제시된 입력들을 받아온다.

### 3-4. list_insert()
```c++
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
```

### 3-5. list_find()
```c++
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
```

### 3-6. list_delete()
```c++
// 삭제하는 함수
void list_delete(const int key)
{
	int hash_key = key % HASH_NUM;
	if (hash_table[hash_key].erase(key))
		cout << 0 << endl;
	else
		cout << -1 << endl;
}
```

### 3-7. routine()
```c++
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
```
기본 루틴을 처리하는 함수이다. 쓰레드를 통해 입력들을 모두 처리하고 그 이후에 input case에 대해 적절한 함수를 실행시켜 처리하였다.

---

## 4. 실행 결과

![image](https://user-images.githubusercontent.com/35681772/59995272-a38f1b80-9691-11e9-8603-256c7cf0b548.png)
