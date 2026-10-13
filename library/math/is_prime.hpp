#pragma once
#include "base/template.hpp"

// 素数判定：O(√n)
bool is_prime(ll n) {
  if (n <= 1) return false;
  if (n == 2) return true;
  if (n % 2 == 0) return false;
  for (ll p = 3; p * p <= n; p += 2) {
    if (n % p == 0) return false;
  }
  return true;
}
