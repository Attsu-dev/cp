// 幅優先探索
VLL dist(G.size(), -1);
queue<ll> q;

dist[s] = 0;
q.push(s);

while (!q.empty()) {
  ll v = q.front();
  q.pop();

  for (ll to : G[v]) {
    if (dist[to] != -1) continue;

    dist[to] = dist[v] + 1;
    q.push(to);
  }
}
