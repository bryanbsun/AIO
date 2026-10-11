#include <iostream>
using namespace std;

const int MAXN = 100005;
long long a[MAXN];

int main() {
    int N, K;
    cin >> N >> K;
    for (int i = 0; i < N; i++) cin >> a[i];

    long long window = 0;
    for (int i = 0; i < K; i++) window += a[i];   /* first window */
    long long best = window;
    for (int i = K; i < N; i++) {
        window += a[i] - a[i - K];                /* repair, don't recompute */
        if (window > best) best = window;
    }
    cout << best << "\n";
    return 0;
}
