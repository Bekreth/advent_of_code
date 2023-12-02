
class Hand:
    red: int
    blue: int
    green: int

    def __init__(self, red, blue,green):
        self.red = red
        self.blue = blue
        self.green = green

    def update_counts(self, cube_sets):
        for cube_set in cube_sets:
            for cubes in cube_set:
                value = int(cubes[0])
                match cubes[1]:
                    case "red":
                        self.red = value if value > self.red else self.red
                    case "blue":
                        self.blue = value if value > self.blue else self.blue
                    case "green":
                        self.green = value if value > self.green else self.green

    def calculate_power(self):
        return self.red * self.blue * self.green

    def __le__(self, other):
        return self.red <= other.red and self.green <= other.green and self.blue <= other.blue

    def __str__(self):
        return '(red {0}, blue {1}, green {2})'.format(self.red, self.blue, self.green)

maximum = Hand(12, 14, 13)
game_counter = 1
silver_accumulator = 0
gold_accumulator = 0

for line in open("input.txt"):
    clean = line.strip().replace("\n", "")
    game = clean.split(":")
    hands = game[1].split(";")
    cube_sets = [[count.strip().split(" ") for count in hand.split(",")] for hand in hands]
    hand = Hand(0, 0, 0)
    hand.update_counts(cube_sets)
    if hand <= maximum:
        silver_accumulator += game_counter
    game_counter += 1
    gold_accumulator += hand.calculate_power()

print(silver_accumulator)
print(gold_accumulator)
