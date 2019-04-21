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

// ���� ������ �ִ��� Ȯ���ϴ� �Լ�(check there is empty space)
bool map_check() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] != 0 && map_visited[i][j]==0) {
				q.push(make_pair(i, j));
				map_visited[i][j] = 1;
				return true;	//��������������, �׿��� ������ �� �ִ� ��ǥ����
			}
		}
	}
	return false;	//���� ��, ������ ���� ������(if no exist, return false to end of BFS function)
}

//max_rain�� ���� ���� ������ �����ϱ� ���ؼ� �����س��� ����
//(if map area value is lower than max_rain, set the visited value 1->to do no visit)
void BFS(int max_rain) {
	
	int cnt = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] <= max_rain) {
				map_visited[i][j] = 1;	//���� ���� �κ��� ������ �� �ֵ��� ����
			}
		}
	}

	while (1) {

		if (map_check() == false) break;
		
		while (!q.empty()) {

			int y = q.front().first;
			int x = q.front().second;
			q.pop();

			//�ش� ������ ��ȭ�¿� �湮(visit up,down,right,left)
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
		cnt++;	//�ش� ������ ���� ��� �湮�� ī��Ʈ(to calculate area count)
	}
	ans = max(ans, cnt);	//�� ������ ���帹�� ���� ����ϱ� ���� ����
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
		map_visited.assign(N,vector<int>(N,0));	//max_rain�� ������ �����ϰ� ��������ϱ� ���� �ʱ�ȭ
	}

	cout << ans;	//�ִ� ������ �� ���(print max count of area)
}