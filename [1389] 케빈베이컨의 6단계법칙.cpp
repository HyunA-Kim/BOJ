#include<iostream>
#include<vector>
#include<stack>

using namespace std;

int N, M;
int min_count=100000;	//최소 방문횟수
int man_num=0;

vector<vector<int>> map;

void DFS(int A) {
	
	vector<int>isVisited;
	stack<int> s;

	isVisited.assign(N, 0);
	s.push(A);	//해당 좌표를 stack에 입력

	while (!s.empty()) {
		int k = s.top();
		s.pop();
		for (int i = 0; i < N; i++) {
			if (i == A) continue;
			if (map[k][i] == 1 && isVisited[i]== 0 ) {
				isVisited[i] = isVisited[k] + 1;	//깊이를 계산하기 위해 전 방문노드의 수에서 더함
				s.push(i);	
			}
		}
	}
	
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		cnt += isVisited[i];	//방문횟수 더하기
	}

	//서로간의 방문횟수 비교 및 저장
	if (min_count > cnt) {
		man_num = A;
		min_count = cnt;
	}
}

int main(void) {
	
	int man_number=0;
	int A, B;

	cin >> N >> M;

	map.assign(N, vector<int>(N, 0));

	for (int i = 0; i < M; i++) {
		cin >> A >> B;
		map[A-1][B-1] = 1;
		map[B-1][A-1] = 1;
	}

	for (int i = 0; i < N; i++) {
		DFS(i);	//각각 방문횟수를 카운트하기 위한 함수
	}

	cout << man_num+1;	//가장 작은 방문횟수 가지고 있는 사람 출력
	return 0;
}
