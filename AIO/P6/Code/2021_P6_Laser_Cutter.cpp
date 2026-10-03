// AIO 2021 P6 - Laser Cutter
// 方法：Binary Search on Answer（二分正方形边长）
#include <bits/stdc++.h>
using namespace std;

int n, ya[200010], yb[200010];      // 第 x 列的下边界、上边界（行号）
char a[400010], b[400010];

// 模拟路径：每次向右走一格，记下当前的行号
void trace(char p[], int y[]){
    int row = 0, col = 1;
    for (int i = 0; i < 2 * n; i ++){
        if (p[i] == 'D')
            row ++;
        else{
            y[col] = row;
            col ++;
        }
    }
}

// 边长 s 能否放下：存在 x，使 ya[x] - yb[x+s-1] >= s
bool check(int s){
    for (int x = 1; x + s - 1 <= n; x ++)
        if (ya[x] - yb[x + s - 1] >= s)
            return true;
    return false;
}

int main(){
    cin >> n >> a >> b;
    trace(a, ya);
    trace(b, yb);

    // 二分：找最大的可行边长
    int l = 1, r = n;
    while (l <= r){
        int mid = (l + r) / 2;
        if (check(mid))
            l = mid + 1;
        else
            r = mid - 1;
    }

    cout << r << endl;
    return 0;
}
