int n, k;
ll dpold[ms], dp[ms], c[ms][ms]; // c(i, j) pode ser funcao
void compute(int l, int r, int optl, int optr) {
    if(l>r) return;
    int mid = (l+r)/2;
    pair<ll, int> best = {inf, -1}; // long long inf
    for(int k = optl; k <= min(mid, optr); k++) {
        best = min(best, {dpold[k-1] + c[k][mid], k});
    }
    dp[mid] = best.first;
    int opt = best.second;
    compute(l, mid-1, optl, opt);
    compute(mid+1, r, opt, optr);
}
ll solve() {
    dp[0] = 0;
    for(int i = 1; i <= n; i++) dp[i] = inf; // initialize row 0 of the dp
    for(int i = 1; i <= k; i++) {
        swap(dpold, dp);
        compute(0, n, 0, n); // solve row i of the dp
    }
    return dp[n]; // return dp[k][n]
}