def is_safe(values):
    previous = -1
    direction = 0
    safe = True
    for value in values:
        if previous == -1:
            previous = value
            continue
        diff = previous - value
        previous = value
        this_direction = 0
        if abs(diff) > 3 or diff == 0:
            safe = False
            break
        if diff < 0:
            this_direction = -1
        else:
            this_direction = 1

        if direction == 0:
            direction = this_direction
        else:
            if direction != this_direction:
                safe = False
                break
    return safe

silver = 0
gold = 0
for line in open("input.txt"):
    values = [int(v) for v in line.strip().split(" ")]
    gold_increment = False
    if is_safe(values):
        silver += 1
        gold += 1
    else:
        print()
        print(values)
        for index in range(0, len(values)):
            new_values = [elements for i, elements in enumerate(values) if i != index]
            print(new_values)
            if is_safe(new_values):
                gold += 1
                gold_increment = True
                break
        if not gold_increment:
            print("FAILED")


# 271 too low
print("Silver:", silver)
print(gold)
