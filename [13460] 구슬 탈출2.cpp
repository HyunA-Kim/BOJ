#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

int N, M;
int ans = 0;
int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

vector<vector<char>> map;
int isVisited[11][11][11][11];

queue<pair<int, int>> rq;	
queue<pair<int, int>> bq;

pair<int, int> goal;	//'0'의 좌표
pair<int, int> r;		//'R'의 좌표
pair<int, int> b;		//'B'의 좌표

void BFS() {

	while (rq.size()) {
	
		int size = rq.size();
		
		while (size--) {

			r.first = rq.front().first;		//각 queue 의 가장앞 원소들을 꺼낸 후, 제거
			r.second = rq.front().second;
			
			b.first = bq.front().first;
			b.second = bq.front().second;
		
			rq.pop();
			bq.pop();

			// R구슬이 골인했을 경우, 출력 ('B'는 골인하면 -1이므로 안됨)
			if (r == goal && r != b) {
				cout << ans;
				return;
			}

			// 각 방향대로 구슬을 굴리기 (상,하,좌,우)
			for (int k = 0; k < 4; k++) {

				pair<int, int> new_r = { r.first,r.second };
				pair<int, int> new_b = { b.first,b.second };

				// 'R'구슬을 k방향으로 굴리기(move R with k direction)
				while (1) {
					if (map[new_r.first + dir[k][0]][new_r.second + dir[k][1]] == '#') break;
					if (new_r == goal) break;
					new_r.first += dir[k][0];
					new_r.second += dir[k][1];
				}

				// 'B'구슬을 k방향으로 굴리기(move B with k direction)
				while (1) {
					if (map[new_b.first + dir[k][0]][new_b.second + dir[k][1]] == '#') break;
					if (new_b == goal) break;
					new_b.first += dir[k][0];
					new_b.second += dir[k][1];
				}

				// 'R'과 'B'좌표가 같을 경우(구멍에 들어간 경우 제외하고는 같을 수 없다는 조건문에 의해)

				if (new_r == new_b && new_r != goal) {

					// 열이다른경우
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
	
					// 행이 다른경우
					else if (r.second == b.second) {
						if (r.first > b.first) {
							if (k == 0) new_r.first += 1;
							if (k == 1) new_b.first -= 1;
						}
						else {
							if (k == 0) new_b.first += 1;
							if (k == 1) new_r.first -= 1;
						}
					}
			
				}

				// 이미 방문한 경우 스킵(already visited don't count)
				if (isVisited[new_r.first][new_r.second][new_b.first][new_b.second] == 1) continue;

				isVisited[new_r.first][new_r.second][new_b.first][new_b.second] = 1;

				// queue에 집어넣기
				rq.push(make_pair(new_r.first, new_r.second));
				bq.push(make_pair(new_b.first, new_b.second));
			}
		}

		// 10번이상일 움직였을 경우 실패(more than 10 counts, failed)
		if (ans == 10) {
			cout << -1;
			return;
		}
		// count 1증가
		ans++;
	}

	cout << -1;
	return;
}

int main(void) {

	cin >> N >> M;

	map.assign(N, vector<char>(M, '.'));

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
	
	isVisited[r.first][r.second][b.first][b.second] = 1;
	
	BFS();

}
