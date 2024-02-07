# TODO


def main():
    # Ask how many cents the customer is owed
    cents = get_cents()
    cents *= 100

    # Calculate the number of quarters to give the customer
    quarters = calculate_quarters(cents)
    cents = cents - quarters * 25

    # Calculate the number of dimes to give the customer
    dimes = calculate_dimes(cents)
    cents = cents - dimes * 10

    # Calculate the number of nickels to give the customer
    nickels = calculate_nickels(cents)
    cents = cents - nickels * 5

    # Calculate the number of pennies to give the customer
    pennies = calculate_pennies(cents)
    cents = cents - pennies

    # Sum coins
    coins = int(quarters + dimes + nickels + pennies)

    # Print total number of coins to give the customer
    print(f"{coins}")


def get_cents():
    while True:
        try:
            change = float(input("Change owed: "))
            if change >= 0:
                return change
        except ValueError:
            print("Neither a float or a integer")


def calculate_quarters(cents):
    rest = cents % 25
    quarters = (cents - rest) / 25
    return quarters


def calculate_dimes(cents):
    rest = cents % 10
    dimes = (cents - rest) / 10
    return dimes


def calculate_nickels(cents):
    rest = cents % 5
    nickels = (cents - rest) / 5
    return nickels


def calculate_pennies(cents):
    rest = cents % 1
    pennies = (cents - rest) / 1
    return pennies


main()
