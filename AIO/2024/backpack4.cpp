#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, K;
    cin >> N >> K;

    vector<long long> D(N - 1), C(N);
    for (int i = 0; i < N - 1; i++) cin >> D[i];
    for (int i = 0; i < N;     i++) cin >> C[i];

    // prefix[i] = cumulative days from town 0 to town i
    vector<long long> prefix(N, 0);
    for (int i = 1; i < N; i++) prefix[i] = prefix[i - 1] + D[i - 1];
    long long total_days = prefix[N - 1];

    // For each town i, find nxt[i] = first j > i where C[j] <= C[i]
    // (next cheaper-or-equal town), using a monotone stack in O(N).
    vector<int> nxt(N, N); // default N = "no such town"
    stack<int> st;
    for (int j = 0; j < N; j++) {
        while (!st.empty() && C[st.top()] >= C[j]) {
            nxt[st.top()] = j;
            st.pop();
        }
        st.push(j);
    }

    long long total_cost = 0;
    long long have = 0;          // cans currently in backpack
    const long long INF = 2e18;

    for (int i = 0; i < N - 1; i++) {
        long long remaining = total_days - prefix[i];

        // Distance to the next town where food is <= current price.
        long long dist_nxt = (nxt[i] < N) ? (prefix[nxt[i]] - prefix[i]) : INF;

        // Greedy rule:
        //   - If a cheaper-or-equal town is reachable (dist_nxt <= K):
        //       only fill enough to arrive there (no point over-buying now).
        //   - Otherwise: fill to K (or remaining days if less).
        long long fill_to = min({(long long)K, dist_nxt, remaining});

        long long buy = max(0LL, fill_to - have);
        total_cost += buy * C[i];
        have += buy - D[i];   // buy cans, then travel one leg
    }

    cout << total_cost << "\n";
    return 0;
}

