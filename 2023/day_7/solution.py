def card_value(card) -> int:
    output: int = 0
    match card:
        case "A": output = 14
        case "K": output = 13
        case "Q": output = 12
        case "J": output = 11
        case "T": output = 10
        case _: output = int(card)
    return output

def calculate_hand(cards) -> int:
    counter = {card: 0 for card in cards}
    for card in cards:
        counter[card] = counter[card] + 1
    possible_full_house = False
    possible_three = False
    possible_two_pair = False
    for key, value in counter.items():
        if value == 5: return 7
        if value == 4: return 6
        if value == 3: 
            if possible_full_house: return 5
            else: 
                possible_full_house = True
                possible_three = True
        if value == 2: 
            if possible_two_pair: return 3
            elif possible_full_house: return 5
            else: 
                possible_full_house = True
                possible_two_pair = True
    if possible_three: return 4
    if possible_two_pair: return 2
    return 1

class Hand:
    _value: int
    _cards: [str]
    _type: int

    def __init__(self, cards, value):
        self._value = int(value)
        valued_cards = [[card, card_value(card)] for card in cards]
        sorted_cards = sorted(valued_cards, key=lambda a: a[1], reverse=True)
        self._cards = [card for [card, value] in valued_cards]
        self._type = calculate_hand(self._cards)

    def __repr__(self):
        return f"{self._value, self._cards, self._type}"

    def __lt__(self, other):
        if self._type == other._type:
            for (s, o) in zip(self._cards, other._cards):
                s_value = card_value(s)
                o_value = card_value(o)
                if s_value == o_value: continue
                else: return s_value < o_value
        return self._type < other._type

silver = 0
gold = 0

hands = []
for line in open("input.txt"):
    parsed = line.split()
    hands += [Hand(list(parsed[0]), parsed[1])]

for i, hand in enumerate(sorted(hands)):
    silver += (i+1)*hand._value
    print(hand, i+1, (i+1)*hand._value, silver)

print("S:", silver,"\nG:", gold)
