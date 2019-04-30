#include<iostream>
#include<vector>
#include<stack>

using namespace std;

int V, E;

vector<vector<int>> map;
vector<vector<int>> map_visited;

void DFS(int num) {
	
	stack<int> s;
	vector<int> isVisited;

	s.push(num);
	isVisited.assign(V, 0);

	while (!s.empty()) {
		int k = s.top();
		s.pop();
		for (int i = 0; i < V; i++) {
			if (map[k][i] == 1 && map_visited[k][i] != 0) {
				map_visited[k][i] *= -1;
			}
		}
	}
}

int main(void) {
	
	int T;
	cin >> T;

	while (T--) {
		cin >> V >> E;
		map.assign(V, vector<int>(V, 0));
		map_visited.assign(V, vector<int>(V, 0));

		for (int i = 0; i < E; i++) {
			int x, y;
			cin >> x >> y;
			map[x - 1][y - 1] = 1;
			map[y - 1][x - 1] = 1;
			map_visited[x - 1][y - 1] = 1;
			map_visited[y - 1][x - 1] = 1;
		}

		for (int i = 0; i < V; i++) {
			DFS(i);
		}
	}

}