#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int R = 12;
int C = 6;

vector<vector<char>> map;
vector<vector<int>> map_visited;
	
int dir[4][2] = { {-1,0},{0,-1},{0,1},{1,0} };
int ans = 0;

//해당 뿌요를 삭제했을 경우 테트리스가 밑으로 내려옴
void Delete() {

	for (int i = 0; i <R; i++) {
		for (int j = 0; j < C; j++) {
			if (map[i][j] == 0) {
				for (int k = i; k > 0; k--) {
					map[k][j] = map[k - 1][j];	//빈 곳을 메꾸기위해 위->아래로 한칸씩 이동
				}
				map[0][j] = '.';	//가장 윗칸은 '.'를 표시
			}
		}
	}

}

bool BFS() {

	bool isDelete = false;

	map_visited.assign(R, vector<int>(C, 0));	//다시 테트리스 실행할 수 있도록 만듬
	
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {

			if (map[i][j] != '.' && map_visited[i][j] == 0) {
			
				map_visited[i][j] = 1;
				
				vector<pair<int, int>> m;	//지워야할 문자 위치 장소보관(store delete character location)
				queue< pair<int, int>> q;	//queue를 이용해 BFS 실행
				
				q.push({ i,j });
				m.push_back({ i,j });
				
				//동서남북에 같은 문자가 있는지 확인
				while (!q.empty()) {

					int y = q.front().first;
					int x = q.front().second;
					q.pop();
					
					for (int k = 0; k < 4; k++) {
						int new_y = y + dir[k][0];
						int new_x = x + dir[k][1];
						if (new_y < 0 || new_y >= R || new_x<0 || new_x>C) continue;
						
						//같은 문자일 경우, 지워야할 문자로 선택(select delete character when same character)
						if (map[y][x] == map[new_y][new_x] && map_visited[new_y][new_x] == 0) {
							q.push({ new_y,new_x });		//queue에 저장 (BFS active)
							m.push_back({ new_y,new_x });	//지워야 할 문자위치 보관(store location)
							map_visited[new_y][new_x] = 1;
						}
					}
				}

				//4개 이상일 경우, 지울 수 있도록 '.'로 표기
				if (m.size() >= 4) {
					for (int z = 0; z < m.size(); z++) {
						map[m[z].first][m[z].second] = 0;	// 0으로 표기하여 비었다는 것을 나타냄
					}
					isDelete = true;	//하나 이상 터트릴 수 있을 때 true값으로 변경
				}
				m.clear();	//다음 문자들을 위해 공백으로 처리
			}
		}
	}

	if (isDelete == true) {
		ans++;	//터트림의 수 1증가
		Delete();	//테트리스 빈 공간 메꾸기 및 밑으로 나머지 내려오는 함수
		return true;	//테트리스 실행가능
	}
	else return false;	//테트리스 실행불가능
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
		if (BFS() == false) break;	//테트리스 실행할 수 있을 때까지 실행(until BFS is true, do again)
	}

	cout << ans;
}
