/*
 * AIO 2024 - Problem 4: Backpacking
 * Full-marks solution - O(N), suitable for all subtasks
 *
 * OPTIMISATION over O(N^2):
 *   Precompute next_cheaper_dist[i] = distance to the next town j > i
 *   where C[j] <= C[i] AND dist(i,j) <= K.
 *
 *   Uses a MONOTONIC STACK (classic "next smaller element" pattern)
 *   to compute this for all towns in O(N) total.
 *
 * MONOTONIC STACK IDEA:
 *   Process towns left to right. Maintain a stack of towns whose
 *   "next cheaper town" hasn't been found yet (in increasing cost order).
 *   When we reach town j, pop every town i on the stack where C[j] <= C[i]
 *   — town j is the answer for those towns (if within K days).
 */
 
#include <bits/stdc++.h>
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int N, K;
    cin >> N >> K;
 
    vector<int> D(N - 1);
    for (int i = 0; i < N - 1; i++) cin >> D[i];
 
    vector<int> C(N);
    for (int i = 0; i < N; i++) cin >> C[i];
 
    // --- Prefix distance array ---
    // prefix[i] = total days from town 0 to town i
    vector<long long> prefix(N, 0);
    for (int i = 1; i < N; i++)
        prefix[i] = prefix[i - 1] + D[i - 1];
 
    // dist(i, j) = days from town i to town j
    auto dist = [&](int i, int j) -> long long {
        return prefix[j] - prefix[i];
    };
 
    // --- Compute next_cheaper_dist[i] using a monotonic stack ---
    vector<long long> next_cheaper_dist(N, K);  // default: fill to K
    stack<int> stk;  // stack of town indices, maintained with non-decreasing cost
 
    for (int j = 0; j < N; j++) {
        while (!stk.empty()) {
            int i = stk.top();
            long long d = dist(i, j);
 
            if (d > K) {
                // j is out of range for i; since costs on stack are
                // non-decreasing and we've passed K, no future town
                // can be both cheaper and closer — pop i with default K.
                stk.pop();
                continue;
            }
            if (C[j] <= C[i]) {
                // j is the next cheaper town for i, and it's within range
                next_cheaper_dist[i] = d;
                stk.pop();
            } else {
                break;  // C[j] > C[i]: not useful for i, stop here
            }
        }
        stk.push(j);
    }
    // Remaining towns on the stack keep their default value of K (fill up).
 
    // --- Greedy simulation ---
    long long total_cost = 0;
    long long stock = 0;
 
    for (int i = 0; i < N - 1; i++) {
        long long need = next_cheaper_dist[i];
        long long buy = max(0LL, need - stock);
 
        total_cost += buy * C[i];
        stock += buy;
        stock -= D[i];
    }
 
    cout << total_cost << "\n";
    return 0;
}



