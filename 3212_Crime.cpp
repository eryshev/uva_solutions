/*
*	3212_Crime
*	simple BFS on graph in order to check if our graph is bi or not
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

vector<vector<int>> adj_list;

unordered_map<int, int> visited; 

queue<pair<int, int>> to_visit;

//start is one of verticies that compose a connected component
int BFS(int start) {
	to_visit = queue<pair<int, int>>();
	to_visit.push(pair<int, int>(start, 0));
	
	visited.insert({start, 0});

	int odd = 0;
	int even = 1;

	pair<int,int> node;
	while (!to_visit.empty()) {
		node = to_visit.front();
		to_visit.pop();
		int next = node.second + 1;

		for(auto s: adj_list[node.first]) {
			auto got_it = visited.find(s);
			if(got_it == visited.end()) {
				to_visit.push(pair<int, int>(s, next));
				visited.insert({s, next});
				if (next % 2 == 0) even++;
				else odd++;
			} else if((got_it->second % 2 == 0 && node.second % 2 == 0) || ((got_it->second % 2 == 1 && node.second % 2 == 1))) {
				return -1;
			}
		}
	}

	return min(odd, even);
}

int main() {
	int n, m, from, to, num_stations;
	
	while(scanf("%d %d\n", &n, &m) == 2) {
		adj_list.clear();
		adj_list.resize(n);
		visited.clear();
		
		for (int i = 0; i < m; ++i)
		{
			scanf("%d %d\n", &from, &to);
			adj_list[from-1].push_back(to-1);
			adj_list[to-1].push_back(from-1);
		}

		num_stations = 0;

		int result = 0;
		for (int i = 0; i < n; ++i)
		{
			//we take care about connected components
			if ((!adj_list[i].empty()) && (visited.find(i) == visited.end())) {
				result = BFS(i);
				if (result == -1) break;
				else num_stations += result;
			} else if (adj_list[i].empty()) visited.insert({i, -1});
		}
		
		if (result == -1) printf("%s\n", "Impossible");
		else printf("%d\n", num_stations);
	}

	return 0;
}
