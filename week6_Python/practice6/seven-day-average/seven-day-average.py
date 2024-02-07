import csv
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        state = state.title().strip()
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    new_cases = {}
    previous_cases = {}

    for row in reader:
        state = row["state"]
        cases = int(row["cases"])

        if state in previous_cases:
            new = cases - previous_cases[state]
        else:
            new = 0

        if state in new_cases:
            if len(new_cases[state]) < 14:
                new_cases[state].append(new)
            else:
                new_cases[state].pop(0)
                new_cases[state].append(new)
        else:
            new_cases[state] = [new]

        previous_cases[state] = cases

    return new_cases


# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    for state in states:
        new_avg = round((sum(new_cases[state][7:]) / 7))
        old_avg = round((sum(new_cases[state][:7]) / 7))
        try:
            change = round(((new_avg - old_avg) / old_avg) * 100)
        except ZeroDivisionError:
            print(f"{state} had a 7-day average of {new_avg}.")
            continue

        if change >= 0:
            print(f"{state} had a 7-day average of {new_avg} and an increase of {change}%.")
        else:
            print(f"{state} had a 7-day average of {new_avg} and a decrease of {-change}%.")


main()
