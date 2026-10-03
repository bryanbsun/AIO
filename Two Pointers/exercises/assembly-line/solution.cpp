#include <iostream>
using namespace std;

const int MAXN = 100005;
long long d[MAXN];

int main() {
    int N, K;
    cin >> N >> K;
    for (int i = 0; i < N; i++) cin >> d[i];

    long long window = 0;
    for (int i = 0; i < K; i++) window += d[i];
    long long best = window;
    for (int i = K; i < N; i++) {
        window += d[i] - d[i - K];
        if (window < best) best = window;
    }
    cout << best << "\n";
    return 0;
}
