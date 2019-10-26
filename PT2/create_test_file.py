f = open('test.txt', 'w')
f.write(str(10000) + '\n' + str(5000) + '\n')
for i in range(10000*5000):
    f.write(str(i) + '\n')
f.close
