#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX = 10e+5; 
int n, m;
unsigned long long takeover[MAX];
unsigned long long buyout[MAX];

int main() {
	int t = 1;
	while (scanf("%d%d", &n, &m) == 2) {

		for (int i = 0; i < n; ++i)
		{
			scanf("%llu", &takeover[i]);
		}
		for (int i = 0; i < m; ++i)
		{
			scanf("%llu", &buyout[i]);
		}

		sort(takeover, takeover + n);
		sort(buyout, buyout + m);

		// while (n != 0 && m != 0) {
		// 	if (takeover[n-1] > buyout[m-1]) m--;
		// 	else {
		// 		if (n != 1) {
		// 			takeover[n-2] += takeover[n-1];
		// 			n--;
		// 		}
		// 	}

		// 	if (n == 0 || m == 0) break;

		// 	if (takeover[n-1] < buyout[m-1]) n--;
		// 	else {
		// 		if (m != 1) {
		// 			buyout[m-2] += buyout[m-1];
		// 			m--;
		// 		}
		// 	}
		// }

		// if (n) printf("Case %d: Takeover Incorporated\n", t++);
		// else printf("Case %d: Buyout Limited\n", t++);
		
		bool friendly_one = false, take_over_is_winnner = false;
		while (n != 0 && m != 0) {
			if (takeover[n-1] > buyout[m-1]) {
				if (friendly_one) {
					take_over_is_winnner = true;
					break;
				}
				m--;
			}
			else {
				if (n != 1) {
					takeover[n-2] += takeover[n-1];
					friendly_one = true;
					n--;
				}
			}

			if (n == 0 || m == 0) break;

			if (takeover[n-1] < buyout[m-1]) {
				if (friendly_one) {
					take_over_is_winnner = false;
					break;
				}
				n--;
			}
			else {
				if (m != 1) {
					buyout[m-2] += buyout[m-1];
					friendly_one = true;
					m--;
				}
			}
		}

		if (take_over_is_winnner || m == 0) printf("Case %d: Takeover Incorporated\n", t++);
		else printf("Case %d: Buyout Limited\n", t++);
	}

	return 0;
}
