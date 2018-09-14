// by luucasv
typedef long long T;
const T INF = 1e18, EPS = 1;
const int BUFFER_SIZE = 1e4;

struct Line {
  T m, b;
  
  Line(T m = 0, T b = INF): m(m), b(b){}
  T apply(T x) { return x * m + b; }
};


struct Node {
  Node *left, *right;
  Line line;
  Node(): left(NULL), right(NULL) {}
};

struct LiChaoTree {
  Node *root, buffer[BUFFER_SIZE];
  T min_value, max_value;
  int buffer_pointer;
  LiChaoTree(T min_value, T max_value): min_value(min_value), max_value(max_value + 1) { clear(); }
  void clear() { buffer_pointer = 0; root = newNode(); }
  void insert_line(T m, T b) { update(root, min_value, max_value, Line(m, b)); }
  T eval(T x) { return query(root, min_value, max_value, x); }
  void update(Node *cur, T l, T r, Line line) {
    T m = l + (r - l) / 2;
    bool left = line.apply(l) < cur->line.apply(l);
    bool mid = line.apply(m) < cur->line.apply(m);
    bool right = line.apply(r) < cur->line.apply(r);
    if (mid) {
      swap(cur->line, line);
    }
    if (r - l <= EPS) return;
    if (left == right) return;
    if (mid != left) {
      if (cur->left == NULL) cur->left = newNode();
      update(cur->left, l, m, line);
    } else {
      if (cur->right == NULL) cur->right = newNode();
      update(cur->right, m, r, line);
    }
  }
  T query(Node *cur, T l, T r, T x) {
    if (cur == NULL) return INF;
    if (r - l <= EPS) {
      return cur->line.apply(x);
    }
    T m = l + (r - l) / 2;
    T ans;
    if (x < m) {
      ans = query(cur->left, l, m, x);
    } else {
      ans = query(cur->right, m, r, x);
    }
    return min(ans, cur->line.apply(x));
  }
  Node* newNode() {
      buffer[buffer_pointer] = Node();
      return &buffer[buffer_pointer++];
  }
};
