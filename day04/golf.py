import sys
E=enumerate
T=range
K=int
R=T(0,5)
B=lambda i:[[K(c) for c in r.split()] for r in i]
D=lambda I:sum([I[i][j] if I[i][j]>=0 else 0 for i in R for j in R])
S=lambda I:any([all([I[i][z]==q for z in R]) or all([I[z][i]==q for z in R]) for i in R])
q=-1
def C(I,n):
 for i,r in E(I):
  for j,c in E(r): 
   if c==n:I[i][j]=q
 return I
l=open(sys.argv[1]).readlines()
c=l[0]
X=l[1:]
Y=Z=0
A=[B(X[5*i+i+1:5*i+i+6]) for i in T(0,K(len(X)/6))]
f=[]
for n in c.split(","):
 N=K(n)
 for b in A:
  c=C(b,N)
  if not S(c):f+=[c]
  else:
   if Y==0:Y=D(c)*N
   elif len(A)==1:Z=D(c)*N
 if Z!=0:break
 A=f.copy()
 f=[]
print(f"Silver: {Y}\nGold: {Z}")