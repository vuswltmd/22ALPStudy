#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <stack>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <queue>
#include <cstdlib>
#include <tuple>
#include <cstring>
#include <utility>
using namespace std;

#define X first
#define Y second

int dx[4] = { 0, -1, 1, 0};
int dy[4] = { -1, 0, 0, 1}; //가장 위에 있는 물고기, 그러한 물고기가 여러마리라면, 가장 왼쪽에 있는 물고기를 먹는다.
int board[25][25];
int visited[25][25];
int baby_size = 2; //처음 아기상어의 크기는 2;
int fish_stack = 0; // 현재 먹은 물고기 수
int N; // 공간의 크기 N(2 ≤ N ≤ 20)
int Time = 0;
int cnt = 0;

struct cmp{
	bool operator()(pair<int, int >&a, pair<int, int>&b) {
		if (visited[a.X][a.Y] > visited[b.X][b.Y]) return true; //거리 순
		else if (visited[a.X][a.Y] == visited[b.X][b.Y]) {
			if (a.X > b.X) return true; // 위쪽 먼저
			else if (a.X == b.X) return a.Y > b.Y; // 왼쪽 먼저
			else return false;
		}
		else return false;
	}
};

queue<pair<int, int>> Q;
priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> PQ;

void bfs() {
	while (!Q.empty()) {
		auto cur = Q.front(); Q.pop();
		for (int dir = 0; dir < 4; dir++) {
			int nx = cur.X + dx[dir];
			int ny = cur.Y + dy[dir];

			if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;
			if (visited[nx][ny] != -1) continue;
			if (board[nx][ny] != 0 && board[nx][ny] > baby_size) continue;

			if (board[nx][ny] == baby_size || board[nx][ny] == 0) {
				//크기가 같거나 빈칸이면 그냥 지나간다.
				Q.push({ nx, ny });
				visited[nx][ny] = visited[cur.X][cur.Y] + 1;
			}
			else { // 크기가 작은 물고기가 있으면 우선순위 큐에 넣는다
				Q.push({ nx, ny });
				visited[nx][ny] = visited[cur.X][cur.Y] + 1;
				PQ.push({ nx, ny });
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> board[i][j];

			if (board[i][j] >= 1 && board[i][j] <= 6) cnt++;
			else if (board[i][j] == 9) Q.push({ i, j });
		}
	}

	int Time = 0; //??
	int fish_stack = 0;

	while (cnt) {
		PQ = {};
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				visited[i][j] = -1;
			}
		}

		auto start = Q.front();
		visited[start.X][start.Y] = 0;
		bfs();
		if (PQ.size() == 0) break; //먹을 수 있는 물고기가 없을 때 프로그램 종료

		auto target = PQ.top(); //우선순위큐에 의하여 문제조건에 맞는 먹잇감의 좌표가 정해짐

		board[start.X][start.Y] = 0;
		board[target.X][target.Y] = 0;

		Time += visited[target.X][target.Y];
		Q.push({ target.X, target.Y });
		fish_stack++;
		if (fish_stack == baby_size) {
			fish_stack = 0;
			baby_size++;
		}
		cnt--;
	}

	cout << Time;

}
