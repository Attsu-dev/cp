#pragma once
#include "../template.hpp"
#include <atcoder/segtree>
ll op_max(ll a, ll b) { return max(a, b); }
ll e_max() { return -INF; }
using SegMAX = atcoder::segtree<ll, op_max, e_max>;
