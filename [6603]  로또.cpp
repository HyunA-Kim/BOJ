#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int K;

vector<int> map;
vector<int> map_visited;
vector<int> v;	//����� �� ���ڸ� ����ִ� ����

//����� �� ����� �Լ�
void pick(int cnt, int next) {	

	//6�� ���� ����� ���(if select 6 numbers finish)
	if (cnt == 6) {
		
		for (int i = 0; i < K; i++) {
			if (map_visited[i] == 1) {
				v.push_back(map[i]);	//ǥ�õ� ���͵� ���� ����(�����ϱ� ����)
			}
		}

		sort(v.begin(), v.end());	//������������ ����

		for (int i = 0; i < v.size(); i++) {
			cout << v[i]<<" ";
		}
		cout << endl;

		v.clear();	//�ٸ� ����� ���� ���ϱ� ����, �ش� ���� �ʱ�ȭ
		return;
	}

	//������ �ƴ�, �ߺ��� ���� ���� ���ؼ� ���������� �����
	for (int i = next; i < K; i++) {
		if (map_visited[i] == 0) {
			map_visited[i] = 1;
			pick(cnt + 1,i+1);	//�ϳ��� ���� ���� ���� ����������, ���� (add another number)
			map_visited[i] = 0;	//�ٸ� ���� ���� ���� �ʱ�ȭ (Initalize for pick different number array)
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

		//������ ����ϱ� ���� �Լ�(calculate with Combination skill)
		for (int i = 0; i < K; i++) {
			map_visited[i] = 1;
			pick(1,i+1);	//���� ������ ����� �� �ֵ��� ����(making combination)
			map_visited[i] = 0;
		}

		cout << endl;

	}
	
}