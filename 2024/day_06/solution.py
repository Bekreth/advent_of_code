from enum import Enum

class Direction(Enum):
    Up = 0
    Right = 1
    Down = 2
    Left = 3

silver = 0

obstacle_map = []
guard_position = (0, 0)
direction = Direction.Up
i = 0
max_x = 0
for line in open("input.txt"):
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

locations_visited = set()
walk_counter = 0
while True:
    breaker = False
    loop_set = set()
    #print()
    #print(direction)
    #print("Guard", guard_position)
    #print(locations_visited)
    match direction:
        case Direction.Up:
            y_values = x_map[guard_position[0]]
            possible_values = [y for y in y_values if y < guard_position[1]]
            new_position = (guard_position[0], -1)
            if len(possible_values) == 0:
                breaker = True
            else:
                new_position = (guard_position[0], possible_values[-1] + 1)
            print(possible_values)
            print("Next", new_position)
            for i in range(new_position[1], guard_position[1] + 1):
                locations_visited.add((guard_position[0], i))
                loop_set.add((guard_position[0], i))
            guard_position = new_position
            direction = Direction.Right

        case Direction.Right:
            x_values = y_map[guard_position[1]]
            possible_values = [x for x in x_values if x > guard_position[0]]
            new_position = (max_x, guard_position[1])
            if len(possible_values) == 0:
                breaker = True
            else:
                new_position = (possible_values[0] - 1, guard_position[1])
            print(possible_values)
            print("Next", new_position)
            for i in range(guard_position[0], new_position[0] + 1):
                locations_visited.add((i, guard_position[1]))
                loop_set.add((i, guard_position[1]))
            guard_position = new_position
            direction = Direction.Down

        case Direction.Down:
            y_values = x_map[guard_position[0]]
            possible_values = [y for y in y_values if y > guard_position[1]]
            new_position = (guard_position[0], max_y)
            if len(possible_values) == 0:
                breaker = True
            else:
                new_position = (guard_position[0], possible_values[0] - 1)
            print(possible_values)
            print("Next", new_position)
            for i in range(guard_position[1], new_position[1] + 1):
                locations_visited.add((guard_position[0], i))
                loop_set.add((guard_position[0], i))
            guard_position = new_position
            direction = Direction.Left

        case Direction.Left:
            x_values = y_map[guard_position[1]]
            possible_values = [x for x in x_values if x < guard_position[0]]
            new_position = (-1, guard_position[1])
            if len(possible_values) == 0:
                breaker = True
            else:
                new_position = (possible_values[-1] + 1, guard_position[1])
            print(possible_values)
            print("Next", new_position)
            for i in range(new_position[0], guard_position[0]):
                locations_visited.add((i, guard_position[1]))
                loop_set.add((i, guard_position[1]))
            guard_position = new_position
            direction = Direction.Up
    #print("This loop:", loop_set)
    #input("...")
    if breaker:
        break

print("Silver:", len(locations_visited))
