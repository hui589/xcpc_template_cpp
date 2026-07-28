#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

struct AC_auto_m {
    static const int N = 1e5;
    int son[N][26];
    int pass[N];
    int ed[N];
    int fail[N];
    int idx;
    void insert(const string& s) {
        int cur = 0;
        for (int i = 0; i < s.size(); i++) {
            int c = s[i] - 'a';
            if (son[cur][c] == 0) {
                son[cur][c] = ++idx;
            }
            cur = son[cur][c];
            pass[cur]++;
        }
        ed[cur]++;
    }

    void build_fail() {
        queue<int> q;
        for (int i = 0; i < 26; i++) {
            if (son[0][i] != 0) {
                fail[son[0][i]] = 0;
                q.push(son[0][i]);
            }
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < 26; i++) {
                if (son[u][i] != 0) {
                    fail[son[u][i]] = son[fail[u]][i];
                    q.push(son[u][i]);
                }
                else {
                    // fail[son[u][i]] = son[fail[u]][i];
                    son[u][i] = son[fail[u]][i];
                }
            }
        }
    }

    int query(const string& s) {
        int ans = 0, cur = 0;
        for (int i = 0; i < s.size(); i++) {
            cur = son[cur][s[i] - 'a'];
            for (int j = cur; j && ed[j] != -1; j = fail[j]) {
                ans += ed[j];
                ed[j] = -1;
            }
        }
        return ans;
    }
};

struct Tire {
    static const int N = 1e5;
    int son[N][11];
    int end[N];
    int pass[N];
    int idx = 0;
    void clear() {
        memset(son, 0, sizeof(son));
        memset(end, 0, sizeof(end));
        memset(pass, 0, sizeof(pass));
        idx = 0;
    }
    bool insert(const string& s) {
        int cur = 0;
        int len = s.size();
        for (int i = 0; i < len; i++) {
            int c = s[i] - '0';
            if (!son[cur][c]) {
                idx++;
                son[cur][c] = idx;
            }
            else {
            }
            cur = son[cur][c];
            if (i == len - 1) {
                if (pass[cur]) {
                    return false;
                }
            }
            pass[cur]++;
            if (end[cur]) {
                return false;
            }
        }
        end[cur]++;
        return true;
    }

    // void insert(const string& s) {
    //     int cur = 0;
    //     for (int i = 0; i < s.size(); i++) {
    //         int c = s[i] - 'a';
    //         if (!son[cur][c]) {
    //             son[cur][c] = ++idx;
    //         }
    //         cur = son[cur][c];
    //         pass[cur]++;
    //     }
    // }
};

struct Z_fun {
    vector<int> Z_function(const string& s) {
        int n = s.size();
        vector<int> z(n);
        for (int i = 1, l = 0, r = 0; i < n; i++) {
            if (i <= r && z[i - l] < r - i + 1) {
                z[i] = z[i - l];
            }
            else {
                z[i] = std::max(0, r - i + 1);
                while (i + z[i] < n && s[i + z[i]] == s[z[i]]) {
                    z[i]++;
                }
            }
            if (i + z[i] - 1 > r) {
                r = i + z[i] - 1;
                l = i;
            }
        }
        return z;
    }

    vector<int> find_occurrences(const string& target, const string& text) {
        string cur = target + "#" + text;
        int sz1 = target.size(), sz2 = text.size();
        vector<int> res;
        vector<int> z = Z_function(cur);
        for (int i = sz1 + 1; i <= sz1 + sz2; i++) {
            if (z[i] == sz1) {
                res.push_back(i - sz1);
            }
        }
        return res;
    }
};

struct KMP {
    vector<int> prefix(const string& s) {
        int n = s.size();
        vector<int> v(n, 0);
        for (int i = 1; i < n; i++) {
            int j = v[i - 1];
            while (j > 0 && s[i] != s[j]) {
                j = v[j - 1];
            }
            if (s[i] == s[j]) {
                v[i] = j + 1;
            }
        }
        return v;
    }

    vector<int> find_occurences(const string& target, const string& text) {
        string cur = target + '$' + text;
        int sz1 = target.size(), sz2 = text.size();
        vector<int> idx;
        vector<int> pre = prefix(cur);
        for (int i = sz1 + 1; i <= sz1 + sz2; i++) {
            if (pre[i] == sz1) {
                idx.push_back(i - sz1 * 2);
            }
        }
        return idx;
    }
};

struct Manacher {
    vector<int> t;
    Manacher() {}
    Manacher(int n_) {
        t.resize(n_ + 1);
    }

    string initstr(string& s) {
        string ret = "#";
        for (int i = 0; i < s.size(); i++) {
            ret += s[i];
            ret += "#";
        }
        return ret;
    }

    void manacher(string& s) {
        s = initstr(s);
        int idx = 0, mx = -1;
        for (auto x : t) {
            x = 0;
        }
        for (int i = 0; i < s.size(); i++) {
            if (i > mx) {
                t[i] = 1;
            }
            else {
                t[i] = min(t[2 * idx - i], mx - i + 1);
            }
            while (i - t[i] >= 0 && i + t[i] < s.size() && s[i - t[i]] == s[i + t[i]]) {
                t[i]++;
            }
            t[i]--;
            if (i + t[i] > mx) {
                mx = i + t[i];
                idx = i;
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