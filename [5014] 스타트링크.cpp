#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int F, S, G, U, D;
int dir[2];	//Up,Down 기록

vector<int> map;	
queue<int> q;	

//예외조건 명시
bool Except_Case() {
	
	bool finish = false;

	//더이상 올라가거나 내려갈 경우가 없을 경우 계단이용(use the stairs, when can't use elevator)
	if (S < G) {
		if (U == 0) {
			finish = true;
		}
		else if (D == 0 && (G - S) % U != 0) {
			finish = true;
		}
	}
	else if (S > G) {
		if (D == 0) {
			finish = true;
		}
		else if (U == 0 && (S - G) % D != 0) {
			finish = true;
		}
	}

	if (finish == true) 
		cout << "use the stairs";
	
	return finish;
}
void BFS() {

	//예외조건에서 걸러질 경우 리턴(return when catch the except_case)
	if (S == G) {
		cout << map[S - 1];
		return;
	}
	else if (Except_Case() == true) return;

	//맵에 현재 위치 저장(save the map with current location)
	map[S - 1] = 1;
	q.push(S - 1);

	while (!q.empty()) {

		int k = q.front();
		q.pop();

		//도착 했을 경우(when arrived at goal)
		if (k == G - 1) {
			cout << map[k] - 1;
			return;
		}

		//위로 올라가거나, 내려가는 동작(move to up and down case)
		for (int i = 0; i < 2; i++) {

			int new_k = k + dir[i];
			
			if (new_k < 0 || new_k >= F) continue;	//배열을 벗어낫을 경우, 동작이 일어나지 않도록 함(if out of index, do not anything)
			
			if (map[new_k] == 0) {
				map[new_k] = map[k] + 1;	//최소 움직임의 수를 기록(note count of minimum move)
				q.push(new_k);	//다음 칸으로 갈 수 있도록 queue에 저장(save in queue to move next)
			}

		}
	}

	//해당 queue에서 끝나지 않았을 경우, 계단이용(use the stairs, when can't go to the goal)
	cout << "use the stairs";
	return;
}

int main(void) {

	cin >> F >> S >> G >> U >> D;

	//Up,Down 기록(note the up and down)
	dir[0] = U;
	dir[1] = -D;

	map.assign(F+1, 0);
		
	BFS();	//BFS실행(action BFS)
}
