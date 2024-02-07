import sys

class Jar:
    max = 0
    now = 0

    def __init__(self, capacity=12):
        if capacity < 0:
            raise ValueError("Capacity must be a non-negative integer")
        self.max = capacity
        self.now = 0

    def __str__(self):
        return "🍪" * self.now

    def deposit(self, n):
        if self.now + n > self.max:
            raise ValueError("Too many cookies to deposit")
        self.now += n

    def withdraw(self, n):
        if self.now - n < 0:
            raise ValueError("Not enough cookies to withdraw")
        self.now -= n

    @property
    def capacity(self):
        return self.max

    @property
    def size(self):
        return self.now


def main():
    while True:
        try:
            n = int(input("Create a cookie jar of size: "))
            break
        except ValueError:
            print("Not an integer")

    cookie = Jar(n)

    while True:
        cmd = input("What do we do next (deposit, withdraw, capacity, size or stop) ? ")
        cmd.lower()

        if cmd == "deposit":
            while True:
                try:
                    dep = int(input("How much? "))
                    break
                except ValueError:
                    print("Not an integer")
            cookie.deposit(dep)
            print(cookie)

        elif cmd == "withdraw":
            while True:
                try:
                    wit = int(input("How much? "))
                    break
                except ValueError:
                    print("Not an integer")
            cookie.withdraw(wit)
            print(cookie)

        elif cmd == "capacity":
            total = cookie.capacity
            print(f"The cookie jar can hold up to {total} cookies")
            print(cookie)

        elif cmd == "size":
            current = cookie.size
            print(f"The cookie jar now contains {current} cookies")
            print(cookie)

        elif cmd == "stop":
            sys.exit(0)

        else:
            print("Wrong command")

main()