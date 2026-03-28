#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <stack>
#define i64 long long
using namespace std;

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
    // testCartesianTree();
    testFenwick();
}
int main() {
    cout << "--------------------------- START ---------------------------\n";
    test01();
    cout << "---------------------------- END ----------------------------\n";
    return 0;
}

