#pragma once

#include <vector>

template <typename mint>
std::vector<mint> bell_numbers(int N) {
  std::vector<mint> bell(N + 1), dp(N + 1);
  bell[0] = dp[0] = 1;

  for (int n = 1; n <= N; n++) {
    for (int k = n; k >= 1; k--) {
      dp[k] = dp[k] * k + dp[k - 1];
      bell[n] += dp[k];
    }
    dp[0] = 0;
  }

  return bell;
}
