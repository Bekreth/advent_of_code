silver = 0
gold = 0

rock_map = []
for line in open("input.txt"):
    row = [c for c in line.strip()]
    rock_map += [row]
for r in rock_map: print(r)

print()
updated_map = []
for i, row in enumerate(rock_map):
    if i == 0: 
        updated_map += [row]
        continue
    updated_row = [c if c != "O" else "."  for c in row]
    updated_map += [updated_row]
    for j, column in enumerate(row):
        if column == "O":
            k = i - 1
            while k >= -1:
                if k == -1:
                    updated_map[0][j] = "O"
                elif updated_map[k][j] != ".":
                    updated_map[k + 1][j] = "O"
                    break
                k -= 1

print("=======")
for i,r in enumerate(updated_map):
    factor = len(updated_map) - i
    line_count = len(list(filter(lambda a: a == "O", r)))
    total = factor * line_count
    print(factor, "*", line_count, "=", total)
    silver += total

print("S:", silver,"\nG:", gold)
