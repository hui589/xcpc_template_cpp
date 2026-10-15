#include <bits/stdc++.h>
using i64 = long long;
using namespace std;

// hash
struct my_hash {
    struct custom_hash {
        static uint64_t splitmix64(uint64_t x) {
            x += 0x9e3779b97f4a7c15;
            x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
            x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
            return x ^ (x >> 31);
        }
        size_t operator()(uint64_t x) const {
            static const uint64_t SEED = std::chrono::steady_clock::now().time_since_epoch().count();
            return splitmix64(x + SEED);
        };
    };
    template <int s>
    struct XorHash {
        // s 代表 位移
        size_t operator()(uint64_t x) const {
            return (size_t)((uint64_t)x ^ ((uint64_t)x >> s));
        } 
    };
    unordered_map<int, int, XorHash<8>> map1;
    unordered_set<int, int, XorHash<8>> set1;
    unordered_map<int, int, custom_hash> map2;
    unordered_set<int, int, custom_hash> set2;
};

void test01() {

}

int main() {
    cout << "--------------------------- START ---------------------------\n";
    test01();
    cout << "---------------------------- END ----------------------------\n";
    return 0;
}