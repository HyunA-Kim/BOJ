#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int N, M;
int crush = 0;
int minimum = 10000;

int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

vector<vector<int>> map;
vector<vector<int>> map_visited;

queue<pair<int, int>> q;

void BFS() {
	int ans = 1;
	bool isFind = false;
	q.push({ 0,0 });
	
	while (!q.empty()) {
		
		isFind = false;

		int y = q.front().first;
		int x = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {

			int new_y = y + dir[i][0];
			int new_x = x + dir[i][1];
			if (new_y < 0 || new_y >= N || new_x < 0 || new_x >= M) continue;
			if (map[new_y][new_x]== 0 && map_visited[new_y][new_x] == 0) {
				map_visited[new_y][new_x] = 1;
				q.push({ new_y,new_x });
				isFind = true;
				//시간초과를 위해 안에 집어넣음
				if (new_y == N - 1 && new_x == M - 1 && q.front().first == new_y && q.front().second == new_x) {
					if (minimum > ans)
					{
						minimum = ans;
						return;
					}
				}
			}
		
		}
		if(isFind==true) ans++;
	}

	return;
}
int main(void) {
	
	cin >> N >> M;

	map.assign(N, vector<int>(M, 0));
	map_visited.assign(N, vector<int>(M, 0));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%1d", &map[i][j]);
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			map_visited.assign(N, vector<int>(M, 0));
			if (map[i][j] == 1) {
				//백트래킹 방법
				map[i][j] = 0;
				BFS();
				map[i][j] = 1;
			}

		}
	}
	if (minimum == 10000) cout << -1;
	else cout << minimum;
}
