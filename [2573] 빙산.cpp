#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int N, M;
int dj[4] = { -1,0,0,1 };
int di[4] = { 0,1,-1,0 };
int ans=1;	// ����� ���������� ���� ��(answer)

vector<vector<int>> map;
vector<vector<int>> map_collapsed;	//�����¿� �����ƴ� �κ� ������� ��(calculate non-ice area)
vector<vector<int>> map_visited;	//���� �湮���� üũ(visit or non-visit check)

queue<pair<int, int>> q;

//���� �����κκ� ã���Լ�(find area those part of ice)
bool map_find() {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] != 0 && map_visited[i][j]==0) {
				
				map_visited[i][j] = 1;
				q.push(make_pair(i, j));
				return true;
			}
		}
	}

	return false;
}

//���� ������ ����κ� ã���ִ� �Լ�(find connected non-ice area)
bool BFS() {

	int separate = 0;	//������ �и������ Ȯ��(certificate separte ice area)

	while (1) {

		if (map_find() == false) {
			//�ϳ��̻��� �и��������� ���, ���
			if (separate > 1) {
				cout << ans;
				return true;
			}

			//�и����� �ʰ�, ��� �� ����� ��� 0�� ���
			else if (separate == 0) {
				cout << 0;
				return true;
			}

			//������ �κ�, �� ������Ƿ� ������ �쵵����
			else return false;

		};

		separate++;
		
		while (!q.empty()) {

			int y = q.front().first;
			int x = q.front().second;
			
			q.pop();

			//��ȭ�¿� �����κκ� ����(connect up,down,right,left ice area)
			for (int i = 0; i < 4; i++) {
			
				int new_y = y + di[i];
				int new_x = x + dj[i];
				
				if (new_y < 0 || new_y >= N || new_x < 0 || new_x >= M) continue;

				if (map[new_y][new_x] != 0 && map_visited[new_y][new_x] == 0) {
					map_visited[new_y][new_x] = 1;
					q.push(make_pair(new_y, new_x));
				}

			}
		}
	}
}

void iceCollapsed() {
	
	map_collapsed.assign(N, vector<int>(M, 0));
	map_visited.assign(N, vector<int>(M, 0));

	//���� �����¿쿡 �ٴ��� ��� ���
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] != 0) {
				
				//�ٴ��� ���� ����
				int cnt = 0;

				//�����¿� �ٴ��ΰ��, �쿩���� ���� ������
				for (int k = 0; k < 4; k++) {
					int new_i = i + di[k];
					int new_j = j + dj[k];
					if (map[new_i][new_j] == 0) {
						cnt++;
					}
				}

				//�쿩�Һκ��� ��ŭ�쿩�ߵǴ��� ����(save data melt ice-area)
				map_collapsed[i][j] = cnt;
			}
		}
	}

	//������̱� �۾�(work melt ice-area)
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			map[i][j] = map[i][j] - map_collapsed[i][j];
			if (map[i][j] < 0) map[i][j] = 0;	//�ٴ��ΰ��, 0���� ����
		}
	}

	//���� �� ����� ���, 1���� �����ְ� �ٽ� �������̱�(yet ice is melt, do again)
	if (BFS() == false) {
		ans++;
		iceCollapsed();
	}
}

int main(void) {
	
	cin >> N >> M;
	map.assign(N, vector<int>(M, 0));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	//������̱� ����(start melt ice area)
	iceCollapsed();
}