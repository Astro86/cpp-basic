# 과제 내용 및 제한 사항

![img1](https://user-images.githubusercontent.com/35681772/59993198-5491b800-968a-11e9-87ab-e1d021fa9e40.png)

![img2](https://user-images.githubusercontent.com/35681772/59993205-5b202f80-968a-11e9-90c6-653144454505.png)

<br>

# 과제 구현 결과
## 1. 구현 환경
>OS : Window<br>
IDE : Visual Studio 2017 (v141) (Windows SDK Version : 10.0.17763.0)<br>
Language : C++

## 2. 함수 설명

### 2-1. main()

```c++
int main() {
	cin >> testcase;
	while (testcase--) {
		job_vector.clear();
		cin >> job;
		for (int i = 0; i < job; ++i) {
			int job_arrival_time = 0, job_amount = 0;
			cin >> job_arrival_time >> job_amount;
			job_vector.push_back({ job_arrival_time, job_amount });
		}
		FCFS();
		SJF();
		newRR();
	}
	//system("pause");
	return 0;
}
```
메인함수에서는 입력을 받고 각 함수를 호출하는 형태로 구현하였다.

---

### 2-2. FCFS()
```c++
// First In First Served, 선입선출
void FCFS() {
	vector<pair<int, int>> FCFS_job_vector = job_vector;
	int total_turnaround_time = 0, total_response_time = 0, accumulated_time = 0;

	// 작업의 처리가 시작되는 첫 시간을 할당해준다.
	accumulated_time = FCFS_job_vector.front().first;
	for (int i = 0; i < FCFS_job_vector.size(); ++i) {
		int response_time = 0;
		if (accumulated_time - FCFS_job_vector[i].first < 0)
			accumulated_time = FCFS_job_vector[i].first;
		// response_time은 누적시간에서 현재 작업의 도착시간을 뺀 값으로 구한다.
		response_time += accumulated_time - FCFS_job_vector[i].first;
		// 전체 response_time은 작업별 response_time의 누적합을 구한다.
		total_response_time += response_time;
		// 누적시간은 작업별 실행시간(job_amount)들의 누적합으로 구한다.
		accumulated_time += FCFS_job_vector[i].second;
		// 전체 turnaround_time은 작업별 turnaround_time의 누적합으로 구한다.
		total_turnaround_time += (accumulated_time - FCFS_job_vector[i].first);
	}
	cout << total_turnaround_time << " " << total_response_time << endl;
}
```
FCFS 함수는 말그대로 먼저 들어온 작업을 처리하는 알고리즘이기 때문에, 입력으로 들어온 벡터 그대로 순차적으로 계산하였다. 
  * 선입선출(First In First Out, FIFO) 스케줄링
FIFO 스케줄링의 문제점 : Convoy effect
Convoy effect란 짧은 시간동안 리소스를 사용 할 프로세스들이 오랜 시간동안 리소스를 사용하는 프로세스가 종료될 때 까지 대기하여 비효율이 발생하는 현상.

---

### 2-3. SFJ()
```c++

// SJF에선 최단 작업을 우선 실행시키기 때문에 두번째 인자(job_amount)가 짧은 순서대로 실행을 시키고,
// 그 실행 도중 다른 인자가 들어왔는데 만약 작업이 더 빠른게 들어온 경우 그 순서대로 정렬을 해 준다.
// 만약 arrival time이 같으면 더 빠른 작업 순으로 정렬하고
// 그 실행시간 도중 다른 job이 들어오면 그 순서대로 재 정렬한다.
vector<pair<int, int>> SJF_sort() {
	list<pair<int, int>> tmp_job_list = {};
	vector<pair<int, int>> return_job_vector = {};
	int accumulated_time = 0;

	// 가변적인 삽입 삭제를 용이하게 하고자 임시 list 생성
	for (auto job : job_vector) {
		tmp_job_list.push_back(job);
	}

	// 입력으로 들어온 정렬 순서에 의하면 첫번째 작업은 확실하게 결정할 수 있다.
	pair<int, int> first_job = {};
	list<pair<int, int>>::iterator remove_iter;
	for (auto iter = tmp_job_list.begin(); iter != tmp_job_list.end(); ++iter) {
		if (!first_job.first && !first_job.second) {
			first_job = *iter;
			remove_iter = iter;
		}
		if (first_job.first != iter->first)
			break;
		if (iter->second < first_job.second) {
			first_job = *iter;
			remove_iter = iter;
		}
	}
	return_job_vector.push_back(first_job);
	accumulated_time += first_job.first + first_job.second;
	tmp_job_list.erase(remove_iter);

	// 그다음 실행중인 작업을 기준으로 다음 작업들의 우선순위를 결정한다.
	// 전체 리스트를 돌면서 그 다음 실행하는 작업들의 우선순위를 결정하게 된다.
	while (!tmp_job_list.empty()) {
		pair<int, int> next_job = { INT_MAX, INT_MAX };
		if (tmp_job_list.front().first > accumulated_time) {
			accumulated_time = tmp_job_list.front().first;
		}
		for (auto iter = tmp_job_list.begin(); iter != tmp_job_list.end(); ++iter) {
			if ((accumulated_time >= iter->first) && (iter->second < next_job.second)) {
				next_job = *iter;
				remove_iter = iter;
			}
		}
		accumulated_time += next_job.second;
		return_job_vector.push_back(next_job);
		tmp_job_list.erase(remove_iter);
	}
	return return_job_vector;
}

// Shortest Job First, 최단 작업 우선
void SJF() {
	vector<pair<int, int>> SJF_job_vector = SJF_sort();
	int total_turnaround_time = 0, total_response_time = 0, accumulated_time = 0;

	accumulated_time = SJF_job_vector.front().first;

	for (int i = 0; i < SJF_job_vector.size(); ++i) {
		int response_time = 0;
		if (accumulated_time - SJF_job_vector[i].first < 0)
			accumulated_time = SJF_job_vector[i].first;
		response_time += accumulated_time - SJF_job_vector[i].first;
		total_response_time += response_time;
		accumulated_time += SJF_job_vector[i].second;
		total_turnaround_time += (accumulated_time - SJF_job_vector[i].first);
	}
	cout << total_turnaround_time << " " << total_response_time << endl;
}

```

최단작업을 우선적으로 처리하기 때문에 가장 빠르게 들어온 입력(같다면 실행시간이 더 짧은 입력)을 실행시키고 그 도중 다른 작업이 들어온 경우 그에 맞춰 순서가 정해지도록 구현하였다.
  * 최단 작업 우선(Shortest Job First, SJF) 스케줄링 : 소요시간↑, 응답시간↓
모든 작업이 동시에 도착한다는 가정 하에, 가장 짧은 실행시간을 가진 프로세스를 먼저 실행시킨다. 이 방법은 가정이 성립한다면 대안이 될 수 있으나 불가능함.


---

### 2-4. RR(Round Robin)

```c++

// turnaround_time : 작업이 완료된 시간 - 작업이 도착한 시간
// response_time : 작업 시작된 시간 - 작업이 도착한 시간
bool isInQueue(queue<tuple<int, int, int>>& req_q, tuple<int, int, int> chk_job) {
	queue<tuple<int, int, int>> tmp_q = req_q;
	while (!tmp_q.empty()) {
		auto ready_job = tmp_q.front();
		tmp_q.pop();
		if (get<2>(chk_job) == get<2>(ready_job))
			return true;
	}
	return false;
}

void new_check_job(queue<tuple<int, int, int>>& req_q, list<tuple<int, int, int>>& job_list, int time) {
	for (auto job : job_list) {
		// 현재 큐에 있지 않고, 아직 실행을 안한 작업 중 도착시간이 현재시간과 같거나 그 전인경우
		// 레디큐에 push
		if (get<0>(job) <= time) {
			req_q.push(job);
			job_list.remove(job);
			new_check_job(req_q, job_list, time);
			return;
		}
	}
}

void newRR() {
	list<tuple<int, int, int>> RR_job_list = {};
	list<tuple<int, int, int, int>> RR_job_start_finish_arrive_idx = {};
	int job_count = 0;
	int total_job_amount = 0;

	// RR을 위한 벡터를 새로 설정해준다. 작업별 인덱스를 작업번호로 쓰기위해 새로 할당함.
	for (int i = 0; i < job_vector.size(); ++i) {
		RR_job_list.push_back({ job_vector[i].first, job_vector[i].second, i });
		total_job_amount += job_vector[i].second;
	}

	// 작업의 시작시간과 종료시간을 저장하는 배열
	// 0 : 시작시간, 1 : 종료시간
	queue<tuple<int, int, int>> request_queue = {};
	auto first_job = RR_job_list.front();
	RR_job_list.pop_front();
	request_queue.push(first_job);
	const int time_slice = 4;
	int accumulated_time = get<0>(first_job);

	while (true) {
		if (total_job_amount <= 0)
			break;

		// 만약 위 조건에서 전체 작업량은 남아있는데 현재 큐는 비어있는경우
		// 누적시간보다 새로운 작업이 그 이후에 시작되기 때문에 갱신해줘야한다.
		if (request_queue.empty()) {
			auto job = RR_job_list.front();
			RR_job_list.pop_front();
			accumulated_time = get<0>(job);
			request_queue.push(job);
		}
		else {
			auto job = request_queue.front();
			request_queue.pop();

			// job의 잔여 작업량이 time_slice 이상인경우
			if (get<1>(job) >= time_slice) {
				// 현재 작업의 시작시간이 설정되지 않은 경우
				bool already_check = false;
				for (auto already : RR_job_start_finish_arrive_idx) {
					if (get<3>(already) == get<2>(job)) {
						already_check = true;
						break;
					}
				}

				if (!already_check)
					RR_job_start_finish_arrive_idx.push_back({ accumulated_time, NULL,get<0>(job) ,get<2>(job) });

				get<1>(job) -= time_slice;
				accumulated_time += time_slice;
				total_job_amount -= time_slice;
				// 시간이 갱신되면 항상 새로운 작업이 큐에 쌓여야하는지 체크한다.
				new_check_job(request_queue, RR_job_list, accumulated_time);

				// 현재 작업이 종료된 경우 종료시간을 저장한다.
				if (get<1>(job) == 0) {
					for (auto already : RR_job_start_finish_arrive_idx) {
						if (get<2>(job) == get<3>(already)) {
							RR_job_start_finish_arrive_idx.remove(already);
							get<1>(already) = accumulated_time;
							RR_job_start_finish_arrive_idx.push_back(already);
							break;
						}
					}
				}
				// 현재 작업의 amount_time이 아직 남은경우 다시 큐로 넣는다.
				else
					request_queue.push(job);
			}

			// job의 잔여 작업량이 time_slice 미만인경우
			else {
				int remain_time = get<1>(job);
				get<1>(job) -= remain_time;
				accumulated_time += remain_time;
				total_job_amount -= remain_time;
				// 시간이 갱신되면 항상 새로운 작업이 큐에 쌓여야하는지 체크한다.
				new_check_job(request_queue, RR_job_list, accumulated_time);

				// 작업이 종료되었으므로 종료시간을 설정해준다.
				for (auto already : RR_job_start_finish_arrive_idx) {
					if (get<2>(job) == get<3>(already)) {
						RR_job_start_finish_arrive_idx.remove(already);
						get<1>(already) = accumulated_time;
						RR_job_start_finish_arrive_idx.push_back(already);
						break;
					}
				}
			}
		}
	}
	int total_turnaround_time = 0, total_response_time = 0;
	for (auto job : RR_job_start_finish_arrive_idx) {
		total_turnaround_time += (get<1>(job) - get<2>(job));
		total_response_time += (get<0>(job) - get<2>(job));
	}
	cout << total_turnaround_time << " " << total_response_time << endl;
}
```

RR방식을 구현할 땐, 큐를 이용하였다. 큐에 작업들을 넣고 시간이 갱신될 때(time-slice 만큼의 시간이 흘렀을 때)마다 아직 실행하지 않은 작업이 있는지를 확인하고 있다면 새로 작업을 넣어줬다.




  * 라운드 로빈(Round-Robin, RR) 스케줄링(a.k.a. 타임 슬라이싱) : 응답시간↑, 소요시간↓
응답시간(Response Time)에 민감한 스케줄러가 필요해서 등장하였다.
라운드 로빈 방법은 작업이 끝날 때 까지 기다리지 않고 "일정 시간" 후 실행 큐의 다음 작업으로 전환. 여기서 작업이 실행되는 "일정 시간" 을 타임 슬라이스(Time Slice) 또는 스케줄링 퀀텀(Scheduling Quantum) 이라 부른다.


---

## 3. 실행 화면

### 3-1. small_input.txt 실행화면

![image](https://user-images.githubusercontent.com/35681772/59993613-ddf5ba00-968b-11e9-99f6-39c3a01f3152.png)

---

### 3-2. big_input.txt 실행화면


![image](https://user-images.githubusercontent.com/35681772/59993634-f1a12080-968b-11e9-9f56-bc6a2c6446e9.png)

---