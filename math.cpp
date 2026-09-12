// 阶乘，阶乘逆元，快速幂，组合数
// MEX函数
// nim游戏
// 线性基
// 模拟退火
// 伽马常数
// 矩阵计算，矩阵快速幂
// 莫比乌斯反演
// 欧拉函数
// 扩展欧几里德
#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
const double gama = 0.57721566490153286; // 伽马常数


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

// 矩阵计算，矩阵快速幂
struct Matrix {
    int n;
    int mod = 998244353;
	vector<vector<i64>> mat;
	Matrix(int n1) {
		n = n1;
		mat.resize(n, vector<i64>(n));
	}
    void diag(i64 val) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    mat[i][j] = 0;
                }
                else {
                    mat[i][j] = val;
                }
            }
        }
    }
	Matrix operator * (const Matrix& m) const {
		Matrix ret(n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					ret.mat[i][j] = (ret.mat[i][j] + mat[i][k] * m.mat[k][j]) % mod;
				}
			}
		}
		return ret;
	}
    Matrix operator * (const i64 k) const {
        Matrix ret(n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				ret.mat[i][j] = mat[i][j] * k;
			}
		}
		return ret;
    }
    Matrix operator + (const Matrix& m) const {
		Matrix ret(n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
                ret.mat[i][j] = mat[i][j] + m.mat[i][j];
			}
		}
		return ret;
	}
    Matrix operator + (const i64 k) const {
        Matrix ret(n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				ret.mat[i][j] = mat[i][j] + k;
			}
		}
		return ret;
    }
    Matrix powD(const Matrix& ma, int x) {
        Matrix m = ma;
        Matrix ret(m.n);
        ret.diag(1);
        while (x) {
            if (x & 1) {
                ret = ret * m;
            }
            m = m * m;
            x >>= 1;
        }
        return ret;
    }
    void qaq(vector<i64> v) {
        int sz = v.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (n * i + j < sz) {
                    mat[i][j] = v[n * i + j];
                }
            }
        }
    }
    //
    void prt(Matrix A, string s) {
        cout << "--------------- " << s << " ---------------\n";
        for (int i = 0; i < A.n; i++) {
            for (int j = 0; j < A.n; j++) {
                cout << A.mat[i][j] << " \n"[j == A.n - 1];
            }
        }
    }
};

// 模拟退火
struct simulate {
    double func(double x, double y) {
        return x + y;
    }
    void SimulateAnneal() {
        srand(time(0));
        double T = 3e3;
        double end_T = 1e-15;
        double d_T = 0.996;
        double ans_x = 0;
        double ans_y = 0;
        double f = func(ans_x, ans_y);
        while (T > end_T) {
            double nx = ans_x + T * (2 * rand() - RAND_MAX);
            double ny = ans_y + T * (2 * rand() - RAND_MAX);
            double df = func(nx, ny);
            if (df <= f) {
                ans_x = nx;
                ans_y = ny;
                f = df;
            }
            else if (exp((f - df) / T) * RAND_MAX > rand()) {
                ans_x = nx;
                ans_y = ny;
            }
            T *= d_T;
        }
    }
};

// 线性基
template <typename T>
struct Linear {
    vector<T> b;
    int sz;
    Linear() { sz = 32; }
    Linear(int _sz) {
        sz = _sz;
        b.resize(sz);
    }

    void insert(T x) {
        for (int i = sz - 1; i >= 0; i--) {
            if (!(x >> i) & 1) {
                continue;
            }
            if (!b[i]) {
                b[i] = x;
                break;
            }
            x ^= b[i];
        }
    }
};

// ### nim游戏
// #### 1.阶梯nim
// 偶数层无效，只需查看奇数层nim和
// #### 2.反nim游戏(最后一个拿的玩家失败)
// 奇异局势Y：num-sum = 0; 非奇异局势N：num-sum0 != 0
// 定义：第i堆为充裕堆：a[i] > 1；第i堆为孤单堆：a[i] = 1，充裕堆的数量cnt
// NO, NI, N2：非奇异局势下，cnt 分别为0,1, >=2
// Y0, Y1, Y2：奇异局势下，cnt 分别为0,1, >=2
// 显然：N能转移到Y,也能转移到N；只能转移到N
// 1、N0必败，Y0必胜
// 2、N1必胜，N1可以转移到N0
// 3、N2必胜，Y2必败
// Y2只能转移到N1和N2：若Y2转移到N1（必胜态），则Y2败；若Y2转移到N2，
// N2只需要转回到Y2即可,Y1不可能达到），直到Y2只能转移到N1为止,所以Y2必败，N2必胜。
// 必胜态：Y0, N1, N2
// 必败态：NO, Y2

// SG_MEX
// 不包含在集合 S 中的最小非负整数
struct MEX {
int mex(vector<int> &v) {
    sort(v.begin(), v.end());
    int ans = 0;
    for(int i = 0; i < v.size(); i++) {
        if(v[i] == ans) ans++;
    }
    return ans;
}
};

// fact, inv_fact, pow_mod, C(n, k)
// 阶乘，阶乘逆元，快速幂，组合数
struct FACT_struct {
const int N = 100009;
const int mod = 998244353;
// i64 fact[N], inv_fact[N];
vector<i64> fact, inv_fact;
FACT_struct() {
    fact.resize(N);
    inv_fact.resize(N);
}
i64 pow_mod(i64 a, i64 x, i64 m) {
    i64 ret = 1;
    while (x) {
        if (x & 1) {
            ret = ret * a % m;
        }
        a = a * a % m;
        x >>= 1;
    }
    return ret;
}
i64 C(int n, int k, int m) {
    if (k > n || k < 0) {
        return 0;
    }
    else {
        return (fact[n] * inv_fact[k] % mod) * inv_fact[n - k] % mod;
    }
}
void init_fact_inv(int n) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = fact[i - 1] * i % mod;
    }
    inv_fact[n] = pow_mod(fact[n], mod - 2, mod);
    for (int i = n - 1; i >= 0; i--) {
        inv_fact[i] = inv_fact[i + 1] * (i + 1) % mod;
    }
}
};
void test_fact_inv_C_n_m() {
    cout << "-------------------- test_fact_inv_C_n_m --------------------\n";
    FACT_struct T;
    T.init_fact_inv(T.N - 1);
    for (int i = 0; i <= 10; i++) {
        cout << i << "! = " << T.fact[i] << '\n';
    }
    auto C = [&](int x, int y) -> void {
        cout << "C(" << x << ", " << y << ") = " << T.C(x, y, T.mod) << '\n';
    };
    for (int i = 0, n = 7; i <= n; i++) {
        C(n, i);
    }
}

void test01() {

}

int main() {
    cout << "--------------------------- START ---------------------------\n";
    test01();
    cout << "---------------------------- END ----------------------------\n";
    return 0;
}