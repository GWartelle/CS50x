import csv

# Works even if name and number columns were swapped
with open("phonebook.csv", "a") as file:
    name = input("Name: ")
    number = input("Number: ")

    writer = csv.DictWriter(file, fieldnames=["name", "number"])
    writer.writerow({"name": name, "number": number})

'''
with open("phonebook.csv", "a") as file:
    name = input("Name: ")
    number = input("Number: ")

    writer = csv.writer(file)
    writer.writerow([name, number])
'''

'''
file = open("phonebook.csv", "a")

name = input("Name: ")
number = input("Number: ")

writer = csv.writer(file)
writer.writerow([name, number])

file.close()
'''

'''
people = {
    "Carter": "+1-617-495-1000",
    "David": "+1-949-468-2750"
}

name = input("Name: ")
if name in people:
    print(f"Number: {people[name]}")
'''