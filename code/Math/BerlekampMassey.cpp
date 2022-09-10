vector<int> berlekampMassey(const vector<int> &s) {
    int n = (int) s.size(), l = 0, m = 1;
    vector<int> b(n), c(n);
    int ld = b[0] = c[0] = 1;
    for (int i=0; i<n; i++, m++) {
        int d = s[i];
        for (int j=1; j<=l; j++)
            d = (d + c[j] * s[i-j]) % mod;
        if (d == 0)
            continue;
        vector<int> temp = c;
        int coef = d * fexp(ld, mod-2) % mod;
        for (int j=m; j<n; j++) 
            c[j] = ((c[j] - coef * b[j-m]) % mod + mod) % mod;
        if (2 * l <= i) {
            l = i + 1 - l;
            b = temp;
            ld = d;
            m = 0;
        }
    }
    c.resize(l + 1);
    c.erase(c.begin());
    for (int &x : c)
        x = mod-x;
    return c;
}

// p = p*q % h
void mull(vector<int> &p,vector<int> &q, vector<int> &h, int m) {
	vector<int> t_(m+m);
	for(int i=0;i<m;++i) if(p[i])
		for(int j=0;j<m;++j)
			t_[i+j]=(t_[i+j]+p[i]*q[j])%mod;
	for(int i=m+m-1;i>=m;--i) if(t_[i])
		//miuns t_[i]x^{i-m}(x^m-\sum_{j=0}^{m-1} x^{m-j-1}h_j)
		for(int j=m-1;~j;--j)
			t_[i-j-1]=(t_[i-j-1]+t_[i]*h[j])%mod;
	for(int i=0;i<m;++i) p[i]=t_[i];
}

// a = caso base, h = recorrencia, m = tamanho da recorrencia
inline int calc(vector<int> &a, vector<int> &h, int K, int m) {
	vector<int> s(m), t(m);
	//init
	s[0]=1; if(m!=1) t[1]=1; else t[0]=h[0];
	//binary-exponentiation
	while(K) {
		if(K&1) mull(s,t,h,m);
		mull(t,t,h,m); K>>=1;
	}
	int su=0;
	for(int i=0;i<m;++i) su=(su+s[i]*a[i])%mod;
	return (su%mod+mod)%mod;
}
