int maxSegOverlap(vector<pair<int, int>> v) {
    int n = v.size();
    vector<pair<int, int>> events(n * 2);
    // tipo 1 = Inicio de segmento
    // tipo 0 = Fim de segmento
    for(int i = 0; i < n; i++) {
        events[i*2] = make_pair(v[i].first, 1);
        events[i*2+1] = make_pair(v[i].second, 0);
    }
    sort(events.begin(), events.end());
    int qnt = 0, ans = 0;
    for(int i = 0; i < 2 * n; i++) {
        if(events[i].second) {
            ans = max(++qnt, ans);
        } else {
            --qnt;
        }
    }
    return ans;
}
