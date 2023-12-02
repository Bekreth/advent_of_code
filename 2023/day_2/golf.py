Y=lambda T,K:max(T,key=lambda x:x.get(K,0))[K]
N={"r":12,"g":13,"b":14}
S=G=I=0
for L in open("input.txt"):
 I+=1
 s=[[C.strip().split(" ") for C in h.split(",")] for h in L.split(":")[1].split(";")]
 Z=[{k:int(v) for [v,k] in t} for t in s]
 D={"r":Y(Z,"red"),"g":Y(Z,"green"),"b":Y(Z,"blue")}
 if D["r"]<=N["r"] and D["g"]<=N["g"] and D["b"]<=N["b"]:S+=I
 G+=(D["r"]*D["g"]*D["b"])
print("S:",S,"\nG:",G)
