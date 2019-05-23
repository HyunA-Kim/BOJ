#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int F, S, G, U, D;
int dir[2];
vector<int> map;
queue<int> q;

bool Except_Case() {
	bool finish = false;
	if (S < G) {
		if (U == 0) {
			cout << "use the stairs";
			finish = true;
		}
		if (D == 0 && (G - S) % U != 0) {
			cout << "use the stairs";
			finish = true;
		}
	}
	else if (S > G) {
		if (D == 0) {
			cout << "use the stairs";
			finish = true;
		}
		if (U == 0 && (S - G) % D != 0) {
			cout << "use the stairs";
			finish = true;
		}
	}
	else if (S == G) {
		cout << map[S - 1];
		finish = true;
	}

	return finish;
}
void BFS() {

	if (Except_Case() == true) return;

	map[S - 1] = 1;
	q.push(S - 1);

	while (!q.empty()) {
		int k = q.front();
		q.pop();
		for (int i = 0; i < 2; i++) {
			int new_k = k + dir[i];
			if (new_k < 0 || new_k >= F) continue;
			if (map[new_k] == 0) {
				map[new_k] = map[k] + 1;
				q.push(new_k);
			}
			if (new_k == G - 1) {
				cout << map[new_k]-1;
				return;
			}
		}
	}
}

int main(void) {
	cin >> F >> S >> G >> U >> D;

	dir[0] = U;
	dir[1] = -D;
	map.assign(F, 0);
		
	BFS();
}