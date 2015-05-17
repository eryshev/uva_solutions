#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define INF 1000000000

struct Cistern {
	float width;
	float height;
	float depth;
	float base_level;
	float surface;
};

int main() {
	int n;
	cin >> n;

	int cisterns_n;
	float volume;
	vector<Cistern*> cisterns;
	while(cin >> cisterns_n) {
		cisterns.resize(cisterns_n);
		float total_volume = 0.f;
		for (int i = 0; i < cisterns_n; ++i)
		{
			Cistern* cistern = new Cistern;
			cin >> cistern->base_level >> cistern->height >> cistern->width >> cistern->depth;
			cistern->surface = cistern->width * cistern->depth;
			cisterns[i] = cistern;
			total_volume += cistern->surface * cistern-> height;
		}

		cin >> volume;

		if (total_volume < volume) {
			cout << "OVERFLOW" << endl;
			if(--n > 0) cout << endl;
			continue;
		}

		float current_volume = 0.f;
		float bottom = 0.f, top = 1000.f, middle, middle_prev = 0.f;
		while(true) {
			middle = (bottom + top) / 2.f;
			
			current_volume = 0.f;
			for (int i = 0; i < cisterns_n; ++i)
			{
				current_volume += min(max(0.f, middle - cisterns[i]->base_level), cisterns[i]->height) * cisterns[i]->surface; 
			}

			if(current_volume < volume) bottom = middle;
			else top = middle;

			if (abs(middle - middle_prev) < 0.0001f) break;
			else middle_prev = middle;
		}
		
		printf("%.2f\n", middle);

		if(--n > 0) cout << endl;
	}

	return 0;
}
