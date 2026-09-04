// LCA 最近公共祖先
// Dijkstra
// Bellman_Ford
// Bellman_Ford的queue优化 spfa
// 拓扑排序
// 最小生成树
// SCC强连通分量 Tarjan
#include <bits/stdc++.h>
using i64 = long long;
const i64 LLinf = 0x3333ffff3333ffff;
using namespace std;

// SCC强连通分量 Tarjan 
// 1 起始点
struct Tarjan_SCC {
    int n, dfn_cnt, scc_cnt;
    vector<bool> in_stk;
    stack<int> stk;
    vector<int> dfn;
    vector<int> low;
    vector<int> scc_id;
    vector<vector<int>> G;

    vector<int> sum;

    Tarjan_SCC(int n_) {
        n = n_;
        dfn_cnt = 0;
        scc_cnt = 0;
        in_stk.resize(n + 1, false);
        dfn.resize(n + 1, -1);
        low.resize(n + 1, -1);
        scc_id.resize(n + 1, -1);
        G.resize(n + 1, vector<int>());

        sum.resize(n + 1, -1);
    }

    void targan(int u) {
        dfn[u] = low[u] = ++dfn_cnt;
        stk.push(u);
        in_stk[u] = true;
        for (int v : G[u]) {
            if (dfn[v] == -1) {
                targan(v);
                low[u] = min(low[u], low[v]);
            }
            else if (in_stk[v]) {
                low[u] = min(low[u], dfn[v]);
                // low[u] = min(low[u], low[v]);
            }
        }
        if (dfn[u] == low[u]) {
            scc_cnt++;
            int v;
            sum[scc_cnt] = 0;
            do {
                v = stk.top();
                stk.pop();
                in_stk[v] = false;
                scc_id[v] = scc_cnt;
                sum[scc_cnt]++;
            } while (v != u);
        }
    }

    void all() {
        for (int i = 1; i <= n; i++) {
            if (scc_id[i] == -1) {
                targan(i);
            }
        }
    }

    vector<vector<int>> get_deg() {
        vector<vector<int>> ret(scc_cnt + 1);
        for (int i = 1; i <= n; i++) {
            for (int v : G[i]) {
                if (scc_id[i] != scc_id[v]) {
                    ret[scc_id[i]].push_back(scc_id[v]);
                }
            }
        }
        for (int i = 1; i <= scc_cnt; i++) quchong(ret[i]);
        return ret;
    }
    
    vector<vector<int>> get_scc() {
        vector<vector<int>> ret(scc_cnt + 1);
        for (int i = 1; i <= n; i++) {
            ret[scc_id[i]].push_back(i);
        }
        return ret;
    }

    void quchong(vector<int>& v) {
        if (v.empty()) {
            return;
        }
        sort(v.begin(), v.end());
        vector<int> t;
        int ed = v[0];
        t.push_back(ed);
        int sz = v.size();
        for (int i = 1; i < sz; i++) {
            if (v[i] != ed) {
                ed = v[i];
                t.push_back(ed);
            }
        }
        v.swap(t);
    }
};

// 最小生成树
// Kruskal算法，对边长排序，使用并查集合并，修改成下方的形式
// bool Union(int a, int b) {
//     a = find(a); b = find(b);
//     if (a == b) return false;
//     else {
//         if (sz[a] < sz[b]) {
//             fa[a] = b;
//             sz[b] += sz[a];
//         }
//         else {
//             fa[b] = a;
//             sz[a] += sz[b];
//         }
//         return true;
//     }
// }

// 拓扑排序
// 唯一性，自环，排序序列
// string 版本来自 POJ 1094，并且修改返回值为string
struct TOPOSort {
    int n;
    TOPOSort() {};
    TOPOSort(int _n) {
        n = _n;
    }
    int TopoSort(vector<int>& in, vector<vector<int> >& G, int n, vector<int>& ret_vector) {
        queue<int> q;
        // 字典序最大最小，使用 priority_queue
        // for (int i = 0; i < n; i++) {
        for (int i = 1; i <= n; i++) {
            if (in[i] == 0) {
                q.push(i);
            }
        }
        // string ret_string; // 字符串排序序列
        ret_vector.clear(); // 数字排序序列
        bool hasor = false; // 唯一性
        while (!q.empty()) {
            if (q.size() >= 2) {
                hasor = true; // 唯一性
            }
            int tp = q.front();
            q.pop();
            // ret_string.push_back(tp + 'A'); // 排序序列
            ret_vector.push_back(tp); // 排序序列
            for (int ch : G[tp]) {
                in[ch]--;
                if (in[ch] == 0) {
                    q.push(ch);
                }
            }
        }
        // for (int i = 0; i < n; i++) {
        for (int i = 1; i <= n; i++) {
            if (in[i] > 0) {
                // return "circle"; // 自环
                return 0; // 自环
            }
        }
        if (hasor) {
            // return "or"; // 不唯一
            return 2; // 不唯一
        }
        // return ret_string; // 排序序列
        return 1; // 排序序列
    }

    int TopoSort(vector<int>& in, vector<vector<int> >& G, int n) {
        vector<int> ret_vector;
        return TopoSort(in, G, n, ret_vector);
    }
};

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

void test01() {

}

int main() {
    cout << "--------------------------- START ---------------------------\n";
    test01();
    cout << "---------------------------- END ----------------------------\n";
    return 0;
}