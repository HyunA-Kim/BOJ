#include<iostream>
#include<vector>

using namespace std;

int V, E;

vector<int> map[20001];
vector<int> isVisited;

//해당 그래프가 이분그래프인지 판별
void isBinary() {

	for (int i = 1; i <= V; i++) {
	
		int find = isVisited[i];
		
		for (int j = 0; j < map[i].size(); j++) {
			
			//해당그래프의 isVisited이 find와 동일할시, 같은부분 -> 이분그래프가 아님
			if (find == isVisited[map[i][j]]) {
				cout << "NO" << endl;
				return;
			}

		}
	}

	//동일한 부분이 없을시, 홀수사이클이 아니므로 이분그래프
	cout << "YES" << endl;
	return;
}

void DFS(int num, int find) {

	for (int i = 0; i < map[num].size(); i++) {

		//해당그래프 정점을 방문하지 않았을 때
		if (!isVisited[map[num][i]]) {

			//가지고 있던 변수와 다른 변수를 저장해줌
			isVisited[map[num][i]] = find * -1;
			
			//또다른 연결선 찾는 재귀함수(recursive function start)
			DFS(map[num][i], find*-1);
		}
	}

}

int main(void) {
	
	int T;
	cin >> T;

	while (T--) {
		cin >> V >> E;
		isVisited.assign(V+1, 0);

		for (int i = 0; i < E; i++) {

			int x, y;
			cin >> x >> y;
			//맵에 해당 정점 추가
			map[x].push_back(y);
			map[y].push_back(x);
		
		}

		for (int i = 1; i <= V; i++) {

			//각 정점마다 연결되어있는 간선찾기(find connected line)
			if (!isVisited[i]) {
				isVisited[i] = 1;
				DFS(i, 1);
			}
		}

		//이분그래프인지 판별함수 ( Discrimination Bipartite Graph)
		isBinary();

		//맵 리셋(map reset)
		for (int i = 1; i <= V; i++) map[i].clear();
	}

}
