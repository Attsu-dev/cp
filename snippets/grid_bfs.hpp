// グリッド幅優先探索
VVLL dist(H, VLL(W, -1));
queue<array<ll, 2>> q;

dist[s.first][s.second] = 0;
q.push({s.first, s.second});

while (!q.empty()) {
  auto [i, j] = q.front();
  q.pop();

  rep(dir, 4) {
    ll ni = i + dx[dir];
    ll nj = j + dy[dir];
    if (ni < 0 || H <= ni || nj < 0 || W <= nj) continue;
    if (S[ni][nj] == '#') continue;
    if (dist[ni][nj] != -1) continue;

    dist[ni][nj] = dist[i][j] + 1;
    q.push({ni, nj});
  }
}
