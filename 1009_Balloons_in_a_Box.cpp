#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int n;

struct Point {
    int x, y, z;

    Point operator-(const Point& p2) const{
        Point p;

        p.x = x - p2.x;
        p.y = y - p2.y;
        p.z = z - p2.z;
        return p;
    }

    int distance2(const Point& that) const {
        return pow(x - that.x, 2) + pow(y - that.y, 2) + pow(z - that.z, 2);
    }

    float distance(const Point& that) const {
        return sqrt(distance2(that));
    }
};

const int kmax = 10;
Point c1, c2, set[kmax];
int max_radius[kmax], config[kmax];
float r[kmax];
float total_volume, box_volume, answer;

bool isInsideBox(const Point& d1, const Point& d2) {
    return (d1.x && d1.y && d1.z && d2.x && d2.y && d2.z);
    //return (p.x > c1.x && p.y > c1.y && p.z > c1.z && p.x < c2.x && p.y < c2.y && p.z < c2.z);
}

void calcMaxRadius(const Point& p, int i) {
    Point d1, d2;
    d1 = p - c1;
    d2 = c2 - p;

    if (isInsideBox(d1, d2)) {
        int min_radius[3];

        min_radius[0] = min(d1.x, d2.x);
        min_radius[1] = min(d1.y, d2.y);
        min_radius[2] = min(d1.z, d2.z);

        max_radius[i] = *min_element(min_radius, min_radius + 3);
    } else max_radius[i] = -1;
}

const float ksphere_vol = 4.f/3.f*M_PI;
float calcVolume(float r) {
    return (r*r*r * ksphere_vol);
}

void solve() {
    //for (int i = 0; i < (1<<n); ++i) {

        total_volume = 0.f;
        for (int j = 0; j < n; ++j) {
        //    if (!(i & (1 << j))) continue;

            float mr = max_radius[config[j]];

            for(int k = 0; k < j; ++k) {
                //if (!(i & (1 << k))) continue;
                mr = min(mr, set[config[j]].distance(set[config[k]]) - r[config[k]]);
            }

            r[config[j]] = max(0.f, mr);

            if (mr <= 0) continue;

            total_volume += calcVolume(r[config[j]]);

        }
        answer = max(answer, total_volume);
    //}
}

int main()
{
    int c = 0;
    scanf("%d", &n);
    while(true) {
        scanf("%d%d%d", &c1.x, &c1.y, &c1.z);
        scanf("%d%d%d", &c2.x, &c2.y, &c2.z);
        Point dif = c2 - c1;
        box_volume = dif.x * dif.y * dif.z;

        for (int i = 0; i < n; ++i) {
            scanf("%d%d%d", &set[i].x, &set[i].y, &set[i].z);
            calcMaxRadius(set[i], i);
            config[i] = i;
        }

        answer = 0.f;
        do {
            solve();
        } while (next_permutation(config, config + n));

        printf("Box %d: %.0lf\n", ++c, box_volume - answer);
        scanf("%d", &n);
        if(n == 0) break;
        else printf("\n");
    }
    return 0;
}
