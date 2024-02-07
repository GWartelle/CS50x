def main():
    height = get_height()
    print_hash(height)


def get_height():
    while True:
        try:
            n = int(input("Height: "))
            if n > 0:
                return n
        except ValueError:
            print("Not an integer")


def print_hash(n):
    for i in range(n):
        print("#")


main()