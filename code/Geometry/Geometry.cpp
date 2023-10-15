#include <bits/stdc++.h>
using namespace std;

const double inf = 1e100, eps = 1e-9;
const double PI = acos(-1.0L);
int cmp (double a, double b = 0) {
  if (abs(a-b) < eps) return 0;
  return (a < b) ? -1 : +1;
}
struct PT {
  typedef long long T;
  T x, y;
  PT(T x = 0, T y = 0) : x(x), y(y) {}
  PT operator + (const PT &p) const { return PT(x+p.x, y+p.y); }
  PT operator - (const PT &p) const { return PT(x-p.x, y-p.y); }
  PT operator * (double c) const { return PT(x*c, y*c); }
  PT operator / (double c) const { return PT(x/c, y/c); }
  T operator * (const PT &p) const { return x*p.x + y*p.y; }
  T operator % (const PT &p) const { return x*p.y - y*p.x; }
  double operator !()        const { return hypot(x, y);   }
  bool operator <(const PT &p) const {
    if(cmp(x, p.x) != 0) return x < p.x;
    return cmp(y, p.y) < 0;
  }
  bool operator ==(const PT &p) const {return !cmp(x, p.x) && !cmp(y, p.y);}
  bool operator != (const PT &p) const {return !(p == *this);}
};
ostream &operator<<(ostream &os, const PT &p) {
  return os << "(" << p.x << "," << p.y << ")"; 
}

double angle (PT p, PT q) { return atan2(p % q, p * q); }
double angle (PT p) { return atan2(p.y, p.x); }
double polarAngle (PT p) {
  double a = atan2(p.y,p.x);
  return a < 0 ? a + 2*PI : a;
}

PT rotateCCW90 (PT p) { return PT(-p.y, p.x); }
PT rotateCW90 (PT p) { return PT(p.y, -p.x); }
PT rotateCCW (PT p, double t) {
  return PT(p.x*cos(t)-p.y*sin(t), p.x*sin(t)+p.y*cos(t));
}
PT projPtLine (PT a, PT b, PT c) { // ponto c na linha a - b, a.b = |a| cost * |b|
  b = b - a, c = c  - a;
  return a + b*(c*b)/(b*b);
}
PT reflectPointLine (PT a, PT b, PT c) {
  PT p = projPtLine(a, b, c);
  return p*2 - c;
}
PT projPtSeg (PT a, PT b, PT c) { // c no segmento a - b
  b = b - a, c = c - a;
  double r = b * b;
  if (cmp(r) == 0) return a;
  r = c * b / r;
  if (cmp(r, 0) < 0) return a;
  if (cmp(r, 1) > 0) return a + b;
  return a + b * r;
}
double distPtSeg (PT a, PT b, PT c) { //  ponto c e o segmento a - b
  return !(c - projPtSeg(a, b, c));
}
bool ptInSegment (PT a, PT b, PT c) { // ponto c esta em um segmento a - b
  if (a == b) return a == c;
  a = a-c, b = b-c;
  return cmp(a % b) == 0 && cmp(a * b) <= 0;
}
bool parallel (PT a, PT b, PT c, PT d) {
  return cmp((b - a)%(c - d)) == 0;
}
bool collinear (PT a, PT b, PT c, PT d) {
  return parallel(a, b, c, d) && cmp((a - b)%(a - c)) == 0 && cmp((c - d)%(c - a)) == 0;
}
// Calcula distancia entre o ponto (x, y, z) e o plano ax + by + cz = d
double distPtPlane (double x, double y, double z, double a, double b, double c, double d) {
    return abs(a * x + b * y + c * z - d) / sqrt(a * a + b * b + c * c);
}
bool segInter (PT a, PT b, PT c, PT d) {
  if (collinear(a, b, c, d)) {
    if (a == c || a == d || b == c || b == d) return true;
    if (cmp((c - a)*(c - b)) > 0 && cmp((d - a)*(d - b)) > 0 && cmp((c - b)*(d - b)) > 0) return false;
    return true;
  }
  if (cmp((d - a)%(b - a) * ((c - a)%(b - a))) > 0) return false;
  if (cmp((a - c)%(d - c) * ((b - c)%(d - c))) > 0) return false;
  return true;
}
// Calcula a intersecao entre as retas a - b e c - d assumindo que uma unica intersecao existe
// Para intersecao de segmentos, cheque primeiro se os segmentos se intersectam e que nao sao paralelos
PT lineLine (PT a, PT b, PT c, PT d) {
  b = b - a; d = c - d; c = c - a;
  // assert(cmp(cross(b, d)) != 0);
  return a + b * (c % d) / (b % d);
}
PT circleCenter (PT a, PT b, PT c) {
  b = (a + b) / 2; // bissector
  c = (a + c) / 2; // bissector
  return lineLine(b, b + rotateCW90(a - b), c, c + rotateCW90(a - c));
}
vector<PT> circle2PtsRad (PT p1, PT p2, double r) {
  vector<PT> ret;
  double d2 = p1 * p2;
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
bool circleLineIntersection (PT a, PT b, PT c, double r) {
    return cmp(!(c - projPtLine(a, b, c)), r) <= 0;
}
vector<PT> circleLine (PT a, PT b, PT c, double r) {
  vector<PT> ret;
  PT p = projPtLine(a, b, c), p1;
  double h = !(c-p);
  if (cmp(h,r) == 0) {
    ret.push_back(p);
  } else if (cmp(h,r) < 0) {
    double k = sqrt(r*r - h*h);
    p1 = p + (b-a)/(!(b-a))*k;
    ret.push_back(p1);
    p1 = p - (b-a)/(!(b-a))*k;
    ret.push_back(p1);
  }
  return ret;
}
bool ptInsideTriangle (PT p, PT a, PT b, PT c) {
  if((b-a) % (c-b) < 0) swap(a, b);
  if(ptInSegment(a,b,p)) return 1;
  if(ptInSegment(b,c,p)) return 1;
  if(ptInSegment(c,a,p)) return 1;
  bool x = (b-a)%(p-b) < 0;
  bool y = (c-b)%(p-c) < 0;
  bool z = (a-c)%(p-a) < 0;
  return x == y && y == z;
}
bool pointInConvexPolygon (const vector<PT> &p, PT q) {
  if (p.size() == 1) return p.front() == q;
  int l = 1, r = p.size()-1;
  while(abs(r-l) > 1) {
    int m = (r+l)/2;
    if((p[m]-p[0])%(q-p[0]) < 0) r = m;
    else l = m;
  }
  return ptInsideTriangle(q, p[0], p[l], p[r]);
}
// Determina se o ponto esta num poligono possivelmente nao-convexo
// Retorna 1 para pontos estritamente dentro, 0 para pontos estritamente fora do poligno 
// e 0 ou 1 para os pontos restantes
bool pointInPolygon (const vector<PT> &p, PT q) {
  bool c = 0;
  for(int i = 0; i < p.size(); i++){
    int j = (i + 1) % p.size();
    if((p[i].y <= q.y && q.y < p[j].y || p[j].y <= q.y && q.y < p[i].y) &&
      q.x < p[i].x + (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y))
      c = !c;
  }
  return c;
}
// area / semiperimeter
double rIncircle (PT a, PT b, PT c) {
  double ab = !(a-b), bc = !(b-c), ca = !(c-a);
  return abs((b-a)%(c-a)/(ab+bc+ca));
}
vector<PT> circleCircle (PT a, double r, PT b, double R) {
  vector<PT> ret;
  double d = !(a-b);
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
  return area/2.0;
}
double computeArea (const vector<PT> &p) { return abs(computeSignedArea(p)); }
PT computeCentroid (const vector<PT> &p) {
  PT c(0,0);
  double scale = 6.0 * computeSignedArea(p);
  for(int i = 0; i < p.size(); i++){
    int j = (i + 1) % p.size();
    c = c + (p[i] + p[j]) * (p[i].x * p[j].y - p[j].x * p[i].y);
  }
  return c / scale;
}
// Testa se o poligno listada em ordem CW ou CCW eh simples (nenhuma linha se intersecta)
bool isSimple (const vector<PT> &p) {
  for(int i = 0; i < p.size(); i++) {
    for(int k = i + 1; k < p.size(); k++) {
      int j = (i + 1) % p.size();
      int l = (k + 1) % p.size();
      if (i == l || j == k) continue;
      if (segInter(p[i], p[j], p[k], p[l])) 
        return false;
    }
  }
  return true;
}

PT normalize (PT p) { return p/!p; }
vector< pair<PT, PT> > getTangentSegs (PT c1, double r1, PT c2, double r2) {
  if (r1 < r2) swap(c1, c2), swap(r1, r2);
  vector<pair<PT, PT> > ans;
  double d = !(c1 - c2);
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
