/*
* 3511 Consecutive ones
* DFS with choosing of next possible candidate
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1000000000;
const int N = 400;

bool cols[N*N];
int ones_memo[N];

bool visited[N];

vector<int> result;

int n, m;

void initialize() {
	for (int i = 0; i < m; ++i)
	{
		visited[i] = false;
		ones_memo[i] = 0;
	}
	result.clear();
	memset(cols, false, sizeof(bool) * n * m);
}

bool checkLine(int l) {
	int ones_count = 0;
	int ones_in_line = ones_memo[l];
	for (size_t i = 0; i < result.size(); ++i)
	{
		if (cols[l*m + result[i]]) ones_count++;
		else if (ones_count != 0 && ones_count < ones_in_line) return false;
		if (ones_count == ones_in_line) return true;
	}
	return true;
}

bool checkAllLines() {
	for (int i = 0; i < n; ++i)
	{
		if (!checkLine(i)) return false;
	}
	return true;
}

bool isPossibleCandidate(int c1, int c2) {
	for (int i = 0; i < n; ++i)
	{
		if(cols[i*m + c1] && !cols[i*m + c2]) {
			for (int j = 0; j < m; ++j)
			{
				if (!visited[j] && j != c2 && cols[i*m + j]) return false;
			}
		} 
	}
	return true;
}

int stopDFS = false;
void DFS(int start) {
	result.push_back(start);
	
	//printf("%d\n", start);
	
	if (!checkAllLines()) {
 		result.pop_back();
 		return;
 	}

 	if (result.size() == size_t(m)) {
 		for (size_t i = 0; i < result.size(); ++i)
		{
			printf("%d\n", result[i]);
		}
		stopDFS = true;
 		return;
 	}
 	if (stopDFS) return;

 	vector<int> candidates;
 	candidates.reserve(10);
 	for (int i = 1; i < m; i++) {
 		if (!visited[i] && isPossibleCandidate(start, i)) {
 			candidates.push_back(i);
 		}
 	}

 	for(auto c: candidates) {
 		visited[c] = true;
 		DFS(c);
 		visited[c] = false;
 		if (stopDFS) return;
 	}

 	result.pop_back();
}

int main() {
	int t;

	scanf("%d", &t);

	while(t--) {
		scanf("%d\n%d\n", &n, &m);

		initialize();

		char bit;
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < m; ++j)
			{
				scanf("%c", &bit);
				//printf("(%d,%d)=%c", i, j, bit);
				if (bit == '1') {
					cols[i*m + j] = true; 
					ones_memo[i]++;
				}
			}
			scanf("\n");
		}

		stopDFS = false;
		visited[0] = 1;
		DFS(0);
		if (t > 0) puts("");
	}

	return 0;
}
