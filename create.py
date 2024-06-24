same = 4;
diff = 1;

for i in range(1, same + 1):
    f = open("huff" + str(i) + ".job", 'w')
    f.write("[repeat" + str(i) + "]\n")
    f.write("ioengine=psync\n")
    f.write("direct=0\n")
    f.write("thread\n")
    f.write("rw=read\n")
    f.write("bs=1k\n")
    f.write("size=8k\n")

    f.write("nrfiles=1000\n")
    f.write("numjobs=10\n")
    
    f.write("runtime=10000\n")
    f.write("group_reporting")

f.close()

for i in range(same + 1, same + diff + 1):
    f = open("huff" + str(i) + ".job", 'w')
    f.write("[repeat" + str(i) + "]\n")
    f.write("ioengine=psync\n")
    f.write("direct=0\n")
    f.write("thread\n")
    f.write("rw=write\n")
    f.write("bs=1k\n")
    f.write("size=8k\n")

    f.write("nrfiles=1000\n")
    f.write("numjobs=10\n")

    f.write("runtime=10000\n")
    f.write("group_reporting")

f.close()
'''
[repeat]
ioengine=psync
direct=0
thread
rw=read
bs=1k
size=8k
nrfiles=1000
numjobs=5
runtime=10000
group_reporting
'''

