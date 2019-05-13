#include<iostream>
#include<vector>
#include<queue>

using namespace std;

vector<vector<char>> map;
vector<vector<int>> map_visited;
vector<vector<int>> isLand_visited;

queue<pair<int, int>> q;
queue<pair<int, int>> q2;
queue<pair<int, int>> q3;

int M, N;
int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
int minimum = 10000;

void findMaximum() {

	isLand_visited.assign(M, vector<int>(N, 0));
	int ans = 0;
	while (q3.size()) {
		int size = q3.size();
		while (size--) {
			
			int y = q3.front().first;
			int x = q3.front().second;
			q3.pop();

			for (int i = 0; i < 4; i++) {
				
				int new_y = y + dir[i][0];
				int new_x = x + dir[i][1];
				
				if (new_y < 0 || new_y >= M || new_x < 0 || new_x >= N) continue;

				if (map[new_y][new_x] == 'L' && isLand_visited[new_y][new_x] == 1) {
					isLand_visited[new_y][new_x] = 1;
					q3.push(make_pair(new_y, new_x));
				}
			}
			ans++;

		}
	}

	minimum = min(minimum, ans);
}

bool map_q() {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] == 'L' && map_visited[i][j] == 0) {
				map_visited[i][j] = 1;
				q.push(make_pair(i, j));
				q2.push(make_pair(i, j));
				return true;
			}
		}
	}
	return false;
}

void BFS() {
	while (1) {
		if (map_q() == false) return;
		while (!q.empty()) {
			int y = q.front().first;
			int x = q.front().second;
			q.pop();
			for (int i = 0; i < 4; i++) {
				int new_y = y + dir[i][0];
				int new_x = x + dir[i][1];
				
				if (new_y < 0 || new_y >= M || new_x < 0 || new_x >= N) continue;

				if (map[new_y][new_x] == 'L' && map_visited[new_y][new_x] == 0) {
					map_visited[new_y][new_x] = 1;
					q.push(make_pair(new_y, new_x));
					q2.push(make_pair(new_y, new_x));
				}
			}
		}
		int size = q2.size();
		while(size--){
			int y = q2.front().first;
			int x = q2.front().second;
			q2.pop();
			q3.push(make_pair(y, x));
			findMaximum();
		}
	}
}

int main(void) {

	cin >> M >> N;
	
	map.assign(M, vector<char>(N, 0));
	map_visited.assign(M, vector<int>(N, 0));

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	BFS();

	cout << minimum;
}