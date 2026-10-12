#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1), all_cnt(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        all_cnt[a[i]]++;
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        all_cnt[b[i]]++;
    }
    for (int i = 1; i <= n; i++) {
        if (all_cnt[i] & 1) {
            cout << "-1\n";
            return;
        }
    }
    vector<array<int, 2>> ans;
    vector<vector<int>> num_idx(n + 1);
    for (int i = n; i >= 1; i--) {
        num_idx[a[i]].push_back(i);
        num_idx[b[i]].push_back(i);
    }
    i64 cost = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] == b[i]) {
            num_idx[a[i]].pop_back();
            num_idx[b[i]].pop_back();
            continue;
        }
        num_idx[a[i]].pop_back();
        num_idx[b[i]].pop_back();
        int a_idx = num_idx[a[i]].back();
        int b_idx = num_idx[b[i]].back();
        if (a_idx < b_idx) {
            num_idx[a[i]].pop_back();
            num_idx[b[i]].push_back(a_idx);
            if (a[a_idx] == a[i]) {
                swap(b[i], a[a_idx]);
                ans.push_back({a_idx, i});
            }
            else {
                swap(a[a_idx], b[a_idx]);
                swap(a[a_idx], b[i]);
                ans.push_back({a_idx, a_idx});
                ans.push_back({a_idx, i});
            }
            cost += a_idx - i;
        }
        else {
            num_idx[b[i]].pop_back();
            num_idx[a[i]].push_back(b_idx);
            if (b[b_idx] == b[i]) {
                swap(a[i], b[b_idx]);
                ans.push_back({i, b_idx});
            }
            else {
                swap(b[b_idx], a[b_idx]);
                swap(b[b_idx], a[i]);
                ans.push_back({b_idx, b_idx});
                ans.push_back({i, b_idx});
            }
            cost += b_idx - i;
        }
    }
    cout << cost << ' ' << ans.size() << '\n';
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i][0] << ' ' << ans[i][1] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    
}