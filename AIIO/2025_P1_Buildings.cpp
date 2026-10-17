// AIIO 2025 P1 - Buildings
// 方法：枚举右边的楼 j + 计数数组 counting array（"已见集合"随 j 只增不减）
#include <bits/stdc++.h>
using namespace std;

int n, K, X;
int h[200010];
bool seen[2000010];                 // seen[v]：某栋"足够远"的楼高度为 v

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> K >> X;
    for (int i = 1; i <= n; i ++)
        cin >> h[i];

    // 考察 j 之前，把 i = j-K 放进已见集合；然后查 h[j]-X 和 h[j]+X
    for (int j = K + 1; j <= n; j ++){
        seen[h[j - K]] = true;
        int lo = h[j] - X, hi = h[j] + X;
        if ((lo >= 1 && seen[lo]) || seen[hi]){
            cout << "YES" << endl;
            return 0;
        }
    }

    cout << "NO" << endl;
    return 0;
}
