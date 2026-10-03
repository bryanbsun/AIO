#include <bits/stdc++.h>
using namespace std;

int     n, h[100010], im[100010], ug;

int     main(){
    cin >> n;
    for (int i = 1; i <= n; i ++)
        cin >> h[i];

    for (int i = 1; i <= n; i ++){
        if (i != n) 
            ug += abs(h[i] - h[i+1]);
        
        if (i == 1)
            im[i] = abs(h[i] - h[i+1]);
        else if (i == n)
            im[i] = abs(h[i] - h[i-1]);
        else
            if ((h[i-1] - h[i]) * (h[i] - h[i+1]) >= 0)
                im[i] = 0;
            else
                im[i] = 2 * min(abs(h[i] - h[i-1]), abs(h[i+1] - h[i]));    
    }

    sort(im+1, im+n+1);
    cout << ug - im[n] << endl;

    return 0;
}