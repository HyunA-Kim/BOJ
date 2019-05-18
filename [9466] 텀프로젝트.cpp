#include<iostream>
#include<vector>
#include<stack>

using namespace std;
int N;

vector<int> map;
vector<int> map_visited;

stack<int> s;

void DFS(int i,int goal) {

	if (i == goal) map_visited[i] = 1;
	
	if (map_visited[i] == 1) {

		if (goal != i) return;
		
		while (!s.empty()) {
			int k = s.top();
			s.pop();
			map_visited[k] = 0;
		}
		return;
	
	}

	map_visited[i] = 1;
	int k = map[i];
	s.push(k);
	DFS(k,goal);
	
}

int main(void) {
	
	int T;
	cin >> T;

	while (T--) {
		cin >> N;

		map.assign(N+1, 0);
		map_visited.assign(N + 1, 0);
		
		for (int i = 1; i <= N; i++) {
			cin >> map[i];
		}

		for (int i = 1; i <= N; i++) {
			if (map_visited[i] !=-1) continue;
			DFS(i, i);
		}

		int cnt = 0;
		
		for (int i = 1; i <= N; i++) {
			if (map_visited[i] == 0) cnt++;
		}

		cout << cnt << endl;
	}
}
