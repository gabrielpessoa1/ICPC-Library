struct PT {
  double x, y, z;
  PT (double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {};
  PT operator - (const PT other) {
    return PT(x - other.x, y - other.y, z - other.z);
  }
  bool operator == (const PT other) {
    PT norm = *this - other;
    return (abs(norm.y) < 1e-9 && abs(norm.y) < 1e-9 && abs(norm.x) < 1e-9);
  }
};

PT cross (PT a, PT b) {
  return PT(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}

double dot (PT a, PT b) {
  return a.x*b.x + a.y*b.y + a.z*b.z;
}

// same plane (a, b, c, p) = norm = cross((a-b), (c-b)), dot(norm, p) == dot(norm, a)
// same line (a, b, c) = cross((a-b), (c-b)) == PT(0, 0, 0)
