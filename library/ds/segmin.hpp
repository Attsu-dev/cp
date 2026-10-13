#pragma once
#include "base/template.hpp"
#include <atcoder/segtree>
ll op_min(ll a, ll b) { return min(a, b); }
ll e_min() { return 2e18; }
using SegMIN = atcoder::segtree<ll, op_min, e_min>;
