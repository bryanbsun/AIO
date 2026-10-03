// AIIO 2023 P2 - Electrical Fault
// 方法：多源 Dijkstra（multi-source，手写小根堆 heap）+ 来源标签 owner + 枚举"边界边"
#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int V, E, K;
int ea[300010], eb[300010], ew[300010];         // 所有的边
int head[100010], nxt[600010], to[600010], wt[600010], cnt;   // 邻接表（链式前向星）
long long dist[100010];         // dist[v]：v 到最近接地端子的距离
int owner[100010];              // owner[v]：离 v 最近的接地端子是谁

// 手写小根堆：按 hd[] 从小到大，堆里存 (距离, 点)
long long hd[1000010];
int hv[1000010], hs;

void push(long long d, int v){
    hs ++;
    int i = hs;
    while (i > 1 && hd[i / 2] > d){             // 往上浮
        hd[i] = hd[i / 2];
        hv[i] = hv[i / 2];
        i /= 2;
    }
    hd[i] = d;
    hv[i] = v;
}

void pop(){                                     // 删掉堆顶
    long long d = hd[hs];
    int v = hv[hs];
    hs --;
    int i = 1;
    while (2 * i <= hs){                        // 往下沉
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

void addEdge(int u, int v, int w){
    cnt ++;
    to[cnt] = v;
    wt[cnt] = w;
    nxt[cnt] = head[u];
    head[u] = cnt;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> V >> E >> K;
    for (int i = 1; i <= V; i ++){
        dist[i] = INF;
        owner[i] = 0;
    }
    for (int i = 1; i <= K; i ++){
        int x;
        cin >> x;
        dist[x] = 0;                            // 所有接地端子同时作为起点
        owner[x] = x;
        push(0, x);
    }
    for (int i = 1; i <= E; i ++){
        cin >> ea[i] >> eb[i] >> ew[i];
        addEdge(ea[i], eb[i], ew[i]);
        addEdge(eb[i], ea[i], ew[i]);
    }

    // 1) 多源 Dijkstra
    while (hs > 0){
        long long d = hd[1];
        int u = hv[1];
        pop();
        if (d > dist[u])                        // 过期的记录，跳过
            continue;
        for (int e = head[u]; e; e = nxt[e]){
            int v = to[e];
            if (d + wt[e] < dist[v]){
                dist[v] = d + wt[e];
                owner[v] = owner[u];            // 继承来源
                push(dist[v], v);
            }
        }
    }

    // 2) 枚举每条边：两端来源不同，就连起了两个不同的接地端子
    long long ans = INF;
    for (int i = 1; i <= E; i ++){
        int u = ea[i], v = eb[i];
        if (owner[u] != 0 && owner[v] != 0 && owner[u] != owner[v])
            ans = min(ans, dist[u] + ew[i] + dist[v]);
    }

    cout << ans << endl;
    return 0;
}
