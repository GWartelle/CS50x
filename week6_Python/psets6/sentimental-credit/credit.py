# TODO
from cs50 import get_int

number = get_int("Number: ")
other = 0
last_other = 0
rest = 0
last_rest = 0
count = 0
i = 10

while i <= (10 * number):
    count += 1
    x = 10 * (number % i) / i
    y = 2 * x
    if (count % 2) == 0:
        if y < 10:
            other = other + y
        else:
            other = other + (y % 10) + 1
        last_other = x
    else:
        rest = rest + x
        last_rest = x
    number = number - (number % i)
    i *= 10

first = 0
second = 0
if count >= 2:
    if (count % 2) > 0:
        first = last_rest
        second = last_other
    else:
        first = last_other
        second = last_rest

checksum = other + rest
if (checksum % 10) == 0:
    if count == 13:
        if first == 4:
            print("VISA\n")
        else:
            print("INVALID\n")
    elif count == 15:
        if first == 3:
            if second == 4 or second == 7:
                print("AMEX\n")
            else:
                print("INVALID\n")
    elif count == 16:
        if first == 4:
            print("VISA\n")
        elif first == 5:
            if second == 1 or second == 2 or second == 3 or second == 4 or second == 5:
                print("MASTERCARD\n")
            else:
                print("INVALID\n")
        else:
            print("INVALID\n")
    else:
        print("INVALID\n")
else:
    print("INVALID\n")
