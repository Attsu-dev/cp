#pragma once
#include "base/template.hpp"
#include <atcoder/segtree>
ll op_max(ll a, ll b) { return max(a, b); }
ll e_max() { return -2e18; }
using SegMAX = atcoder::segtree<ll, op_max, e_max>;
