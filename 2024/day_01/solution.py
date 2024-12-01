
left = []
right = []
for line in open("input.txt"):
    values = line.strip().split("   ")
    left.append(int(values[0]))
    right.append(int(values[1]))
left.sort()
right.sort()
pairs = zip(left, right)


diffs = [abs(pair[0] - pair[1]) for pair in pairs]
silver = sum(diffs)
print("Silver: ", silver)

counter = {3: 0}
for item in right:
    if item in counter:
        counter[item] += 1
    else:
        counter[item] = 1

gold = 0
for item in left:
    if item in counter:
        gold += item * counter[item]
print("Gold: ", gold)


