#include<iostream>
#include<vector>
#include<stack>
#include<queue>

using namespace std;

int N;
vector<vector<int>> map;

void dfs(int node) {
	
	stack<int> s;
	vector<int> isVisited;
	
	s.push(node);
	isVisited.assign(N, 0);

	while (s.size()) {
		int now_node = s.top();
		s.pop();

		for (int to = 0; to < N; to++) {
			if (map[now_node][to] && isVisited[to] == 0) {
				s.push(to);
				isVisited[to] = 1;
			}
		}
	}
	
	for (int i = 0; i < N; i++) {
		if (isVisited[i] == 1) {
			map[node][i] = 1;
		}
	}
		return;
}

int main(void) {
		
	cin >> N;

	map.assign(N, vector<int>(N, 0));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < N; i++) {
		dfs(i);
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << map[i][j] << " ";
		}
		cout << "\n";
	}

}