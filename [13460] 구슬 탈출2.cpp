#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int N, M;
int ans = 0;
int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

vector<vector<char>> map;

vector<vector<int>> rq_visited;
vector<vector<int>> bq_visited;

queue<pair<int,int>> rq;
queue<pair<int, int>> bq;

pair<int, int> goal;
pair<int, int> r;
pair<int, int> b;

void BFS() {
	while (rq.size()) {
		int size = rq.size();
		while (size--) {
			r.first = rq.front().first;
			r.second = rq.front().second;
			b.first = bq.front().first;
			b.second = bq.front().second;
			rq.pop();
			bq.pop();

			if (r == goal && r == b) {
				cout << -1;
				return;
			}
			else if (r == goal && r != b) {
				if (ans >= 10) {
					cout << -1;
				}
				else {
					cout << ans;
				}
				return;
			}

			for (int k = 0; k < 4; k++) {

				pair<int, int> new_r = { r.first,r.second };
				pair<int, int> new_b = { b.first,b.second };

				while (1) {
					if (map[new_r.first + dir[k][0]][new_r.second + dir[k][1]] == '#') break;
					if (new_r.first == goal.first && new_r.second == goal.second) break;
					new_r.first += dir[k][0];
					new_r.second += dir[k][1];
				}

				while (1) {
					if (map[new_b.first + dir[k][0]][new_b.second + dir[k][1]] == '#') break;
					if (new_b.first == goal.first && new_b.second == goal.second) break;
					new_b.first += dir[k][0];
					new_b.second += dir[k][1];
				}

				if (new_r == new_b && new_r != goal) {
					//열이다른경우
					if (r.first == b.first) {
						if (r.second > b.second) {
							if (k == 2) new_r.second += 1;
							if (k == 3) new_b.second -= 1;
						}
						else {
							if (k == 2) new_b.second += 1;
							if (k == 3) new_r.second -= 1;
						}
					}
					//행이 다른경우
					else if (r.second == b.second) {
						if (r.first > b.first) {
							if (k == 0) new_r.second += 1;
							if (k == 1) new_b.second -= 1;
						}
						else {
							if (k == 0) new_b.second += 1;
							if (k == 1) new_r.second -= 1;
						}
					}
				}

				if (new_r == goal || new_b == goal) continue;
				if (bq_visited[new_b.first][new_b.second] == 1 && rq_visited[new_r.first][new_r.second] == 1) continue;

				rq_visited[new_r.first][new_r.second] = 1;
				bq_visited[new_b.first][new_b.second] = 1;

				map[r.first][r.second] = '.';
				map[b.first][b.second] = '.';
				map[new_r.first][new_r.second] = 'R';
				map[new_b.first][new_b.second] = 'B';


				rq.push(make_pair(new_r.first, new_r.second));
				bq.push(make_pair(new_b.first, new_b.second));

				for (int i = 0; i < N; i++) {
					for (int j = 0; j < M; j++) {
						cout << map[i][j] << " ";
					}
					cout << endl;
				}
			}
			ans++;
		}
	}
}

int main(void) {
	
	cin >> N >> M;
	map.assign(N, vector<char>(M, '.'));

	rq_visited.assign(N, vector<int>(M, 0));
	bq_visited.assign(N, vector<int>(M, 0));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == 'R') {
				r.first = i;
				r.second = j;
			}
			else if (map[i][j] == 'B') {
				b.first = i;
				b.second = j;
			}
			else if (map[i][j] == 'O') {
				goal.first = i;
				goal.second = j;
			}
		}
	}

	rq.push(make_pair(r.first, r.second));
	bq.push(make_pair(b.first, b.second));

	BFS();
}
