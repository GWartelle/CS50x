from sys import argv

if len(argv) > 1:
    print("hello", end=" ")
    for arg in argv[1:]:
        print(arg, end=" ")
    print()
else:
    print("hello, world")

'''
from sys import argv

if len(argv) == 2:
    print(f"hello, {argv[1]}")
else:
    print("hello, world")
'''