// Hiring Monks — Correct Solution
// AIO 2019
//
// Key idea: In any optimal assignment, all student-job monks can be
// assumed to have lower skill than all master-job monks. (If monk A is
// in a student job with higher skill than monk B in a master job, we can
// swap them and the assignment remains valid.) So there exists a "split
// point" k: monks[0..k-1] go to student jobs, monks[k..n-1] go to
// master jobs.
//
// We precompute:
//   f[k] = max student matches using the k lowest-skill monks
//   g[k] = max master  matches using the (n-k) highest-skill monks
// Answer = max over k of f[k] + g[k].
//
// Both f and g are computed in O(N + S) and O(N + M) respectively,
// using greedy two-pointer passes on sorted arrays.

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, s, m;
    cin >> n;
    vector<int> x(n);
    for (int i = 0; i < n; i++) cin >> x[i];

    cin >> s;
    vector<int> st(s);
    for (int i = 0; i < s; i++) cin >> st[i];

    cin >> m;
    vector<int> ms(m);
    for (int i = 0; i < m; i++) cin >> ms[i];

    sort(x.begin(),  x.end());   // monks ascending
    sort(st.begin(), st.end());   // student caps ascending
    sort(ms.begin(), ms.end());   // master minimums ascending

    // ---------------------------------------------------------------
    // Compute f[k]: max student matches using monks x[0..k-1].
    //
    // Greedy: process monks ascending skill, assign each to the
    // smallest student cap that fits (cap >= skill). This is optimal
    // because using a tighter cap for a lower-skill monk leaves
    // looser caps for higher-skill monks.
    //
    // We advance pointer j through sorted caps. Caps smaller than
    // x[k-1] are skipped — they can never be used by x[k-1] (skill
    // too high) nor by any future (even higher-skill) monk.
    // ---------------------------------------------------------------
    vector<int> f(n + 1, 0);
    {
        int j = 0; // next available student cap
        for (int k = 1; k <= n; k++) {
            while (j < s && st[j] < x[k-1]) j++; // skip caps too small
            if (j < s) {
                f[k] = f[k-1] + 1; // monk x[k-1] fills cap st[j]
                j++;
            } else {
                f[k] = f[k-1];     // no suitable cap
            }
        }
    }

    // ---------------------------------------------------------------
    // Compute g[k]: max master matches using monks x[k..n-1].
    //
    // We compute g from right to left (adding the smallest available
    // monk one at a time). The greedy assigns each new monk (added
    // at the "bottom") to the most demanding master job it can fill.
    // This leaves less-demanding jobs available for smaller monks.
    //
    // Pointer j scans master minimums from right (highest) to left.
    // Master jobs with min > x[k] are skipped — too demanding for x[k]
    // and for all smaller monks (x[k-1], x[k-2], ...) too.
    // ---------------------------------------------------------------
    vector<int> g(n + 1, 0);
    {
        int j = m - 1; // next available master job (from highest min)
        for (int k = n - 1; k >= 0; k--) {
            while (j >= 0 && ms[j] > x[k]) j--; // skip too demanding
            if (j >= 0) {
                g[k] = g[k+1] + 1; // monk x[k] fills master job ms[j]
                j--;
            } else {
                g[k] = g[k+1];     // no suitable master job
            }
        }
    }

    // ---------------------------------------------------------------
    // Try every split: first k monks → student jobs,
    //                  remaining n-k monks → master jobs.
    // ---------------------------------------------------------------
    int ans = 0;
    for (int k = 0; k <= n; k++) {
        ans = max(ans, f[k] + g[k]);
    }

    cout << ans << "\n";
    return 0;
}
