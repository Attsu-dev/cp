#pragma once
#include "base/template.hpp"
#include <atcoder/fenwicktree>

class SortedSet {
  int MAX, sz;
  mutable atcoder::fenwick_tree<int> fw;
  vector<bool> exists;

public:
  SortedSet(int MAX) : MAX(MAX), sz(0), fw(MAX), exists(MAX, false) {}

  bool contains(int x) const {
    assert(0 <= x && x < MAX);
    return exists[x];
  }

  int size() const { return sz; }

  bool add(int x) {
    assert(0 <= x && x < MAX);
    if (exists[x])
      return false;
    exists[x] = true;
    fw.add(x, 1);
    sz++;
    return true;
  }

  bool erase(int x) {
    assert(0 <= x && x < MAX);
    if (!exists[x])
      return false;
    exists[x] = false;
    fw.add(x, -1);
    sz--;
    return true;
  }

  int operator[](int k) const {
    assert(0 <= k && k < sz);
    int l = -1, r = MAX;
    while (r - l > 1) {
      int m = (l + r) / 2;
      if (fw.sum(0, m + 1) > k)
        r = m;
      else
        l = m;
    }
    return r;
  }

  int order(int x) const {
    assert(0 <= x && x <= MAX);
    return fw.sum(0, x);
  }
};
