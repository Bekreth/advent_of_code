class Mapping:
    range_delta = []
    known_values = {}
    def __init__(self):
        self.range_delta = []
        self.known_values = {}

    def update_mapping(self, mapping_info: [int]):
        destination = int(mapping_info[0])
        source = int(mapping_info[1])
        _range = int(mapping_info[2])
        rd = (range(source, source + _range), destination - source)
        self.range_delta += [rd]

    def apply_mapping(self, pre_map: int) -> int:
        key = pre_map.__str__()
        if key in self.known_values:
            return self.known_values[str(pre_map)]
        output = pre_map
        for (_range, delta) in self.range_delta:
            if pre_map in _range:
                output = pre_map + delta
                break
        self.known_values[key] = output
        return output

mapper = Mapping()
mappers = []
silver_seeds = []
gold_seed_ranges = []
for line in open("input.txt"):
    if line == "\n":
        silver_seeds = list(map(mapper.apply_mapping, silver_seeds))
        mappers += [mapper]
        mapper = None
    elif silver_seeds == []:
        silver_seeds = list(map(int, line.split()[1:]))
        for i in range(0, int(len(silver_seeds) / 2)):
            start = silver_seeds[2*i]
            end = start + silver_seeds[2*i + 1]
            gold_seed_ranges += [range(start, end)]
    else:
        if mapper == None:
            mapper = Mapping()
        else:
            mapper.update_mapping(line.split())

silver = sorted(silver_seeds)[0] 

gold = 1_000_000_000
for seed_range in gold_seed_ranges:
    print(seed_range)
    for seed in seed_range:
        for m in mappers:
            seed = m.apply_mapping(seed)
        if seed < gold:
            print("Update", seed, seed)
            gold = seed
#for m in mappers:
#    print(m.range_delta, m.known_values)
print("S:", silver,"\nG:", gold)
