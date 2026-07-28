#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
// 伽马常数
const double gama = 0.57721566490153286;

// 莫比乌斯反演
struct mubiwusi {
    int tot;
    bool not_prime[666];
    int mu[666];
    int phi[666];
    int p[666];
    void getmu(int maxx) {
        tot = 0;
        memset(not_prime, false, sizeof(not_prime));
        mu[1] = 1;
        phi[1] = 1;
        for (int i = 2; i <= maxx; i++) {
            if (!not_prime[i]) {
                p[tot++] = i;
                mu[i] = -1;
                phi[i] = i - 1;
            }
            for (int j = 0; j < tot; j++) {
                if (i * p[j] > maxx) {
                    break;
                }
                not_prime[i * p[j]] = true;
                if (i % p[j] == 0) {
                    mu[i * p[j]] = 0;
                    phi[i * p[j]] = phi[i] * p[j];
                    break;
                }
                mu[i * p[j]] = -mu[i];
                phi[i * p[j]] = phi[i] * phi[p[j]];
                // mu[i * p[j]] = mu[i] * mu[p[j]];
            }
        }
    }
};

// 欧拉函数
struct Euler_Func {
    i64 phi_function(i64 x) {
        i64 ret = x;
        for (int i = 2; i * i <= x; i++) {
            if (x % i == 0) {
                ret = ret / i * (i - 1);
            }
            while (x % i == 0) {
                x /= i;
            }
        }
        if (x > 1) {
            ret = ret / x * (x - 1);
        }
        return ret;
    }

    static const int N = 1e5;
    bool not_prime[N];
    i64 phi[N];
    void euler_prime(int maxx) {
        vector<int> pi;
        for (int i = 2; i <= maxx; i++) {
            if (!not_prime[i]) {
                pi.push_back(i);
                phi[i] = i - 1;
            }
            for (int j = 0; j < pi.size(); j++) {
                i64 pri_j = pi[j];
                if (pri_j * i > maxx) {
                    break;
                }
                not_prime[pri_j * i] = true;
                if (i % pri_j == 0) {
                    phi[i * pri_j] = phi[i] * pri_j;
                    break;
                }
                phi[i * pri_j] = phi[i] * phi[pri_j];
            }
        }
    }
};

// 扩展欧几里德
struct Exgcd {
    i64 gcd, x, y;

    Exgcd exgcd(i64 a, i64 b) {
        if (b == 0) {
            return {a, 1, 0};
        }
        Exgcd t = exgcd(b, a % b);
        i64 now_x = t.y;
        i64 now_y = t.x - (a / b) * t.y;
        return {t.gcd, now_x, now_y};
    }

    i64 exgcd2(i64 a, i64 b, i64& x, i64& y) {
        if (b == 0) {
            x = 1;
            y = 0;
            return a;
        }
        i64 g = exgcd2(b, a % b, x, y);
        i64 t = x;
        x = y;
        y = t - a / b * y;
        return g;
    }
};


// 高精度
struct Bignum {
    static const int LEN = 207;
    void clear(int a[]) {
        for (int i = 0; i < LEN; i++) {
            a[i] = 0;
        }
    }

    bool read(int a[]) {
        bool is_zero;
        clear(a);
        string s;
        cin >> s;
        if (s == "0") {
            is_zero = true;
        }
        else {
            is_zero = false;
        }

        int len = s.size();
        for (int i = 0; i < len; i++) {
            a[len - i - 1] = s[i] - '0';
        }
        return is_zero;
    }

    void prt(int a[]) {
        int i;
        for (i = LEN - 1; i >= 1; i--) {
            if (a[i] != 0) {
                break;
            }
        }
        for (; i >= 0; i--) {
            cout << a[i];
        }
    }

    void add(int a[], int b[], int res[]) {
        clear(res);
        for (int i = 0; i < LEN - 1; i++) {
            res[i] += a[i] + b[i];
            if (res[i] >= 10) {
                res[i + 1] += 1;
                res[i] -= 10;
            }
        }
    }

    void sub(int a[], int b[], int res[]) {
        clear(res);
        for (int i = 0; i < LEN - 1; i++) {
            res[i] += a[i] - b[i];
            if (res[i] < 0) {
                res[i + 1] -= 1;
                res[i] += 10;
            }
        }
    }

    void mul_short(int a[], int b, int res[]) {
        clear(res);
        for (int i = 0; i < LEN - 1; i++) {
            res[i] += a[i] * b;
            if (res[i] >= 10) {
                res[i + 1] += res[i] / 10;
                res[i] %= 10;
            }
        }
    }

    void mul(int a[], int b[], int res[]) {
        clear(res);
        for (int i = 0; i < LEN - 1; i++) {
            for (int j = 0; j <= i; j++) {
                res[i] += a[j] * b[i - j];
            }
            if (res[i] >= 10) {
                res[i + 1] += res[i] / 10;
                res[i] %= 10;
            }
        }
    }
    int mod(int a[], int b) {
        int res = 0;
        int i;
        for (i = LEN - 1; i >= 1; i--) {
            if (a[i] != 0) {
                break;
            }
        }
        for (; i >= 0; i--) {
            res = (res * 10 + a[i]) % b;
        }
        return res;
    }
};

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