long long int mod = (119ll << 23) + 1, c_root = 3;

namespace NTT {
	typedef long long int ll;
	
	ll fexp(ll base, ll e) {
		ll ans = 1;
		while(e > 0) {
			if (e & 1) ans = ans * base % mod;
			base = base * base % mod;
			e >>= 1;
		}
		return ans;
	}
	
	ll inv_mod(ll base) {
		return fexp(base, mod - 2);
	}
	
	void ntt(vector<ll>& a, bool inv) {
		int n = (int) a.size();
		if (n == 1) return;
		
		for(int i = 0, j = 0; i < n; i++) {
			if (i > j) {
				swap(a[i], a[j]);
			}
			for(int l = n / 2; (j ^= l) < l; l >>= 1);
		}
		
		for(int sz = 1; sz < n; sz <<= 1) {
			ll delta = fexp(c_root, (mod - 1) / (2 * sz)); //delta = w_2sz
			if (inv) {
				delta = inv_mod(delta);
			}
			for(int i = 0; i < n; i += 2 * sz) {
				ll w = 1;
				for(int j = 0; j < sz; j++) {
					ll u = a[i + j], v = w * a[i + j + sz] % mod;
					a[i + j] = (u + v + mod) % mod;
					a[i + j] = (a[i + j] + mod) % mod;
					a[i + j + sz] = (u - v + mod) % mod;
					a[i + j + sz] = (a[i + j + sz] + mod) % mod;
					w = w * delta % mod;
				}
			}
		}
		if (inv) {
			ll inv_n = inv_mod(n);
			for(int i = 0; i < n; i++) {
				a[i] = a[i] * inv_n % mod;
			}
		}
		for(int i = 0; i < n; i++) {
			a[i] %= mod;
			a[i] = (a[i] + mod) % mod;
		}
	}
	
	void multiply(vector<ll> &a, vector<ll> &b, vector<ll> &ans) {
		int lim = (int) max(a.size(), b.size());
		int n = 1;
		while(n < lim) n <<= 1;
		n <<= 1;
		a.resize(n);
		b.resize(n);
		ans.resize(n);
		ntt(a, false);
		ntt(b, false);
		for(int i = 0; i < n; i++) {
			ans[i] = a[i] * b[i] % mod;
		}
		ntt(ans, true);
	}
};
