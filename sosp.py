import os


class Tree:
    def __init__(self):
        self.base = [str(x) for x in range(10)] + [ chr(x) for x in range(ord('A'),ord('A')+6)]
        pass
    
    def dec2bin(self, h):
        h_size = len(h) * 4
        h = (bin(int(h, 16))[2:]).zfill(h_size)
        return h
    
    def construct(self, T):
        if len(T) == 0 or len(T) == 1:
            return []
        else:
            L = [key[1:] for key in T if key[0] == '0']
            R = [key[1:] for key in T if key[0] == '1']
            return [len(L)] + self.construct(L) + self.construct(R)

    def run(self, T):
        return self.construct(T)

def get_md5():
    global time
    files = os.listdir(".")
    f = []
    cnt = 0
    for fn in files:
        d = os.popen("md5sum " + fn)
        txt = d.read()
        f.append(txt)
    ret = []
    for x in f:
        if x == '':
            continue
        if x[:8] in ret:
            time = time + 0.0001
            continue
        cnt = cnt + 1
        if cnt > 5000:
            cnt = cnt - 1
            time = time + 10
        ret.append(x[:8])
    return ret

if __name__ == "__main__":
    t = Tree()
    time = 0
    md = get_md5()
    keys = [t.dec2bin(x) for x in md]
    res = t.run(keys)
    print("sosp size: " + str(len(res) * 4))
    print("sosp time: " + str(time))

