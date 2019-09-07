namespace SA {
  typedef pair<int, int> ii;
  
  vector<int> buildSA(string s) {
    int n = (int) s.size();
    vector<int> ids(n), pos(n);
    vector<ii> pairs(n);
    for(int i = 0; i < n; i++) {
      ids[i] = i;
      pairs[i] = ii(s[i], -1);
    }
    sort(ids.begin(), ids.end(), [&](int a, int b) -> bool {
      return pairs[a] < pairs[b];
    });
    int on = 0;
    for(int i = 0; i < n; i++) {
      if (i && pairs[ids[i - 1]] != pairs[ids[i]]) on++;
      pos[ids[i]] = on;
    }
    for(int offset = 1; offset < n; offset <<= 1) {
      //ja tao ordenados pelos primeiros offset caracteres
      for(int i = 0; i < n; i++) {
        pairs[i].first = pos[i];
        if (i + offset < n) {
          pairs[i].second = pos[i + offset];
        } else {
          pairs[i].second = -1;
        }
      }
      sort(ids.begin(), ids.end(), [&](int a, int b) -> bool {
        return pairs[a] < pairs[b];
      });
      int on = 0;
      for(int i = 0; i < n; i++) {
        if (i && pairs[ids[i - 1]] != pairs[ids[i]]) on++;
        pos[ids[i]] = on;
      }
    }
    return ids;
  }
  
  vector<int> buildLCP(string s, vector<int> sa) {
    int n = (int) s.size();
    vector<int> pos(n), lcp(n, 0);
    for(int i = 0; i < n; i++) {
      pos[sa[i]] = i;
    }
    int k = 0;
    for(int i = 0; i < n; i++) {
      if (pos[i] + 1 == n) {
        k = 0;
        continue;
      }	
      int j = sa[pos[i] + 1];
      while(i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
      lcp[pos[i]] = k;
      k = max(k - 1, 0);
    }
    return lcp;
  }
};

//nlogn

vector<int> suffix_array(const string& in) {
    int n = (int)in.size(), c = 0;
    vector<int> temp(n), pos2bckt(n), bckt(n), bpos(n), out(n);
    for (int i = 0; i < n; i++) out[i] = i; 
    sort(out.begin(), out.end(), [&](int a, int b) { return in[a] < in[b]; });
    for (int i = 0; i < n; i++) {
        bckt[i] = c;
        if (i + 1 == n || in[out[i]] != in[out[i + 1]]) c++;
    }
    /*Start*/
    for (int h = 1; h < n && c < n; h <<= 1) {// executes log n times
        for (int i = 0; i < n; i++) pos2bckt[out[i]] = bckt[i];
	for (int i = n - 1; i >= 0; i--) bpos[bckt[i]] = i;
	for (int i = 0; i < n; i++)
            if (out[i] >= n - h) temp[bpos[bckt[i]]++] = out[i];
        for (int i = 0; i < n; i++)
            if (out[i] >= h) temp[bpos[pos2bckt[out[i] - h]]++] = out[i] - h;
        c = 0;
        for (int i = 0; i + 1 < n; i++) {
            int a = (bckt[i] != bckt[i + 1]) || (temp[i] >= n - h)
                || (pos2bckt[temp[i + 1] + h] != pos2bckt[temp[i] + h]);
            bckt[i] = c;
            c += a;
        }
        bckt[n - 1] = c++;
        temp.swap(out);
    }
    return out;
}