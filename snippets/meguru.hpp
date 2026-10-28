// めぐる式二分探索
auto isOK = [&](${1:ll} X) -> bool {

};

${1:ll} ok = 1;
${1:ll} ng = INF;

while (abs(ok - ng) > 1) {
  ${1:ll} mid = (ok + ng) / 2;
  if (isOK(mid))
    ok = mid;
  else
    ng = mid;
}

print(ok);
