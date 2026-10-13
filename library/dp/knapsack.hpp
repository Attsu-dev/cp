#pragma once
#include "base/template.hpp"

template <class T>
T knapsack(const VLL& w, const vector<T>& v, ll W) {
  assert(w.size() == v.size());
  assert(0 <= W && W <= INT_MAX);
  int N = w.size();

  vector<T> dp(W + 1);

  for (int i = 0; i < N; i++) {
    assert(0 <= w[i] && w[i] <= W);
    for (ll j = W; j >= w[i]; j--) {
      chmax(dp[j], dp[j - w[i]] + v[i]);
    }
  }

  return *max_element(dp.begin(), dp.end());
}
