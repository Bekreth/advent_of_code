E=enumerate
R=range
S=[]
p=[]
for i,L in E(open("input.txt")):
 N=""
 for j,C in E(L):
  if C.isdigit():N+=C
  else:
   if C!=".":S+=[(i,j,C)]
   if N!="":
    p+=[[R(i-1,i+2),R(j-len(N)-1,j+1),int(N)]]
    N=""
P=[]
Y=Z=0
for [a,b,n]in p:
 for s in S:
  if s[0]in a and s[1]in b:
   P+=[[a, b,n]]
   Y+=n
   break
for g in S:
 A=[N for [a,b,N]in P if g[2]=="*"and g[0]in a and g[1]in b]
 r=1
 if len(A)>1:
  for G in A:r*=G
  Z+=r
print("S:",Y,"\nG:",Z)
