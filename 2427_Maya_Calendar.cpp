#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

#define FOR(i, N) for( int i = 0 ; i < N ; ++i )
#define FOR1e(i, N) for( int i = 1 ; i <= N ; ++i )
#define FORe(i, N) for(int i = 0 ; i <= N ; ++i )
#define FOR1(i, N) for(int i = 1 ; i < N ; ++i )

using namespace std;

vector<string> tzolkin_dn = {"Imix", "Ik", "Akbal", "Kan", "Chikchan", "Kimi", "Manik", "Lamat", "Muluk", "Ok", "Chuen", "Eb", "Ben", "Ix", "Men", "Kib", "Kaban", "Etznab", "Kawak", "Ajaw"};
vector<string> haab_mn = {"Pohp", "Wo", "Sip", "Zotz", "Sek", "Xul", "Yaxkin", "Mol", "Chen", "Yax", "Sak", "Keh", "Mak", "Kankin", "Muan", "Pax", "Kayab", "Kumku", "Wayeb"};
int epoch_start = 1152000;
int epoch_finish = 1440000;
int period_52years = 18980;
pair<int, int> start_tzolkin_pair(9, 19);
pair<int, int> start_haab_pair(3, 2);
pair<int, int> seeking_tp;
pair<int, int> seeking_hp;

inline string int_to_long_count(int int_date) {
	int num144000 = int_date / 144000;
	int num7200 = (int_date % 144000) / 7200;
	int num360 = (int_date % 144000 % 7200) / 360;
	int num20 = (int_date % 144000 % 7200 % 360) / 20;
	int num1 = (int_date % 144000 % 7200 % 360 % 20);
	return to_string(num144000) + "." + to_string(num7200) + "." + to_string(num360) + "." + to_string(num20) + "." + to_string(num1); 
}

inline bool is_seeking_pair(pair<int, int>& tp, pair<int, int>& hp) {
	return (tp == seeking_tp && hp == seeking_hp);
}

int main() {
	int n;
	scanf("%d\n", &n);

	int dayNumber1, dayNumber2;
	char dn[10], mn[10];
	string dayName, monthName;

	pair<int, int> current_tp;
	pair<int, int> current_hp;

	while(scanf("%d.%s %d.%s\n\n", &dayNumber1, dn, &dayNumber2, mn) == 4) {
		dayName = dn;
		monthName = mn;

		seeking_tp = pair<int, int>(dayNumber1, distance(tzolkin_dn.begin(), find(tzolkin_dn.begin(), tzolkin_dn.end(), dayName)));
		seeking_hp = pair<int, int>(dayNumber2, distance(haab_mn.begin(), find(haab_mn.begin(), haab_mn.end(), monthName)));
		
		current_tp = start_tzolkin_pair;
		current_hp = start_haab_pair;

		int iterator = epoch_start;

		while(iterator != epoch_finish) {
			if(is_seeking_pair(current_tp, current_hp)) break;

			iterator++;
			current_tp.first = (current_tp.first + 1) % 13;
			if (current_tp.first == 0) current_tp.first = 13;
			current_tp.second = (current_tp.second + 1) % 20;

			current_hp.first = (current_hp.second != 18) ? (current_hp.first + 1) % 20 : (current_hp.first + 1) % 5;
			if (current_hp.first == 0) current_hp.first = (current_hp.second != 18) ? 20 : 5;
			if(current_hp.first == 1) {
				current_hp.second = (current_hp.second + 1) % 19;
			} 
		}

		if(iterator != epoch_finish) {
			while(iterator < epoch_finish) { 
				printf("%s\n", &int_to_long_count(iterator)[0]);
				iterator += period_52years;
			}
		}
		else printf("%s\n", "NO SOLUTION");
		if(--n >= 1) printf("\n");
	}

	return 0;
}
