#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int R = 12;
int C = 6;

vector<vector<char>> map;
vector<vector<int>> map_visited;
	
queue<pair<int, int>> red;
queue<pair<int, int>> blue;
queue<pair<int, int>> yellow;
queue<pair<int, int>> green;
pair<int, int> first;

int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

void DFS(pair<int, int> first) {
	
	int cnt = 0;

	for (int i = 0; i < 4; i++) {
		
		int new_y = first.first + dir[i][0];
		int new_x = first.second + dir[i][1];
		
		if (new_y < 0 || new_y >= R || new_x < 0 || new_x >= C) continue;

		if (map[new_y][new_x] == map[first.first][first.second]) {
			cnt++;
		}
	}
}

int main(void) {
	map.assign(12, vector<char>(6, '.'));
	map_visited.assign(12, vector<int>(6, 0));
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> map[R][C];
			if (map[i][j] == 'R') {
				red.push({ i,j });
			}
			else if (map[i][j] == 'Y') {
				yellow.push({ i,j });
				first = { i,j };
			}
			else if (map[i][j] == 'G') {
				green.push({ i,j });
			}
			else if (map[i][j] == 'B') {
				blue.push({ i,j });
			}

			if (map[i][j] != '.' && first != {NULL, NULL}) {
				first = { i,j };
			}
		}
	}

	DFS(first);
}