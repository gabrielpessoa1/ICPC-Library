const int limit = 

vector<vector<int>> build_automaton(string s) {
    s += '#'; //tem que ser diferente de todos os caracteres
    int n = (int) s.size();
    vector<vector<int>> ans(n, vector<int>(limit));
    vector<int> fail(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < limit; j++) {
            if (i == 0) {
                if (s[i] == j + 'a') {
                    ans[i][j] = i + 1;
                } else {
                    ans[i][j] = 0;
                }
            } else {
                if (s[i] == j + 'a') {
                    ans[i][j] = i + 1;
                } else {
                    ans[i][j] = ans[fail[i - 1]][j];
                }
            }
        }
        if (i == 0) {
            continue;
        }
        int j = fail[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = fail[j - 1];
        }
        fail[i] = j + (s[i] == s[j]);
    }
    return ans;
}