// AIO 2023 P6 - Yet Another Lights Problem
// 方法：奇偶性（Parity）构造：x[i][j] = t[i][j] ^ rw[i] ^ cl[j]
#include <bits/stdc++.h>
using namespace std;

int R, C;
char s[210];
int t[210][210], x[210][210];   // t = 1：这盏灯要翻奇数次；x = 1：在这里 cross-flip
int tr[210], tc[210];           // 每行、每列 t 的奇偶
int rw[210], cl[210];           // 每行、每列操作次数的奇偶
int rs[210], cs[210];           // 构造出的 x 每行、每列的奇偶（用来验证）

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

    // 枚举所有操作的总奇偶 S
    for (int S = 0; S < 2; S ++){
        // C 偶数：rw[i] 唯一确定；C 奇数：rw 自由，只要总奇偶 = S
        for (int i = 1; i <= R; i ++)
            rw[i] = (C % 2 == 0) ? (tr[i] ^ S) : 0;
        if (C % 2 == 1)
            rw[1] = S;
        for (int j = 1; j <= C; j ++)
            cl[j] = (R % 2 == 0) ? (tc[j] ^ S) : 0;
        if (R % 2 == 1)
            cl[1] = S;

        // 按公式构造 x
        memset(rs, 0, sizeof(rs));
        memset(cs, 0, sizeof(cs));
        for (int i = 1; i <= R; i ++)
            for (int j = 1; j <= C; j ++){
                x[i][j] = t[i][j] ^ rw[i] ^ cl[j];
                rs[i] ^= x[i][j];
                cs[j] ^= x[i][j];
            }

        // 验证：每盏灯翻转的奇偶 = rs[i] ^ cs[j] ^ x[i][j]，必须等于 t[i][j]
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
                    cout << i - 1 << " " << j - 1 << endl;   // 题目的行列从 0 开始
        return 0;
    }

    cout << -1 << endl;
    return 0;
}
