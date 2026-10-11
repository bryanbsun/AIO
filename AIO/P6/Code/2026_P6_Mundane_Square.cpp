// AIO 2026 P6 - Mundane Square
// Method: row-by-row Greedy (serve the columns with the largest remaining demand first) + binary search on the water level lam (water-filling)
#include <bits/stdc++.h>
using namespace std;

int n;
long long K, R[1010], C[1010], rem[1010];   // rem[j]: how much column j still needs
int a[1010][1010];

// with water level lam, how much this row hands out in total: min(K, max(0, rem[j] - lam)) per column
long long give(long long lam){
    long long sum = 0;
    for (int j = 1; j <= n; j ++)
        sum += min(K, max(0LL, rem[j] - lam));
    return sum;
}

int main(){
    // up to 10^6 numbers of output: turn off sync with stdio and untie cin from cout for faster I/O
    // (once this is on, do not mix cin/cout with scanf/printf)
    ios::sync_with_stdio(false);
    cin.tie(0);

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

    // the total of the row sums must equal the total of the column sums
    if (sr != sc){
        cout << "NO" << endl;
        return 0;
    }

    for (int i = 1; i <= n; i ++){
        // a. this row's capacity give(0) is less than R[i]: it cannot fit
        if (give(0) < R[i]){
            cout << "NO" << endl;
            return 0;
        }

        // b. binary search: the smallest lam with give(lam) <= R[i]
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
        long long left = R[i] - give(lam);     // remainder smaller than one full level

        // c. allocate by the water level; the remainder goes to columns sitting exactly at the water level and still below K
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

    // every column must be filled exactly
    for (int j = 1; j <= n; j ++)
        if (rem[j] != 0){
            cout << "NO" << endl;
            return 0;
        }

    cout << "YES" << endl;
    for (int i = 1; i <= n; i ++){
        for (int j = 1; j <= n; j ++)
            cout << a[i][j] << " ";
        cout << "\n";             // use "\n" rather than endl: endl flushes the buffer every time
    }
    return 0;
}
