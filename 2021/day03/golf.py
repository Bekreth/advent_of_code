import sys
A=lambda a,b:[q+r for q,r in zip(a,b)]
Z=lambda v:sum([int(v[len(v)-i-1])*(2**i) for i,_ in enumerate(v)])
C=lambda L:O([[-1 if c=='0' else 1 for c in l.strip()] for l in L])
def O(C):
 t=C[0]
 for c in C[1:]:t=A(t,c)
 g=[1 if i<0 else 0 for i in t]
 return(g,[0 if v==1 else 1 for v in g])
def R(L,i,h):
 c=C(L)[h]
 if len(L)<=1:return Z(L[0][:-1])
 return R([l for l in L if int(l[i])==c[i]],i+1,h)
f=open(sys.argv[1]).readlines()
(g,e)=C(f)
print(f"Silver: {Z(g)*Z(e)}\nGold: {R(f,0,1)*R(f,0,0)}")