// AIO 2024 P6 - Atlantis III: Twin Rivers
// Method: Binary Search (nearest bridges) + second differences / two Prefix Sums
//
// Idea:
//   The new bridge goes on river w at position p. For each trip, treat "its cost"
//   as a function f(p) of p. f(p) is a broken line with slopes -2, 0, +2 only,
//   and just a few turning points.
//   The total cost is the sum of all trips' f. Instead of adding them at every p,
//   we record the second difference d2[q] only at the turning points q, then
//   rebuild the total cost at every p with two prefix sums.
#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e13;         // means "no route"

int n, L, T;
int nb[3];                          // nb[1], nb[2]: number of existing bridges on each river
long long br[3][200010];            // br[r][1..nb[r]]: bridges on river r (ascending)
long long d2[3][1000010];           // second differences: [1] new bridge on River 1, [2] on River 2
long long tot[3][1000010];          // rebuilt total cost: tot[w][p]

// the trip being processed right now
long long X;                        // starting position
int S;                              // destination: Strip 2 or Strip 3
long long u1, w1;                   // nearest bridges left / right of X on River 1 (-1 if none)
long long u2, w2;                   // nearest bridges left / right of X on River 2 (-1 if none)
long long oldCost;                  // shortest trip without the new bridge

// binary search: largest bridge <= v on river r, -1 if none
long long pred(int r, long long v){
    int l = 1, h = nb[r];
    while (l <= h){
        int mid = (l + h) / 2;
        if (br[r][mid] <= v)
            l = mid + 1;
        else
            h = mid - 1;
    }
    if (h >= 1)
        return br[r][h];
    return -1;
}

// binary search: smallest bridge >= v on river r, -1 if none
long long succ(int r, long long v){
    int l = 1, h = nb[r];
    while (l <= h){
        int mid = (l + h) / 2;
        if (br[r][mid] < v)
            l = mid + 1;
        else
            h = mid - 1;
    }
    if (l <= nb[r])
        return br[r][l];
    return -1;
}

// to Strip 2: walk to bridge a on River 1, cross, walk back to X
long long way2(long long a){
    if (a < 0)
        return INF;
    return 1 + 2 * abs(X - a);
}

// to Strip 3: use bridge a on River 1 and bridge b on River 2
// walk the stretch covering X, a and b twice (there and back), plus two bridges
long long way3(long long a, long long b){
    if (a < 0 || b < 0)
        return INF;
    long long hi = max(X, max(a, b));
    long long lo = min(X, min(a, b));
    return 2 + 2 * (hi - lo);
}

// f(w, p): shortest length of the current trip if the new bridge is at p on river w
long long f(int w, long long p){
    long long c = oldCost;
    if (S == 2 && w == 1)                               // new bridge used as the River 1 bridge
        c = min(c, way2(p));
    if (S == 3 && w == 1)                               // new bridge used as the River 1 bridge
        c = min(c, min(way3(p, u2), way3(p, w2)));
    if (S == 3 && w == 2)                               // new bridge used as the River 2 bridge
        c = min(c, min(way3(u1, p), way3(w1, p)));
    // S == 2 and w == 2: a bridge on River 2 does not help a trip to Strip 2
    return c;
}

// add the current trip's f(w, p) into accumulator w
void addTrip(int w){
    // 1. the first two values, needed for the rebuild
    tot[w][0] += f(w, 0);
    if (L >= 1)
        tot[w][1] += f(w, 1);

    // 2. candidate turning points: the key points, and each key point ± k (where f reaches oldCost)
    long long a, b;                                     // nearest bridges left / right of X on the OTHER river
    if (w == 1){
        a = u2;
        b = w2;
    }else{
        a = u1;
        b = w1;
    }
    long long key[5];
    int nk = 0;
    key[nk ++] = X;
    if (S == 3){
        if (a >= 0)
            key[nk ++] = a;
        if (b >= 0)
            key[nk ++] = b;
        if (a >= 0 && b >= 0)
            key[nk ++] = a + b - X;                     // where the two routes are equally long
    }
    long long k = (oldCost - (S - 1)) / 2;              // oldCost = (S - 1) + 2k

    long long cand[15];
    int nc = 0;
    for (int i = 0; i < nk; i ++){
        cand[nc ++] = key[i] - k;
        cand[nc ++] = key[i];
        cand[nc ++] = key[i] + k;
    }
    sort(cand, cand + nc);

    // 3. record the second difference at each candidate q (it is exactly 0 where f does not bend)
    for (int i = 0; i < nc; i ++){
        long long q = cand[i];
        if (i > 0 && q == cand[i-1])                    // skip duplicates
            continue;
        if (q < 1 || q > L - 1)
            continue;
        d2[w][q] += f(w, q + 1) - 2 * f(w, q) + f(w, q - 1);
    }
}

// two prefix sums: rebuild the total cost at every p from the second differences
void build(int w){
    for (int q = 1; q + 1 <= L; q ++)
        tot[w][q+1] = 2 * tot[w][q] - tot[w][q-1] + d2[w][q];
}

int main(){
    cin >> n >> L;
    for (int i = 1; i <= n; i ++){
        long long b;
        int r;
        cin >> b >> r;
        br[r][++ nb[r]] = b;
    }
    sort(br[1] + 1, br[1] + nb[1] + 1);
    sort(br[2] + 1, br[2] + nb[2] + 1);

    bool hasS3 = false;
    cin >> T;
    for (int j = 1; j <= T; j ++){
        cin >> X >> S;
        if (S == 3)
            hasS3 = true;

        // binary search: nearest bridges left / right of X on both rivers
        u1 = pred(1, X);
        w1 = succ(1, X);
        u2 = pred(2, X);
        w2 = succ(2, X);

        // shortest trip without the new bridge
        if (S == 2)
            oldCost = min(way2(u1), way2(w1));
        else
            oldCost = min(min(way3(u1, u2), way3(u1, w2)),
                          min(way3(w1, u2), way3(w1, w2)));

        addTrip(1);
        addTrip(2);
    }

    build(1);
    build(2);

    long long ans = -1;
    for (int p = 0; p <= L; p ++){
        // with the new bridge on River 1, trips to Strip 3 still need an existing River 2 bridge
        if (!hasS3 || nb[2] > 0)
            if (ans == -1 || tot[1][p] < ans)
                ans = tot[1][p];
        if (ans == -1 || tot[2][p] < ans)
            ans = tot[2][p];
    }
    cout << ans << endl;
    return 0;
}
