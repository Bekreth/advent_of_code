E=[0]
for l in open('d'):
 if l=="\n":E+=[0]
 else:E[-1]+=int(l)
o=sorted(E)[-3:]
print(f"{o[2]}\n{sum(o)}")
