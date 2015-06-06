#include <cstdio>
#include <algorithm>

using namespace std;

const int kmax = 100001;
int houses[kmax];
int n, m;

int use(float mid) {
    int used = 1;

    float range = houses[0] + mid;

    for (int i = 0; i < m; ++i) {
        if (float(houses[i]) - mid > range) {
            range = houses[i] + mid;
            if (++used > n) return used;
        }
    }

    return used;
}

int main()
{
    int t;

    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &m);

        for (int i = 0; i < m; ++i)
            scanf("%d", &houses[i]);

        if (n >= m) printf("%.1f\n",0.0f);
        else {
            float f = 0.f, l = 1000000.f, mid;
            sort(houses, houses+m);

            while(l - f > 0.05f) {
                mid = (f + l) / 2.f;
                int used = use(mid);
                if (used > n) f = mid;
                else l = mid;
            }

            printf("%.1f\n", l);
        }
    }

    return 0;
}
