// グラフ入力
VVLL G(N);
rep(i, M) {
  ll u, v;
  cin >> u >> v;
  u--, v--;
  G[u].emplace_back(v);
  G[v].emplace_back(u);
}
