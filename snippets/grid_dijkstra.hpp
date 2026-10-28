// グリッドダイクストラ
VVLL dist(H, VLL(W, INF));
priority_queue<array<ll, 3>, vector<array<ll, 3>>, greater<array<ll, 3>>> pq;

dist[s.first][s.second] = 0;
pq.push({0, s.first, s.second});

while (!pq.empty()) {
  auto [d, i, j] = pq.top();
  pq.pop();
  if (d != dist[i][j]) continue;

  rep(dir, 4) {
    ll ni = i + DX[dir];
    ll nj = j + DY[dir];
    if (!inside(ni, nj, H, W)) continue;
    if (S[ni][nj] == INF) continue;

    if (chmin(dist[ni][nj], d + S[ni][nj])) {
      pq.push({dist[ni][nj], ni, nj});
    }
  }
}
