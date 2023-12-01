S=G=0
D=lambda K:[i for i in K if i.isdigit()]
V=lambda K:int(K[0]+K[-1])
for L in open("input.txt"):
 S+=V(D(L))
 for p in [("eight","e8t"),("one","o1"),("two","2"),("three","3"),("four","4"),("five","5"),("six","6"),("nine","9"),("seven","7")]:L=L.replace(*p)
 G+=V(D(L))
print("S:",S,"\nG:",G)
