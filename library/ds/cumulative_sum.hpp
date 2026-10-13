#pragma once
#include "base/template.hpp"

// 累積和
template <class T>
vector<T> cumsum(const vector<T>& a) {
  int n = a.size();
  vector<T> s(n + 1, T{});
  for (int i = 0; i < n; i++) s[i + 1] = s[i] + a[i];
  return s;
}
