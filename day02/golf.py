import sys
a=x=h=0
for l in open(sys.argv[1]).readlines():
 v=int(l[-2])
 if "f"in l:
  x+=v
  h+=a*v
 else:a+=[v,-v]["u"in l]
print(f"Silver: {x*a}\nGold: {x*h}")