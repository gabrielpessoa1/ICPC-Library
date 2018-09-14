// Construa a Trie do seu dicionario com o codigo acima

int fail[ms];
queue<int> q;

void buildFailure() {
  q.push(0);
  while(!q.empty()) {
    int node = q.front();
    q.pop();
    for(int pos = 0; pos < sigma; pos++) {
      int &v = trie[node][pos];
      int f = node == 0 ? 0 : trie[fail[node]][pos];
      if(v == -1) {
        v = f;
      } else {
        fail[v] = f;
        q.push(v);
        // juntar as informacoes da borda para o V ja q um match em V implica um match na borda
        terminal[v] += terminal[f];
      }
    }
  }
}

int search(string &txt) {
  int node = 0;
  int ans = 0;
  for(int i = 0; i < txt.length(); i++) {
    int pos = get_id(txt[i]);
    node = trie[node][pos];
    // processar informacoes no no atual
     ans += terminal[node];
  }
  return ans;
}