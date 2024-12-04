import re

silver_expression = "mul\((\d{1,3}),(\d{1,3})\)"
gold_expression = "(^|do\(\))(.*?)(don't|$)"

def search_and_multiply(text):
    silver_matches = re.findall(silver_expression, text)
    ouput = 0
    for (x, y) in silver_matches:
        ouput += int(x)*int(y)
    return ouput

text = ""
for line in open("input.txt"):
    text = line


silver = search_and_multiply(text)
print("Silver:", silver)

gold = 0
for (_, match, _) in re.findall(gold_expression, text):
    gold += search_and_multiply(match)

print("Gold:", gold)
