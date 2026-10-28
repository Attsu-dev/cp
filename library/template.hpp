#pragma once
#include <bits/stdc++.h>
using namespace std;

// clang-format off
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using VLL = vector<ll>;
using VVLL = vector<vector<ll>>;
using VVVLL = vector<vector<vector<ll>>>;
using VD = vector<double>;
using VVD = vector<vector<double>>;
using VVVD = vector<vector<vector<double>>>;
using VS = vector<string>;
using VVS = vector<vector<string>>;
using VB = vector<bool>;
using VVB = vector<vector<bool>>;
using VVVB = vector<vector<vector<bool>>>;
using PLL = pair<ll, ll>;
using VPLL = vector<pair<ll, ll>>;
using VVPLL = vector<vector<pair<ll, ll>>>;
template<class T> using minpq = priority_queue<T, vector<T>, greater<T>>;
#define rep(i, n) for (ll i = 0; i < ll(n); ++i)
#define rrep(i, n) for (ll i = ll(n) - 1; i >= 0; --i)
#define reps(i, s, n) for (ll i = ll(s); i < ll(n); ++i)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
const ll INF = 4e18;
const int DX[] = {1, 0, -1, 0, 1, 1, -1, -1};
const int DY[] = {0, 1, 0, -1, -1, 1, -1, 1};
void print(const auto& x, const auto&... xs) { cout << x; ((cout << ' ' << xs), ...); cout << '\n'; }
void printv(const auto& v, bool ln = 0) { int n = v.size(); rep(i, n) cout << v[i] << " \n"[ln || i + 1 == n]; if (!n) cout << '\n'; }
void printvv(const auto& vv) { for (const auto& v : vv) printv(v); }
void YesNo(bool b) { cout << (b ? "Yes" : "No") << '\n'; }
bool chmax(auto& a, auto b) { return a < b ? a = b, 1 : 0; }
bool chmin(auto& a, auto b) { return a > b ? a = b, 1 : 0; }
ll sq(ll x) { return x * x; }
ll cube(ll x) { return x * x * x; }
ll digit_sum(ll n) { ll s = 0; for (; n; n /= 10) s += n % 10; return s; }
ll floor_div(ll a, ll b) { ll q = a / b, r = a % b; return q - (r != 0 && ((r < 0) != (b < 0))); }
ll ceil_div(ll a, ll b) { ll q = a / b, r = a % b; return q + (r != 0 && ((r < 0) == (b < 0))); }
bool inside(ll y, ll x, ll H, ll W) { return 0 <= y && y < H && 0 <= x && x < W; }
template<class T> void sort_unique(vector<T>& v) { sort(all(v)); v.erase(unique(all(v)), v.end()); }
VLL cumsum(const VLL& a) { VLL s(a.size() + 1); rep(i, a.size()) s[i + 1] = s[i] + a[i]; return s; }
template<class T> ll lb(const vector<T>& v, const T& x) { return lower_bound(all(v), x) - v.begin(); }
template<class T> ll ub(const vector<T>& v, const T& x) { return upper_bound(all(v), x) - v.begin(); }
