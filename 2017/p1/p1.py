import sys
from functools import reduce

inp = sys.stdin.readline().strip()

l = zip(inp, inp[-1:] + inp[:-1])
lf = filter(lambda t: t[0] == t[1], l)
tot = reduce(lambda acc, t: acc + int(t[0]), lf, 0)
print(tot)
