const double eps = 1e-7;

int gauss (vector<vector<double>> a, vector<double> & ans) {
    int n = (int) a.size();
    int m = (int) a[0].size() - 1;

    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        int sel = row;
        for (int i=row; i<n; ++i){
            if (abs (a[i][col]) > abs (a[sel][col]))
                sel = i;
        }
        if (abs (a[sel][col]) < eps) continue;
        for (int i=col; i<=m; ++i)
            swap (a[sel][i], a[row][i]);
        where[col] = row;
        for (int i=0; i<n; ++i){
            if (i != row) {
                double c = a[i][col] / a[row][col];
                for (int j=col; j<=m; ++j)
                    a[i][j] -= a[row][j] * c;
            }
        }
        ++row;
    }
    ans.assign (m, 0);
    for (int i=0; i<m; ++i){
        if (where[i] != -1)
            ans[i] = a[where[i]][m] / a[where[i]][i];
    }
    for (int i=0; i<n; ++i) {
        double sum = 0;
        for (int j=0; j<m; ++j)
            sum += ans[j] * a[i][j];
        if (abs (sum - a[i][m]) > eps)
            return 0;
    }
    for (int i=0; i<m; ++i){
        if (where[i] == -1)
            return INF;
    }
    return 1;
}

// mod 2 (xor);
int gauss (vector <bitset<ms>> a, int m) {
    int n = (int) a.size();
    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        for (int i=row; i<n; ++i){
            if (a[i][col]) {
                swap (a[i], a[row]);
                break;
            }
        }
        if (!a[row][col]) continue;
        where[col] = row;
        for (int i=0; i<n; ++i){
            if (i != row && a[i][col])
                a[i] ^= a[row];
        }
        ++row;
    }
    //same above
}
