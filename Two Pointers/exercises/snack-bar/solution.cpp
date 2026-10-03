#include <iostream>
using namespace std;

const int MAXN = 100005;
long long p[MAXN];

int main() {
    int N;
    long long B;
    cin >> N >> B;
    for (int i = 0; i < N; i++) cin >> p[i];

    long long sum = 0;
    int best = 0;
    int l = 0;
    for (int r = 0; r < N; r++) {
        sum += p[r];
        while (sum > B) {          /* shrink from the left until affordable */
            sum -= p[l];
            l++;
        }
        int len = r - l + 1;       /* window [l, r] is now within budget */
        if (len > best) best = len;
    }
    cout << best << "\n";
    return 0;
}
