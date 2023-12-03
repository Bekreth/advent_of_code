file = "input.txt"

symbols = []
possible_parts = []
for i, line in enumerate(open(file)):
    part_number = ""
    for j, character in enumerate(line.strip()):
        if character.isdigit():
            part_number += character
        else:
            if character != ".":
                symbols += [(i, j, character)]
            if part_number != "":
                possible_parts += [[(range(i - 1, i + 2), range(j - len(part_number) - 1, j + 1)), int(part_number)]]
                part_number = ""
    if part_number != "":
        possible_parts += [[(range(i - 1, i + 2), range(j - len(part_number) - 1, j + 1)), int(part_number)]]
        part_number = ""

debug = []
parts = []
total_part_number = 0
for possible_part in possible_parts:
    [(r0, r1), part] = possible_part
    adjacent = False
    for symbol in symbols:
        if symbol[0] in r0:
            if symbol[1] in r1:
                adjacent = True
                break
    debug +=[(r0, r1, adjacent, part)]
    if adjacent:
        parts += [[(r0, r1), part]]
        total_part_number += part

total_gear_ratio = 0
for possible_gear in symbols:
    if possible_gear[2] != "*":
        continue
    adjacent_parts = []
    for part in parts:
        [(r0, r1), part_number] = part
        if possible_gear[0] in r0:
            if possible_gear[1] in r1:
                adjacent_parts += [part_number]
    if len(adjacent_parts) > 1:
        gear_ratio = 1
        for gear_part in adjacent_parts:
            gear_ratio *= gear_part
        total_gear_ratio += gear_ratio

print("S:", total_part_number)
print("G:", total_gear_ratio)
exit(0)

running_total = 0
for d in debug:
    if d[2]:
        running_total +=d[3]
    print(d[2], "====", d[3], "====", running_total)
    for i, line in enumerate(open(file)):
        if i in d[0]:
            output = ""
            for j, character in enumerate(line.strip()):
                if j in d[1]:
                    output += character
            if output != "":
                print(output)

