from walker import path_check
import copy

silver = 0

obstacle_map = []
guard_position = (0, 0)
i = 0
max_x = 0
for line in open("sample.txt"):
    j = 0
    for c in line.strip():
        if c == '#':
            obstacle_map.append((j, i))
        if c == "^":
            guard_position = (j, i)
        j += 1
    if i == 0:
        max_x = j
    i += 1
max_y = i

x_map = {}
y_map = {}

for (x, y) in obstacle_map:
    if x in x_map:
        x_map[x].append(y)
    else:
        x_map[x] = [y]
    if y in y_map:
        y_map[y].append(x)
    else:
        y_map[y] = [x]

for key, value in x_map.items():
    value.sort()

for key, value in y_map.items():
    value.sort()

paths_traveled = list(path_check(guard_position, x_map, y_map, max_x, max_y)[1])
paths_traveled.sort()

# TODO: (7,6) and (7,7) from sample fails.  Add a line round by round break to sort that out
gold_counter = 0
print(paths_traveled)
for (x, y) in paths_traveled:
    if x in x_map and y in x_map[x]:
        continue
    new_x_map = copy.deepcopy(x_map)
    new_y_map = copy.deepcopy(y_map)
    if x in new_x_map:
        new_x_map[x].append(y)
    else:
        new_x_map[x] = [y]
    if y in new_y_map:
        new_y_map[y].append(x)
    else:
        new_y_map[y] = [x]
    
    if path_check(guard_position, new_x_map, new_y_map, max_x, max_y)[0]:
        print((x, y), "Success!")
        gold_counter += 1
    else:
        print((x, y), "Fail!")

print("Silver", len(paths_traveled) - 1)
print("Gold", gold_counter)
