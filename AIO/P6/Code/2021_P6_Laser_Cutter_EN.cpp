// AIO 2021 P6 - Laser Cutter
// Method: Binary Search on the answer (the side length of the square)
#include <bits/stdc++.h>
using namespace std;

int n, ya[200010], yb[200010];      // bottom and top boundary (row) of column x
char a[400010], b[400010];

// walk the cut: each time it steps right, record the current row
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

// does side s fit? some x with ya[x] - yb[x+s-1] >= s
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

    // binary search: the largest side that fits
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
