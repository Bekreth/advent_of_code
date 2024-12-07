import math

def base(b,n):
    size = math.ceil(math.log(max(1,n),b))
    return [place
        for i in range(size,-1,-1)
        if (place := n//b**i%b) or i<size] or [0]

def is_silver(test_value, numbers):
    operator_count = len(numbers) - 1
    for i in range(0, 2**operator_count):
        bits = [int(n) for n in bin(i)[2:].zfill(operator_count)]
        solution = numbers[0]
        operators = ""
        for j in range(0, len(bits)):
            value = numbers[j + 1]
            if bits[j] == 0:
                operators += " + " 
                solution += value
            else:
                operators += " * " 
                solution *= value
        if solution == test_value:
            return True
    return False

def is_gold(test_value, numbers):
    operator_count = len(numbers) - 1
    for i in range(0, 3**operator_count):
        ternary = base(3, i)
        bits = [0]*(operator_count - len(ternary)) + ternary
        solution = numbers[0]
        operators = ""
        for j in range(0, len(bits)):
            value = numbers[j + 1]
            if bits[j] == 0:
                operators += " + " 
                solution += value
            elif bits[j] == 1:
                operators += " * " 
                solution *= value
            else:
                operators += " || " 
                solution = int(str(solution) + str(value))
        if solution == test_value:
            return True
    return False

silver = 0
gold = 0
for line in open("input.txt"):
    values = line.strip().split(": ")
    test_value = int(values[0])
    numbers = [int(x) for x in values[1].split(" ")]
    if is_silver(test_value, numbers):
        silver += test_value
    if is_gold(test_value, numbers):
        gold += test_value

print("Silver", silver)
print("Gold", gold)
