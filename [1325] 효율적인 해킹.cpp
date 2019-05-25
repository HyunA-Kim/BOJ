#include<iostream>
#include<vector>
#include<stack>

using namespace std;

int N, M;
vector<vector<int>> map;
vector<vector<int>> map_visited;

stack<int> s;

void DFS(int pos,int cnt) {
	while (!s.empty()) {
		int k = s.top();
		s.pop();
		if (map_visited[k] == 0) {
			for (int i = 0; i < map[k].size(); i++) {
				s.push(map[k][i]);
			}
		}
	}
}

int main(void) {
	
	cin >> N >> M;
	map.assign(N + 1, vector<int>(N+1,0));
	map_visited.assign(N + 1, vector<int>(N + 1, 0));
	while (M--) {
		int x, y;
		cin >> x >> y;
		map[y].push_back(x);
		for (int i = 0; i < N; i++) {
			DFS(i,0);
		}
	}
}