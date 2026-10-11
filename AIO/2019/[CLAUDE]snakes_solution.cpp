// Medusa's Snakes — Correct Solution
// AIO 2019
//
// We want the largest x such that the string contains x S's, then x N's
// (after those S's), then x A's, then x K's, then x E's as a subsequence.
//
// Key observations:
//   1. If venom level x is achievable, then level x-1 is also achievable
//      (just use one fewer of each letter). So the achievable levels form
//      a range [0, answer]. → Binary search on x is valid.
//
//   2. To check if level x is achievable: scan the string left-to-right,
//      greedily collecting x S's, then x N's, then x A's, then x K's,
//      then x E's. Taking each letter as early as possible is always
//      at least as good as waiting (it leaves more string remaining for
//      later letters). → A single greedy scan suffices for the check.
//
// Time complexity: O(N log N) — binary search O(log N) rounds,
//                               each check O(N).

#include <bits/stdc++.h>
using namespace std;

int n;
string dna;
const char letters[5] = {'S', 'N', 'A', 'K', 'E'};

// Returns true if we can achieve venom level x using dna as a subsequence.
bool check(int x) {
    if (x == 0) return true;

    int phase = 0;  // which letter we're currently collecting (0=S ... 4=E)
    int count = 0;  // how many of letters[phase] collected so far

    for (int i = 0; i < n && phase < 5; i++) {
        if (dna[i] == letters[phase]) {
            count++;
            if (count == x) {   // finished collecting x of this letter
                count = 0;
                phase++;
            }
        }
    }
    return phase >= 5;  // completed all five letter groups
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> dna;

    // Binary search: find largest x in [0, n/5] where check(x) is true.
    int lo = 0, hi = n / 5;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (check(mid))
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    // After the loop, hi is the largest x where check(x) is true.
    cout << hi << "\n";
    return 0;
}
