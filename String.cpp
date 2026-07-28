#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

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