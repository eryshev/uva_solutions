#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int M = 100000;
const int N = 50000;

struct Edge {
    int x, y, d;
};

struct Pair {
    int s, t;
};

int n, m, q;
Edge edges[M];
Pair paths[N];

int sorted_edges[M];
//vector<int> min_span_tree;
vector<Pair> min_span_tree[N];
int parent[N];

//find_set with path compressing
int find_set(int i)
{
    int j = i;
    while(i != parent[i]) i = parent[i];
    while(parent[j] != i) {
        int tmp = parent[j];
        parent[j] = i;
        j = tmp;
    }
    return i;
}

void kruskal() {
    int en = 0;
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
        min_span_tree[i].clear();
    }

    for (int i = 0; i < m; ++i) {
        int from = edges[sorted_edges[i]].x;
        int to = edges[sorted_edges[i]].y;
        int x = find_set(from);
        int y = find_set(to);

        if (x == y) continue;

        parent[x] = y;

        min_span_tree[from].push_back({to, sorted_edges[i]});
        min_span_tree[to].push_back({from, sorted_edges[i]});

        if (en++ == n - 1) break;
    }
}

queue<Pair> to_visit;
bool visited[N];
int finish;
int bfs() {
    auto start = to_visit.front();
    to_visit.pop();
    visited[start.s] = true;

    for(auto&& v: min_span_tree[start.s]) {
        if (v.s == finish) return max(start.t, edges[v.t].d);
        if (!visited[v.s]) {
            to_visit.push({v.s, max(start.t, edges[v.t].d)});
        }
    }
    return bfs();
}

bool compare(int a, int b) {
    return (edges[b].d > edges[a].d);
}

int main()
{
    while(scanf("%d%d", &n, &m) == 2) {
        for (int i = 0; i < m; ++i) {
            scanf("%d%d%d", &edges[i].x, &edges[i].y, &edges[i].d);
            edges[i].x -= 1;
            edges[i].y -= 1;
            sorted_edges[i] = i;
        }

        scanf("%d", &q);

        for (int i = 0; i < q; ++i) {
            scanf("%d%d", &paths[i].s, &paths[i].t);
            paths[i].s -= 1;
            paths[i].t -= 1;
        }

        sort(sorted_edges, sorted_edges + m, compare);

        kruskal();

        for (int i = 0; i < q; ++i) {
            to_visit = queue<Pair>();
            memset(visited, false, n);
            to_visit.push({paths[i].s, 0});
            finish = paths[i].t;
            printf("%d\n", bfs());
        }

        /*for(int i = 0; i < n; ++i) {
            for(auto v: min_span_tree[i]) {
                printf("%d ", v.s);
            }
            printf("\n");
        }
        //for(int i = 0; i < int(min_span_tree.size()); ++i) printf("%d %d\n", edges[min_span_tree[i].x].x, edges[min_span_tree[i].x].y);
        for(int i = 0; i < m; ++i) printf("%d %d %d\n", edges[i].x, edges[i].y, edges[i].d);
        for(int i = 0; i < q; ++i) printf("%d %d\n", paths[i].s, paths[i].t);*/

        printf("\n");
    }

    return 0;
}
