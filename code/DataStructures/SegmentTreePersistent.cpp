struct PSEGTREE{
  private:
    int z, t, sz, *tree, *L, *R, head[112345];
    
    void _build(int l, int r, int on, vector<int> &v){
      if(l == r){
        tree[on] = v[l];
        return;
      }
      L[on] = ++z;
      int mid = (l+r)>>1;
      _build(l, mid, L[on], v);
      R[on] = ++z;
      _build(mid+1, r, R[on], v);
      tree[on] = tree[L[on]] + tree[R[on]];
    }
  
    int _upd(int ql, int qr, int val, int l, int r, int on){
      if(l > qr || r < ql) return on;
      int curr = ++z;
      if(l >= ql && r <= qr){
        tree[curr] = tree[on] + val;
        return curr;
      }
      int mid = (l+r)>>1;
      L[curr] = _upd(ql, qr, val, l, mid, L[on]);
      R[curr] = _upd(ql, qr, val, mid+1, r, R[on]);
      tree[curr] = tree[L[curr]] + tree[R[curr]];
      return curr;
    }
    
    int _query(int ql, int qr, int l, int r, int on){
      if(l > qr || r < ql) return 0;
      if(l >= ql && r <= qr){
        return tree[on];
      }
      int mid = (l+r)>>1;
      return _query(ql, qr, l, mid, L[on]) + _query(ql, qr, mid+1, r, R[on]);
    }
    
  public:
    PSEGTREE(vector<int> &v){
      tree = new int[1123456];
      L = new int[1123456];
      R = new int[1123456];
      build(v);
    }
    void build(vector<int> &v){
      t = 0, z = 0;
      sz = v.size();
      head[0] = 0;
      _build(0, sz-1, 0, v);
    }
    
    void upd(int pos, int val, int idx){
      head[++t] = _upd(pos, pos, val, 0, sz-1, head[idx]);
    }
    
    int query(int l, int r, int idx){
      return _query(l, r, 0, sz-1, head[idx]);
    }
};
