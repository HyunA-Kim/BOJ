#include<iostream>
#include<vector>
#include<stack>

using namespace std;
int N;

vector<int> map;
vector<int> map_visited;

stack<int> s;

void DFS(int i,int goal) {
	

	if (map_visited[i] == 1) return;

	int k = map[i];

	if (k == i) {
		map_visited[i] = 1;
		while (!s.empty()) {
			int num = s.top();
			s.pop();
			map_visited[num] = 0;
		}
		return;
	}
	
	if (k == goal) {
		while (!s.empty()) {
			int num = s.top();
			s.pop();
			map_visited[num] = 1;
		}
		return;
	}
	else if (map_visited[k] == 1) return;
	else {
		s.push(k);
		DFS(k,goal);
	}
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
