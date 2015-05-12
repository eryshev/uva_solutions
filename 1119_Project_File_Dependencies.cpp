/**
  UVa 1119	Project File Dependencies
  */
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

int main()
{
    string line;
    int case_num;
    cin >> case_num;

    for (int c = 0; c < case_num; ++c) {
        getline(cin, line);
        int ntasks, nrules;
        cin >> ntasks >> nrules;
        bool* d = new bool [ntasks*ntasks];
        bool* checked = new bool[ntasks];
        memset(d, false, sizeof(*d));
        memset(checked, false, sizeof(*checked));

        for (int i = 0; i < nrules; ++i) {
            int t0, nd, dep;
            cin >> t0 >> nd;
            for (int j = 0; j < nd; ++j) {
                cin >> dep;
                d[(t0-1) * ntasks + dep - 1] = true;
            }
        }

        int counter = 0;
        for (int i = 0; i < ntasks; ++i) {
            if (checked[i]) continue;
            bool is_candidate = true;
            for (int j = 0; j < ntasks; ++j) {
                if(d[i*ntasks + j]) {
                    is_candidate = false;
                    break;
                }
            }
            if (is_candidate) {
                checked[i] = true;
                counter++;
                for (int j = 0; j < ntasks; ++j) {
                    d[j*ntasks + i] = false;
                }
                cout << i + 1 << (counter == ntasks ? "\n" : " ");
                i = -1;
            }
        }
        if (c != case_num - 1) cout << endl;
    }


    return 0;
}
