import sys

silver = 0
elves = []

file = open('d')
lines = file.readlines()
currentValue = 0
for line in lines:
    if line == "\n":
        elves += [currentValue]
        currentValue = 0
    else:
        currentValue += int(line)

output = sorted(elves)
print(output[len(elves) - 1])
print(sum(output[len(elves) - 3:len(elves)]))

