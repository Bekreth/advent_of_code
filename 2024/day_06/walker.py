from enum import Enum

class Direction(Enum):
    Up = 0
    Right = 1
    Down = 2
    Left = 3

def path_check(guard_position, x_map, y_map, max_x, max_y):
    direction = Direction.Up
    locations_visited = set()
    history = []
    walk_counter = 0
    breaker = False
    while not breaker:
        loop_set = set()
        match direction:
            case Direction.Up:
                new_position = (guard_position[0], -1)
                if guard_position[0] not in x_map:
                    breaker = True
                else:
                    y_values = x_map[guard_position[0]]
                    possible_values = [y for y in y_values if y < guard_position[1]]
                if len(possible_values) == 0:
                    breaker = True
                else:
                    new_position = (guard_position[0], possible_values[-1] + 1)
                for i in range(new_position[1], guard_position[1] + 1):
                    locations_visited.add((guard_position[0], i))
                    loop_set.add((guard_position[0], i))
                guard_position = new_position
                direction = Direction.Right

            case Direction.Right:
                new_position = (max_x, guard_position[1])
                if guard_position[1] not in y_map:
                    breaker = True
                else:
                    x_values = y_map[guard_position[1]]
                    possible_values = [x for x in x_values if x > guard_position[0]]
                if len(possible_values) == 0:
                    breaker = True
                else:
                    new_position = (possible_values[0] - 1, guard_position[1])
                for i in range(guard_position[0], new_position[0] + 1):
                    locations_visited.add((i, guard_position[1]))
                    loop_set.add((i, guard_position[1]))
                guard_position = new_position
                direction = Direction.Down

            case Direction.Down:
                new_position = (guard_position[0], max_y)
                if guard_position[0] not in x_map:
                    breaker = True
                else:
                    y_values = x_map[guard_position[0]]
                    possible_values = [y for y in y_values if y > guard_position[1]]
                if len(possible_values) == 0:
                    breaker = True
                else:
                    new_position = (guard_position[0], possible_values[0] - 1)
                for i in range(guard_position[1], new_position[1] + 1):
                    locations_visited.add((guard_position[0], i))
                    loop_set.add((guard_position[0], i))
                guard_position = new_position
                direction = Direction.Left

            case Direction.Left:
                new_position = (-1, guard_position[1])
                if guard_position[1] not in y_map:
                    breaker = True
                else:
                    x_values = y_map[guard_position[1]]
                    possible_values = [x for x in x_values if x < guard_position[0]]
                if len(possible_values) == 0:
                    breaker = True
                else:
                    new_position = (possible_values[-1] + 1, guard_position[1])
                for i in range(new_position[0], guard_position[0]):
                    locations_visited.add((i, guard_position[1]))
                    loop_set.add((i, guard_position[1]))
                guard_position = new_position
                direction = Direction.Up

        for previous_path in history:
            if previous_path == loop_set:
                return (True, locations_visited)
        history.append(loop_set)

    return (False, locations_visited)
