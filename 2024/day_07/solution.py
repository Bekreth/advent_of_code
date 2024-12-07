def add(a, b):
    return a + b

def mul(a, b):
    return a * b

def is_valid(test_value, numbers):
    operator_count = len(numbers) - 1
    for i in range(0, 2**operator_count):
        bits = [int(n) for n in bin(i)[2:].zfill(operator_count)]
        solution = numbers[0]
        operators = ""
        for j in range(0, len(bits)):
            if bits[j] == 0:
                operators += " + " 
                solution += numbers[j + 1]
            else:
                operators += " * " 
                solution *= numbers[j + 1]
        if solution == test_value:
            return True
    return False

silver = 0
for line in open("input.txt"):
    values = line.strip().split(": ")
    test_value = int(values[0])
    numbers = [int(x) for x in values[1].split(" ")]
    if is_valid(test_value, numbers):
        silver += test_value

print("Silver", silver)
