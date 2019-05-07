#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int N, M;
int ans;
char dir[4] = { 'N','E','S','W'};

vector<vector<char>> map;
queue<pair<pair<int, int>,int>> q;
pair<int, int> goal;
pair<int, int> r;
pair<int, int> b;

bool check() {

	r.first = q.front().first.first;
	r.second = q.front().first.second;
	int count = q.front().second;
	
	//�Ķ������� ���� ��� || �Ķ�,�������� ���ÿ� ���� ���
	if (b.first == goal.first && b.second == goal.second) {
		cout << -1;
		return true;
	}
	//���������� ���� ���
	else if (r.first == goal.first && r.second == goal.second) {
		//10�ʰ��϶� ����
		if (count > 10) cout << -1;
		else cout << count;
		return true;
	}
}

void BFS() {

	vector<vector<int>> map_visited;
	map_visited.assign(N, vector<int>(N, 0));

	while (!q.empty()) {

		r.first = q.front().first.first;
		r.second = q.front().first.second;
		int count = q.front().second;

		//�����¿�� ����
		for (int k = 0; k < 4; k++) {
			//��
			if (dir[k] == 'N') {
				while (1) {
					if (map[r.first][r.second] == '#' || map_visited[r.first-1][r.second] != 0) break;
					r.first -= 1;
					map_visited[r.first][r.second] = 1;
					if (check() == true) exit;
				}
				r.first += 1;
				while (1) {
					if (map[b.first][b.second] == '#') break;
					b.first -= 1;
					if (check() == true) exit;
				}
				b.first += 1;
			}
			//��
			else if (dir[k] == 'E') {
				while (1) {
					if (map[r.first][r.second] == '#' || map_visited[r.first][r.second+1] != 0) break;
					r.second += 1;
					map_visited[r.first][r.second] = 1;
					if (check() == true) exit;
				}
				r.second -= 1;
				while (1) {
					if (map[b.first][b.second] == '#') break;
					b.second += 1;
					if (check() == true) exit;
				}
				b.second -= 1;
			}
			//��
			else if (dir[k] == 'S') {
				while (1) {
					if (map[r.first][r.second] == '#' || map_visited[r.first+1][r.second] != 0) break;
					r.first += 1;
					map_visited[r.first][r.second] = 1;
					if (check() == true) exit;
				}
				r.first -= 1;
				while (1) {
					if (map[b.first][b.second] == '#') break;
					b.first += 1;
					if (check() == true) exit;
				}
				b.first -= 1;
			}
			//��
			else if (dir[k] == 'W') {
				while (1) {
					if (map[r.first][r.second] == '#' || map_visited[r.first][r.second-1] != 0) break;
					r.second -= 1;
					map_visited[r.first][r.second] = 1;
					if (check() == true) exit;
				}
				r.second += 1;
				while (1) {
					if (map[b.first][b.second] == '#') break;
					b.second -= 1;
					if (check() == true) exit;
				}
				b.second += 1;
			}

			//��� �����̴� Ȯ���ϴ� �ڵ�
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M; j++) {
					cout << map[i][j] << " ";
				}
				cout << endl;
			}
			q.pop();
			q.push(make_pair(make_pair(r.first, r.second), count + 1));

		}
	}
}

int main(void) {
	
	cin >> N >> M;
	map.assign(N, vector<char>(M, '.'));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'R') {
				q.push(make_pair(make_pair(i, j),0));
			}
			else if (map[i][j] == 'O') {
				goal.first = i;
				goal.second = j;
			}
		}
	}

	BFS();
	
}