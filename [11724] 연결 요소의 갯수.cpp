#include<iostream>
#include<vector>
#include<stack>

using namespace std;

int N, M;
int cnt = 1;			 //���� ���� ���� ����

vector<vector<int>> map; //������ ��
vector<int> total_check; //cnt�� ���ֱ� ���ؼ�, �̹� ����� ��� ���

void DFS(int node) {
	
	stack<int> s;
	vector<int> isVisited;

	isVisited.assign(N, 0);
	s.push(node);
	total_check[node] = 1;
	
	//node���� �� �湮������ ������ isVisited[i]�� ���
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

	//��Ʈ��忡�� �̾����������� ��� = ����Ǿ����� ���� ���
	//total_check ����� 0 �ϰ��, �ٸ� ������ �̹� count�� ��尡 �ƴϹǷ� ���ο� ������ �ν�
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