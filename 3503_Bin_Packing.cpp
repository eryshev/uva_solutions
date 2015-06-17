/*
*	ACM-ICPC Bin packing 
*	Greedy algo
*/

#include <cstdio>
#include <algorithm>

using namespace std;

const long MAX = 100000;

int t, l;
long n;
int ls[MAX];
int bins[MAX];
int used[MAX];
long used_bins;
bool placed;

int main () {
	scanf("%d", &t);

	while(t--) {
		scanf("%d%d", &n, &l);

		for (long i = 0; i < n; ++i)
		{
			scanf("%d", &ls[i]);
			bins[i] = l;
			used[i] = 2;
		}

		sort(ls, ls + n, [] (int a, int b) {return b < a;});

		used_bins = 1;

		for (long i = 0; i < n; ++i)
		{
			placed = false;
			for (long j = 0; j < used_bins; ++j)
			{
				if (ls[i] <= bins[j] && used[j]) {
					bins[j] -= ls[i];
					placed = true;
					used[j] -= 1;
					break;
				}
			}
			if (!placed) {
				bins[used_bins++] -= ls[i];
				used[used_bins - 1] -= 1;
			}
		}

		printf("%d\n", used_bins);

		if (t) printf("\n");
	}

	return 0;
}