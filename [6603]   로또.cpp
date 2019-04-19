#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int K;

vector<int> map;
vector<int> map_visited;
vector<int> v;	//경우의 수 숫자를 담아주는 벡터

//경우의 수 만드는 함수
void pick(int cnt, int next) {	

	//6개 숫자 골랐을 경우(if select 6 numbers finish)
	if (cnt == 6) {
		
		for (int i = 0; i < K; i++) {
			if (map_visited[i] == 1) {
				v.push_back(map[i]);	//표시된 벡터들 값을 저장(정렬하기 위함)
			}
		}

		sort(v.begin(), v.end());	//오름차순으로 정렬

		for (int i = 0; i < v.size(); i++) {
			cout << v[i]<<" ";
		}
		cout << endl;

		v.clear();	//다른 경우의 수를 구하기 위해, 해당 벡터 초기화
		return;
	}

	//순열이 아닌, 중복된 것을 빼기 위해서 다음값부터 경우계산
	for (int i = next; i < K; i++) {
		if (map_visited[i] == 0) {
			map_visited[i] = 1;
			pick(cnt + 1,i+1);	//하나더 숫자 고르기 위해 증가시켜줌, 조합 (add another number)
			map_visited[i] = 0;	//다른 숫자 고르기 위한 초기화 (Initalize for pick different number array)
		}
	}

}
int main(void) {
	

	while (1) {

		cin >> K;
		
		map.assign(K, 0);
		map_visited.assign(K, 0);

		if (K == 0) break;

		for (int i = 0; i < K; i++) {
			int num;
			cin >> num;
			map[i] = num;
		}

		//조합을 계산하기 위한 함수(calculate with Combination skill)
		for (int i = 0; i < K; i++) {
			map_visited[i] = 1;
			pick(1,i+1);	//다음 수부터 계산할 수 있도록 만듬(making combination)
			map_visited[i] = 0;
		}

		cout << endl;

	}
	
}