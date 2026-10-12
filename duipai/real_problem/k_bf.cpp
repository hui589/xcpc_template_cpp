#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    vector<int> all(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        all[a[i]]++;
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        all[b[i]]++;
    }
    // if (n > 15) {
    //     cout << "-1\n";
    //     return;
    // }
    for (int i = 1; i <= n; i++) {
        if (all[i] & 1) {
            cout << "-1\n";
            return;
        }
    }
    i64 cost = 0;
    for (int i = 1; i <= n; i++) {
        if (b[i] == a[i]) continue;
        int aid = -1, bid = -1;
        int aab = -1, bab = -1;
        for (int idx = i + 1; idx <= n; idx++) {
            if (aid == -1) {
                if      (a[idx] == a[i]) aid = idx, aab = 1;
                else if (b[idx] == a[i]) aid = idx, aab = 2;
            }
            if (bid == -1) {
                if      (a[idx] == b[i]) bid = idx, bab = 1;
                else if (b[idx] == b[i]) bid = idx, bab = 2;
            }
        }
        if (aid < bid) {
            if (aab == 1) swap(b[i], a[aid]);
            else          swap(b[i], b[aid]);
        } else {
            if (bab == 1) swap(a[i], a[bid]);
            else          swap(a[i], b[bid]);
        }
        cost += min(aid, bid) - i;
    }
    cout << cost << " 0\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}