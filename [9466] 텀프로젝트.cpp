#include<iostream>
#include<vector>

using namespace std;
int N;
int ans = 0;

vector<int> map;
vector<int> map_visited;	//맵의 방문여부
vector<int> map_finished;	//해당 숫자의 카운트가 끝났는지 확인

void DFS(int i,int goal) {

	map_visited[i] = 1;	//맵을 방문했다는 확인
	int k = map[i];

	//해당 맵의 결과값으로 DFS실행
	if (map_visited[k] == 0) {
		DFS(k, goal);
	}
	//해당 맵의 결과값이 이미 방문했으며, 카운트가 끝나지 않았을 경우
	//카운트 실행
	else if(map_finished[k]==0){
		for (int j = k; j != i; j = map[j])
			ans++;
		ans++;
		//카운트
	}

	map_finished[i] = 1;	//해당 인덱스 방문끝
}

int main(void) {
	
	int T;
	cin >> T;

	while (T--) {
		ans = 0;
		cin >> N;

		map.assign(N+1, 0);
		map_visited.assign(N + 1, 0);
		map_finished.assign(N + 1, 0);

		for (int i = 1; i <= N; i++) {
			cin >> map[i];
		}

		for (int i = 1; i <= N; i++) {
			if(map_visited[i]==0) 
				DFS(i, i);
		}
		
		ans = N - ans;	//방문안한 것으로 업데이트
		cout << ans << endl;
	}
}
