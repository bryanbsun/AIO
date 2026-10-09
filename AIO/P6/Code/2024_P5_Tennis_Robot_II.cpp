// AIO 2024 P5 - Tennis Robot II
// Method: net change over one round (Prefix Sum) + division to get the number of full rounds directly + simulate the last round
#include <bits/stdc++.h>
using namespace std;

int n, m, A[200010], B[200010];
long long x[200010];
long long cur[200010];      // within a round, change in box i relative to the start of the round
long long mn[200010];       // minimum of cur over the moments just before a ball is taken from box i
long long d[200010];        // net change in box i over one full round
bool take[200010];          // whether a ball is ever taken from box i during a round
long long b[200010];

int main(){
    cin >> n >> m;
    for (int i = 1; i <= n; i ++)
        cin >> x[i];
    for (int j = 1; j <= m; j ++)
        cin >> A[j] >> B[j];

    // 1) run through the instructions once to get mn and d for every box
    for (int j = 1; j <= m; j ++){
        int a = A[j];
        if (!take[a] || cur[a] < mn[a])
            mn[a] = cur[a];
        take[a] = true;
        cur[a] --;
        cur[B[j]] ++;
    }
    for (int i = 1; i <= n; i ++)
        d[i] = cur[i];

    // 2) box i is fine in round r <=> x[i] + mn[i] + (r-1)*d[i] >= 1
    //    let s = x[i] + mn[i]:
    //    s < 1          : fails in round 1, so 0 full rounds at most
    //    d[i] >= 0      : never fails
    //    d[i] < 0       : r - 1 <= (s - 1) / (-d[i]), so at most (s-1)/(-d[i]) + 1 full rounds (integer division)
    long long R = -1;                       // -1 means no box ever fails
    for (int i = 1; i <= n; i ++)
        if (take[i]){
            long long s = x[i] + mn[i];
            long long t;
            if (s < 1)
                t = 0;
            else if (d[i] >= 0)
                continue;
            else
                t = (s - 1) / (-d[i]) + 1;
            if (R == -1 || t < R)
                R = t;
        }
    if (R == -1){
        cout << "FOREVER" << endl;
        return 0;
    }

    // 3) R full rounds complete and round R+1 stops: simulate that round to find the instruction where it stops
    for (int i = 1; i <= n; i ++)
        b[i] = x[i] + R * d[i];
    long long ans = R * m;
    for (int j = 1; j <= m; j ++){
        if (b[A[j]] == 0)
            break;
        b[A[j]] --;
        b[B[j]] ++;
        ans ++;
    }

    cout << ans << endl;
    return 0;
}
