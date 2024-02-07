import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # TODO: Read database file into a variable
    individuals = []
    with open(sys.argv[1], encoding="utf-8-sig") as file:
        reader = csv.DictReader(file)
        for person in reader:
            individuals.append(person)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2]) as file:
        dna_sequence = file.read()

    # TODO: Find longest match of each STR in DNA sequence
    STR = list(individuals[0].keys())
    STR = STR[1:]
    matchs = {}
    for i in range(len(STR)):
        matchs[STR[i]] = longest_match(dna_sequence, STR[i])

    # TODO: Check database for matching profiles
    for i in range(len(individuals)):
        if is_match(individuals[i], matchs, STR):
            print(individuals[i]["name"])
            sys.exit(0)
    print("No match")
    sys.exit(0)


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


# Compare the count of STRs of an individual with the DNA sequence
def is_match(person, matchs, STR):
    n = 0
    for i in range(len(STR)):
        if int(person[STR[i]]) == int(matchs[STR[i]]):
            n += 1
    if n == len(STR):
        return True
    else:
        return False


main()
