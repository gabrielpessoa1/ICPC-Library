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
