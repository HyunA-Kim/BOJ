#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<vector<char>> map;
vector<vector<int>> map_visited;
vector<char> alphabet;
int ans=0;

int R, C;
int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

void chess(int y, int x, int cnt) {

	//상화좌우로 이동
	for (int i = 0; i < 4; i++) {
	
		int new_y = y + dir[i][0];
		int new_x = x + dir[i][1];
		
		if (new_y < 0 || new_y >= R || new_x < 0 || new_x >= C) continue;
		
		bool find_alphabet = false;	//같은 알파벳이 있을 때, 스킵 (if same alphabet, continue )

		for (int i = 0; i < alphabet.size(); i++) {
			if (alphabet[i] == map[new_y][new_x]) {
				find_alphabet = true; 
				break;
			}
		}
		if (find_alphabet == true) continue;
		
		//방문하지 않은 노드일 때, 해당 노드 추가
		if (map_visited[new_y][new_x] == 0) {
			map_visited[new_y][new_x] = 1;
			alphabet.push_back(map[new_y][new_x]);
			chess(new_y, new_x, cnt+1);	//DFS를 이용해 다음 노드 탐색 (using dfs, search next node)
			map_visited[new_y][new_x] = 0;	//다른 경로도 탐색하기 위해 선언 (go to different route too )
			alphabet.pop_back();
		}
	}


	ans = max(ans, cnt);	//최대 경로수구하기 (get max route count)
}

int main(void) {

	cin >> R >> C;

	map.assign(R, vector<char>(C, 0));
	map_visited.assign(R, vector<int>(C, 0));

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> map[i][j];
		}
	}
	
	alphabet.push_back(map[0][0]);	//같은 알파벳이 있는지 확인 여부를 위해 추가
	map_visited[0][0] = 1;
	chess(0, 0, 1);
	
	cout << ans;	//최대값 출력

	return 0;
}