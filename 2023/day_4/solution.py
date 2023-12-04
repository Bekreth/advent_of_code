silver = 0
gold = 0

cards = [1] * 201
for i, line in enumerate(open("input.txt")):
    [hand_set, winner_set] = line.split(": ")[1].strip().split(" | ")
    hand = hand_set.split()
    winners = winner_set.split()
    wins = [number for number in hand if number in winners]
    win_count = len(wins)
    if win_count == 0: continue
    value = 2**(win_count - 1)
    silver += value
    for j in range(i + 1, i + 1 + win_count):
        cards[j] += cards[i]


print("S:", silver,"\nG:", sum(cards))
