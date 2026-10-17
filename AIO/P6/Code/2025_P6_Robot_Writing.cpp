// AIO 2025 P6 - Robot Writing
// Method: key observation (the robot carries the maximum, so the recorded sequence never decreases)
//       + advance "level by new value" + Sparse Table (range maximum) + binary search for interval boundaries
#include <bits/stdc++.h>
using namespace std;

int n, m, t[200010], s[200010];
int sp[18][200010], lg[200010];     // sp[k][i] = max(t[i .. i + 2^k - 1])
int lv[200010], ti[200010], K;      // level k: value lv[k], first appears at step ti[k]
int cur[200010], nc;                // feasible positions on the current level
int nxt[200010], nn;                // feasible positions on the next level
int mark[200010];                   // mark[q] = k: q is already in level k (dedup)

// maximum of range [l, r]
int qmax(int l, int r){
    int k = lg[r - l + 1];
    return max(sp[k][l], sp[k][r - (1 << k) + 1]);
}

// extend left from p: the smallest l with all of t[l..p] <= v
int extendLeft(int p, int v){
    int l = 1, r = p;
    while (l <= r){
        int mid = (l + r) / 2;
        if (qmax(mid, p) <= v)
            r = mid - 1;
        else
            l = mid + 1;
    }
    return l;
}

// extend right from p: the largest r with all of t[p..r] <= v
int extendRight(int p, int v){
    int l = p, r = n;
    while (l <= r){
        int mid = (l + r) / 2;
        if (qmax(p, mid) <= v)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return r;
}

// can we go from p to q in exactly dt steps? (the interval is big enough to walk back and forth to use up time)
bool check(int p, int q, int dt){
    int d = abs(q - p);
    return d <= dt && (dt - d) % 2 == 0;
}

// add q to level k (dedup)
void add(int q, int k){
    if (mark[q] != k){
        mark[q] = k;
        nxt[++ nn] = q;
    }
}

int main(){
    cin >> n;
    for (int i = 1; i <= n; i ++)
        cin >> t[i];
    cin >> m;
    for (int i = 1; i <= m; i ++)
        cin >> s[i];

    // observation 1: the recorded sequence must never decrease
    for (int i = 2; i <= m; i ++)
        if (s[i] < s[i-1]){
            cout << "NO" << endl;
            return 0;
        }

    // Sparse Table
    for (int i = 2; i <= n; i ++)
        lg[i] = lg[i/2] + 1;
    for (int i = 1; i <= n; i ++)
        sp[0][i] = t[i];
    for (int k = 1; (1 << k) <= n; k ++)
        for (int i = 1; i + (1 << k) - 1 <= n; i ++)
            sp[k][i] = max(sp[k-1][i], sp[k-1][i + (1 << (k-1))]);

    // split s into levels: each newly appearing value is a level
    for (int i = 1; i <= m; i ++)
        if (i == 1 || s[i] != s[i-1]){
            K ++;
            lv[K] = s[i];
            ti[K] = i;
        }

    // level 1 (start): t[p] = s[1]; handle each "maximal interval [i, j] with values <= s[1]"
    bool start = false;
    int i = 1;
    while (i <= n){
        if (t[i] > lv[1]){
            i ++;
            continue;
        }
        int j = i;
        while (j + 1 <= n && t[j+1] <= lv[1])
            j ++;
        int sz = j - i + 1;
        for (int p = i; p <= j; p ++){
            if (t[p] != lv[1])
                continue;
            if (K == 1){
                // only one level: OK if there is just 1 record, or the interval has at least 2 cells to walk back and forth
                if (m == 1 || sz >= 2)
                    start = true;
                continue;
            }
            // targets for the next level: the first cell > lv[1] just left or right of the interval
            int dt = ti[2] - ti[1];
            int q = i - 1;
            if (q >= 1 && t[q] == lv[2] && check(p, q, dt) && (p - q == dt || sz >= 2))
                add(q, 2);
            q = j + 1;
            if (q <= n && t[q] == lv[2] && check(p, q, dt) && (q - p == dt || sz >= 2))
                add(q, 2);
        }
        i = j + 1;
    }
    if (K == 1){
        cout << (start ? "YES" : "NO") << endl;
        return 0;
    }

    // every later level
    for (int k = 2; k < K && nn > 0; k ++){
        nc = nn;
        for (int u = 1; u <= nn; u ++)
            cur[u] = nxt[u];
        nn = 0;
        int dt = ti[k+1] - ti[k];
        for (int u = 1; u <= nc; u ++){
            int p = cur[u];
            int l = extendLeft(p, lv[k]), r = extendRight(p, lv[k]);
            if (l - 1 >= 1 && t[l-1] == lv[k+1] && check(p, l - 1, dt))
                add(l - 1, k + 1);
            if (r + 1 <= n && t[r+1] == lv[k+1] && check(p, r + 1, dt))
                add(r + 1, k + 1);
        }
    }

    cout << (nn > 0 ? "YES" : "NO") << endl;
    return 0;
}
