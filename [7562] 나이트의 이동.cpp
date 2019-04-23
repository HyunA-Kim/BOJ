#include<iostream>
#include<vector>
#include<queue>

using namespace std;
vector<vector<int>> map_visited;

int N;
int cur_y, cur_x;
int goal_y, goal_x;
int dir[8][2] = { {-1,2},{-1,-2},{1,2},{1,-2},{2,1},{2,-1},{-2,1},{-2,-1} };	//8����

void BFS(queue<pair<int, pair<int, int>>> q) {
	
	while (!q.empty()) {
		
		int cnt = q.front().first;			// �̵� Ƚ��
		int y = q.front().second.first;		//����Ʈ�� ���� y��ǥ ��ġ
		int x = q.front().second.second;	//����Ʈ�� ���� x��ǥ ��ġ
		
		q.pop();

		//������ġ == ����������ġ�϶� �̵��� ���
		if (y == goal_y && x == goal_x) {
			cout << cnt << "\n";
			break; 
		}


		for (int i = 0; i < 8; i++) {

			int new_y = y + dir[i][0];
			int new_x = x + dir[i][1];

			if (new_y < 0 || new_y >= N || new_x < 0 || new_x >= N) continue;

			if (map_visited[new_y][new_x] == 0) {
				map_visited[new_y][new_x] = 1;	
				q.push(make_pair(cnt+1,make_pair(new_y, new_x)));
			}
		}
	}
}

int main(void) {
	
	int T;
	cin >> T;
	
	while (T--) {

		//���� pair�� ����� "�����̵���,(y��ǥ,x��ǥ)"�� queue�� �Է�
		queue < pair<int, pair<int, int>>> q;

		cin >> N;
		map_visited.assign(N, vector<int>(N, 0));

		cin >> cur_x >> cur_y;
		cin >> goal_x >> goal_y;
	
		q.push(make_pair(0,make_pair(cur_y, cur_x)));
		BFS(q);	//����Ʈ �̵��Լ�
	}
}