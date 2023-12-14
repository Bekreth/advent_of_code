def map_printer(name, input_map):
    print(name, "vvvv")
    for i in input_map: print(i)
    print(name, "^^^^")

def tip_verticle(input_map, reverse):
    updated_map = []
    reference_map = []
    if reverse: 
        reference_map = reversed(input_map)
    else: 
        reference_map = input_map
    for i, row in enumerate(reference_map):
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
    if reverse:
        return reversed(updated_map)
    else:
        return updated_map

def tip_horizontal(input_map, reverse):
    updated_map = []
    reference_map = []
    if reverse: 
        reference_map = [list(reversed(r)) for r in input_map]
    else: 
        reference_map = input_map
    for i, row in enumerate(reference_map):
        updated_row = [c if c != "O" else "."  for c in row]
        updated_map += [updated_row]
        for j, column in enumerate(row):
            if column == "O":
                k = j - 1
                while k >= -1:
                    if k == -1:
                        updated_map[i][0] = "O"
                    elif updated_map[i][k] != ".":
                        updated_map[i][k + 1] = "O"
                        break
                    k -= 1
    if reverse:
        return [list(reversed(r)) for r in updated_map]
    else:
        return updated_map

def weigh_north_posts(input_map):
    output = 0
    for i,r in enumerate(input_map):
        factor = len(input_map) - i
        line_count = len(list(filter(lambda a: a == "O", r)))
        total = factor * line_count
        output += total
    return output

silver = 0
gold = 0

rock_map = []
for line in open("input.txt"):
    row = [c for c in line.strip()]
    rock_map += [row]

map_0 = [r.copy() for r in rock_map]
for i in range(0, 1_000_000_000):
    if i % 1_000 == 0: print(i / 10_000_000)
    map_1 = tip_verticle(map_0, False)
    map_2 = tip_horizontal(map_1, False)
    map_3 = tip_verticle(map_2, True)
    map_0 = tip_horizontal(map_3, True)
    

gold = weigh_north_posts(map_0)

print("S:", silver,"\nG:", gold)
