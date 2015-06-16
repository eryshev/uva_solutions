/*
*	UVA 821 - Page Hopping
*	Floyd-Warshall algo
*/

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX = 101;
int d[MAX][MAX];
int n;

int main() {

	int f, s, counter = 1;
	while (scanf("%d%d", &f, &s)) {
		if (f == s && f == 0) {
			break;
		}

		memset(d, 1, MAX*MAX * sizeof(int));

		d[f-1][s-1] = 1;
		n = max(f, s);

		while (scanf("%d%d", &f, &s)) {
			if (f == s && f == 0) {
				break;
			}			

			d[f-1][s-1] = 1;
			n = max(max(n, f), s);
		}

		for (int i = 0; i < n; ++i)
		{
			d[i][i] = 0;
		}

		for (int k = 0; k < n; ++k)
		{
			for (int i = 0; i < n; ++i)
			{
				for (int j = 0; j < n; ++j)
				{
					d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
				}
			}
		}

		int answer = 0;
		int perm = 0;
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
				if (d[i][j] < MAX && i != j) {
					answer +=  d[i][j];
					perm++;
				}
		}

		printf("Case %d: average length between pages = %1.3f clicks\n", counter++, answer / double(perm));
	}

	return 0;
}
