f = open('test.txt', 'w')
for i in range(10000*5000):
    f.write(str(i) + '\n')
f.close
