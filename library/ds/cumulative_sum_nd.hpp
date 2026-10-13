#pragma once
#include "base/template.hpp"

// n 次元累積和
template <class T = ll>
class CumulativeSumND {
  VLL shape;
  vector<size_t> stride;
  vector<T> prefix;
  bool built = false;

  size_t point_index(const VLL& p) const {
    assert(p.size() == shape.size());

    size_t index = 0;
    for (int d = 0; d < (int)shape.size(); d++) {
      assert(0 <= p[d] && p[d] < shape[d]);
      index += (p[d] + 1) * stride[d];
    }
    return index;
  }

 public:
  CumulativeSumND() = default;

  explicit CumulativeSumND(const VLL& shape) {
    init(shape);
  }

  void init(const VLL& new_shape) {
    assert(!new_shape.empty());

    shape = new_shape;
    stride.assign(shape.size(), 1);

    size_t total = 1;
    for (int d = (int)shape.size() - 1; d >= 0; d--) {
      assert(shape[d] >= 0);
      size_t width = (size_t)shape[d] + 1;
      stride[d] = total;
      assert(total <= numeric_limits<size_t>::max() / width);
      total *= width;
    }

    prefix.assign(total, T{});
    built = false;
  }

  // 座標 p に value を加える。
  void add(const VLL& p, const T& value) {
    assert(!built);
    prefix[point_index(p)] += value;
  }

  void build() {
    assert(!built);

    for (int d = 0; d < (int)shape.size(); d++) {
      size_t width = (size_t)shape[d] + 1;
      for (size_t i = 0; i < prefix.size(); i++) {
        if (i / stride[d] % width > 0) prefix[i] += prefix[i - stride[d]];
      }
    }
    built = true;
  }

  // 半開区間 [l, r) の総和を返す。
  T sum(const VLL& l, const VLL& r) const {
    assert(built);
    assert(l.size() == shape.size() && r.size() == shape.size());
    assert(shape.size() < numeric_limits<size_t>::digits);
    for (int d = 0; d < (int)shape.size(); d++)
      assert(0 <= l[d] && l[d] <= r[d] && r[d] <= shape[d]);

    T answer{};
    for (size_t mask = 0; mask < (size_t(1) << shape.size()); mask++) {
      size_t index = 0;
      int chosen_l = 0;

      for (int d = 0; d < (int)shape.size(); d++) {
        if (mask >> d & 1) {
          index += l[d] * stride[d];
          chosen_l++;
        } else {
          index += r[d] * stride[d];
        }
      }

      if (chosen_l % 2 == 0)
        answer += prefix[index];
      else
        answer -= prefix[index];
    }
    return answer;
  }
};
