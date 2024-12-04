import re


def xmas_counter(text):
    matches = re.findall("XMAS", text)
    return len(matches)

def forward_backward(list_text):
    output = 0
    output += xmas_counter("".join(list_text))
    output += xmas_counter("".join(reversed(list_text)))
    return output


crossword = []
height = 0
for line in open("input.txt"):
    crossword.append(list(line.strip()))
    height += 1

silver = 0

## Left / Right
for line in crossword:
    silver += forward_backward(line)

## Up / Down
for i in range(0, height):
    up = []
    for j in range(0, height):
        up.append(crossword[j][i])
    silver += forward_backward(up)

## +45 / -45
for i in range(-height, height):
    dia_right = []
    dia_left = []
    for j in range(-height, height):
        y = j
        x = y + i
        xi = (height -1) - x
        if y < 0:
            continue
        if y >= height:
            continue
        if not x < 0 and not x >= height:
            dia_right.append(crossword[x][y])
        if not xi < 0 and not xi >= height:
            dia_left.append(crossword[xi][y])
    if len(dia_right) >= 4:
        silver += forward_backward(dia_right)
    if len(dia_left) >= 4:
        silver += forward_backward(dia_left)

print("Silver:", silver)


## Gold
def match_scan(input_array):
    #print(input_array)
    d_right = "".join([input_array[0][0], input_array[1][1], input_array[2][2]])
    d_left = "".join([input_array[2][0], input_array[1][1], input_array[0][2]])
    match_r = (d_right == "MAS" or d_right == "SAM" )
    #print(d_right, match_r)
    match_l = (d_left == "MAS" or d_left == "SAM" )
    #print(d_left, match_l)
    #print()
    return match_r and match_l

gold = 0
for i in range(1, height - 1):
    for j in range(1, height - 1):
        window = [
            [crossword[i - 1][j - 1], crossword[i - 1][j], crossword[i - 1][j + 1]],
            [crossword[i][j - 1], crossword[i][j],crossword[i][j + 1]],
            [crossword[i + 1][j - 1], crossword[i + 1][j], crossword[i + 1][j + 1]],
        ]
        if match_scan(window):
            gold += 1

print("Gold:", gold)
