/**
*	3502 The mysterious X network
*	Simple breadth-first search on graph
*/

#include <cstdio>
#include <vector>
#include <queue>
#include <utility>
#include <unordered_set>

using namespace std;

vector<vector<int>> camarades;

unordered_set<int> visited; 

queue<pair<int, int>> to_visit;
queue<int> empty;

int BFS(int start, int target) {
	to_visit = queue<pair<int, int>>();
	visited.clear();
	to_visit.push(pair<int, int>(start, 0));
	visited.insert(start);

	pair<int,int> node;
	while (!to_visit.empty()) {
		node = to_visit.front();
		to_visit.pop();

		if(node.first == target) return node.second;

		for(auto c: camarades[node.first]) {
			if(c == target) return node.second;
			if(visited.find(c) == visited.end()) {
				to_visit.push(pair<int, int>(c, node.second + 1));
				visited.insert(c);
			}
		}
	}

	return -1;
}

int main() {
	int t;
	scanf("%d\n", &t);
	int n, cam_number, con_number, temp, start, end;
	
	while(t--) {
		scanf("%d\n", &n);
		camarades.resize(n);
		for (int i = 0; i < n; ++i)
		{
			scanf("%d", &cam_number);
			scanf(" %d", &con_number);
			camarades[cam_number].resize(con_number); 
			for (int j = 0; j < con_number; ++j) {
				scanf(" %d", &temp);
				camarades[cam_number][j] = temp;
			}	
			scanf("\n");
		}		 

		scanf("%d %d\n", &start, &end);

		printf("%d %d %d\n", start, end, BFS(start, end));

		if(t > 0) printf("\n");
	}

	return 0;
}