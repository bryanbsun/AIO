// AIIO 2025 P2 - Retail Empire
// 方法：Greedy（每天都取最大增量，靠单调性证明）+ 0/1 背包 0/1 knapsack（DP）
#include <bits/stdc++.h>
using namespace std;

int n, A, K;
int c[60], p[60];
long long best[150010];             // best[b]：预算 b 时，每种店最多开一家，能增加的最大日利润

int main(){
    cin >> n >> A >> K;
    for (int i = 1; i <= n; i ++)
        cin >> c[i] >> p[i];

    // 1) 0/1 背包：b 从大到小，保证每种店只用一次
    for (int i = 1; i <= n; i ++)
        for (int b = K; b >= c[i]; b --)
            best[b] = max(best[b], best[b - c[i]] + p[i]);

    // 2) 模拟：每天把当天利润全部用在"最赚的组合"上
    long long profit = A;
    int day = 1;
    while (profit < K){
        profit += best[profit];     // profit < K，下标不会越界
        day ++;
    }

    cout << day << endl;
    return 0;
}
