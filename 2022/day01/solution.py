E=[0]
for l in open('sample'):
 if l=="\n":E=[0]+E
 else:E[0]+=int(l)
E.sort()
o=E[-3:]
print(f"{o[0]}\n{sum(o)}")
