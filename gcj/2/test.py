import sys
sum=int(sys.argv[1]) * 1.0
d=int(sys.argv[2])
for i in range(-d + 1, 30):
    ans = sum/(d+i) + i
    #print "i=" + str(i) + " dis=" + str(ans)
    print "[" + str(i) + "," + str(ans) + "],"

