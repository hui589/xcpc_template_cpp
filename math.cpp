#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
// 伽马常数
const double gama = 0.57721566490153286;

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