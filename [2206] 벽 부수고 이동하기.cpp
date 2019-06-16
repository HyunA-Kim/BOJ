#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int N, M;
int crush = 0;
int minimum = 10000;

int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

vector<vector<int>> map;
int map_visited[100][100][2];
queue<pair<pair<int, int>,int>> q;

void BFS() {
	int ans = 1;
	bool isFind = false;
	q.push({ { 0,0 },0 });
	
	while (!q.empty()) {
		
		isFind = false;

		int y = q.front().first.first;
		int x = q.front().first.second;
		int wall = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {

			int new_y = y + dir[i][0];
			int new_x = x + dir[i][1];
			if (new_y < 0 || new_y >= N || new_x < 0 || new_x >= M) continue;
			if (map[new_y][new_x] == 1 && wall == 1) {
				q.push({ {new_y,new_x},wall-1 });
			}
			else if (map[new_y][new_x] == 0 && map_visited[new_y][new_x][1] == 0) {
				map_visited[new_y][new_x][wall] = map_visited[y][x][wall] + 1;
				q.push({{ new_y,new_x }, wall});
				isFind = true;
				if (new_y == N - 1 && new_x == M - 1) {
					ans = map_visited[new_y][new_x][wall];
					return;
				}
			}
		
		}
	}

	ans = -1;
	return;
}
int main(void) {
	
	cin >> N >> M;

	map.assign(N, vector<int>(M, 0));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf_s("%1d", &map[i][j],sizeof(map[i][j]));
		}
	}

	BFS();

	if (minimum == 10000) cout << -1;
	else cout << minimum;
}
