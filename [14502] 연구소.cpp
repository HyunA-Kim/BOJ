#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int N, M;
int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
int wall = 3;

vector<vector<int>> map;
vector<vector<int>> map_visited;
queue<pair<int,int>> q;

int map_check(int y, int x) {
	int num = 0;
	for (int i = 0; i < 4; i++) {

		int new_y = y + dir[i][0];
		int new_x = x + dir[i][1];

		if (new_y < 0 || new_y >= N || new_x < 0 || new_x >= M) continue;

		if (map[new_y][new_x] == 0 && map_visited[new_y][new_x] == 0) {
			num++;
		}
	}
	return num;
}

void DFS(int y, int x) {

	map_visited[y][x] = 1;
	map[y][x] = 2;

	int num = map_check(y, x);

	if (wall - q.size() + 1 >= num) {

		for (int i = 0; i < 4; i++) {

			int new_y = y + dir[i][0];
			int new_x = x + dir[i][1];

			if (new_y < 0 || new_y >= N || new_x < 0 || new_x >= M) continue;

			if (map[new_y][new_x] == 0 && map_visited[new_y][new_x] == 0) {
				map[new_y][new_x] = 1;
				map_visited[new_y][new_x] = 1;
				wall--;
			}
		}
	}
	else {
		for (int i = 0; i < 4; i++) {

			int new_y = y + dir[i][0];
			int new_x = x + dir[i][1];

			if (new_y < 0 || new_y >= N || new_x < 0 || new_x >= M) continue;

			if (map[new_y][new_x] == 0 && map_visited[new_y][new_x] == 0) {
				DFS(new_y, new_x);
			}
		}
	}
}

int main(void) {
	
	cin >> N >> M;

	map.assign(N, vector<int>(M, 0));
	map_visited.assign(N, vector<int>(M, 0));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == 2) {
				q.push(make_pair(i, j));
			}
			else if (map[i][j] == 1) {
				map_visited[i][j] = 1;
			}

		}
	}

	while(!q.empty()){
		int y = q.front().first;
		int x = q.front().second;
		DFS(y, x);
		q.pop();
	}

	int cnt = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cout << map[i][j] << " ";
			if (map[i][j] == 0) cnt++;
		}
		cout << endl;
	}

	cout << cnt;
}