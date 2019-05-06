#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int N, M;
int dj[4] = { -1,0,0,1 };
int di[4] = { 0,1,-1,0 };
int ans=1;	// 몇년이 지났는지에 대한 답(answer)

vector<vector<int>> map;
vector<vector<int>> map_collapsed;	//상하좌우 빙수아닌 부분 갯수계산 맵(calculate non-ice area)
vector<vector<int>> map_visited;	//맵의 방문여부 체크(visit or non-visit check)

queue<pair<int, int>> q;

//맵의 빙산인부분 찾는함수(find area those part of ice)
bool map_find() {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] != 0 && map_visited[i][j]==0) {
				
				map_visited[i][j] = 1;
				q.push(make_pair(i, j));
				return true;
			}
		}
	}

	return false;
}

//맵의 빙산인 연결부분 찾아주는 함수(find connected non-ice area)
bool BFS() {

	int separate = 0;	//빙산이 분리됬는지 확인(certificate separte ice area)

	while (1) {

		if (map_find() == false) {
			//하나이상의 분리구간있을 경우, 출력
			if (separate > 1) {
				cout << ans;
				return true;
			}

			//분리되지 않고, 모두 다 녹았을 경우 0을 출력
			else if (separate == 0) {
				cout << 0;
				return true;
			}

			//나머지 부분, 덜 녹았으므로 빙산이 녹도록함
			else return false;

		};

		separate++;
		
		while (!q.empty()) {

			int y = q.front().first;
			int x = q.front().second;
			
			q.pop();

			//상화좌우 빙산인부분 연결(connect up,down,right,left ice area)
			for (int i = 0; i < 4; i++) {
			
				int new_y = y + di[i];
				int new_x = x + dj[i];
				
				if (new_y < 0 || new_y >= N || new_x < 0 || new_x >= M) continue;

				if (map[new_y][new_x] != 0 && map_visited[new_y][new_x] == 0) {
					map_visited[new_y][new_x] = 1;
					q.push(make_pair(new_y, new_x));
				}

			}
		}
	}
}

void iceCollapsed() {
	
	map_collapsed.assign(N, vector<int>(M, 0));
	map_visited.assign(N, vector<int>(M, 0));

	//빙산 상하좌우에 바다인 경우 계산
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] != 0) {
				
				//바다인 구역 갯수
				int cnt = 0;

				//상하좌우 바다인경우, 녹여야할 수를 더해줌
				for (int k = 0; k < 4; k++) {
					int new_i = i + di[k];
					int new_j = j + dj[k];
					if (map[new_i][new_j] == 0) {
						cnt++;
					}
				}

				//녹여할부분의 얼만큼녹여야되는지 저장(save data melt ice-area)
				map_collapsed[i][j] = cnt;
			}
		}
	}

	//빙산녹이기 작업(work melt ice-area)
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			map[i][j] = map[i][j] - map_collapsed[i][j];
			if (map[i][j] < 0) map[i][j] = 0;	//바다인경우, 0으로 수렴
		}
	}

	//아직 덜 녹았을 경우, 1년을 더해주고 다시 얼음녹이기(yet ice is melt, do again)
	if (BFS() == false) {
		ans++;
		iceCollapsed();
	}
}

int main(void) {
	
	cin >> N >> M;
	map.assign(N, vector<int>(M, 0));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	//빙산녹이기 시작(start melt ice area)
	iceCollapsed();
}