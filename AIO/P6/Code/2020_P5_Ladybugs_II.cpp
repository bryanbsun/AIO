// AIO 2020 P5 - Ladybugs II
// Method: the best plan always takes K consecutive ladybugs (a window) + Binary Search (locate the start) + Sparse Table (range minimum)
#include <bits/stdc++.h>
using namespace std;

int n, K, q;
long long p[100010];
long long f1[18][100010], f2[18][100010];   // Sparse Table: the two costs of window [l, l+K-1] (without the D part)
int lg[100010];

long long qmin(long long f[][100010], int l, int r){
    int k = lg[r - l + 1];
    return min(f[k][l], f[k][r - (1 << k) + 1]);
}

int main(){
    cin >> n >> K >> q;
    for (int i = 1; i <= n; i ++)
        cin >> p[i];

    // when window l (ladybugs l .. l+K-1) straddles the start D:
    //   left first, then right: (D - p[l]) + (p[r] - p[l]) = p[r] - 2p[l] + D
    //   right first, then left: (p[r] - D) + (p[r] - p[l]) = 2p[r] - p[l] - D
    int w = n - K + 1;                      // number of windows
    for (int l = 1; l <= w; l ++){
        f1[0][l] = p[l + K - 1] - 2 * p[l];
        f2[0][l] = 2 * p[l + K - 1] - p[l];
    }
    for (int i = 2; i <= w; i ++)
        lg[i] = lg[i/2] + 1;
    for (int k = 1; (1 << k) <= w; k ++)
        for (int l = 1; l + (1 << k) - 1 <= w; l ++){
            f1[k][l] = min(f1[k-1][l], f1[k-1][l + (1 << (k-1))]);
            f2[k][l] = min(f2[k-1][l], f2[k-1][l + (1 << (k-1))]);
        }

    for (int t = 1; t <= q; t ++){
        long long D;
        cin >> D;

        // binary search: s = the first ladybug with position >= D
        int l = 1, r = n;
        while (l <= r){
            int mid = (l + r) / 2;
            if (p[mid] < D)
                l = mid + 1;
            else
                r = mid - 1;
        }
        int s = l;

        long long ans = LLONG_MAX;
        // window entirely right of D: best to start at s and keep walking right
        if (s <= w)
            ans = min(ans, p[s + K - 1] - D);
        // window entirely left of D: best to end at s-1 and keep walking left
        if (s - K >= 1)
            ans = min(ans, D - p[s - K]);
        // window straddles D: l is in [s-K+1, s-1] (and must be a valid window)
        int lo = max(1, s - K + 1), hi = min(s - 1, w);
        if (lo <= hi){
            ans = min(ans, qmin(f1, lo, hi) + D);
            ans = min(ans, qmin(f2, lo, hi) - D);
        }

        cout << ans << " ";
    }
    cout << endl;
    return 0;
}
