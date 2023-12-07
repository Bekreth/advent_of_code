S=sorted
Z=zip
T=True
F=False
def V(c,j):
 o=0
 match c:
  case "A":o=14
  case "K":o=13
  case "Q":o=12
  case "J":o=1 if j else 11
  case "T":o=10
  case _:o=int(c)
 return o
def C(z,j):
 t={c:0 for c in z}
 for c in [c for[c,_]in S([[c, V(c,j)]for c in z],key=lambda a:a[1],reverse=T)]:
  if j and c=="J":t[S(t,key=lambda k:(t[k],V(k,j)),reverse=T)[0]]+=1
  else: t[c]=t[c]+1
 fh=th=tp=F
 for _,v in t.items():
  if v==5:return 7
  if v==4:return 6
  if v==3: 
   if fh:return 5
   else:fh=th=T
  if v==2: 
   if tp:return 3
   elif fh:return 5
   else:fh=tp=T
 if th:return 4
 if tp:return 2
 return 1
class H:
 def __init__(s,c,v,j):
  s.v=int(v)
  s.j=j
  s.c=c
  s.t=C(s.c,j)
 def __lt__(s,o):
  if s.t==o.t:
   for(c,r)in Z(s.c, o.c):
    a=V(c,s.j)
    b=V(r,s.j)
    if a==b:continue
    else:return a<b
  return s.t<o.t
G=[]
J=[]
for l in open("input.txt"):
 [p,P]=l.split()
 a=list(p)
 G+=[H(a,P,F)]
 J+=[H(a,P,T)]
Q=list(Z(*[[(i+1)*h.v,(i+1)*j.v]for i,(h,j) in enumerate(Z(S(G),S(J)))]))
A=sum(Q[0])
B=sum(Q[1])
print("S:",A,"\nG:",B)

