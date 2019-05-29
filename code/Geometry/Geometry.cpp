const double inf = 1e100, eps = 1e-9;

struct PT {
	double x, y;
	PT(double x = 0, double y = 0) : x(x), y(y) {}
	PT operator + (const PT &p) { return PT(x + p.x, y + p.y); }
	PT operator - (const PT &p) { return PT(x - p.x, y - p.y); }
	PT operator * (double c) { return PT(x * c, y * c); }
	PT operator / (double c) { return PT(x / c, y / c); }
	bool operator <(const PT &p) const {
		if(fabs(x - p.x) >= eps) return x < p.x;
		return fabs(y - p.y) >= eps && y < p.y;
	}
	bool operator ==(const PT &p) const {
		return fabs(x - p.x) < eps && fabs(y - p.y) < eps;
	}
};

double dot(PT p, PT q) { return p.x * q.x + p.y * q.y; }
double dist2(PT p, PT q) { return dot(p - q, p - q); }
double dist(PT p, PT q) {return hypot(p.x-q.x, p.y-q.y); }
double cross(PT p, PT q) { return p.x * q.y - p.y * q.x; }

// Rotaciona o ponto CCW ou CW ao redor da origem
PT rotateCCW90(PT p) { return PT(-p.y, p.x); }
PT rotateCW90(PT p) { return PT(p.y, -p.x); }
PT rotateCCW(PT p, double t) {
    return PT(p.x * cos(t) - p.y * sin(t), p.x * sin(t) + p.y * cos(t));
}

// Projeta ponto c na linha a - b assumindo a != b
PT projectPointLine(PT a, PT b, PT c) {
    return a + (b - a) * dot(c - a, b - a) / dot(b - a, b - a);
}

// Projeta ponto c no segmento a - b
PT projectPointSegment(PT a, PT b, PT c) {
    double r = dot(b - a, b - a);
    if(abs(r) < eps) return a;
    r = dot(c - a, b - a) / r;
    if(r < 0) return a;
    if(r > 1) return b;
    return a + (b - a) * r;
}
// Calcula distancia entre o ponto c e o segmento a - b
double distancePointSegment(PT a, PT b, PT c) {
    return dist(c, projectPointSegment(a, b, c));
}

// Determina se o ponto c esta em um segmento a - b
bool ptInSegment(PT a, PT b, PT c) {
  bool x = min(a.x, b.x) <= c.x && c.x <= max(a.x, b.x);
  bool y = min(a.y, b.y) <= c.y && c.y <= max(a.y, b.y);
  return x && y && cross(b-a, c-a) == 0; // testar com eps se for double
}

// Calcula distancia entre o ponto (x, y, z) e o plano ax + by + cz = d
double distancePointPlane(double x, double y, double z, double a, double b, double c, double d) {
    return abs(a * x + b * y + c * z - d) / sqrt(a * a + b * b + c * c);
}

// Determina se as linhas a - b e c - d sao paralelas ou colineares
bool linesParallel(PT a, PT b, PT c, PT d) {
    return abs(cross(b - a, c - d)) < eps;
}

bool linesCollinear(PT a, PT b, PT c, PT d) {
    return linesParallel(a, b, c, d) && abs(cross(a - b, a - c)) < eps && abs(cross(c - d, c - a)) < eps;
}

// Determina se o segmento a - b intersecta com o segmento c - d
bool segmentsIntersect(PT a, PT b, PT c, PT d) {
    if(linesCollinear(a, b, c, d)) {
        if(dist2(a, c) < eps || dist2(a, d) < eps || dist2(b, c) < eps || dist2(b, d) < eps) return true;
        if(dot(c - a, c - b) > 0 && dot(d - a, d - b) > 0 && dot(c - b, d - b) > 0) return false;
        return true;
    }
    if(cross(d - a, b - a) * cross(c - a, b - a) > 0) return false;
    if(cross(a - c, d - c) * cross(b - c, d - c) > 0) return false;
    return true;
}

// Calcula a intersecao entre as retas a - b e c - d assumindo que uma unica intersecao existe
// Para intersecao de segmentos, cheque primeiro se os segmentos se intersectam e que nao paralelos
PT computeLineIntersection(PT a, PT b, PT c, PT d) {
    b = b - a; d = c - d; c = c - a;
    assert(cross(b, d) != 0); // garante que as retas nao sao paralelas, remover pra evitar tle
    return a + b * cross(c, d) / cross(b, d);
}

// Calcula centro do circulo dado tres pontos
PT computeCircleCenter(PT a, PT b, PT c) {
    b = (a + b) / 2;
    c = (a + c) / 2;
    return computeLineIntersection(b, b + rotateCW90(a - b), c, c + rotateCW90(a - c));
} 

// Determina se o ponto p esta dentro do triangulo (a, b, c)
bool ptInsideTriangle(PT p, PT a, PT b, PT c) {
  if(cross(b-a, c-b) < 0) swap(a, b);
  ll x = cross(b-a, p-b);
  ll y = cross(c-b, p-c);
  ll z = cross(a-c, p-a);
  if(x > 0 && y > 0 && z > 0) return true;
  if(!x) return ptInSegment(a,b,p);
  if(!y) return ptInSegment(b,c,p);
  if(!z) return ptInSegment(c,a,p);
  return false;
}

// Determina se o ponto esta num poligono convexo em O(lgn)
bool pointInConvexPolygon(const vector<PT> &p, PT q) {
  PT pivot = p[0];
  int x = 1, y = p.size();
  while(y-x != 1) {
    int z = (x+y)/2;
    PT diagonal = pivot - p[z];
    if(cross(p[x] - pivot, q - pivot) * cross(q-pivot, p[z] - pivot) >= 0) y = z;
    else x = z;
  }
  return ptInsideTriangle(q, p[x], p[y], pivot);
}

// Determina se o ponto esta num poligono possivelmente nao-convexo
// Retorna 1 para pontos estritamente dentro, 0 para pontos estritamente fora do poligno 
// e 0 ou 1 para os pontos restantes
// Eh possivel converter num teste exato usando inteiros e tomando cuidado com a divisao
// e entao usar testes exatos para checar se esta na borda do poligno
bool pointInPolygon(const vector<PT> &p, PT q) {
  bool c = 0;
  for(int i = 0; i < p.size(); i++){
    int j = (i + 1) % p.size();
    if((p[i].y <= q.y && q.y < p[j].y || p[j].y <= q.y && q.y < p[i].y) &&
      q.x < p[i].x + (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y))
      c = !c;
  }
  return c;
}

// Determina se o ponto esta na borda do poligno
bool pointOnPolygon(const vector<PT> &p, PT q) {
  for(int i = 0; i < p.size(); i++)
    if(dist2(projectPointSegment(p[i], p[(i + 1) % p.size()], q), q) < eps)
      return true;
    return false;
}

// Calcula intersecao da linha a - b com o circulo centrado em c com raio r > 0
vector<PT> circleLineIntersection(PT a, PT b, PT c, double r) {
  vector<PT> ans;
  b = b - a;
  a = a - c;
  double x = dot(b, b);
  double y = dot(a, b);
  double z = dot(a, a) - r * r;
  double w = y * y - x * z;
  if (w < -eps) return ans;
  ans.push_back(c + a + b * (-y + sqrt(w + eps)) / x);
  if (w > eps)
    ans.push_back(c + a + b * (-y - sqrt(w)) / x);
  return ans;
}

// Calcula intersecao do circulo centrado em a com raio r e o centrado em b com raio R
vector<PT> circleCircleIntersection(PT a, PT b, double r, double R) {
  vector<PT> ans;
  double d = sqrt(dist2(a, b));
  if (d > r + R || d + min(r, R) < max(r, R)) return ans;
  double x = (d * d - R * R + r * r)/(2 * d);
  double y = sqrt(r * r - x * x);
  PT v = (b - a) / d;
  ans.push_back(a + v * x + rotateCCW90(v) * y);
  if (y > 0)
    ans.push_back(a + v * x - RotateCCW90(v) * y);
  return ans;
}

// Calcula a area ou o centroide de um poligono (possivelmente nao-convexo)
// assumindo que as coordenadas estao listada em ordem horaria ou anti-horaria
// O centroide eh equivalente a o centro de massa ou centro de gravidade
double computeSignedArea(const vector<PT> &p) {
  double area = 0;
  for(int i = 0; i < p.size(); i++) {
    int j = (i + 1) % p.size();
    area += p[i].x * p[j].y - p[j].x * p[i].y;
  }
  return area / 2.0;
}

double computeArea(const vector<PT> &p) {
  return abs(computeSignedArea(p));
}

PT computeCentroid(const vector<PT> &p) {
  PT c(0,0);
  double scale = 6.0 * ComputeSignedArea(p);
  for(int i = 0; i < p.size(); i++){
    int j = (i + 1) % p.size();
    c = c + (p[i] + p[j]) * (p[i].x * p[j].y - p[j].x * p[i].y);
  }
  return c / scale;
}

// Testa se o poligno listada em ordem CW ou CCW eh simples (nenhuma linha se intersecta)
bool isSimple(const vector<PT> &p) {
  for(int i = 0; i < p.size(); i++) {
    for(int k = i + 1; k < p.size(); k++) {
      int j = (i + 1) % p.size();
      int l = (k + 1) % p.size();
      if (i == l || j == k) continue;
      if (segmentsIntersect(p[i], p[j], p[k], p[l])) 
        return false;
    }
  }
  return true;
}
