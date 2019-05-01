#include<iostream>
#include<vector>
#include<stack>

using namespace std;

int V, E;

vector<vector<int>> map;
vector<int> isVisited;

void isBinary() {
	for (int i = 0; i < V; i++) {
		int find = isVisited[i];
		for (int j = 0; j < map[i].size(); j++) {
			if (find == isVisited[map[i][j]]) {
				cout << "NO" << endl;
				return;
			}
		}
	}
	cout << "YES" << endl;
	return;
}

void DFS(int num, int find) {

	for (int i = 0; i < map[num].size(); i++) {
		if (!isVisited[map[num][i]]) {
			isVisited[map[num][i]] = find * -1;
			DFS(map[num][i], find*-1);
		}
	}

}

int main(void) {
	
	int T;
	cin >> T;

	while (T--) {
		cin >> V >> E;
		map.assign(V, vector<int>(V, 0));
		isVisited.assign(V, 0);

		for (int i = 0; i < E; i++) {
			int x, y;
			cin >> x >> y;
			map[x - 1][y - 1] = 1;
			map[y - 1][x - 1] = 1;
		
		}

		for (int i = 0; i < V; i++) {
			isVisited[i] = 1;
			DFS(i, 1);
		}

		isBinary();
	}

}
