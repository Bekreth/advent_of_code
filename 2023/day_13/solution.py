silver = 0
gold = 0

paths = []

def find_mirror(path):
    print(path)
    row_count = len(path)
    for i in range(0, row_count):
        if path[i] == path[i+1]:
            r = (i + 1)*100
            j = (row_count - i + 1)
            print(r, j)
            return r + j
    return 0
    #column_count = len(path[0])
    #for j in range(0, column_count):
    #    pass

swap_path = []
for line in open("sample.txt"):
    if line == "\n":
        silver += find_mirror(swap_path)
        swap_path = []
        continue
    swap_path += [[c == "." for c in line.strip()]]
    

for i, p in enumerate(paths):
    print(i, p)

print([find_mirror(p) for p in paths])

print("S:", silver,"\nG:", gold)
