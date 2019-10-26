f = open('test.txt', 'w')
f.write(str(5) + '\n' + str(10) + '\n')
for i in range(1, 51):
    f.write(str(i) + '\n')
f.close
