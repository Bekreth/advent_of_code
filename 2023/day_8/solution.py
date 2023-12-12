stringer = lambda a: ''.join(a)

silver = 0
gold = 0

mapping = {}
direction = []
gold_direction = []
ghost_nodes = []
for i,line in enumerate(open("input.txt")):
    data = list(line.strip())
    if i == 0: 
        direction = data
        gold_direction = data
    elif i >= 2: 
        key = stringer(data[:3])
        mapping[key] = (stringer(data[7:10]), stringer(data[12:15]))
        if data[2] == "A": ghost_nodes += [key]

node = "AAA"
while node != "ZZZ":
    silver += 1
    move = direction[0]
    direction = direction[1:] + [move]
    node_data = mapping[node]
    if move == "L": node = node_data[0]
    else: node = node_data[1]

def ghost_ending(nodes):
    for node in nodes:
        if node[2] != "Z": return False
    return True

print(ghost_nodes)
while not ghost_ending(ghost_nodes):
    gold += 1
    move = gold_direction[0]
    gold_direction = gold_direction[1:] + [move]
    update_nodes = []
    for g_node in ghost_nodes:
        node_data = mapping[g_node]
        if move == "L": update_nodes += [node_data[0]]
        else: update_nodes += [node_data[1]]
    ghost_nodes = update_nodes
    if gold % 10_000_000 == 0: print(gold, ghost_nodes)


print("S:", silver,"\nG:", gold)
