greet = input("Greeting: ")

greet = greet.strip().lower()

if greet[0:5] == "hello":
    print("$0")
elif greet[0] == "h":
    print("$20")
else:
    print("$100")
