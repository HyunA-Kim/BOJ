#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

int M, N, K;
int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

vector<vector<int>> map;
queue<pair<int,int>> q;

//맵의 빈공간좌표를 구하기 위한 체크함수(get x,y point if map[x][y]==0)
bool map_check() {

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] == 0) {
				q.push(make_pair(i, j));
				map[i][j] = 1;
				return true;
			}
		}
	}
	return false;

}

void BFS() {

	vector<int> count;

	while (1) {

		if (map_check() == false) break; //if map doesn't have 0 -> no empty ground -> return;
		int cnt = 1; //맵 빈공간 카운트이용해 넓이구하기

		while (!q.empty()) {
			
			int y = q.front().first;
			int x = q.front().second;
			q.pop();

			//동서남북으로 0공간 찾기(find empty place to spread)
			for (int i = 0; i < 4; i++) {
			
				int new_y = y + dir[i][0];
				int new_x = x + dir[i][1];

				if (new_y < 0 || new_y >= M || new_x < 0 || new_x >= N) continue;

				if (map[new_y][new_x] == 0) {
					q.push(make_pair(new_y, new_x));
					map[new_y][new_x] = 1;
					cnt++;
				}
			}
		}

		count.push_back(cnt); //save cnt in the vector count
	}

	//각 빈공간 넓이를 오름차순으로 정렬
	sort(count.begin(), count.end());

	//정답 출력(answer print)
	cout << count.size()<<"\n";

	for (int i = 0; i < count.size(); i++) {
		cout << count[i] << " ";
	}
}

int main(void) {
	
	cin >> M >> N >> K;

	map.assign(M, vector<int>(N, 0));

	for (int i = 0; i < K; i++) {
		int y1, x1, y2, x2;
		cin >> x1 >> y1 >> x2 >> y2;
		
		//직사각형 모양 정하기 위해 조건문 사용
		if (x1 < x2) {
			for (int i = y1; i < y2; i++) {
				for (int j = x1; j < x2; j++) {
					map[i][j] = 1;
				}
			}
		}
		else {
			for (int i = y2; i < y1; i++) {
				for (int j = x2; j < x1; j++) {
					map[i][j] = 1;
				}
			}
		}
	}

	//빈공간 찾기 위한 DFS알고리즘(find empty ground)
	BFS();
}