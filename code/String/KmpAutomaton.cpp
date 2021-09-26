// trad converts a char to its index
int trad(char ch) { return (int) ch; }
// sigma should be greater then the greatest value returned by trad
vector<vector<int>> buildAutomaton(string p, int sigma=300) {
  vector<vector<int>> A(p.size() + 1, vector<int>(sigma));
  int brd = 0;
  for (int i = 0; i < sigma; i++) A[0][i] = 0;
  A[0][trad(p[0])] = 1;
  for (int i = 1; i <= p.size(); i++) {
    for (int ch = 0; ch < sigma; ch++) {
      A[i][ch] = A[brd][ch];
    }
    if (i < p.size()) {
      A[i][trad(p[i])] = i + 1;
      brd = A[brd][trad(p[i])];
    }
  }
  return A;
}
