#pragma once
#include "base/template.hpp"

ll digit_sum(ll x) {
  assert(x >= 0);
  ll res = 0;
  while (x > 0) {
    res += x % 10;
    x /= 10;
  }
  return res;
}
