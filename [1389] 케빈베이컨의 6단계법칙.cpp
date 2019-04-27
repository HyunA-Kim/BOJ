#include<iostream>
#include<vector>

using namespace std;

int N, M;
int MAX = 100000;
int min_count = 100000;	//최소 방문횟수
int man_num=0;

vector<vector<int>> map;

void Distance() {
	
	// Floyd-Warshall Algorithm(플로이드-워셜 알고리즘)

	//거쳐가는 정점
	for (int k = 0; k < N; ++k) {
		//출발하는 정점
		for (int i = 0; i < N; ++i) {
			//도착하는 정점
			for (int j = 0; j < N; ++j) {
				//최단거리 구하기
				if (map[i][k] + map[k][j] < map[i][j])
					map[i][j] = map[i][k] + map[k][j];
			}
		}
	}
	
	//최소한으로의 거리를 가진 사람구하기(find smaller distance)
	for (int i = 0; i < N; i++) {
		int temp = 0;
		for (int j = 0; j < N; j++) {
			temp += map[i][j];
		}
		//최소값보다 작을 갱신(when value is the smallest, update)
		if (temp < min_count) {
			min_count = temp;
			man_num = i + 1;
		}
	}
}

int main(void) {
	
	int A, B;

	cin >> N >> M;

	map.assign(N, vector<int>(N, 0));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			//같은정점 빼고는, 최대값으로 만들기
			map[i][j] = i == j ? 0 : MAX;
		}
	}

	for (int i = 0; i < M; i++) {
		cin >> A >> B;
		//연결된 선 1로 업데이트(when connected, update 1)
		map[A-1][B-1] = 1;
		map[B-1][A-1] = 1;
	}

	//연결간선 구하기(find distance over dot to dot)
	Distance();

	cout << man_num;	//가장 작은 방문횟수 가지고 있는 사람 출력
	return 0;
}
