#pragma once
#include "base/template.hpp"
#include <atcoder/segtree>
ll op_sum(ll a, ll b) { return a + b; }
ll e_sum() { return 0; }
using SegSUM = atcoder::segtree<ll, op_sum, e_sum>;
