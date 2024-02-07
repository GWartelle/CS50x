# TODO


def main():
    h = get_height()
    for i in range(1, h + 1):
        print(" " * (h - i) + "#" * i)


def get_height():
    while True:
        try:
            h = int(input("Height: "))
            if h > 0 and h < 9:
                return h
        except ValueError:
            print("Not an integer")


main()
