int ds[ms], sz[ms], n;

void dsBuild() {
  for(int i = 0; i < n; i++) {
    ds[i] = i;
    sz[i] = 1;
  }
}

int dsFind(int i) {
  while(ds[i] != i) {
    ds[i] = ds[ds[i]];
    i = ds[i];
  }
  return ds[i];
}

void dsUnion(int a, int b) {
  a = dsFind(a); 
  b = dsFind(b);
  if(sz[a] < sz[b]) swap(a, b);
  if(a != b) sz[a] += sz[b];
  ds[b] = a;
}
