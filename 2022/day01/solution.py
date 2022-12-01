E=[0]
for l in open('sample'):
 if l=="\n":E=[0]+E
 else:E=[E[0]+int(l)]+E[1:]
o=sorted(E)[-3:]
print(f"{o[2]}\n{sum(o)}")
