// AIO 2026 P6 - Mundane Square
// 方法：逐行 Greedy（优先给剩余需求最大的列）+ 二分水位线 lam（water-filling）
#include <bits/stdc++.h>
using namespace std;

int n;
long long K, R[1010], C[1010], rem[1010];   // rem[j]：第 j 列还缺多少
int a[1010][1010];

// 水位线为 lam 时，这一行一共能发出多少：每列 min(K, max(0, rem[j] - lam))
long long give(long long lam){
    long long sum = 0;
    for (int j = 1; j <= n; j ++)
        sum += min(K, max(0LL, rem[j] - lam));
    return sum;
}

int main(){
    long long sr = 0, sc = 0;

    cin >> n >> K;
    for (int i = 1; i <= n; i ++){
        cin >> R[i];
        sr += R[i];
    }
    for (int j = 1; j <= n; j ++){
        cin >> C[j];
        sc += C[j];
        rem[j] = C[j];
    }

    // 行和总数必须等于列和总数
    if (sr != sc){
        cout << "NO" << endl;
        return 0;
    }

    for (int i = 1; i <= n; i ++){
        // a. 这一行的容量上限 give(0) 不够 R[i]，放不下
        if (give(0) < R[i]){
            cout << "NO" << endl;
            return 0;
        }

        // b. 二分：最小的 lam，使 give(lam) <= R[i]
        long long l = 0, r = 0;
        for (int j = 1; j <= n; j ++)
            r = max(r, rem[j]);
        while (l <= r){
            long long mid = (l + r) / 2;
            if (give(mid) <= R[i])
                r = mid - 1;
            else
                l = mid + 1;
        }
        long long lam = l;
        long long left = R[i] - give(lam);     // 不足一层的零头

        // c. 按水位线分配；零头给恰好顶着水位线、还没到 K 的列
        for (int j = 1; j <= n; j ++){
            long long v = min(K, max(0LL, rem[j] - lam));
            if (left > 0 && v < K && rem[j] - v == lam && lam > 0){
                v ++;
                left --;
            }
            a[i][j] = v;
            rem[j] -= v;
        }
        if (left > 0){
            cout << "NO" << endl;
            return 0;
        }
    }

    // 每一列都必须刚好填满
    for (int j = 1; j <= n; j ++)
        if (rem[j] != 0){
            cout << "NO" << endl;
            return 0;
        }

    cout << "YES" << endl;
    for (int i = 1; i <= n; i ++){
        for (int j = 1; j <= n; j ++)
            cout << a[i][j] << " ";
        cout << endl;
    }
    return 0;
}
