#include<iostream>
#include<vector>

using namespace std;

int N, M;
int ans = 0;
int maximum = 0;

vector<int> map[10001];
vector<int> map_visited;
vector<int> computer;	//컴퓨터를 해킹할 수 있는 수 (count on computer hacking)

void DFS(int pos) {

	map_visited[pos] = 1;
	
	for (int i = 0; i < map[pos].size(); i++) {
	
		if (map_visited[map[pos][i]] == 0) {
			ans++;	//해킹한 수 더하기 (count hacking computer)
			DFS(map[pos][i]);	//더 해킹할 수 있는지 확인(check possible hacking computer)
		}

	}
}

int main(void) {
	
	cin >> N >> M;
	computer.assign(N + 1, 0);

	while (M--) {
		int x, y;
		cin >> x >> y;
		map[y].push_back(x);

	}

	for (int i = 1; i <= N; i++) {
		ans = 0;	//각 컴퓨터에서 실행하므로 초기화(initalize because each computer do)
		map_visited.assign(N + 1, 0);	//각 컴퓨터에서 실행하므로 초기화(initalize because each computer do)
		DFS(i);
		computer[i] = ans;	//해킹 한 수 저장(save hacking computers)
		if (maximum < ans) maximum = ans;	//가장 큰 수 확인(check maximum number)
	}


	for (int i = 1; i <= N; i++) {
		if (computer[i] == maximum) {
			cout << i << " ";	//가장 큰 수 가지고 있는 컴퓨터 출력(print if there has a lot of maximum computer)
		}
	}

}
