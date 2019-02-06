import sys
import datamanager as DM
from stringdist import levenshtein_norm as difference
sentence = ' '.join(sys.argv[1:])

print("diferencies amb:"+sentence)

ALL = DM.load("test.json")
c0 = ALL["classe0"]
c1 = ALL["classe1"]
c2 = ALL["classe2"]
c3 = ALL["classe3"]

def try_c0():
    i = 0
    for list in c0:
        print(i)
        i += 1
        for case in list:
            print(case, difference(case,sentence))
def try_c1():
    i = 0
    for list in c1:
        print(i)
        i += 1
        for case in list:
            print(case, difference(case,sentence))
def try_c2():
    i = 0
    for list in c2:
        print(i)
        i += 1
        for case in list:
            print(case, difference(case,sentence))
def try_c3():
    i = 0
    for list in c3:
        print(i)
        i += 1
        for case in list:
            print(case, difference(case,sentence))

print("Classe0 test")
try_c0()
print("Classe1 test")
try_c1()
print("Classe2 test")
try_c2()
print("Classe3 test")
try_c3()
