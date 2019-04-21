#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

int N;
int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
int ans=0;

vector<vector<int>> map;
vector<vector<int>> map_visited;
queue<pair<int,int>> q;

// 남은 영역이 있는지 확인하는 함수(check there is empty space)
bool map_check() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] != 0 && map_visited[i][j]==0) {
				q.push(make_pair(i, j));
				map_visited[i][j] = 1;
				return true;	//남은영역있을시, 그영역 시작할 수 있는 좌표대입
			}
		}
	}
	return false;	//없을 시, 끝내기 위한 리턴형(if no exist, return false to end of BFS function)
}

//max_rain은 물에 잠기는 영역을 제외하기 위해서 설정해놓은 변수
//(if map area value is lower than max_rain, set the visited value 1->to do no visit)
void BFS(int max_rain) {
	
	int cnt = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] <= max_rain) {
				map_visited[i][j] = 1;	//물에 잠기는 부분은 제외할 수 있도록 설정
			}
		}
	}

	while (1) {

		if (map_check() == false) break;
		
		while (!q.empty()) {

			int y = q.front().first;
			int x = q.front().second;
			q.pop();

			//해당 영역의 상화좌우 방문(visit up,down,right,left)
			for (int i = 0; i < 4; i++) {
				int new_y = y + dir[i][0];
				int new_x = x + dir[i][1];

				if (new_y < 0 || new_y >= N || new_x < 0 || new_x >= N) continue;
				
				if (map[new_y][new_x] != 0 && map_visited[new_y][new_x] == 0) {
					q.push(make_pair(new_y, new_x));
					map_visited[new_y][new_x] = 1;
				}
			}
		}
		cnt++;	//해당 영역의 공간 모두 방문시 카운트(to calculate area count)
	}
	ans = max(ans, cnt);	//영 역수가 가장많은 것을 출력하기 위해 선언
}

int main(void) {

	int max_rain = 0;

	cin >> N;

	map.assign(N, vector<int>(N, 0));
	map_visited.assign(N, vector<int>(N, 0));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			max_rain = max(max_rain, map[i][j]);
		}
	}

	for (int i = 0; i <= max_rain; i++) {
		BFS(i);
		map_visited.assign(N,vector<int>(N,0));	//max_rain의 변수를 설정하고 영역계산하기 위한 초기화
	}

	cout << ans;	//최대 영역의 수 출력(print max count of area)
}