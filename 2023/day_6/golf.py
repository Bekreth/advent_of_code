I=int
C=lambda t,d:len(list(filter(lambda a:a>I(d),[i*(I(t)-i)for i in range(I(t))])))
S=G=j=1
T=[]
for l in open("input.txt"):
 Z=l.split()[1:]
 g="".join(Z)
 if j==1:
  T=Z
  j=g
 else:
  for L in [C(t,d)for(t,d)in zip(T,Z)]:S*=L
  G=C(j,g)
print("S:",S,"\nG:",G)
