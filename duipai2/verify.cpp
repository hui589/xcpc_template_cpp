#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

string mycode       = "duipai";
string baoli        = "baoli";
string random_gener = "gener";
string in;
int random_cnt      = 100;

int main() {
    cin >> mycode >> baoli >> random_gener;
    in = "random_t_1.in";
    for (int i = 1; i <= random_cnt; i++) {
        system(("./" + random_gener + " > " + in).c_str());
        system(("./" + mycode + " < " + in + " > mycode.out").c_str());
        system(("./" + baoli  + " < " + in + " > baoli.out").c_str());
        int res = system("cmp -s mycode.out baoli.out");
        if (res == 1) {
            cout << "wrong on " << i << "\n";
            break;
        }
        else if (res == 2) {
            cout << "badbad on " << i << "\n";
            break;
        }
        else {
            cout << "test " << i << " AC\n";
        }
    }
    return 0;
}