#include<iostream>
#include<vector>

using namespace std;

int n;
int goal_x, goal_y;
int m;
int cnt = 0; //�̼�

vector<int> map[101];
vector<int> map_visited[101];

void Relative(int root) {

	for (int i = 0; i < n; i++) {
	
		if (map[i].size() == 0) continue;
		
		for (int j = 0; j < map[i].size(); j++) {
		
			if (map[i][j] == root) {
				// �ش� ��ȣ�� ã���� ��, �װ����� ���� ����
				// 1. ���� �ö󰡴� ��� -> �ö󰡸鼭 cnt+1 ����
				// 2. �Ʒ��� �������� ��� -> �Ʒ��� �������鼭 cnt+1 ����
			}
		}
	}
}

int main(void) {

	cin >> n;
	cin >> goal_x >> goal_y;
	cin >> m;

	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		map[x].push_back(y);
	}

	Relative(goal_x);
}