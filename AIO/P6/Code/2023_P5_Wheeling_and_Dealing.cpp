// AIO 2023 P5 - Wheeling and Dealing
// Method: try every target k (candidate 1 gets >= k votes, each rival <= k-1, water level k-1) + Greedy (buy the cheapest when cutting peaks)
//       + cost buckets (one block per 100 cost values) to get "the sum of the t cheapest remaining"
//       note: after the forced purchases candidate 1 may have more than k votes, which is still valid
#include <bits/stdc++.h>
using namespace std;

struct voter{
    int v, p;           // who they vote for, cost to buy them
}a[100010];

int n, m;
int st[100010], votes[100010], taken[100010];  // voters of candidate j are a[st[j] .. st[j]+votes[j]-1]
int head[100010], nx[100010];   // bucket by vote count: head[c] is the first candidate with c votes
int act[100010], na;            // rivals currently with >= k votes
long long cnt[10010];           // cnt[c]: number of voters in the pool with cost c
long long bcnt[110], bsum[110]; // count and cost sum of block b (costs 100b .. 100b+99)
long long pool;                 // number of voters left in the pool

bool cmp(voter x, voter y){
    if (x.v != y.v)
        return x.v < y.v;
    return x.p < y.p;
}

// add (d = 1) or remove (d = -1) a voter with cost c in the pool
void add(int c, int d){
    cnt[c] += d;
    bcnt[c / 100] += d;
    bsum[c / 100] += d * c;
}

// sum of the t cheapest voters in the pool: skip whole blocks first, then go cost by cost inside a block
long long cheapest(long long t){
    long long sum = 0;
    int b = 0;
    while (bcnt[b] < t){          // take the whole block
        t -= bcnt[b];
        sum += bsum[b];
        b ++;
    }
    for (int c = b * 100; t > 0; c ++){   // inside the block, cheapest to dearest
        long long take = min(cnt[c], t);   // how many to take at this cost
        sum += take * c;
        t -= take;
    }
    return sum;
}

int main(){
    cin >> n >> m;
    for (int i = 1; i <= m; i ++)
        cin >> a[i].v;
    for (int i = 1; i <= m; i ++)
        cin >> a[i].p;

    // 1) sort by (candidate, cost), so each candidate's voters go from cheapest to dearest
    sort(a + 1, a + m + 1, cmp);
    for (int i = m; i >= 1; i --){
        votes[a[i].v] ++;
        st[a[i].v] = i;
    }

    // 2) put every voter not voting for candidate 1 into the pool (buyable voters, bucketed by cost)
    for (int i = 1; i <= m; i ++)
        if (a[i].v != 1){
            add(a[i].p, 1);
            pool ++;
        }

    // 3) bucket the rivals by vote count
    memset(head, 0, sizeof(head));
    for (int j = 2; j <= n; j ++)
        if (votes[j] > 0){
            nx[j] = head[votes[j]];
            head[votes[j]] = j;
        }

    // 4) k from large to small: every rival with >= k votes must be cut down to k-1
    int c1 = votes[1];
    long long fc = 0, fn = 0;       // total cost and total votes of the forced purchases
    long long best = -1;
    for (int k = m; k >= max(c1, 1); k --){
        for (int j = head[k]; j; j = nx[j])
            act[++ na] = j;

        for (int u = 1; u <= na; u ++){
            int j = act[u];
            while (taken[j] < votes[j] - (k - 1)){     // buy their cheapest remaining voter
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
            if (k - have > pool)        // not enough voters: this k is impossible
                continue;
            cost += cheapest(k - have);
        }
        if (best == -1 || cost < best)
            best = cost;
    }

    cout << best << endl;
    return 0;
}
