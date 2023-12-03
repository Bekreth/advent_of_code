E=enumerate
R=range
S=[]
p_parts=[]
for i,L in E(open("input.txt")):
    p_num=""
    for j,C in E(L):
        if C.isdigit():
            p_num+=C
        else:
            if C!=".":
                S+=[(i,j,C)]
            if p_num!="":
                p_parts+=[[(R(i-1, i+2), R(j-len(p_num)-1, j+1)), int(p_num)]]
                p_num=""

parts = []
Y=Z=0
for possible_part in p_parts:
    [(r0, r1), part] = possible_part
    adjacent = False
    for s in S:
        if s[0] in r0:
            if s[1] in r1:
                adjacent = True
    if adjacent:
        parts += [[(r0, r1), part]]
        Y += part

for possible_gear in S:
    if possible_gear[2] != "*":
        continue
    adjacent_parts = []
    for part in parts:
        [(r0, r1), p_num] = part
        if possible_gear[0] in r0:
            if possible_gear[1] in r1:
                adjacent_parts += [p_num]
    if len(adjacent_parts) > 1:
        gear_ratio = 1
        for gear_part in adjacent_parts:
            gear_ratio *= gear_part
        Z += gear_ratio
print("S:", Y, "\nG:", Z)
