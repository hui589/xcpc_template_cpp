// 树状数组
// 笛卡尔树
// 并查集
// 线段树
// st表，稀疏表
#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

// st表，稀疏表
// 1_base 起始下标
template <typename T>
struct SparseTable {
    int n;
    vector<T> a;
    vector<vector<T>> MAX;
    vector<vector<T>> MIN;
    // vector<vector<T>> GCD;
#define qMAX 1
#define qMIN 2
// #define qGCD 3
    SparseTable() {}
    SparseTable(int _n) {
        n = _n;
        int lg = __lg(n);
        a.resize(n + 1);
        MAX.resize(n + 1, vector<T>(lg + 1));
        MIN.resize(n + 1, vector<T>(lg + 1));
        // GCD.resize(n + 1, vector<T>(lg + 1));
    }

    void build() {
        int lg = __lg(n);
        for (int i = 1; i <= n; i++) {
            MAX[i][0] = a[i];
            MIN[i][0] = a[i];
            // GCD[i][0] = a[i];
        }
        for (int j = 1; j <= lg; j++) {
            for (int i = 1; i <= (n - (1 << j) + 1); i++) {
                MAX[i][j] = max(MAX[i][j - 1], MAX[i + (1 << (j - 1))][j - 1]);
                MIN[i][j] = min(MIN[i][j - 1], MIN[i + (1 << (j - 1))][j - 1]);
                // GCD[i][j] = __gcd(GCD[i][j - 1], GCD[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    T query(int l, int r, int q) {
        if (l > r) {
            return 0; // MAX, GCD
            // return ((~0 << 2) >> 2); // int MIN
            // return ((~0LL << 2) >> 2); // long long MIN
        }
        int lg = __lg(r - l + 1);
        if (q == qMAX) {
            return max(MAX[l][lg], MAX[r - (1 << lg) + 1][lg]);
        }
        else if (q == qMIN) {
            return min(MIN[l][lg], MIN[r - (1 << lg) + 1][lg]);
        }
        // else if (q == qGCD) {
        //     return __gcd(GCD[l][lg], GCD[r - (1 << lg) + 1][lg]);
        // }
        return 0;
    }
};

// 线段树
// 简化参数成员函数为 1_base 起始下标
// 可手动变为 0_base 起始下标
template <typename T>
struct SegmentTree {
    #define lc (node << 1)
    #define rc ((node << 1) | 1)
    #define mid ((l + r) >> 1)
    int n_;
    vector<T> a;
    // vector<T> MAX;
    vector<T> SUM;
    // vector<T> GCD;
    vector<T> lazy;

    SegmentTree() {}
    SegmentTree(int __n__) {
        n_ = __n__;
        a.resize(n_ + 1);
        // MAX.resize(n_ * 4 + 1);
        SUM.resize(n_ * 4 + 1);
        // GCD.resize(n_ * 4 + 1);
        lazy.resize(n_ * 4 + 1);
    }

    void build() { build(1, 1, n_); }
    void update(int idx, T val) { update(1, 1, n_, idx, val); }
    void update_range(int ul, int ur, T val) { update_range(1, 1, n_, ul, ur, val); }
    T query(int ql, int qr) { return query(1, 1, n_, ql, qr); }

    void pushup(int node) {
        // MAX[node] = max(MAX[lc], MAX[rc]);
        SUM[node] = SUM[lc] + SUM[rc];
        // GCD[node] = __gcd(GCD[lc], GCD[rc]);
    }
    void pushdown(int node, int l, int r) {
        if (l == r) {
            return;
        }
        if (lazy[node] != 0) {
            SUM[lc] += lazy[node] * (mid - l + 1);
            SUM[rc] += lazy[node] * (r - mid); // 不需要 -1
            lazy[lc] += lazy[node];
            lazy[rc] += lazy[node];
            lazy[node] = 0;
        }
    }
    void build(int node, int l, int r) {
        if (l == r) {
            // MAX[node] = a[l];
            SUM[node] = a[l];
            // GCD[node] = a[l];
            return;
        }
        build(lc, l, mid);
        build(rc, mid + 1, r);
        pushup(node);
    }
    void update(int node, int l, int r, int idx, T val) {
        if (r < idx || l > idx) {
            return;
        }
        if (l == r && l == idx) {
            // MAX[node] = val;
            SUM[node] = val;
            // GCD[node] = val;
            return;
        }
        update(lc, l, mid, idx, val);
        update(rc, mid + 1, r, idx, val);
        pushup(node);
    }
    void update_range(int node, int l, int r, int ul, int ur, T val) {
        if (ur < l || r < ul) {
            return;
        }
        if (ul <= l && r <= ur) {
            SUM[node] += val * (r - l + 1);
            lazy[node] += val;
            return;
        }
        pushdown(node, l, r);
        update_range(lc, l, mid, ul, ur, val);
        update_range(rc, mid + 1, r, ul, ur, val);
        pushup(node);
    }
    T query(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            // return MAX[node];
            return SUM[node];
            // return GCD[node];
        }
        pushdown(node, l, r);
        T L = query(lc, l, mid, ql, qr);
        T R = query(rc, mid + 1, r, ql, qr);
        // return max(L, R);
        return L + R;
        // return __gcd(L, R);
    }
};

// 并查集
struct DSU {
    int n;
    vector<int> fa, sz;
    DSU(int _n) {
        n = _n;
        fa.resize(n + 1);
        sz.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            fa[i] = i;
            sz[i] = 1;
        }
    }
    // int fa[N], sz[N];
    int find(int x) {
        if (x == fa[x]) {
            return x;
        }
        else {
            return fa[x] = find(fa[x]);
        }
    }
    
    void Union(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            if (sz[a] < sz[b]) {
                fa[a] = b;
                sz[b] += sz[a];
            }
            else {
                fa[b] = a;
                sz[a] += sz[b];
            }
        }
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

}

int main() {
    cout << "--------------------------- START ---------------------------\n";
    test01();
    cout << "---------------------------- END ----------------------------\n";
    return 0;
}