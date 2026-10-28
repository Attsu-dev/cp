// ダイクストラ
VLL dist(G.size(), INF);
priority_queue<array<ll, 2>, vector<array<ll, 2>>, greater<array<ll, 2>>> pq;

dist[s] = 0;
pq.push({0, s});

while (!pq.empty()) {
  auto [d, v] = pq.top();
  pq.pop();
  if (d != dist[v]) continue;

  for (auto [to, cost] : G[v]) {
    if (chmin(dist[to], d + cost)) {
      pq.push({dist[to], to});
    }
  }
}
