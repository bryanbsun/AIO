// AIIO 2023 P3 - Pinnacle
// 方法：山峰放在区间最大值处 + 单调栈 monotonic stack（找下一个更大）
//       + "跳跃链"上的后缀和 + 稀疏表 Sparse Table（区间最大值位置）+ Prefix Sum
#include <bits/stdc++.h>
using namespace std;

int n, q;
long long a[100010], pre[100010];
int nx[100010], pv[100010];         // nx[i]：右边第一个 >= a[i] 的位置；pv[i]：左边第一个 > a[i] 的位置
long long SL[100010], SR[100010];   // 沿链的和：SL 向右（前缀最大值之和），SR 向左（后缀最大值之和）
int st[100010], top;                // 单调栈
int sp[18][100010], lg[100010];     // 稀疏表：sp[k][i] = [i, i+2^k-1] 中最大值的位置

// 两个位置中值更大的；相等时取更靠右的
int better(int i, int j){
    if (a[i] != a[j]){
        if (a[i] > a[j])
            return i;
        return j;
    }
    return max(i, j);
}

int queryMaxPos(int l, int r){
    int k = lg[r - l + 1];
    return better(sp[k][l], sp[k][r - (1 << k) + 1]);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> q;
    pre[0] = 0;
    for (int i = 1; i <= n; i ++){
        cin >> a[i];
        pre[i] = pre[i - 1] + a[i];
    }

    // 1) 单调栈：从右往左求 nx[]（第一个 >=），从左往右求 pv[]（第一个 >）
    top = 0;
    for (int i = n; i >= 1; i --){
        while (top > 0 && a[st[top]] < a[i])
            top --;
        if (top > 0)
            nx[i] = st[top];
        else
            nx[i] = n + 1;
        st[++ top] = i;
    }
    top = 0;
    for (int i = 1; i <= n; i ++){
        while (top > 0 && a[st[top]] <= a[i])
            top --;
        if (top > 0)
            pv[i] = st[top];
        else
            pv[i] = 0;
        st[++ top] = i;
    }

    // 2) 沿链的后缀和：每一段"台阶"贡献 a[x] * 长度
    SL[n + 1] = 0;
    for (int i = n; i >= 1; i --)
        SL[i] = a[i] * (nx[i] - i) + SL[nx[i]];
    SR[0] = 0;
    for (int i = 1; i <= n; i ++)
        SR[i] = a[i] * (i - pv[i]) + SR[pv[i]];

    // 3) 稀疏表
    lg[1] = 0;
    for (int i = 2; i <= n; i ++)
        lg[i] = lg[i / 2] + 1;
    for (int i = 1; i <= n; i ++)
        sp[0][i] = i;
    for (int k = 1; (1 << k) <= n; k ++)
        for (int i = 1; i + (1 << k) - 1 <= n; i ++)
            sp[k][i] = better(sp[k - 1][i], sp[k - 1][i + (1 << (k - 1))]);

    // 4) 回答询问
    for (int t = 1; t <= q; t ++){
        int l, r;
        cin >> l >> r;
        int m = queryMaxPos(l, r);                  // 最高塔（最靠右的那个）
        long long leftSum = SL[l] - SL[m] + a[m];   // sum_{i=l..m} max(a[l..i])
        long long rightSum = SR[r] - SR[m] + a[m];  // sum_{i=m..r} max(a[i..r])
        long long ans = leftSum + rightSum - a[m] - (pre[r] - pre[l - 1]);   // m 被算了两次
        cout << ans << "\n";
    }
    return 0;
}
