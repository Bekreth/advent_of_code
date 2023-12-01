class Adder:
    total = 0
    first = None
    last = None

    def handle_character(self, character):
        if character.isdigit():
            number = int(character)
            if self.first == None:
                self.first = number
            self.last = number

    def total_line(self):
        add = self.first * 10 + self.last
        self.total += add
        self.first = None
        self.last = None

def make_gold_line(line: str) -> str:
    # Safety replace for joint words like "twone"
    line = line.replace("one", "one1one")
    line = line.replace("two", "two2two")
    line = line.replace("three", "three3three")
    line = line.replace("four", "four4four")
    line = line.replace("five", "five5five")
    line = line.replace("six", "six6six")
    line = line.replace("seven", "seven7seven")
    line = line.replace("eight", "eight8eight")
    line = line.replace("nine", "nine9nine")
    return line

silver_adder = Adder()
gold_adder = Adder()
for line in open("input.txt"):
    silver_line = line
    gold_line = make_gold_line(line)
    print(gold_line.strip())
    for character in silver_line:
        if character.isdigit():
            silver_adder.handle_character(character)
    for character in gold_line:
        if character.isdigit():
            gold_adder.handle_character(character)
    silver_adder.total_line()
    gold_adder.total_line()

print("S:", silver_adder.total)
print("G:", gold_adder.total)
