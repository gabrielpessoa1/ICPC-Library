template <class T>
T fexp(T x, long long e) {
	T ans(1);
	for(; e > 0; e /= 2) {
		if(e & 1) ans = ans * x;
		x = x * x;
	}
	return ans;
}

template <int mod = 998244353>
struct modBase {
	modBase(int v = 0) : val(v < 0 ? v + mod : v) {}
	int val;
 
	void operator += (modBase<mod> o) { *this = *this + o; }
	void operator -= (modBase<mod> o) { *this = *this - o; }
	void operator *= (modBase<mod> o) { *this = *this * o; }
  bool operator == (modBase<mod> o) { return val == o.val; }
	void operator /= (modBase<mod> o) { *this = *this / o; }
	modBase<mod> operator * (modBase<mod> o) { return (int)((long long) val * o.val % mod); }
	modBase<mod> operator / (modBase<mod> o) { return *this * fexp(o, mod - 2); }
	modBase<mod> operator + (modBase<mod> o) { return val + o.val >= mod ? val + o.val - mod : val + o.val; }
	modBase<mod> operator - (modBase<mod> o) { return val - o.val < 0 ? val - o.val + mod : val - o.val; }

	friend std::ostream& operator << (std::ostream &os, const modBase<mod> &p) {
		return os << p.val;
	}
	friend std::istream& operator >> (std::istream &is, modBase<mod> &p) {
		return is >> p.val;
	}
};

template<typename T>
vector<T> berlekampMassey(const vector<T> &s) {
    int n = (int) s.size(), l = 0, m = 1;
    vector<T> b(n), c(n);
    T ld = b[0] = c[0] = 1;
    for (int i=0; i<n; i++, m++) {
        T d = s[i];
        for (int j=1; j<=l; j++)
            d += c[j] * s[i-j];
        if (d == 0)
            continue;
        vector<T> temp = c;
        T coef = d / ld;
        for (int j=m; j<n; j++)
            c[j] -= coef * b[j-m];
        if (2 * l <= i) {
            l = i + 1 - l;
            b = temp;
            ld = d;
            m = 0;
        }
    }
    c.resize(l + 1);
    c.erase(c.begin());
    for (T &x : c)
        x = modBase(0)-x;
    return c;
}

int m;
ll t_[ms],s[ms],t[ms];
ll h[ms];
ll a[ms];

inline void mull(ll*p,ll*q) {
	for(int i=0;i<m+m;++i) t_[i]=0;
	for(int i=0;i<m;++i) if(p[i])
		for(int j=0;j<m;++j)
			t_[i+j]=(t_[i+j]+p[i]*q[j])%mod;
	for(int i=m+m-1;i>=m;--i) if(t_[i])
		//miuns t_[i]x^{i-m}(x^m-\sum_{j=0}^{m-1} x^{m-j-1}h_j)
		for(int j=m-1;~j;--j)
			t_[i-j-1]=(t_[i-j-1]+t_[i]*h[j])%mod;
	for(int i=0;i<m;++i) p[i]=t_[i];
}

inline ll calc(ll K) {
	for(int i=m;~i;--i)
		s[i]=t[i]=0;
	//init
	s[0]=1; if(m!=1) t[1]=1; else t[0]=h[0];
	//binary-exponentiation
	while(K)
	{
		if(K&1) mull(s,t);
		mull(t,t); K>>=1;
	}
	ll su=0;
	for(int i=0;i<m;++i) su=(su+s[i]*a[i])%mod;
	return (su%mod+mod)%mod;
}

vector<modBase<>> arr;