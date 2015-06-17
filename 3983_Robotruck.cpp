#include <cstdio>
#include <cmath>

using namespace std;

const long MAX = 100000;
long N, total_moves;
int T, C, x[MAX], y[MAX], w[MAX], weight;

int moves(int i, int j) {
	return abs(x[i] - x[j]) + abs(y[i] - y[j]);
}

int main () {
	scanf("%d", &T);

	while(T--) {
		scanf("%d%d", &C, &N);

		for (long i = 0; i < N; ++i)
			scanf("%d%d%d", &x[i], &y[i], &w[i]);

		total_moves = 0;
		long j;
		for (long i = 0; i < N; ++i) {
			weight = w[i];
			total_moves += x[i] + y[i];
			for (j = i + 1; (weight + w[j] <= C) && j < N; ++j) {
				if (moves(j - 1, j) <= (j + 1 < N ? moves(j, j + 1) : x[j] + y[j])) {
					weight += w[j];
					total_moves += moves(j - 1, j);
				} else break;

				// printf("w%d\n", weight);
			}

			total_moves += x[j - 1] + y[j - 1];
			i = j - 1;
		}

		printf("%d\n", total_moves);

		// for(long i = 0; i < N; ++i) {
		// 	printf("%d ", w[i]);
		// }
		// printf("\n");

		if (T) printf("\n");
	}

	return 0;
}