#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
int R, C;

vector<vector<char>> map;
vector<vector<char>> map_visited;

pair<int, int> man;
pair<int, int> cave;
queue<pair<int, int>> water;
queue<pair<pair<int, int>,int>> biber;

void BFS() {
	
	bool expect_waterbound = false;

	while (1) {

		if (biber.empty()) break;
		pair<int, int> man_move = biber.front().first;
		int cnt = biber.front().second;
		biber.pop();
		pair<int, int> water_move = water.front();
		water.pop();
	
		for (int i = 0; i < 4; i++) {
			pair<int, int> new_water_move = { water_move.first + dir[i][0], water_move.second + dir[i][1] };
			if (new_water_move.first < 0 || new_water_move.first >= R || new_water_move.second < 0 || new_water_move.second >= C) continue;
			if (map[new_water_move.first][new_water_move.second] == '.') {
				water.push(new_water_move);
				map[new_water_move.first][new_water_move.second] = '*';
			}
		}


		for (int i = 0; i < 4; i++) {

			pair<int, int> new_man_move = { man_move.first + dir[i][0],man_move.second + dir[i][1] };
			pair<int, int> new_water_move = { water.front().first,water.front().second };
			if (new_man_move.first < 0 || new_man_move.first >= R || new_man_move.second < 0 || new_man_move.second >= C) continue;
			//물이 들어올 예정인칸 처리할 수 있는 로직 구현
			expect_waterbound = false;
			for (int z = 0; z < 4; z++) {
				if ((new_man_move.first == new_water_move.first + dir[z][0]) && (new_man_move.second == new_water_move.second + dir[z][1]))
				{
					expect_waterbound = true;
					break;
				}
			}
			if (map[new_man_move.first][new_man_move.second] == '.'&& expect_waterbound == false) {
				biber.push({ new_man_move,cnt + 1 });
				map_visited[new_man_move.first][new_man_move.second] = 1;
			}
			if (cave == new_man_move) {
				cout << cnt + 1;
				return;
			}
		}

		
		
	}

	cout << "KAKTUS";
	return;
}
int main(void) {

	cin >> R >> C;
	map.assign(R+1, vector<char>(C+1, 0));
	map_visited.assign(R+1, vector<char>(C+1, 0));

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'S') {
				man = { i,j };
				biber.push({ man,0 });
			}
			else if (map[i][j] == 'D') {
				cave = { i,j };
			}
			else if (map[i][j] == '*') {
				water.push({ i,j });
			}
		}
	}

	BFS();
	return 0;
}
