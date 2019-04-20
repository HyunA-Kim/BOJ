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

	//��ȭ�¿�� �̵�
	for (int i = 0; i < 4; i++) {
	
		int new_y = y + dir[i][0];
		int new_x = x + dir[i][1];
		
		if (new_y < 0 || new_y >= R || new_x < 0 || new_x >= C) continue;
		
		bool find_alphabet = false;	//���� ���ĺ��� ���� ��, ��ŵ (if same alphabet, continue )

		for (int i = 0; i < alphabet.size(); i++) {
			if (alphabet[i] == map[new_y][new_x]) {
				find_alphabet = true; 
				break;
			}
		}
		if (find_alphabet == true) continue;
		
		//�湮���� ���� ����� ��, �ش� ��� �߰�
		if (map_visited[new_y][new_x] == 0) {
			map_visited[new_y][new_x] = 1;
			alphabet.push_back(map[new_y][new_x]);
			chess(new_y, new_x, cnt+1);	//DFS�� �̿��� ���� ��� Ž�� (using dfs, search next node)
			map_visited[new_y][new_x] = 0;	//�ٸ� ��ε� Ž���ϱ� ���� ���� (go to different route too )
			alphabet.pop_back();
		}
	}


	ans = max(ans, cnt);	//�ִ� ��μ����ϱ� (get max route count)
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
	
	alphabet.push_back(map[0][0]);	//���� ���ĺ��� �ִ��� Ȯ�� ���θ� ���� �߰�
	map_visited[0][0] = 1;
	chess(0, 0, 1);
	
	cout << ans;	//�ִ밪 ���

	return 0;
}