#include <bits/stdc++.h>
using i64 = long long;
const i64 LLinf = 0x3333ffff3333ffff;
using namespace std;

const double eps = 1e-5;

struct Point {
    double x, y, z;
    Point() {}
    Point(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}
    Point operator+(const Point &a) const { return Point(x + a.x, y + a.y, z + a.z); }
    Point operator-(const Point &a) const { return Point(x - a.x, y - a.y, z - a.z); }
    Point operator+() const { return Point(+x, +y, +z); }
    Point operator-() const { return Point(-x, -y, -z); }
    Point operator*(const double &k) const { return Point(x * k, y * k, z * k); }
    Point operator/(const double &k) const { return Point(x / k, y / k, z / k); }
    friend Point operator*(const double &k, const Point &a) { return Point(k * a.x, k * a.y, k * a.z); }
    Point &operator+=(const Point &a) { x += a.x; y += a.y; z += a.z; return *this; }
    Point &operator-=(const Point &a) { x -= a.x; y -= a.y; z -= a.z; return *this; }
    Point &operator*=(const double &k) { x *= k; y *= k; z *= k; return *this; }
    Point &operator/=(const double &k) { x /= k; y /= k; z /= k; return *this; }
    double abs() const { return sqrt(x * x + y * y + z * z); }
    double abs2() const { return x * x + y * y + z * z; }
    double dot(const Point &a) const { return x * a.x + y * a.y + z * a.z; }
    Point cross(const Point a) const { return Point(y * a.z - z * a.y, z * a.x - x * a.z, x * a.y - y * a.x); }
    friend ostream &operator<<(ostream &os, const Point &a) { os << "(" << a.x << ", " << a.y << ", " << a.z << ")"; return os; }
};

struct Andrew_ {
    double cross(Point p1, Point p2) {
        return p1.x * p2.y - p1.y * p2.x;
    }
    
    vector<Point> Andrew (vector<Point>& p) {
        sort(p.begin(), p.end());
        vector<Point> v, c;
        for (int i = 0; i < p.size(); i++) {
            while (v.size() >= 2 && cross(v[v.size() - 1] - v[v.size() - 2], p[i] - v[v.size() - 2]) < eps) {
                v.pop_back();
            }
            v.push_back(p[i]);
        }
        for (int i = p.size() - 1; i >= 0; i--) {
            while (c.size() >= 2 && cross(c[c.size() - 1] - c[c.size() - 2], p[i] - c[c.size() - 2]) < eps) {
                c.pop_back();
            }
            c.push_back(p[i]);
        }
        for (int i = 1; i < c.size() - 1; i++) {
            v.push_back(c[i]);
        }
        return v;
    }
};

bool same_line(const Point v1, const Point v2) {
    return v1.y * v2.x == v1.x * v2.y;
}

void test01() {

}

int main() {
    cout << "--------------------------- Si64ARi64 ---------------------------\n";
    test01();
    cout << "---------------------------- END ----------------------------\n";
    return 0;
}