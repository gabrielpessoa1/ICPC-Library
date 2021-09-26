const int ms = 1e6;    // quantidade de caracteres
const int sigma = 26;  // tamanho do alfabeto
int trie[ms][sigma], fail[ms], terminal[ms], qtd;

void init() {
  qtd = 1;
  memset(trie[0], -1, sizeof trie[0]);
}
void add(string &s) {
  int node = 0;
  for (char ch : s) {
    int pos = val(ch);  // no caso de alfabeto a-z: val(ch) = ch - 'a'
    if (trie[node][pos] == -1) {
      memset(trie[qtd], -1, sizeof trie[qtd]);
      terminal[qtd] = 0;
      trie[node][pos] = qtd++;
    }
    node = trie[node][pos];
  }
  ++terminal[node];  // trocar pela info que quiser
}
void buildFailure() {
  memset(fail, 0, sizeof(int) * qtd);
  queue<int> Q;
  Q.push(0);
  while (Q.size()) {
    int node = Q.front();
    Q.pop();
    for (int pos = 0; pos < sigma; ++pos) {
      int &v = trie[node][pos];
      int f = node == 0 ? 0 : trie[fail[node]][pos];
      if (v == -1) {
        v = f;
      } else {
        fail[v] = f;
        Q.push(v);
        // dar merge nas infos (por ex: terminal[v] += terminal[f])
      }
    }
  }
}
void search(string &s) {
  int node = 0;
  for (char ch : s) {
    int pos = val(ch);
    node = trie[node][pos];
    // processar infos no nó atual (por ex: ocorrencias += terminal[node])
  }
}