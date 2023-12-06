silver = 1
gold = 1

solver = lambda t0, t1: t1 * (t0 - t1)

def solve_best(time, distance):
    return list(filter(lambda a: a  > distance, [solver(time, i) for i in range(1, time)]))

times_distances =  []
times = []
distances = []
gold_time_distance = [0, 0]

for i, line in enumerate(open("input.txt")):
    split_string = line.split()[1:]
    gold_value = int("".join(split_string))
    if i == 0:
        times = list(map(int, split_string))
        gold_time_distance[0] = gold_value
    else:
        distances = list(map(int, split_string))
        gold_time_distance[1] = gold_value

times_distances = list(zip(times, distances))

best_solves = []
for (time, distance) in times_distances:
    solves = solve_best(time, distance)
    best_solves += [len(solves)]

for solve in best_solves:
    silver *= solve

gold = len(solve_best(gold_time_distance[0], gold_time_distance[1]))

print("S:", silver,"\nG:", gold)
