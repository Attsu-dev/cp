#pragma once
#include "base/template.hpp"

VPLL run_length(const VLL& A) {
  VPLL res;
  for (const ll& x : A) {
    if (res.empty() || res.back().first != x) {
      res.emplace_back(x, 1);
    } else {
      res.back().second++;
    }
  }
  return res;
}

vector<pair<char, ll>> run_length(const string& s) {
  vector<pair<char, ll>> res;
  for (char c : s) {
    if (res.empty() || res.back().first != c) {
      res.emplace_back(c, 1);
    } else {
      res.back().second++;
    }
  }
  return res;
}
