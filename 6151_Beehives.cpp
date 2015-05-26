/*
*	6151_Beehives
*	Task is about finding a minimum cycle in non-oriented graph,
*	Solution: BFS with little modification, queue stocks also parents and we stock also a depth of each vertex respectively of start
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

#define inf 1000000
#define N 500

int visited[N];
int got_it;
queue<pair<int, int>> to_visit;

vector<int> adj_list[N];
int result = inf;

void BFSToFindMinCycle(int start, int n) {
	memset(visited, -1, n * sizeof(int));
	visited[start] = 0;
	
	if(!to_visit.empty()) to_visit = queue<pair<int, int>>();
	to_visit.push(pair<int, int>(start, -1));

	pair<int,int> node;
	int depth;

	while (!to_visit.empty()) {
		//take next node with its depth
		node = to_visit.front();
		to_visit.pop();

		//calculate the current of ancestors	
		depth = visited[node.first];

		//looking on each children
		for(auto s: adj_list[node.first]) {
			got_it = visited[s];
			
			//if it's non visited children, add it to_visit and save its depth
			if(got_it == -1) {
				to_visit.push(pair<int, int>(s, node.first));
				visited[s] = depth + 1;
			} else {
				if(s != node.second) {
					result = min(result, got_it + depth + 1);
					if (result == 3) return;
				}
			}
		}
	}
}

int main() {
	int t;
	scanf("%d\n", &t);
	
	int n, m, from, to;
	int case_num = 0;	
	while(case_num++ < t) {
		scanf("%d %d\n", &n, &m);
	
		for (int i = 0; i < n; ++i)
		{
			adj_list[i].clear();
		}
		
		for (int i = 0; i < m; ++i)
		{
			scanf("%d %d\n", &from, &to);
			adj_list[from].push_back(to);
			adj_list[to].push_back(from);	
		}

		result = inf;
		for (int i = 0; (i < n)&&(result!=3); ++i)
		{
			BFSToFindMinCycle(i, n);
		}
		
		if (result < inf) printf("Case %d: %d\n", case_num, result);
		else printf("Case %d: %s\n", case_num, "impossible");
	}

	return 0;
}
