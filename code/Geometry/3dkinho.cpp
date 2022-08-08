struct PT {
  double x, y, z;
  PT (double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {};
  PT operator - (const PT other) {
    return PT(x - other.x, y - other.y, z - other.z);
  }
  bool operator == (const PT other) {
    return !cmp(x, other.x) && !cmp(y, other.y) && !cmp(z, other.z);
  }
};

PT cross (PT a, PT b) {
  return PT(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}

double dot (PT a, PT b) {
  return a.x*b.x + a.y*b.y + a.z*b.z;
}

boolean samePlane (PT a, PT b, PT c, PT p) {
  PT norm = cross(a-b, c-b);
  return !cmp(dot(norm, p), dot(norm, a));
}

boolean sameLine (PT a, PT b, PT c, PT p) {
  return cross(a-b, c-b) == PT();
}
