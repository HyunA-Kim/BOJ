#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

int N, M;
int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };	//방향
int ans=0;

vector<vector<int>> map;	//기존맵	
vector<vector<int>> map_copy;	//맵 카피본
vector<pair<int,int>> virus;
queue<pair<int, int>> q;

void count_empty() {
	int num = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 0) {
				num++;
			}
		}
	}
	ans = max(ans, num);
}

void copy_recover() {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			map[i][j] = map_copy[i][j];
		}
	}

}

void copy() {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			map_copy[i][j] = map[i][j];
		}
	}
}

void wall(int cnt) {
	
	//벽을 다 세웠을 경우 (In case, built all of the wall)
	//바이러스 퍼트리기 (spread virus)
	if (cnt == 3) {
		copy();
		for (int a = 0; a < virus.size(); a++) {
			q.push(virus[a]);
		}

		while (!q.empty()) {
			int y = q.front().first;
			int x = q.front().second;
			
			q.pop();

			for (int i = 0; i < 4; i++) {
				
				int new_y = y + dir[i][0];
				int new_x = x + dir[i][1];
				
				if (new_y < 0 || new_y >= N || new_x < 0 || new_x >= M) continue;

				if (map[new_y][new_x] == 0) {
					map[new_y][new_x] = 2;
					q.push(make_pair(new_y, new_x));
				}
			}
		}
		count_empty();
		copy_recover();
		return;
	}

	//벽 세우기 경우의수 (모든 경우를 다 세는것으로 한다)
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 0) {
				map[i][j] = 1;
				wall(cnt + 1);	//벽을 하나더 증가시켜줌
				map[i][j] = 0;	//다른 곳에 벽세우기 위한 기존 벽 초기화
			}
		}
	}
}

int main(void) {
	
	cin >> N >> M;

	map.assign(N, vector<int>(M, 0));
	map_copy.assign(N, vector<int>(M, 0));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == 2) {
				virus.push_back(make_pair(i, j));	//바이러스 해당좌표 입력
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 0) {
				map[i][j] = 1;
				wall(1);
				map[i][j] = 0;
			}
		}
	}

	cout << ans;
}
