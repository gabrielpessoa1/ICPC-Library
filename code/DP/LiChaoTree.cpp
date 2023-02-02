typedef long long T;
const T INF = 2e18, EPS = 1;
 
struct Line {
  T m, b;
  Line(T m = 0, T b = INF): m(m), b(b){}
  T apply(T x) { return x * m + b; }
};
struct Node {
  Node *l = this, *r = this;
  Line line;
};

Node buffer[mx * 31];
const T MIN_VALUE = 0, MAX_VALUE = 1e9;
int CNT = 1;
 
Node* update(Node *root, Line line, T l = MIN_VALUE, T r = MAX_VALUE+1) {
  Node *node = &buffer[CNT++];
  *node = *root;
  T m = l + (r - l) / 2;
  bool left = line.apply(l) < node->line.apply(l);
  bool mid = line.apply(m) < node->line.apply(m);
  bool right = line.apply(r) < node->line.apply(r);
 
  if (mid) swap(node->line, line);
  if (r - l <= EPS) return node;
  if (left == right) return node;
  if (mid != left) node->l = update(root->l, line, l, m);
  else node->r = update(root->r, line, m, r);
  return node;
}
 
T query(Node *root, T x, T l = MIN_VALUE, T r = MAX_VALUE+1) {
  if (!root) return INF;
  if (r - l <= EPS) return root->line.apply(x);
  T m = l + (r - l) / 2;
  T ans;
  if (x < m) ans = query(root->l, x, l, m);
  else ans = query(root->r, x, m, r);
  return min(ans, root->line.apply(x));
}
