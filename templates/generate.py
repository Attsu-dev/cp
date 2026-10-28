import random


def main():
    n = rnd(1, 10)
    a = vec(n, 1, 100)

    print(n)
    print(*a)


def rnd(l, r):
    return random.randint(l, r)


def vec(n, l, r):
    return [rnd(l, r) for _ in range(n)]


def perm(n, start=1):
    p = list(range(start, start + n))
    random.shuffle(p)
    return p


abc = "abcdefghijklmnopqrstuvwxyz"
ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"


def string(n, chars):
    return "".join(random.choice(chars) for _ in range(n))


def tree(n):
    return [(rnd(1, v - 1), v) for v in range(2, n + 1)]


def graph(n, m):
    assert 0 <= m <= n * (n - 1) // 2

    edges = set()
    while len(edges) < m:
        u = rnd(1, n)
        v = rnd(1, n)

        if u == v:
            continue
        if u > v:
            u, v = v, u

        edges.add((u, v))

    return list(edges)


def digraph(n, m):
    assert 0 <= m <= n * (n - 1)

    edges = set()
    while len(edges) < m:
        u = rnd(1, n)
        v = rnd(1, n)

        if u != v:
            edges.add((u, v))

    return list(edges)


def wgraph(n, m, l, r):
    return [(u, v, rnd(l, r)) for u, v in graph(n, m)]


if __name__ == "__main__":
    main()
