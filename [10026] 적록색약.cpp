#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
	
int N;
int ans=0;
int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
int color[3] = { 'G','R','B' };	//색깔구분(classify color array)

vector<vector<char>> map;
vector<vector<int>> map_visited;
queue<pair<int,int>> q;

//같은 색깔 && 다른 영역이 있는지 확인
bool map_check(int select) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] == color[select] && map_visited[i][j] == 0) {
				q.push(make_pair(i, j));
				return true;
			}
		}
	}
	return false;
}

void BFS(int select) {

	while (1) {

		if (map_check(select) == false) break;
		
		while (!q.empty()) {

			int y = q.front().first;
			int x = q.front().second;
			map_visited[y][x] = 1;
			q.pop();

			for (int i = 0; i < 4; i++) {

				int new_y = y + dir[i][0];
				int new_x = x + dir[i][1];

				if (new_y < 0 || new_y >= N || new_x < 0 || new_x >= N) continue;

				//같은색깔이면서, 방문안한노드를 방문(visit the same color and no visit node)
				if (map[new_y][new_x] == color[select] && map_visited[new_y][new_x] == 0) {
					q.push(make_pair(new_y, new_x));
					map_visited[new_y][new_x] = 1;
				}
			}
		}
		ans++;	//각각 다른 영역 카운트
	}
}

int main(void) {
	
	cin >> N;

	map.assign(N, vector<char>(N, 0));
	map_visited.assign(N, vector<int>(N, 0));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	// 1. 정상인인 경우: 각각 다른 색깔 모두 방문(nommal person)
	for (int i = 0; i < 3; i++) {
		BFS(i);
	}
	cout << ans << " ";	//영역갯수 출력

	// 2. 적록색약인 경우 : R->G 또는 G->R로 바꾸어 BFS로 방문
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] == 'R') {
				map[i][j] = 'G';
			}
		}
	}
	map_visited.assign(N, vector<int>(N, 0)); //방문 벡터 초기화
	ans = 0;
	
	for(int i = 0; i < 3; i++) {
		BFS(i);
	}

	cout << ans;	//영역 갯수 출력

	return 0;
}