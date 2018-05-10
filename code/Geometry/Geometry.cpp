struct PT {
    double x, y;
    PT(double x, double y) : x(x), y(y) {}
    PT operator + (const PT &p) { return PT(x + p.x, y + p.y); }
    PT operator - (const PT &p) { return PT(x - p.x, y - p.y); }
    PT operator * (double c) { return PT(x * c, y * c); }
    PT operator / (double c) { return PT(x / c, y / c); }
}

double dot(PT p, PT q) { return p.x * q.x + p.y * q.y; }
double dist2(PT p, PT q) { return dot(p - q, p - q); }
double cross(PT p, PT q) { return p.x * q.y - p.y * q.x; }