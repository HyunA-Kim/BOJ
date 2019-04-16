#include<iostream>
#include<vector>
#include<stack>

using namespace std;

int N, M;
int cnt = 1;			 //선의 갯수 세는 변수

vector<vector<int>> map; //연결노드 맵
vector<int> total_check; //cnt를 세주기 위해서, 이미 연결된 노드 기록

void DFS(int node) {
	
	stack<int> s;
	vector<int> isVisited;

	isVisited.assign(N, 0);
	s.push(node);
	total_check[node] = 1;
	
	//node에서 각 방문가능한 노드들을 isVisited[i]에 기록
	while(s.size()) {

		int new_node = s.top();
		s.pop();
		
		for (int i = 0; i < N; i++) {
			if (isVisited[i] == 0 && map[new_node][i] == 1) {
				s.push(i);
				isVisited[i] = 1;
				total_check[i] = 1;
			}
		}
	}

	//루트노드에서 이어져있지않은 노드 = 연결되어있지 않은 노드
	//total_check 기록이 0 일경우, 다른 곳에서 이미 count된 노드가 아니므로 새로운 선으로 인식
	for (int i = 0; i < N; i++) {
		if (isVisited[i] == 0 && total_check[i]==0) {
			cnt++;
			DFS(i);
		}
	}

	return;
}

int main(void) {
	
	cin >> N >> M;

	map.assign(N, vector<int>(N, 0));
	total_check.assign(N, 0);
	for (int i = 0; i < M; i++) {
		int y, x;
		cin >> y >> x;
		map[y - 1][x - 1] = 1;
		map[x - 1][y - 1] = 1;
	}

	for (int i = 0; i < N; i++) {
		DFS(i);
	}

	cout << cnt;
}