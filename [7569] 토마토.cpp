#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int M, N, H;

int map[100][100][100];
int map_visited[100][100][100];

int dx[6] = { 0,0,-1,1,0,0 };
int dy[6] = { 0,0,0,0,1,-1 };
int dz[6] = { 1,-1,0,0,0,0 };

int apple=0;
int ans=0;

queue<pair<int, pair<int, int>>> q;

void map_checked() {
	for (int k = 0; k < H; k++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (map[k][i][j] == 0) {

					ans = -1;	//����� ���� �ʾ��� ��� -1�� ������ش�.
					return;

				}
			}
		}
	}

	ans -= 1;	//����� �;��� ��� ù���� �����Ƿ� ���ش�.
	return;
}

void BFS() {
	
	while (!q.empty()) {
	
		for(int i=0; i<apple; i++){

			int z = q.front().first;
			int y = q.front().second.first;
			int x = q.front().second.second;
			q.pop();

			for (int i = 0; i < 6; i++) {
				
				int new_z = z + dz[i];
				int new_y = y + dy[i];
				int new_x = x + dx[i];

				if (new_z < 0 || new_z >= H || new_y < 0 || new_y >= N || new_x < 0 || new_x >= M) continue;

				if (map_visited[new_z][new_y][new_x] == 0 && map[new_z][new_y][new_x] == 0) {
					q.push(make_pair(new_z, make_pair(new_y, new_x)));
					map_visited[new_z][new_y][new_x] = 1;
					map[new_z][new_y][new_x] = 1;
				}
			}
		}

		apple = q.size();	//���������ŭ ���ư� �� �ֵ��� �Ѵ�.
		ans++;	//�ּ��ϼ��� ���� �� ���� �����ش�.

	}
}

int main(void) {
	
	cin >> M >> N >> H;

	for (int k = 0; k < H; k++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				cin >> map[k][i][j];
				if (map[k][i][j] == 1) {
					q.push(make_pair(k,make_pair(i, j)));	//���� ��� �־��ֱ�
					apple++;
				}
			}
		}
	}

	BFS();

	map_checked();	//����� ���� �ʾҴ��� Ȯ�� �ʿ�
	
	cout << ans;	//���

}