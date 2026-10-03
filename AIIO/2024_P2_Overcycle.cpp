// AIIO 2024 P2 - Overcycle
// 方法：关键观察（用到捷径的路径一定经过 1 或 N）+ 两次 Dijkstra（手写小根堆）+ Prefix Sum
//       答案 = min(只走路, d1[s] + d1[t], dN[s] + dN[t])
#include <bits/stdc++.h>
using namespace std;

const long long INF = 4e18;

int n, A, B, q;
long long pre[200010];              // pre[i]：沿路从 1 走到 i 的距离
int head[200010], nxt[800010], to[800010], cnt;     // 邻接表（链式前向星）
long long wt[800010];
long long d1[200010], dN[200010];

// 手写小根堆
long long hd[2000010];
int hv[2000010], hs;

void push(long long d, int v){
    hs ++;
    int i = hs;
    while (i > 1 && hd[i / 2] > d){
        hd[i] = hd[i / 2];
        hv[i] = hv[i / 2];
        i /= 2;
    }
    hd[i] = d;
    hv[i] = v;
}

void pop(){
    long long d = hd[hs];
    int v = hv[hs];
    hs --;
    int i = 1;
    while (2 * i <= hs){
        int c = 2 * i;
        if (c + 1 <= hs && hd[c + 1] < hd[c])
            c ++;
        if (hd[c] >= d)
            break;
        hd[i] = hd[c];
        hv[i] = hv[c];
        i = c;
    }
    hd[i] = d;
    hv[i] = v;
}

void addEdge(int u, int v, long long w){
    cnt ++;
    to[cnt] = v;
    wt[cnt] = w;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

// 从 src 出发的最短路，结果写进 dist[]
void dijkstra(int src, long long dist[]){
    for (int i = 1; i <= n; i ++)
        dist[i] = INF;
    dist[src] = 0;
    hs = 0;
    push(0, src);
    while (hs > 0){
        long long d = hd[1];
        int u = hv[1];
        pop();
        if (d > dist[u])
            continue;
        for (int e = head[u]; e; e = nxt[e])
            if (d + wt[e] < dist[to[e]]){
                dist[to[e]] = d + wt[e];
                push(dist[to[e]], to[e]);
            }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    pre[1] = 0;
    for (int i = 1; i < n; i ++){
        long long d;
        cin >> d;
        pre[i + 1] = pre[i] + d;
        addEdge(i, i + 1, d);
        addEdge(i + 1, i, d);
    }
    cin >> A;
    for (int i = 1; i <= A; i ++){
        int x;
        long long k;
        cin >> x >> k;
        addEdge(1, x, k);
        addEdge(x, 1, k);
    }
    cin >> B;
    for (int i = 1; i <= B; i ++){
        int y;
        long long l;
        cin >> y >> l;
        addEdge(n, y, l);
        addEdge(y, n, l);
    }

    dijkstra(1, d1);                // 全图中 1 到每个点的最短路
    dijkstra(n, dN);                // 全图中 N 到每个点的最短路

    cin >> q;
    for (int k = 1; k <= q; k ++){
        int s, t;
        cin >> s >> t;
        long long ans = pre[t] - pre[s];        // 情况 1：只走路
        ans = min(ans, d1[s] + d1[t]);          // 情况 2：经过 1
        ans = min(ans, dN[s] + dN[t]);          // 情况 3：经过 N
        cout << ans << "\n";
    }
    return 0;
}
