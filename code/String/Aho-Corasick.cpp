const int ms = 1e6;    // quantidade de caracteres
const int sigma = 26;  // tamanho do alfabeto
int trie[ms][sigma], fail[ms], superfail[ms], terminal[ms], z = 1;

void add(string &s) {
  int node = 0;
  for (char ch : s) {
    int pos = val(ch);  // no caso de alfabeto a-z: val(ch) = ch - 'a'
    if (!trie[node][pos]) {
      terminal[z] = 0;
      trie[node][pos] = z++;
    }
    node = trie[node][pos];
  }
  ++terminal[node];  // trocar pela info que quiser
}
void buildFailure() {
  memset(fail, 0, sizeof(int) * z), memset(superfail, 0, sizeof(int) * z);
  queue<int> Q;
  Q.push(0);
  while (Q.size()) {
    int node = Q.front();
    Q.pop();
    for (int pos = 0; pos < sigma; ++pos) {
      int &v = trie[node][pos];
      int f = node == 0 ? 0 : trie[fail[node]][pos];
      // int sf = present[f] ? f : superfail[f];
      // present marks if that vertex is a terminal node or not
      // if summing up on terminal, doesn't work
      if (!v) {
        v = f;
      } else {
        fail[v] = f;
      // superfail[v] = sf;
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
    // processar infos no no atual (por ex: ocorrencias += terminal[node])
  }
}
// se tiver usando super fail, cuidado com o estado que voce ta, antes de subir pro sf, porque pode ser que o estado que ta nao seja no terminal
