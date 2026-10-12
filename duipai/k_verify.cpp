#include <bits/stdc++.h>
using i64 = long long;
using namespace std;
string submit =       "K";
string bf =           "k_bf";
string random_gener = "KKKrand";
int random_cnt =       100;
// int WA_cnt = 2;
// int waed_cnt = 0;
struct test_case {
    void init(ifstream& fin) {
    }
};
struct output {
    void init(ifstream& fin) {
    }
};
string in, out_submit, out_bf;
// ofstream wa_case;
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
    }
    return true;
}
// void dump(const string& f) {
//     ifstream g(f);
//     wa_case << g.rdbuf() << "---------------\n";
// }
bool duipai_run() {
    if (test()) {
        cout << "AC\n";
    } else {
        cout << "--------- Wrong\n";
        return true;
        // wa_case << "======================================\n";
        // dump(in); dump(out_submit); dump(out_bf);
        // if (++waed_cnt >= WA_cnt) {
        //     return true;
        // }
    }
    return false;
}
int main() {
    // ========================================== Compile cpp
    system(("g++ " + submit + ".cpp -o " + submit +
            " && g++ " + bf + ".cpp -o " + bf +
            " && g++ " + random_gener + ".cpp -o " + random_gener).c_str());
    cout << "================ ---- Start ---- ================\n";
    // wa_case.open(submit + "_wa.out");
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
        // string cmdto_gener_info = "";
        // |=|=|=|=|=|=|=|=|=|=|=|=|=| what rand // + cmdto_gener_info
        system((".\\" + random_gener + " > " + gener).c_str());
        in = gener;
        if (duipai_run()) return 0;
    }
    cout << "==========================\nAll Accept\n";
    return 0;
}