import sys
R=range
F=[0]*9
S=0
l,=open(sys.argv[1])
for i in [int(i) for i in l[::2]]:F[i]+=1
for i in R(256):
 h=F[0]
 for j in R(8):F[j]=F[j+1]
 F[8]=h
 F[6]+=h
 if i==79:S=sum(F)
print(f"Silver {S}\nGold {sum(F)}")