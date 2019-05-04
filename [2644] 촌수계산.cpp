#include<iostream>
#include<vector>

using namespace std;

int n;
int goal_x, goal_y;
int m;
int cnt = 0; //촌수

vector<int> map[101];
vector<int> map_visited[101];

void Relative(int root) {

	for (int i = 0; i < n; i++) {
	
		if (map[i].size() == 0) continue;
		
		for (int j = 0; j < map[i].size(); j++) {
		
			if (map[i][j] == root) {
				// 해당 번호를 찾았을 시, 그곳에서 부터 실행
				// 1. 위로 올라가는 방법 -> 올라가면서 cnt+1 시행
				// 2. 아래로 내려가는 방법 -> 아래로 내려가면서 cnt+1 시행
			}
		}
	}
}

int main(void) {

	cin >> n;
	cin >> goal_x >> goal_y;
	cin >> m;

	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		map[x].push_back(y);
	}

	Relative(goal_x);
}