#include <iostream>
using namespace std;

const int MAXC = 100005;
int dry[MAXC];   /* dry[i] = 1 if chair i is dry, else 0 */

int main() {
    int C, N, K;
    cin >> C >> N >> K;
    for (int i = 0; i < C; i++) cin >> dry[i];

    int need_dry = N - K;
    int best = C;
    int num_chairs = 0, num_dry = 0;
    int r = 0;                       /* window is half-open [l, r) */
    for (int l = 0; l < C; l++) {
        while (r < C && !(num_chairs >= N && num_dry >= need_dry)) {
            num_chairs++;
            num_dry += dry[r];
            r++;
        }
        if (num_chairs >= N && num_dry >= need_dry) {
            if (num_chairs < best) best = num_chairs;
        }
        if (r > l) { num_chairs--; num_dry -= dry[l]; }
        else { r = l + 1; }
    }
    cout << best << "\n";
    return 0;
}
