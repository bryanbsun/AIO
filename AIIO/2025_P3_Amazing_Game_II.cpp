// AIIO 2025 P3 - Amazing Game II
// 方法：全源 BFS（N <= 1000）+ Greedy（每次选最早能得分的时刻，交换论证）
//       + Two Pointers（Amy 的路"第一次不是最短路"的位置单调）+ 从后往前计数
#include <bits/stdc++.h>
using namespace std;

int n, m, K, Q;
int head[1010], nxt[4010], to[4010], cnt;   // 邻接表（链式前向星）
short dist[1010][1010];                     // dist[u][v]：u 到 v 的最短距离
int A[200010];
int nextT[200010];      // nextT[t]：在时刻 t 于 A[t] 得分后，下一次最早得分的时刻（K+1 表示没有）
int score[200010];      // score[t]：在时刻 t 得分之后（含这一分），最多还能得几分
int que[1010];

void addEdge(int u, int v){
    cnt ++;
    to[cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

void bfs(int s){
    for (int i = 1; i <= n; i ++)
        dist[s][i] = -1;
    int qh = 1, qt = 0;
    dist[s][s] = 0;
    que[++ qt] = s;
    while (qh <= qt){
        int u = que[qh ++];
        for (int e = head[u]; e; e = nxt[e])
            if (dist[s][to[e]] < 0){
                dist[s][to[e]] = dist[s][u] + 1;
                que[++ qt] = to[e];
            }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= m; i ++){
        int u, v;
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    cin >> K;
    for (int i = 1; i <= K; i ++)
        cin >> A[i];

    // 1) 从每个房间做一次 BFS
    for (int s = 1; s <= n; s ++)
        bfs(s);

    // 2) 双指针：g = 使 A[t..g] 仍是最短路的最大下标，随 t 单调不减
    int g = 1;
    for (int t = 1; t <= K; t ++){
        if (g < t)
            g = t;
        while (g + 1 <= K && dist[A[t]][A[g + 1]] == g + 1 - t)
            g ++;
        nextT[t] = g + 1;
    }

    // 3) 沿 nextT 链从后往前计数
    for (int t = K; t >= 1; t --){
        score[t] = 1;
        if (nextT[t] <= K)
            score[t] += score[nextT[t]];
    }

    // 4) 每一局：找第一个能得分的时刻 t（dist(B, A[t]) <= t - 1 - i）
    cin >> Q;
    for (int i = 1; i <= Q; i ++){
        int b;
        cin >> b;
        int ans = 0;
        for (int t = i + 1; t <= K; t ++)
            if (dist[b][A[t]] <= t - 1 - i){
                ans = score[t];
                break;
            }
        cout << ans << "\n";
    }
    return 0;
}
