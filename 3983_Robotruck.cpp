#include <cstdio>
#include <cmath>
#include <algorithm>
#include <stack>
#include <utility>
#include <string>

using namespace std;

const long MAX = 100000;
long N, total_moves;
int T, C, x[MAX], y[MAX], w[MAX], weight, ret[MAX];

int moves(int i, int j) {
	return abs(x[i] - x[j]) + abs(y[i] - y[j]);
}

struct State{
	long next;
	int weight;
	long moves;

	string to_string() {
		return std::to_string(next) + " " + std::to_string(weight) + " " + std::to_string(moves);
	}
};

stack<State> to_deliver;
void DFS() {
	to_deliver.push({0, 0, 0});

	State cur;

	while(!to_deliver.empty()) {
		cur = to_deliver.top();
		to_deliver.pop();

		if (cur.moves > total_moves) continue;

		if (cur.next == N - 1) {
			total_moves = min(total_moves, cur.weight == 0 ? cur.moves + 2 * ret[cur.next] : cur.moves + ret[cur.next]);
			continue;
		}

		if (cur.weight == 0) to_deliver.push({cur.next + 1, cur.weight + w[cur.next], cur.moves + ret[cur.next]});
		else if (cur.weight + w[cur.next] > C) to_deliver.push({cur.next, 0, cur.moves + ret[cur.next - 1]});
		else {
			to_deliver.push({cur.next, 0, cur.moves + ret[cur.next - 1]});
			to_deliver.push({cur.next + 1, cur.weight + w[cur.next], cur.moves + moves(cur.next-1, cur.next)});
		}
	}
}

int main () {
	scanf("%d", &T);

	while(T--) {
		scanf("%d%lo", &C, &N);

		total_moves = 0;

		for (long i = 0; i < N; ++i) {
			scanf("%d%d%d", &x[i], &y[i], &w[i]);
			ret[i] = x[i] + y[i];
			// w[i] += i > 0 ? w[i-1] : 0;
		}

		/*long j;
		for (long i = 0; i < N; ++i)
		{
			j = i;
			while(j + 1 < N && w[j + 1] - w[i] < C) j++;

			for (long k = i; k <= j; ++i)
			{
				
			}
		}*/

		total_moves = MAX;
		DFS();

		printf("%lo\n", total_moves);

		// for(long i = 0; i < N; ++i) {
		// 	printf("%d ", w[i]);
		// }
		// printf("\n");

		if (T) printf("\n");
	}

	return 0;
}