#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

// 欧拉筛 O(n), 素数最大值 <= n
struct Euler_Prime {
    vector<int> p;
    vector<bool> is_prime;

    void euler_prime(int n) {
        p.clear();
        is_prime.clear();
        is_prime.resize(n + 1, true);
        for (int i = 2; i <= n; i++) {
            if (is_prime[i]) {
                p.push_back(i);
            }
            for (auto pp : p) {
                if (pp * i > n) {
                    break;
                }
                is_prime[pp * i] = false;
                if (i % pp == 0) {
                    break;
                }
            }
        }
    }
};

void test01() {

}

int main() {
    cout << "--------------------------- START ---------------------------\n";
    test01();
    cout << "---------------------------- END ----------------------------\n";
    return 0;
}