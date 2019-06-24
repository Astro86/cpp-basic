﻿#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <tuple>
#include <algorithm>
using namespace std;

int testcase, job;
vector<pair<int, int>> job_vector;

// turnaround_time : 작업이 완료된 시간 - 작업이 도착한 시간
// response_time : 작업 시작된 시간 - 작업이 도착한 시간

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