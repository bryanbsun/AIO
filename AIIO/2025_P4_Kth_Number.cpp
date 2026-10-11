// AIIO 2025 P4 - Kth Number（交互题 interactive）
// 方法：分类讨论 case analysis
//   情况 A（M 较小）：S = {0..M}，依次去掉一个元素询问，K = 较大答案出现的次数
//   情况 B（M 较大）：固定底座 T + 探针 z，答案 = clamp(P_z, alpha, beta)，利用"值 = 全局排名"
// 注意：官方接口 ask_host 的参数是 std::vector<int>，这是本题唯一用到 vector 的地方
#include "kthnumber.h"
#include <bits/stdc++.h>
using namespace std;

int idx[210], res[210];

// 把数组 idx[1..cnt] 交给主持人（官方接口需要 vector）
int ask(int cnt){
    std::vector<int> I;
    for (int i = 1; i <= cnt; i ++)
        I.push_back(idx[i]);
    return ask_host(I);
}

int findK(int N, int M, int subtask){
    // ---------- 情况 A：M+1 次询问 ----------
    if (M <= (N + 1) / 2){
        int big = 0;
        for (int j = 0; j <= M; j ++){
            int c = 0;
            for (int i = 0; i <= M; i ++)
                if (i != j)
                    idx[++ c] = i;
            res[j] = ask(c);
            big = max(big, res[j]);
        }
        int K = 0;                          // 去掉"排名 <= K"的元素，得到较大的答案
        for (int j = 0; j <= M; j ++)
            if (res[j] == big)
                K ++;
        return K;
    }

    // ---------- 情况 B：T = {0..M-2}，U = {M-1..N-1} ----------
    int u = N - M + 1;
    int mx = 0, mn = N + 1;
    for (int k = 1; k <= u; k ++){
        int z = M - 2 + k;                  // 第 k 个探针
        int c = 0;
        for (int i = 0; i <= M - 2; i ++)
            idx[++ c] = i;
        idx[++ c] = z;
        res[k] = ask(c);
        mx = max(mx, res[k]);
        mn = min(mn, res[k]);
    }
    if (mx != mn){
        // 最大答案是 beta 或某个夹在中间的 P_z：K = mx - (答案 < mx 的个数)
        int less = 0;
        for (int k = 1; k <= u; k ++)
            if (res[k] < mx)
                less ++;
        return mx - less;
    }

    // 所有答案都等于 x：假设 H（U 全在上方，K = x）或假设 L（U 全在下方，K = x+1-u）
    int x = mx;
    int KH = x, KL = x + 1 - u;
    int capH = M - 1 - KH;                  // H 成立时，T 中排名 > K 的个数
    int capL = KL - 2;                      // L 成立时，T 中排名 <= K-2 的个数
    int eq = 0;
    for (int t = 0; t <= M - 2; t ++){
        if (capH < 0 || eq > capH)          // H 已不可能
            return KL;
        if (capL < 0 || eq > capL)          // L 已不可能
            return KH;
        int c = 0;                          // 询问 T \ {t} ∪ {两个探针}
        for (int i = 0; i <= M - 2; i ++)
            if (i != t)
                idx[++ c] = i;
        idx[++ c] = M - 1;
        idx[++ c] = M;
        int r = ask(c);
        if (r > x)
            return KH;
        if (r < x)
            return KL;
        eq ++;
    }
    if (eq > capH)
        return KL;
    return KH;
}
