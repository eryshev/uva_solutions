/*
*	6202 Memory Overflow
*/
#include <cstdio>
#include <string>

using namespace std;

int n, k;
char names[500];
bool counted[500];

int main() {
	int t;

	scanf("%d", &t);

	int c = 0;
	while (++c <= t) {
		scanf("%d%d ", &n, &k);
		
		for (int i = 0; i < n; ++i)
		{
			scanf("%c", &names[i]);
			counted[i] = false;
		}

		int answer = 0;
		for (int i = 0; i < n; ++i)
		{
			for (int j = i + 1; j <= (i + k < n ? i + k : n - 1); ++j)
			{
				if (!counted[j] && names[i] == names[j]) {
					counted[j] = true;
					answer++;
				}
			}
		}

		printf("Case %d: %d\n", c, answer);
	}

	return 0;
}
