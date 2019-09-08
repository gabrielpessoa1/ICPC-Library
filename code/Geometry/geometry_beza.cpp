#define x first
#define y second
const double inf = 1e100, eps = 1e-9;
const double PI = acos(-1.0L);

int cmp (double a, double b = 0) {
  if (abs(a-b) < eps) return 0;
  return (a < b) ? -1 : +1;
}

struct PT {
  double x, y;
  PT(double x = 0, double y = 0) : x(x), y(y) {}
  PT operator + (const PT &p) const { return PT(x+p.x, y+p.y); }
  PT operator - (const PT &p) const { return PT(x-p.x, y-p.y); }
  PT operator * (double c) const { return PT(x*c, y*c); }
  PT operator / (double c) const { return PT(x/c, y/c); }
  
  bool operator <(const PT &p) const {
    if(cmp(x, p.x) != 0) return x < p.x;
    return cmp(y, p.y) < 0;
  }
  bool operator ==(const PT &p) const {
    return (cmp(x, p.x) || cmp(y, p.y)) == 0;
  }
  bool operator != (const PT &p) const {
    return !(p == *this);
  }
};

double dot (PT p, PT q) { return p.x * q.x + p.y*q.y; }
double cross (PT p, PT q) { return p.x * q.y - p.y*q.x; }
double dist2 (PT p, PT q = PT(0, 0)) { return dot(p-q, p-q); }
double dist (PT p, PT q) { return hypot(p.x-q.x, p.y-q.y); }
double norm (PT p) { return hypot(p.x, p.y); }
PT normalize (PT p) { return p/hypot(p.x, p.y); }
double angle (PT p, PT q) { return atan2(cross(p, q), dot(p, q)); }
double angle (PT p) { return atan2(p.y, p.x); }
double polarAngle (PT p) {
  double a = atan2(p.y,p.x);
  return a < 0 ? a + 2*PI : a;
}

// - p.y*sen(+90), p.x*sen(+90)
PT rotateCCW90 (PT p) { return PT(-p.y, p.x); }
// - p.y*sen(-90), p.x*sen(-90)
PT rotateCW90 (PT p) { return PT(p.y, -p.x); }

PT rotateCCW (PT p, double t) {
  return PT(p.x*cos(t)-p.y*sin(t), p.x*sin(t)+p.y*cos(t));
}

// !!! PT (int, int)
typedef pair<PT, int> Line;
PT getDir (PT a, PT b) {
  if (a.x == b.x) return PT(0, 1);
  if (a.y == b.y) return PT(1, 0);
  int dx = b.x-a.x;
  int dy = b.y-a.y;
  int g = __gcd(abs(dx), abs(dy));
  if (dx < 0) g = -g;
  return PT(dx/g, dy/g);
}

Line getLine (PT a, PT b) {
  PT dir = getDir(a, b);
  return {dir, cross(dir, a)};
}

// a.b = |a| cost * |b|
PT projectPointLine (PT a, PT b, PT c) {
  return a + (b-a) * dot(b-a, c-a)/dot(b-a, b-a);
}

PT reflectPointLine (PT a, PT b, PT c) {
  PT p = projectPointLine(a, b, c);
  return p*2 - c;
}

PT projectPointSegment (PT a, PT b, PT c) {
  double r = dot(b-a, b-a);
  if (cmp(r) == 0) return a;
  r = dot(b-a, c-a)/r;
  if (cmp(r, 0) == 0) return a;
  if (cmp(r, 1) == 0) return b;
  return a + (b - a) * r;
}

double distancePointSegment (PT a, PT b, PT c) {
  return dist(c, projectPointSegment(a, b, c));
}

// Parallel and opposite directions
bool ptInSegment (PT a, PT b, PT c) {
  if (a == b) return a == c;
  a = a-c, b = b-c;
  return cmp(cross(a, b)) == 0 && cmp(dot(a, b)) <= 0;
}

bool parallel (PT a, PT b, PT c, PT d) {
  return cmp(cross(b - a, c - d)) == 0;
}

bool collinear (PT a, PT b, PT c, PT d) {
  return parallel(a, b, c, d) && cmp(cross(a - b, a - c)) == 0 && cmp(cross(c - d, c - a)) == 0;
}

bool segmentsIntersect (PT a, PT b, PT c, PT d) {
  if (collinear(a, b, c, d)) {
    if (cmp(dist(a, c)) == 0 || cmp(dist(a, d)) == 0 || cmp(dist(b, c)) == 0 || cmp(dist(b, d)) == 0) return true;
    if (cmp(dot(c - a, c - b)) > 0 && cmp(dot(d - a, d - b)) > 0 && cmp(dot(c - b, d - b)) > 0) return false;
    return true;
  }
  if (cmp(cross(d - a, b - a) * cross(c - a, b - a)) > 0) return false;
  if (cmp(cross(a - c, d - c) * cross(b - c, d - c)) > 0) return false;
  return true;
}

// r = a1 + t*d1, (r - a2) x d2 = 0
PT computeLineIntersection (PT a, PT b, PT c, PT d) {
  b = b - a; d = c - d; c = c - a;
  assert(cmp(cross(b, d)) != 0);
  return a + b * cross(c, d) / cross(b, d);
}

PT computeCircleCenter (PT a, PT b, PT c) {
  b = (a + b) / 2; // bissector
  c = (a + c) / 2; // bissector
  return computeLineIntersection(b, b + rotateCW90(a - b), c, c + rotateCW90(a - c));
}

vector<PT> circle2PtsRad (PT p1, PT p2, double r) {
  vector<PT> ret;
  double d2 = dist2(p1, p2);
  double det = r * r / d2 - 0.25;
  if (det < 0.0) return ret;
  double h = sqrt(det);
  for (int i = 0; i < 2; i++) {
    double x = (p1.x + p2.x) * 0.5 + (p1.y - p2.y) * h;
    double y = (p1.y + p2.y) * 0.5 + (p2.x - p1.x) * h;
    ret.push_back(PT(x, y));
    swap(p1, p2);
  }
  return ret;
}

bool circleLineIntersection(PT a, PT b, PT c, double r) {
    return cmp(dist(c, projectPointLine(a, b, c)), r) <= 0;
}

vector<PT> circleLine (PT a, PT b, PT c, double r) {
  vector<PT> ret;
  PT p = projectPointLine(a, b, c), p1;
  double h = norm(c-p);
  if (cmp(h,r) == 0) {
    ret.push_back(p);
  } else if (cmp(h,r) < 0) {
    double k = sqrt(r*r - h*h);
    p1 = p + (b-a)/(norm(b-a))*k;
    ret.push_back(p1);
    p1 = p - (b-a)/(norm(b-a))*k;
    ret.push_back(p1);
  }
  return ret;
}

// area / semiperimeter
double rIncircle (PT a, PT b, PT c) {
  double ab = norm(a-b), bc = norm(b-c), ca = norm(c-a);
  return abs(cross(b-a, c-a)/(ab+bc+ca));
}

vector<PT> circleCircle (PT a, double r, PT b, double R) {
  vector<PT> ret;
  double d = norm(a-b);
  if (d > r + R || d + min(r, R) < max(r, R)) return ret;
  double x = (d*d - R*R + r*r) / (2*d); // x = r*cos(R opposite angle)
  double y = sqrt(r*r - x*x);
  PT v = (b - a)/d;
  ret.push_back(a + v*x + rotateCCW90(v)*y);
  if (cmp(y) > 0)
    ret.push_back(a + v*x - rotateCCW90(v)*y);
  return ret;
}

double circularSegArea (double r, double R, double d) {
  double ang = 2 * acos((d*d - R*R + r*r) / (2*d*r)); // cos(R opposite angle) = x/r
  double tri = sin(ang) * r * r;
  double sector = ang * r * r;
  return (sector - tri) / 2;
}

double computeSignedArea (const vector<PT> &p) {
  double area = 0;
  for (int i = 0; i < p.size(); i++) {
    int j = (i+1) % p.size();
    area += p[i].x*p[j].y - p[j].x*p[i].y;
  }
  return area;
}

double computeArea (const vector<PT> &p) {
  return abs(computeSignedArea(p));
}

PT computeCentroid (const vector<PT> &p) {
  PT c(0,0);
  double scale = 6.0 * computeSignedArea(p);
  for(int i = 0; i < p.size(); i++){
    int j = (i + 1) % p.size();
    c = c + (p[i] + p[j]) * (p[i].x * p[j].y - p[j].x * p[i].y);
  }
  return c / scale;
}

vector< pair<PT, PT> > getTangentSegs (PT c1, double r1, PT c2, double r2) {
  if (r1 < r2) swap(c1, c2), swap(r1, r2);
  vector<pair<PT, PT> > ans;
  double d = dist(c1, c2);
  if (cmp(d) <= 0) return ans;
  double dr = abs(r1 - r2), sr = r1 + r2;
  if (cmp(dr, d) >= 0) return ans;
  double u = acos(dr / d);
  PT dc1 = normalize(c2 - c1)*r1;
  PT dc2 = normalize(c2 - c1)*r2;
  ans.push_back(make_pair(c1 + rotateCCW(dc1, +u), c2 + rotateCCW(dc2, +u)));
  ans.push_back(make_pair(c1 + rotateCCW(dc1, -u), c2 + rotateCCW(dc2, -u)));
  if (cmp(sr, d) >= 0) return ans;
  double v = acos(sr / d);
  dc2 = normalize(c1 - c2)*r2;
  ans.push_back({c1 + rotateCCW(dc1, +v), c2 + rotateCCW(dc2, +v)});
  ans.push_back({c1 + rotateCCW(dc1, -v), c2 + rotateCCW(dc2, -v)});
  return ans;
}

bool ptInsideTriangle(PT p, PT a, PT b, PT c) {
  if(cross(b-a, c-b) < 0) swap(a, b);
  long long x = cross(b-a, p-b);
  long long y = cross(c-b, p-c);
  long long z = cross(a-c, p-a);
  if(x > 0 && y > 0 && z > 0) return true;
  if(!x) return ptInSegment(a,b,p);
  if(!y) return ptInSegment(b,c,p);
  if(!z) return ptInSegment(c,a,p);
  return false;
}

bool pointInConvexPolygon(const vector<PT> &hull, PT point) {
  int n = hull.size();
  if(cmp(cross(point - hull[0], hull[1] - hull[0])) || cmp(cross(point - hull[0], hull[n-1] - hull[0]))) return false;
  int l = 1, r = n - 1;
  while(l != r) {
    int mid = (l + r + 1) / 2;
    if(cmp(cross(point - hull[0], hull[mid] - hull[0])) < 0) l = mid;
    else r = mid - 1;
  }
  return cmp(cross(hull[(l+1)%n] - hull[l], point - hull[l])) >= 0;
}
