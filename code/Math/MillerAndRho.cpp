typedef long long int ll;

bool overflow(ll a, ll b) {
	return b && (a >= (1ll << 62) / b);
}

ll add(ll a, ll b, ll md) {
	return (a + b) % md;
}

ll mul(ll a, ll b, ll md) {
	if (!overflow(a, b)) return (a * b) % md;
	ll ans = 0;
	while(b) {
		if (b & 1) ans = add(ans, a, md);
		a = add(a, a, md);
		b >>= 1;
	}
	return ans;
}

ll fexp(ll a, ll e, ll md) {
	ll ans = 1;
	while(e) {
		if (e & 1) ans = mul(ans, a, md);
		a = mul(a, a, md);
		e >>= 1;
	}
	return ans;
}

ll my_rand() {
	ll ans = rand();
	ans = (ans << 31) | rand();
	return ans;
}

ll gcd(ll a, ll b) {
	while(b) {
		ll t = a % b;
		a = b;
		b = t;
	}
	return a;
}

bool miller(ll p, int iteracao) {
	if(p < 2) return 0;
	if(p % 2 == 0) return (p == 2);
	ll s = p - 1;
	while(s % 2 == 0) s >>= 1;
	for(int i = 0; i < iteracao; i++) {
		ll a = rand() % (p - 1) + 1, temp = s;
		ll mod = fexp(a, temp, p);
		while(temp != p - 1 && mod != 1 && mod != p - 1) {
			mod = mul(mod, mod, p);
			temp <<= 1;
		}
		if(mod != p - 1 && temp % 2 == 0) return 0;
	}
	return 1;
}

ll rho(ll n) {
	if (n == 1 || miller(n, 10)) return n;
	if (n % 2 == 0) return 2;
	while(1) {
		ll x = my_rand() % (n - 2) + 2, y = x;
		ll c = 0, cur = 1;
		while(c == 0) {
			c = my_rand() % (n - 2) + 1;
		}
		while(cur == 1) {
			x = add(mul(x, x, n), c, n);
			y = add(mul(y, y, n), c, n);
			y = add(mul(y, y, n), c, n);
			cur = gcd((x >= y ? x - y : y - x), n);
		}
		if (cur != n) return cur;
	}
}