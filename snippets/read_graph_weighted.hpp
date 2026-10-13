// グラフ入力（重み付き）
VVPLL G(N);
rep(i, M) {
  ll u, v, w;
  cin >> u >> v >> w;
  u--, v--;
  G[u].emplace_back(v, w);
  G[v].emplace_back(u, w);
}
