#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

#define inf 10000000

int main() {
	int n;
	cin >> n;

	int N, E, T, cn;
	int row, col, time_unit;
	vector<int> graph;
	vector<bool> visited;
	vector<int> labels;
	while (cin >> N >> E >> T >> cn) {

		graph.resize(N*N);
		visited.resize(N);
		labels.resize(N);
		fill(graph.begin(), graph.end(), 0);

		for (int i = 0; i < cn; ++i)
		{
			cin >> row >> col >> time_unit;
			graph[(row-1)*N + col-1] = time_unit;
		}

		int mice_number = 0;

		for(int k = 0; k < N; ++k) {
			fill(visited.begin(), visited.end(), false);
			fill(labels.begin(), labels.end(), inf);
			labels[k] = 0;

			while(true) {
				int min_label = inf;
				int next_vertex = -1;
				for (int i = 0; i < N; ++i)
				{		
					if((min_label > labels[i]) && !visited[i]) {
						min_label = labels[i];
						next_vertex = i;
					}
				}

				for (int i = 0; i < N; ++i)
				{
					if (graph[next_vertex*N + i]) {
						int new_label = min_label + graph[next_vertex*N + i];
						if(new_label < labels[i]) labels[i] = new_label;
					}  
				}

				if (next_vertex != -1) visited[next_vertex] = true;
				else break;
			}

			if (labels[E-1] <= T) mice_number++;
		}

		cout << mice_number << endl;
		if(--n > 0) cout << endl;
	}

	return 0;
}
