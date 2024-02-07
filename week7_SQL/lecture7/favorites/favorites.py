from cs50 import SQL

db = SQL("sqlite:///favorites.db")

favorite = input("Favorite: ")

rows = db.execute("SELECT COUNT(*) AS n FROM favorites WHERE problem = ?", favorite)

print(rows[0]['n'])

'''
from cs50 import SQL

db = SQL("sqlite:///favorites.db")

rows = db.execute("SELECT problem, COUNT(*) AS n FROM favorites GROUP BY problem ORDER BY n DESC")

for row in rows:
    print(f"{row['problem']}: {row['n']}")
'''
'''
import csv

with open("favorites.csv", "r") as file:
    reader = csv.DictReader(file)
    counts = {}
    for row in reader:
        favorite = row["problem"]
        if favorite in counts:
            counts[favorite] += 1
        else:
            counts[favorite] = 1

favorite = input("Favorite: ")
favorite = favorite.capitalize().strip()
if favorite in counts:
    print(f"{favorite}: {counts[favorite]}")

OR

for favorite in sorted(counts, key=lambda problem: counts[problem], reverse=True):
print(f"{favorite}: {counts[favorite]}")
'''
