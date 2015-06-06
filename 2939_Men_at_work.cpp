/*
* ACM-ICPC 2939 - Men at work
* BFS algoritmn with usage of least common multiple to control cycles in graph
*/
#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
#include <unordered_set>
#include <algorithm>
#include <numeric>

using namespace std;

const int INF = 1000000000;
const int N = 50;

bool field[N * N];
int schedule[N * N];
unordered_set<int> visits[1680];
int periods[9];

int n;
int lcm = 1680;

int gcd(int a, int b) {
	if (b==0) return a;
	else return gcd(b, a%b);
}

int calcLcm(int a, int b) {
	return a*b/gcd(a, b);
}

int calcLcmArray(int* array) {
	int counter = 0;
	for (int i = 1; i < 8; ++i)
	{	
		if (array[i]) swap(array[counter++], array[i]);
	}
	return (counter > 1 ? accumulate(array, array + counter - 1, 1, calcLcm) : counter);
}

bool checkSchedule(int i, int t) {
	int index_by_lcm = t % lcm;
	if (find(visits[index_by_lcm].begin(),  visits[index_by_lcm].end(), i) != visits[index_by_lcm].end()) return false;
	visits[index_by_lcm].insert(i);
	if (schedule[i] == 0) return field[i];
	int checker = (t / schedule[i]) % 2;
	return checker ? !field[i] : field[i];
}

typedef pair<int, int> Pair;
int waveConstruct() {
	queue<Pair> to_visit;
	int t_plus = 0, v, v_plus, v_min, v_plus_row, v_min_row, v_prev = -1; 
	to_visit.push(Pair(0, 0));

	while (!to_visit.empty()) {
		v = to_visit.front().first;
		t_plus = to_visit.front().second + 1;
		to_visit.pop();
		if (v == n*n - 1) return t_plus-1;

		v_plus = v + 1;
		v_min = v - 1;
		v_plus_row = v + n;
		v_min_row = v - n;
		if (v_prev != v && checkSchedule(v, t_plus) ) to_visit.push(Pair(v, t_plus));
		if (v_plus < n*n && v_plus % n != 0 && checkSchedule(v_plus, t_plus)) to_visit.push(Pair(v_plus, t_plus));
		if (v_min > -1 && v_min % n != n-1 && checkSchedule(v_min, t_plus)) to_visit.push(Pair(v_min, t_plus));
		if (v_plus_row < n*n && checkSchedule(v_plus_row, t_plus)) to_visit.push(Pair(v_plus_row, t_plus));
		if (v_min_row > -1 && checkSchedule(v_min_row, t_plus)) to_visit.push(Pair(v_min_row, t_plus));
		v_prev = v;
	}

	return -1;
}

void initialize() {
	for (int i = 0; i < lcm; ++i)
	{
		visits[i].clear();
	}
	memset(periods, 0, sizeof(periods));
}


int main() {
	char bit;
	bool first = true;
	int period;

	while(scanf("%d\n", &n) == 1) {
		if (!first) printf("\n");
		first = false;

		//Input
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				scanf("%c", &bit);
				field[i*n+j] = bit == '.' ? true : false;
			}
			scanf("\n");
		}

		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j) {
				scanf("%c", &bit);
				period = bit - '0';
				schedule[i*n+j] = period;
				if (period) periods[period] = 4*period;
			}
			scanf("\n");
		}

		initialize();

		int result = waveConstruct();
		if (result != -1) 
			printf("%d\n", result);
		else printf("%s\n", "NO");

	}

	return 0;
}
