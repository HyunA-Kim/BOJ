#include<iostream>
#include<vector>
#include<stack>

using namespace std;

vector<vector<int>> map;
vector<vector<int>> map_visited;

stack<pair<int, int>> s;

int N;
int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

class find {
	stack<int> island;
};

bool map_check() {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] == 1 && map_visited[i][j] == 0) {
				s.push(make_pair(i, j));
				map_visited[i][j] = 1;
				return true;
			}
		}
	}

	return false;

}

void DFS() {
	while (1) {
		if (map_check() == false) return;
		while (!s.empty()) {
			int y = s.top().first;
			int x = s.top().second;
			s.pop();
			for (int i = 0; i < 4; i++) {
				int new_y = y + dir[i][0];
				int new_x = x + dir[i][1];
				if (new_y < 0 || new_y >= N || new_x < 0 || new_x >= N) continue;
				if (map[new_y][new_x] == 1 && map_visited[new_y][new_x] == 0) {
					map_visited[new_y][new_x] = 1;
					s.push(make_pair(new_y, new_x));
				}
			}
		}
		s.push(make_pair(-1, -1));	// 섬을 각각 구분하기 위해생성
	}
}

int main(void) {
	
	cin >> N;
	
	map.assign(N, vector<int>(N, 0));
	map_visited.assign(N, vector<int>(N, 0));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	DFS();


}