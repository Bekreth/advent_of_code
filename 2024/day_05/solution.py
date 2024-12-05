class Node:
    def __init__(self, value):
        self.value = value
        self.followers = []

    def add_follower(self, follower):
        #print("{}, adding {} with current{}".format(
        #    self.value,
        #    follower.value,
        #    [x.value for x in self.followers]
        #))
        self.followers.append(follower)

    def has_followers(self, required_followers):
        f_values = [x.value for x in self.followers]
        for follower in required_followers:
            if follower not in f_values:
                #print("fail", follower, self.followers)
                return False
        return True

    def __str__(self):
        return "{}, with current{}".format(
            self.value,
            [x.value for x in self.followers]
        )

    def __repr__(self):
        return "{}, with current{}".format(
            self.value,
            [x.value for x in self.followers]
        )

index = {}
phase = 1
silver = 0
for line in open("input.txt"):
    if line == "\n":
        phase += 1
        continue
    if phase == 1:
        pages = [int(page) for page in line.strip().split("|")]
        base_node = index[pages[0]] if pages[0] in index else Node(pages[0])
        if pages[0] not in index:
            index[pages[0]] = base_node
        if pages[1] not in index:
            extension_node = Node(pages[1])
            index[pages[1]] = extension_node
        base_node.add_follower(index[pages[1]])
    else:
        print(" *** START ***")
        page_numbers = [int(page) for page in line.strip().split(",")]
        current_node = index[page_numbers[0]]
        is_accurate = True
        for i in range(1, len(page_numbers)):
            if not current_node.has_followers(page_numbers[i:]):
                is_accurate = False
                break
            current_node = index[page_numbers[i]]
        if is_accurate:
            value_add = page_numbers[int(len(page_numbers)/2)]
            #print("Added", line, ":", value_add)
            silver += value_add
        else:
            print("Failed", line)
        print()

#for key, value in index.items():
#    print(value)
print(silver)

# 11575 too high
