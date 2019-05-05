#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int n;
int goal_x, goal_y;
int m;
int depth[101];	//촌수를 계산해줄 배열

vector<vector<int>> map;
vector<int> map_visited;
queue<int> q;

void Relative(int goal_x) {

	map_visited[goal_x] = 1;	//해당 번호를 방문표시
	
	q.push(goal_x);
	depth[goal_x] = 0;	//촌수 계산 시작
	
	while(!q.empty()) {

		int value = q.front();
		q.pop();
		
		for (int j = 1; j <= n; j++) {

			if (map[value][j] == 1 && !map_visited[j]) {
				q.push(j);
				map_visited[j] = 1;
				depth[j] = depth[value] + 1;	//방문시, 촌수를 1 늘림
			}
		}

	}
}

int main(void) {

	cin >> n;
	cin >> goal_x >> goal_y;
	cin >> m;

	map.assign(n+1, vector<int>(n+1, 0));
	map_visited.assign(101, 0);

	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		map[x][y] = 1;	//서로간의 부모 여부를 체크
		map[y][x] = 1;
	}

	Relative(goal_x);	//Relative 함수를 이용해 촌수 확인시작
	
	//연관없을시 -1 출력
	if (depth[goal_y] == 0) cout << -1;
	else cout << depth[goal_y];
}
