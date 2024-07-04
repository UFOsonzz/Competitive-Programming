#include <bits/stdc++.h>
using namespace std;
using dt = long double;
struct point {
    dt x, y;
    point() {}
    point(dt x, dt y) :
        x(x), y(y) {}
    point operator+=(const point& t) {
        x += t.x;
        y += t.y;
        return *this;
    }
    point operator-=(const point& t) {
        x -= t.x;
        y -= t.y;
        return *this;
    }
    point operator*=(dt t) {
        x *= t;
        y *= t;
        return *this;
    }point operator/=(dt t) {
        x /= t;
        y /= t;
        return *this;
    }
    point operator+(const point& t) const {
        return point(*this) += t;
    }point operator-(const point& t) const {
        return point(*this) -= t;
    }point operator*(dt t) const {
        return point(*this) *= t;
    }point operator/(dt t) const {
        return point(*this) /= t;
    }
    bool operator<(const point& t) const {
        return x < t.x;
    }
};

point operator*(dt t, point u) {
    return u * t;
}

dt dot(point u, point v) {
    return u.x*v.x + u.y*v.y;
}

dt cross(point u, point v) {
    return u.x*v.y - u.y*v.x;
}

dt orient(point a, point b, point c) {
    return cross(b-a, c-a);
}

bool indisk(point a, point b, point p) {
    return dot(a-p, b-p) <= 0;
}

bool onsegment(point a, point b, point p) {
    return cross(a-p, b-p) == 0 && indisk(a, b, p);
}
struct line {
    point v;
    dt c;
    line(point v, dt c) : v(v), c(c) {}
    line(dt a, dt b, dt c) : v({b, -a}), c(c) {}
    line(point p, point q) : v(q-p), c(cross(v,p)) {}
};

bool line_inter(line u, line v, point& out) {
    dt tmp = cross(u.v, v.v);
    if (tmp == 0) return false;
    out = (u.c*v.v - v.c*u.v) / tmp;
    return true;
}

bool segment_inter(point a1, point d1, point a2, point d2, point& out) {
    if (line_inter(line(a1, d1), line(a2, d2), out) && indisk(a1, d1, out) && indisk(a2, d2, out))
        return true;
    return false;
}

using Segment = pair<point, point>;
#define fi first
#define se second

int n;
Segment seg[33];
map<point, bool> on_seg[33], cir, ver;


int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        point A, B;
        cin >> A.x >> A.y >> B.x >> B.y;
        seg[i] = {A, B};
        cir[A] = cir[B] = ver[A] = ver[B] = 1;
        on_seg[i][A] = on_seg[i][B] = 1;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            point out;
            if (segment_inter(seg[i].fi, seg[i].se, seg[j].fi, seg[j].se, out)) {
                on_seg[i][out] = on_seg[j][out] = 1;
                ver[out] = 1;
            }
        }
    }
    int V = ver.size(), E = cir.size();
    for (int i = 1; i <= n; i++) {
        E += on_seg[i].size() - 1;
    }
    cout << E - V + 2;
}
