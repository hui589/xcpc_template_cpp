#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

struct test_case {
    int n;
    vector<int> a, b;
    void init(ifstream& fin) {
        fin >> n;
        a.resize(n + 1);
        b.resize(n + 1);
        for (int i = 1; i <= n; i++) fin >> a[i];
        for (int i = 1; i <= n; i++) fin >> b[i];
    }
    bool same() {
        for (int i = 1; i <= n; i++) {
            if (a[i] != b[i]) {
                return false;
            }
        }
        return true;
    }
};

struct output {
    i64 cost, cnt;
    vector<array<int, 2>> ans;
    void init(ifstream& fin) {
        fin >> cost;
        if (cost == -1) {
            return;
        }
        fin >> cnt;
        ans.resize(cnt);
        for (int i = 0; i < cnt; i++) {
            fin >> ans[i][0] >> ans[i][1];
        }
    }
};

string submit = "K";
string bf = "k_bf";
string random_gener = "KKKrand";
int random_cnt = 100;
int WA_cnt = 2;
int waed_cnt = 0;
string in, out_submit, out_bf;
ofstream wa_case;

int test() {
    out_submit = submit + ".out";
    out_bf = bf + ".out";
    system((".\\" + submit + " < " + in + " > " + out_submit).c_str());
    system((".\\" + bf + " < " + in + " > " + out_bf).c_str());
    ifstream fin(in);
    ifstream fin_submit(out_submit);
    ifstream fin_bf(out_bf);
    int t = 1; fin >> t;
    for (int i = 0; i < t; i++) {
        test_case TC; output SubMit, BF;
        TC.init(fin);
        SubMit.init(fin_submit);
        BF.init(fin_bf);
        // ----- return false -----
        if (BF.cost != SubMit.cost) {
            return false;
        }
        if (SubMit.cost != -1) {
            if (SubMit.cnt > TC.n * 3) {
                cout << "over 3 * n\n";
                return false;
            }
            for (int j = 0; j < SubMit.cnt; j++) {
                swap(TC.a[SubMit.ans[j][0]], TC.b[SubMit.ans[j][1]]);
            }
            if (!TC.same()) {
                cout << "not same of ( a , b )\n";
                return false;
            }
        }
        // ----- return false -----
    }
    return true;
}

void dump(const string& f) {
    ifstream g(f);
    wa_case << g.rdbuf() << "---------------\n";
}

bool duipai_run() {
    if (test()) {
        cout << "AC\n";
    }
    else {
        cout << "--------- Wrong\n";
        wa_case << "======================================\n";
        dump(in); dump(out_submit); dump(out_bf);
        if (++waed_cnt >= WA_cnt) {
            return true;
        }
    }
    return false;
}

int main() {
    // ========================================== Compile cpp
    system(("g++ " + submit + ".cpp -o " + submit +
            " && g++ " + bf + ".cpp -o " + bf +
            " && g++ " + random_gener + ".cpp -o " + random_gener).c_str());
    cout << "================ ---- Start ---- ================\n";
    wa_case.open(submit + "_wa.out");
    vector<string> real_case = {"k.in"};    // -----------------
    for (string s : real_case) {            // -----------------
        cout << s << "\t : ";               // -----------------
        in = s;                             // -----------------
        if (duipai_run()) return 0;         // -----------------
    }                                       // -----------------
    cout << "================ ---- Random --- ================\n";
    for (int i = 1; i <= random_cnt; i++) {
        cout << i << "\t : ";
        string gener = submit + "_Random.in";
        string cmdto_gener_info = "";
        // |=|=|=|=|=|=|=|=|=|=|=|=|=| what rand
        int what_rand = (i > min(20, random_cnt / 2));
        string to_gener_info = submit + "_info.in";
        ofstream info(to_gener_info);
        info << what_rand << "\n";
        info.close();
        cmdto_gener_info = " < " +  to_gener_info;
        // |=|=|=|=|=|=|=|=|=|=|=|=|=|what rand
        system((".\\" + random_gener + cmdto_gener_info + " > " + gener).c_str());
        in = gener;
        if (duipai_run()) return 0;
    }
    cout << "==========================\nAll Accept\n";
    return 0;
}