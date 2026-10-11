// AIO 2023 P6 - Yet Another Lights Problem
// Method: Parity construction: x[i][j] = t[i][j] ^ rw[i] ^ cl[j]
#include <bits/stdc++.h>
using namespace std;

int R, C;
char s[210];
int t[210][210], x[210][210];   // t = 1: this light must flip an odd number of times; x = 1: cross-flip here
int tr[210], tc[210];           // parity of t in each row / column
int rw[210], cl[210];           // parity of the number of operations in each row / column
int rs[210], cs[210];           // parity of the constructed x in each row / column (for verification)

int main(){
    cin >> R >> C;
    for (int i = 1; i <= R; i ++){
        cin >> s;
        for (int j = 1; j <= C; j ++){
            t[i][j] = (s[j-1] == '.');
            tr[i] ^= t[i][j];
            tc[j] ^= t[i][j];
        }
    }

    // try both values of S, the parity of the total number of operations
    for (int S = 0; S < 2; S ++){
        // C even: rw[i] is fixed; C odd: rw is free as long as the total parity = S
        for (int i = 1; i <= R; i ++)
            rw[i] = (C % 2 == 0) ? (tr[i] ^ S) : 0;
        if (C % 2 == 1)
            rw[1] = S;
        for (int j = 1; j <= C; j ++)
            cl[j] = (R % 2 == 0) ? (tc[j] ^ S) : 0;
        if (R % 2 == 1)
            cl[1] = S;

        // build x from the formula
        memset(rs, 0, sizeof(rs));
        memset(cs, 0, sizeof(cs));
        for (int i = 1; i <= R; i ++)
            for (int j = 1; j <= C; j ++){
                x[i][j] = t[i][j] ^ rw[i] ^ cl[j];
                rs[i] ^= x[i][j];
                cs[j] ^= x[i][j];
            }

        // verify: each light's flip parity = rs[i] ^ cs[j] ^ x[i][j], which must equal t[i][j]
        bool ok = true;
        for (int i = 1; i <= R; i ++)
            for (int j = 1; j <= C; j ++)
                if ((rs[i] ^ cs[j] ^ x[i][j]) != t[i][j])
                    ok = false;
        if (!ok)
            continue;

        int cnt = 0;
        for (int i = 1; i <= R; i ++)
            for (int j = 1; j <= C; j ++)
                cnt += x[i][j];
        cout << cnt << endl;
        for (int i = 1; i <= R; i ++)
            for (int j = 1; j <= C; j ++)
                if (x[i][j])
                    cout << i - 1 << " " << j - 1 << endl;   // the problem numbers rows and columns from 0
        return 0;
    }

    cout << -1 << endl;
    return 0;
}
