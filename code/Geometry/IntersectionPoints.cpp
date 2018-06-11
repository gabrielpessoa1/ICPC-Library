int intersectionPoints(vector<pair<PT, PT>> v) {
    int n = v.size();
    vector<pair<int, int> events;
    vector<pair<int, int>> vertInt;
    // tipo -1 = Inicio de segmento horizontal
    // tipo inf = Fim de segmento horizontal
    // tipo natural = Segmento vertical
    for(int i = 0; i < n; i++) {
        if(v.first.x == v.second.x) {
            int y0 = min(v.first.y, v.second.y), y1 = max(v.first.y, v.second.y);
            events.push_back({v.first.x, vertInt.size()});
            vertInt.push_back({y0, y1});
        } else {
            int x0 = min(v.first.x, v.second.x), x1 = max(v.first.x, v.second.x);
            events.push_back({x0, -1});
            events.push_back({x1, inf});
        }
    }
    sort(events.begin(), events.end());
    int ans = 0;
    for(int i = 0; i < events.size(); i++) {
        int t = events[i].second;
        if(t == -1) {
            segUpdate(events[i].first, 1);
        } else if(t == inf) {
            segUpdate(events[i].first, 0);
        } else {
            ans += segQuery(vertInt[t].first, vertInt[t].second);
        }
    }
    return ans;
}
