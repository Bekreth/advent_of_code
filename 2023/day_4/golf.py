S=0
C=[1]*201
for i,L in enumerate(open("input.txt")):
 [H,w]=[P.split()for P in L.split(":")[1].split("|")]
 W=len([n for n in H if n in w])
 if W>0:
  S+=2**(W-1)
  for j in range(i+1,i+1+W):C[j]+=C[i]
print("S:",S,"\nG:",sum(C))
