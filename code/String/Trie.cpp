int trie[ms][sigma], terminal[ms], z = 1;

void insert(string &p) {
  int cur = 0;
  for(int i = 0; i < p.size(); i++) {
    int id = p[i]-'a';
    if(!trie[cur][id]) {
      trie[cur][id] = z++;
    }
    cur = trie[cur][id];
  }
  terminal[cur]++;
}

int count(string &p) {
  int cur = 0;
  for(int i = 0; i < p.size(); i++) {
    int id = p[i]-'a';
    if(!trie[cur][id]) {
      return false;
    }
    cur = trie[cur][id];
  }
  return terminal[cur];
}
