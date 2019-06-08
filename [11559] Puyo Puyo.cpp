#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int R = 12;
int C = 6;

vector<vector<char>> map;
vector<vector<int>> map_visited;
	
queue<pair<int, int>> del;
queue<pair<int, int>> save;
int dir[4][2] = { {-1,0},{0,-1},{0,1},{1,0} };
int ans = 0;
//해당 뿌요를 삭제했을 경우 테트리스가 밑으로 내려옴
void Delete() {
	while(!del.empty()){
		int y = del.front().first;
		int x = del.front().second;
		del.pop();
		for (int i = y; i > 0; i--){ 
			map[i][x] = map[i - 1][x];
		}
		map[0][x] = '.';
	}
	
}

//해당 뿌요가 4개일 경우 del에 큐 저장
bool DFS(pair<int, int> org, int cnt) {
	
	if (cnt == 4) {
		cnt = 0;
		return true;
	}

	for (int i = 0; i < 4; i++) {
		
		int new_y = org.first + dir[i][0];
		int new_x = org.second + dir[i][1];
		
		if (new_y < 0 || new_y >= R || new_x < 0 || new_x >= C) continue;

		if (map[new_y][new_x] == map[org.first][org.second] && map_visited[new_y][new_x]==0) {
			save.push({ new_y,new_x });
			map_visited[new_y][new_x] = 1;
			if (DFS({ new_y,new_x }, cnt + 1) == true) {
				return true;
			}
		}
	}

	return false;
}

bool map_checked() {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (map[i][j] != '.' && map_visited[i][j]==0) {
				save.push({ i,j });
				map_visited[i][j] = 1;
				return true;
			}
		}
	}
	return false;
}

int main(void) {
	
	map.assign(R, vector<char>(C, '.'));
	map_visited.assign(R, vector<int>(C, 0));
	
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> map[i][j];
		}
	}
	
	while (1) {
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				if (map[i][j] != '.' && map_visited[i][j] == 0) {
					save.push({ i,j });
					map_visited[i][j] = 1;
					if (DFS({ i,j }, 1) == true) {
						while (!save.empty()) {
							del.push(save.front());
							save.pop();
						}
					}
					else {
						while (!save.empty()) {
							save.pop();
						}
					}

				}
			}
		}

		map_visited.assign(R, vector<int>(C, 0));

		if (!del.empty()) {
			Delete();
			ans++;
		}
		else {
			break;
		}
	}

	cout << ans;
}
