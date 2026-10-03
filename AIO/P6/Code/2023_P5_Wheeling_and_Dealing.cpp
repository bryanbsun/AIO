// AIO 2023 P5 - Wheeling and Dealing
// 方法：枚举 1 号的最终票数 k（水位线 k-1）+ Greedy（削峰时买最便宜的）
//       + 树状数组 BIT（按花费统计，求"最便宜的 t 个之和"）
#include <bits/stdc++.h>
using namespace std;

struct voter{
    int v, p;           // 投给谁，收买花费
}a[100010];

int n, m;
int st[100010], votes[100010], taken[100010];  // 候选人 j 的选民是 a[st[j] .. st[j]+votes[j]-1]
int head[100010], nx[100010];   // 按票数分桶：head[c] 是票数为 c 的第一个候选人
int act[100010], na;            // 当前票数 >= k 的对手
long long bc[10010], bs[10010]; // BIT：下标 = 花费 + 1，记录个数、总和
long long pool;                 // BIT 里还剩几个选民

bool cmp(voter x, voter y){
    if (x.v != y.v)
        return x.v < y.v;
    return x.p < y.p;
}

void add(int c, int d){
    for (int i = c + 1; i <= 10001; i += i & (-i)){
        bc[i] += d;
        bs[i] += d * c;
    }
}

// 池子里最便宜的 t 个选民的花费之和（在 BIT 上从高位往低位走）
long long cheapest(long long t){
    int pos = 0;
    long long got = 0, sum = 0;
    for (int step = 16384; step > 0; step /= 2)
        if (pos + step <= 10001 && got + bc[pos + step] < t){
            pos += step;
            got += bc[pos];
            sum += bs[pos];
        }
    return sum + (t - got) * pos;   // 剩下 t-got 个的花费都是 pos
}

int main(){
    cin >> n >> m;
    for (int i = 1; i <= m; i ++)
        cin >> a[i].v;
    for (int i = 1; i <= m; i ++)
        cin >> a[i].p;

    // 1) 按 (候选人, 花费) 排序，每个候选人的选民从便宜到贵
    sort(a + 1, a + m + 1, cmp);
    for (int i = m; i >= 1; i --){
        votes[a[i].v] ++;
        st[a[i].v] = i;
    }

    // 2) 不投 1 号的选民都放进 BIT（可以收买的池子）
    for (int i = 1; i <= m; i ++)
        if (a[i].v != 1){
            add(a[i].p, 1);
            pool ++;
        }

    // 3) 对手按票数分桶
    memset(head, 0, sizeof(head));
    for (int j = 2; j <= n; j ++)
        if (votes[j] > 0){
            nx[j] = head[votes[j]];
            head[votes[j]] = j;
        }

    // 4) k 从大到小：票数 >= k 的对手必须削到 k-1
    int c1 = votes[1];
    long long fc = 0, fn = 0;       // 强制购买的总花费、总票数
    long long best = -1;
    for (int k = m; k >= max(c1, 1); k --){
        for (int j = head[k]; j; j = nx[j])
            act[++ na] = j;

        for (int u = 1; u <= na; u ++){
            int j = act[u];
            while (taken[j] < votes[j] - (k - 1)){     // 买他剩下最便宜的
                int c = a[st[j] + taken[j]].p;
                taken[j] ++;
                fc += c;
                fn ++;
                add(c, -1);
                pool --;
            }
        }

        long long have = c1 + fn, cost = fc;
        if (have < k){
            if (k - have > pool)        // 选民不够，这个 k 做不到
                continue;
            cost += cheapest(k - have);
        }
        if (best == -1 || cost < best)
            best = cost;
    }

    cout << best << endl;
    return 0;
}
