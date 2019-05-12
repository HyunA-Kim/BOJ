#include<iostream>
#include<vector>
#include<stack>

using namespace std;

vector<vector<int>> map;
vector<vector<int>> map_visited;

int N;
int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

stack<pair<int, int>> getland;
stack<pair<pair<int, int>,int>> s;	// stack = ((y좌표,x좌표),섬의 번호)

bool map_check(int count) {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			
			if (map[i][j] == 1 && map_visited[i][j] == 0) {
				
				getland.push(make_pair(i, j));
				s.push(make_pair(make_pair(i, j),count));	//나중에 비교하기 위해 저장
				
				map_visited[i][j] = 1;
				
				return true;
			}

		}
	}

	return false;

}

void DFS() {
	
	int cnt = 1;	//섬 번호
	
	while (1) {
		
		if (map_check(cnt) == false) return;
		
		while (!getland.empty()) {
		
			int y = getland.top().first;
			int x = getland.top().second;
			getland.pop();
			
			//상하좌우로 같은 섬인지 아닌지 확인
			for (int i = 0; i < 4; i++) {
				
				int new_y = y + dir[i][0];
				int new_x = x + dir[i][1];
			
				if (new_y < 0 || new_y >= N || new_x < 0 || new_x >= N) continue;
				
				//방문하지 않았으며, 상하좌우로 같은 섬이면 stack에 저장
				if (map[new_y][new_x] == 1 && map_visited[new_y][new_x] == 0) {
					map_visited[new_y][new_x] = 1;
					getland.push(make_pair(new_y,new_x));
					s.push(make_pair(make_pair(new_y,new_x ), cnt));	//cnt = 섬의 번호
				}

			}
		}
		//같은 섬 지역을 모두 조사했으므로 다른 섬번호로 매김
		cnt++;
	}
}

int main(void) {
	
	cin >> N;
	
	map.assign(N, vector<int>(N, 0));
	map_visited.assign(N, vector<int>(N, 0));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	DFS();
	
	int min = 10000;	//최소길이를 탐색하기 위한 변수

	int size = s.size();

	//서로 섬인 좌표끼리 길이를 비교한 후 최소길이를 출력하기 위한 알고리즘(compare with isLand code)
	//(단, 같은 섬은 비교하지 않는다)
	while (size--) {
		
		int y = s.top().first.first;
		int x = s.top().first.second;
		int num = s.top().second;
		s.pop();
		
		stack<pair<pair<int, int>, int>> s2 = s;
		
		while (!s2.empty()) {
		
			int y2 = s2.top().first.first;
			int x2 = s2.top().first.second;
			int num2 = s2.top().second;
			s2.pop();
			
			if (num == num2) continue;	//같은 섬일 때는 패스(if same isLand, pass)
			
			int cnt = abs(y2 - y) + abs(x2 - x)-1;	//거리구하기(get the length with math solve)
			
			if (cnt < min) min = cnt;	//최소길이일 경우 업데이트(update with minimum length)
		
		}
	}

	cout << min;	//최소길이 출력(print minimum length)
}
