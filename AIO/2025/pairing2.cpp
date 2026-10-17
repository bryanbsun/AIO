#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, D, S;
    cin >> N >> D >> S;
    
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }
    
    const int MAX_VAL = 1000000;
    vector<int> cnt(MAX_VAL + 5, 0);
    
    for (int val : A) {
        cnt[val]++;
    }
    
    vector<int> vals;
    for (int v = 1; v <= MAX_VAL; ++v) {
        if (cnt[v] > 0) vals.push_back(v);
    }
    
    for (int x : vals) {
        while (cnt[x] > 0) {
            int partner = -1;
            
            // Try difference rule first
            if (x + D <= MAX_VAL && cnt[x + D] > 0) {
                partner = x + D;
            }
            // Try sum rule, but only if partner is >= x and not same as diff partner
            else if (S - x >= x && S - x <= MAX_VAL && cnt[S - x] > 0) {
                if (!(D >= 0 && x + D == S - x)) { // avoid double counting same partner
                    partner = S - x;
                }
            }
            
            if (partner == -1) {
                cout << "NO\n";
                return 0;
            }
            
            cnt[x]--;
            cnt[partner]--;
        }
    }
    
    cout << "YES\n";
    return 0;
}
