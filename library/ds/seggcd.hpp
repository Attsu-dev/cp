#pragma once
#include "base/template.hpp"
#include <atcoder/segtree>
ll op_gcd(ll a, ll b) { return gcd(a, b); }
ll e_gcd() { return 0; }
using SegGCD = atcoder::segtree<ll, op_gcd, e_gcd>;
