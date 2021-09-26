template <class T, class C = less<T>>
struct MaxQueue {
  MaxQueue() { clear(); }
  void clear() {
    id = 0;
    q.clear();
  }
  void push(T x) {
    pair<int, T> nxt(1, x);
    while(q.size() > id && cmp(q.back().second, x)) {
      nxt.first += q.back().first;
      q.pop_back();
    }
    q.push_back(nxt);
  }
  T qry() { return q[id].second;}
  void pop() {
    q[id].first--;
    if(q[id].first == 0) { id++; }
  }
private:
  vector<std::pair<int, T>> q;
  int id;
  C cmp;
};