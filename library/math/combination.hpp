#pragma once
#include "base/template.hpp"
#include <atcoder/modint>

template <typename T> struct CombinationBase {
  vector<T> fact, inv_fact;

  CombinationBase(int n = 0) { init(n); }

  void init(int n) {
    assert(n >= 0);
    fact.assign(n + 1, T(1));
    inv_fact.assign(n + 1, T(1));
    for (int i = 1; i <= n; i++)
      fact[i] = fact[i - 1] * T(i);
    inv_fact[n] = fact[n].inv();
    for (int i = n; i >= 1; i--)
      inv_fact[i - 1] = inv_fact[i] * T(i);
  }

  T nCr(ll n, ll r) const {
    if (r < 0 || n < r)
      return T(0);
    assert(n < (ll)fact.size());
    return fact[n] * inv_fact[r] * inv_fact[n - r];
  }

  T nPr(ll n, ll r) const {
    if (r < 0 || n < r)
      return T(0);
    assert(n < (ll)fact.size());
    return fact[n] * inv_fact[n - r];
  }

  T nHr(ll n, ll r) const {
    if (n == 0 && r == 0)
      return T(1);
    return nCr(n + r - 1, r);
  }
};

using Combination = CombinationBase<atcoder::modint998244353>;
