#include <bits/stdc++.h>
using i64 = long long;
const i64 LLinf = 0x3333ffff3333ffff;
using namespace std;

// Bellman_Ford的queue优化 spfa 判断负环，0是超级源点，其他点位 1-n
struct SPFA {
struct node {
    int p;
    i64 d;
};
// n 不包括超级源点
bool spfa(int n, int st, vector<vector<node>>& G) {
    vector<int> cnt(n + 1, 0);
    vector<i64> dis(n + 1, LLinf);
    vector<bool> vis(n + 1, false);
    queue<int> q;
    q.push(st);
    dis[st] = 0;
    cnt[st] = -1; // 超级源点为 -1, 普通点为 0
    // 上面限制了cnt[x]的最大值
    // 其实源点多小都没问题 -10， -100，只需要保证下面return true的部分一定是正确的就行
    vis[st] = true;
    while (!q.empty()) {
        int tp = q.front();
        q.pop();
        vis[tp] = false;
        for (auto [v, w] : G[tp]) {
            if (dis[v] > dis[tp] + w) {
                dis[v] = dis[tp] + w;
                cnt[v] = cnt[tp] + 1;
                if (cnt[v] >= n) {
                    return true;
                }
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
    }
    return false;
}
};

// Bellman_Ford 判断负环，0是超级源点，其他点位 1-n
struct BellmanFord {
struct node {
    int p;
    i64 d;
};
// n 不包括超级源点
bool Bellman_Ford(int n, int st, vector<vector<node>>& G) {
    vector<i64> dis(n + 1, LLinf);
    dis[st] = 0; 
    bool flag;
    for (int cnt = 1; cnt <= n; cnt++) {
        flag = false;
        // 
        for (int i = 0; i <= n; i++) {
            if (dis[i] == LLinf) {
                continue;
            }
            for (auto [ch, d] : G[i]) {
                if (dis[i] + d < dis[ch]) {
                    dis[ch] = dis[i] + d;
                    flag = true;
                }
            }
        }
        if (!flag) {
            break;
        }
    }
    return flag;
}

};

// 最短路O(mlogm), 1-n 索引
// m是边的数量
struct Dijkstra {
struct node {
    int p;
    i64 d;
    bool operator < (const node& n1) const {
        return d > n1.d;
    }
};

vector<i64> dijkstra(vector<vector<node>>& G, int st) {
    int n = G.size();
    vector<i64> dis(n, LLinf);
    vector<bool> vis(n, false);
    dis[st] = 0;
    priority_queue<node> pq;
    pq.push({st, 0});
    while (!pq.empty()) {
        auto [tp, d] = pq.top();
        pq.pop();
        if (vis[tp]) {
            continue;
        }
        else {
            vis[tp] = true;
        }
        for (auto [ch, len] : G[tp]) {
            if (len + d < dis[ch]) {
                dis[ch] = len + d;
                pq.push({ch, dis[ch]});
            }
        }
    }
    return dis;
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

// LCA
template<typename T>
struct LCA_struct {
// int N = 100009;
// int LOGN = 20;
// int lgn, dep[N], mx[N][LOGN], mn[N][LOGN], up[N][LOGN];
int lgn;
vector<int> dep;
vector<vector<T>> mx, mn;
vector<vector<int>> up;
void dfs(int node, int fa, vector<vector<int>>& G) {
    dep[node] = dep[fa] + 1;
    for (int i = 1; i <= lgn; i++) {
        // mx[node][i] = max(mx[node][i - 1], mx[up[node][i - 1]][i - 1]);
        // mn[node][i] = min(mn[node][i - 1], mn[up[node][i - 1]][i - 1]);
        up[node][i] = up[up[node][i - 1]][i - 1];
    }
    for (auto ch : G[node]) {
        if (ch != fa) {
            // mx[ch][0] = dis;
            // mn[ch][0] = dis;
            up[ch][0] = node;
            dfs(ch, node, G);
        }
    }
}

int LCA(int u, int v) {
    if (dep[u] < dep[v]) {
        swap(u, v);
    }
    for (int i = lgn; i >= 0; i--) {
        if (dep[up[u][i]] >= dep[v]) {
            u = up[u][i];
        }
    }
    if (u == v) {
        return u;
    }
    for (int i = lgn; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}
};

// 笛卡尔树，1-n 索引，1-n 节点，O(n)
// 标记1 : 可以修改比较符号
// 标记2 : 只考虑前缀的话在循环内部修改
template<typename T>
struct CartesianTree {
    int n;
    vector<T> l, r, a;

    CartesianTree(int siz) {
        n = siz;
        l.resize(n + 1);
        r.resize(n + 1);
        a.resize(n + 1);
    }

    void build() {
        stack<int> stk;
        int last;
        for (int i = 1; i <= n; i++) {
            last = -1;
            while (!stk.empty() && a[i] < a[stk.top()]) { // 11111
                last = stk.top();
                stk.pop();
            }
            // 22222
            if (!stk.empty()) {
                r[stk.top()] = i;
            }
            if (last != -1) {
                l[i] = last;
            }
            stk.push(i);
        }
    }
};
void testCartesianTree() {
    cout << "--------------------- testCartesianTree ---------------------\n";
    int n = 4;
    CartesianTree<i64> ct(n);
    vector<int> in(n + 1);
    in[1] = 2;
    in[2] = 4;
    in[3] = 3;
    in[4] = 1;
    for (int i = 1; i <= n; i++) {
        ct.a[i] = in[i];
    }
    ct.build();
}

// 树状数组，1-n 索引，O(logn)
template<typename T>
struct Fenwick {
    int n;
    vector<T> t;
    Fenwick(int n_) {
        n = n_;
        t.resize(n_ + 1);
    }

    void add(int idx, T val) {
        while (idx <= n) {
            t[idx] += val;
            idx += idx & -idx;
        }
    }

    T sum(int idx) {
        T ret = 0;
        while (idx >= 1) {
            ret += t[idx];
            idx -= idx & -idx;
        }
        return ret;
    }

    T RangeSum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    // 查找前缀和 <= k 的最大的下标
    // 查找前缀和 >= k 的最小下标为 select(k - 1) + 1
    int select(const T& k) {
        int x = 0;
        T cur = 0;
        for (int i = 1 << __lg(n); i; i /= 2) {
            if (x + i <= n && cur + t[x + i] <= k) {
                x += i;
                cur += t[x];
            }
        }
        return x;
    }
};
void testFenwick() {
    cout << "------------------------ testFenwick ------------------------\n";
    int n = 5;
    vector<int> a(n + 1);
    Fenwick<i64> f(n);
    for (int i = 1; i <= n; i++) {
        a[i] = rand() % 10;
        cout << a[i] << " \n"[i == n];
        f.add(i, a[i]);
    }
    // for (int i = 1; i <= n; i++) {
    //     cout << "a["<<i<<"] = " << f.RangeSum(i, i) << '\n';
    // }
    // auto func = [&](int l, int r) -> void {
    //     cout << "sum(" << l << ", " << r << ") = " << f.RangeSum(l, r) << '\n';
    // };
    // func(3, 5);
    // func(2, 5);
    // func(1, 5);
    // auto func_select = [&](int k) -> void {
    //     int idx = f.select(k);
    //     cout << "sum " << idx << " <= " << k << "\n";
    // };
    // func_select(0);
    // func_select(1);
    // func_select(2);
    // func_select(12);
    // func_select(21);
    // func_select(22);
    auto func_select_2 = [&](int k) -> void {
        int idx = f.select(k - 1) + 1;
        cout << "sum " << idx << " <= " << k << "\n";
    };
    func_select_2(0);
    func_select_2(1);
    func_select_2(2);
    func_select_2(12);
    func_select_2(21);
    func_select_2(22);
}

void test01() {
    testCartesianTree();
    testFenwick();
    test_fact_inv_C_n_m();
}
int main() {
    cout << "--------------------------- START ---------------------------\n";
    test01();
    cout << "---------------------------- END ----------------------------\n";
    return 0;
}

