int ds[ms], sz[ms], n;

void dsBuild() {
  for(int i = 0; i < n; i++) {
    ds[i] = i;
  }
}

int dsFind(int i) {
  while(ds[i] != i) {
    ds[i] = ds[ds[i]];
    i = ds[i];
  }
}

void dsUnion(int a, int b) {
  a = dsFind(a); 
  b = dsFind(b);
  if(sz[a] < sz[b]) swap(a, b);
  sz[a] += sz[b];
  ds[b] = a;
}
