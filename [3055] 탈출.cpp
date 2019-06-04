#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
int R, C;

vector<vector<char>> map;
vector<vector<int>> map_visited;

pair<int, int> man;
pair<int, int> cave;
queue<pair<int, int>> water;
queue<pair<int, int>> biber;

void BFS() {
	
	while (!biber.empty()) {
		
		int man_size = biber.size();	//biber의 사이즈만큼 회전하기 위해 변수를 저장(save size of the biber to spread around the area)
		int water_size = water.size();	//water의 사이즈만큼 회전하기 위해 변수를 저장(save size of the water to spread around the area)

		//물이 먼저 와야 biber에 물 처리조건을 제외한 간편한 알고리즘 가능
		for (int q = 0; q < water_size; q++) {

			pair<int, int> water_move = water.front();
			water.pop();

			//상하좌우로 퍼트리기(spread around the area)
			for (int i = 0; i < 4; i++) {

				pair<int, int> new_water_move = { water_move.first + dir[i][0], water_move.second + dir[i][1] };
				if (new_water_move.first < 0 || new_water_move.first >= R || new_water_move.second < 0 || new_water_move.second >= C) continue;
				
				//빈 공간일 경우, 물이 퍼짐 (if empty space, water spread)
				if (map[new_water_move.first][new_water_move.second] == '.') {
					water.push(new_water_move);	//다음 물 공간 확보
					map[new_water_move.first][new_water_move.second] = '*';
				}

			}
		}

		//biber가 갈 수 있는 방향을 정하기
		for (int q = 0; q < man_size; q++) {

			pair<int, int> man_move = biber.front();
			biber.pop();

			//상하좌우로의 움직임(move all position to go to cave)
			for (int i = 0; i < 4; i++) {

				pair<int, int> new_man_move = { man_move.first + dir[i][0],man_move.second + dir[i][1] };
				if (new_man_move.first < 0 || new_man_move.first >= R || new_man_move.second < 0 || new_man_move.second >= C) continue;
			
				//다음 영역이 cave일 경우, 도착(arrive when position is cave)
				if (new_man_move == cave) {
					cout << map_visited[man_move.first][man_move.second]+1;	//얼만큼 걸렸는지를 출력
					return;
				}

				//빈 공간일 경우(벽이나 물이 없는경우) 비버 보내기
				if (map[new_man_move.first][new_man_move.second] == '.' && map_visited[new_man_move.first][new_man_move.second]==0) {
					biber.push(new_man_move);
					map_visited[new_man_move.first][new_man_move.second] = map_visited[man_move.first][man_move.second] + 1;	//한칸 진전을 뜻함
				}
				
			}
		}
	}

	//도착하지 못하였을 경우 fail 메시지를 출력
	cout << "KAKTUS";
	return;
}

int main(void) {

	cin >> R >> C;
	map.assign(R+1, vector<char>(C+1, 0));
	map_visited.assign(R+1, vector<int>(C+1, 0));

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			
			cin >> map[i][j];
			
			//biber의 위치일경우 biber초기위치를 man에 기입
			if (map[i][j] == 'S') {
				man = { i,j };
				biber.push(man);
			}
			//동굴위치 기입
			else if (map[i][j] == 'D') {
				cave = { i,j };
			}
			//물위치 기입
			else if (map[i][j] == '*') {
				water.push({ i,j });
			}
		}
	}

	BFS();
	return 0;
}
