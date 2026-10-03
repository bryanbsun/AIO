// AIO 2024 P5 - Tennis Robot II
// 方法：一轮的净变化（Prefix Sum）+ 除法直接算出能完整跑完几轮 + 模拟最后一轮
#include <bits/stdc++.h>
using namespace std;

int n, m, A[200010], B[200010];
long long x[200010];
long long cur[200010];      // 一轮中，第 i 个箱子相对于这一轮开始时的变化
long long mn[200010];       // 第 i 个箱子每次被取球之前，cur 的最小值
long long d[200010];        // 一轮下来，第 i 个箱子的净变化
bool take[200010];          // 第 i 个箱子在一轮中有没有被取过球
long long b[200010];

int main(){
    cin >> n >> m;
    for (int i = 1; i <= n; i ++)
        cin >> x[i];
    for (int j = 1; j <= m; j ++)
        cin >> A[j] >> B[j];

    // 1) 走一遍指令，算出每个箱子的 mn 和 d
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

    // 2) 第 r 轮箱子 i 不出问题 <=> x[i] + mn[i] + (r-1)*d[i] >= 1
    //    记 s = x[i] + mn[i]：
    //    s < 1          ：第 1 轮就出问题，最多完整跑 0 轮
    //    d[i] >= 0      ：永远不会出问题
    //    d[i] < 0       ：r - 1 <= (s - 1) / (-d[i])，最多完整跑 (s-1)/(-d[i]) + 1 轮（整数除法）
    long long R = -1;                       // -1 表示没有箱子会出问题
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

    // 3) 完整跑完 R 轮，第 R+1 轮会停：模拟这一轮，找到停下来的那条指令
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
