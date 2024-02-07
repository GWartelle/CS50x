import csv
from cs50 import SQL

db_students = SQL("sqlite:///roster_v2.db")
db_houses = SQL("sqlite:///roster_v2.db")
db_assignments = SQL("sqlite:///roster_v2.db")

with open("students.csv", "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        name = row["student_name"]
        existing_student = db_students.execute("SELECT id FROM students WHERE student_name = ?", name)
        if not existing_student:
            new_student_id = db_students.execute("INSERT INTO students (student_name) VALUES (?)", name)
        else:
            new_student_id = existing_student[0]["id"]

        house = row["house"]
        head = row["head"]
        existing_house = db_houses.execute("SELECT id FROM houses WHERE house = ? AND head = ?", house, head)
        if not existing_house:
            new_house_id = db_houses.execute("INSERT INTO houses (house, head) VALUES (?, ?)", house, head)
        else:
            new_house_id = existing_house[0]["id"]

        db_assignments.execute("INSERT INTO assignments (student_id, house_id) VALUES (?, ?)", new_student_id, new_house_id)
