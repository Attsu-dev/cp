import re
import sys

targets = [
    "ll",
    "ull",
    "ld",
    "VLL",
    "VVLL",
    "VVVLL",
    "VD",
    "VVD",
    "VVVD",
    "VS",
    "VVS",
    "VB",
    "VVB",
    "VVVB",
    "PLL",
    "VPLL",
    "VVPLL",
    "minpq",
    "rep",
    "rrep",
    "reps",
    "all",
    "rall",
    "INF",
    "DX",
    "DY",
    "print",
    "printv",
    "printvv",
    "YesNo",
    "chmax",
    "chmin",
    "cumsum",
]


def clean(code: str) -> str:
    lines = [line for line in code.splitlines() if not line.startswith("#line")]
    code = "\n".join(lines) + "\n"

    while True:
        unused = [
            name for name in targets if len(re.findall(rf"\b{name}\b", code)) == 1
        ]

        if not unused:
            return code

        pattern = r"\b(?:" + "|".join(unused) + r")\b"
        lines = [line for line in code.splitlines() if not re.search(pattern, line)]
        code = "\n".join(lines) + "\n"


sys.stdout.write(clean(sys.stdin.read()))
