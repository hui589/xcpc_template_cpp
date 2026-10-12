#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

void solve() {
    std::mt19937 g{std::random_device{}()}; 
    srand(time(0)); 
    srand(g());

    int what_rand = 1;
    // cin >> what_rand;
    int MUL = 1e3;
    int t = rand() % 5 + 1;
    int n_MAX = rand() % 10 + 1;
    t = 1;
    cout << t << "\n";
    while (t--) {
        int n = ((rand() << 15) | rand()) % n_MAX + 8;
        n += 1;
        int val_MAX = n;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) {
            a[i] = (rand() % val_MAX) + 1;
            b[i] = (rand() % val_MAX) + 1;
        }
        if (what_rand == 1) {
            b = a;
        }
        shuffle(b.begin(), b.end(), g);
        for (int i = 0; i < n * 10; i++) {
            int idx1 = rand() % n;
            int idx2 = rand() % n;
            swap(a[idx1], b[idx2]);
        }
        cout << n << '\n';
        for (int i = 0; i < n; i++) cout << a[i] << " \n"[i == n - 1];
        for (int i = 0; i < n; i++) cout << b[i] << " \n"[i == n - 1];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    solve();
    return 0;
}