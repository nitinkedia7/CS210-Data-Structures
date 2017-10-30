# generating test cases for- Lab Assignment5
import random, string, math

for x in xrange(1,5): 
    random.seed(7*x)
    name = "input"+str(x)+".in"  
    file = open(name,'w')

    n= random.randint(100, 1000)
    m= random.choice([701, 809, 907, 601, 503])
    file.write("%d %d\n" %(n,m))
    s= set()
    
    nn=0
    while nn<n:
        z= random.randint(0,100)
        if z==0:
            if not s: continue
            k= (random.sample(s,1))[0]
            file.write("SEARCH %d\n" %(k))
            nn+=1
        elif z==1:
            if not s: continue
            k= (random.sample(s,1))[0]
            file.write("DELETE %d\n" %(k))
            nn+=1
        else:
            k= random.randint(1,10**8)
            if k in s: continue
            s.add(k)
            file.write("INSERT %d\n" %(k))
            nn+=1 
    file.close()
    
print "Done"
