#include<iostream>
#include<vector>
#include<stack>

using namespace std;

int N, M;
int min_count=1000;
int man_num=0;

vector<vector<int>> map;
vector<vector<int>> map_visited;
vector<int> man;

void DFS(int A) {
	
	vector<int>isVisited;
	stack<int> s;

	isVisited.assign(N, 0);
	s.push(A);
	int count = 0;

	while (!s.empty()) {
		int k = s.top();
		s.pop();

			for(int i=0; i<N; i++){
				if (map[k][i] != 0 && map_visited[k][i] == 0) {
					isVisited[i] = count;
					s.push(i);
					map_visited[k][i] = 1;
					map_visited[i][k] = 1;
				}
			}
		count++;
	}
	
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		cnt += isVisited[i];
	}

	if (min_count > cnt) {
		man_num = A;
		min_count = cnt;
	}
}

int main(void) {
	
	int man_number=0;
	int A, B;

	cin >> N >> M;

	map.assign(N, vector<int>(N, 0));
	man.assign(N, 0);

	for (int i = 0; i < M; i++) {
		cin >> A >> B;
		map[A-1][B-1] = 1;
		map[B-1][A-1] = 1;
	}

	for (int i = 0; i < N; i++) {
		map_visited.assign(N, vector<int>(N, 0));
		DFS(i);
	}

	cout << man_num+1;
}