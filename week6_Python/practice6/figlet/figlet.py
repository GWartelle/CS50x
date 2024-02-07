from pyfiglet import Figlet
from random import randint
import sys

figlet = Figlet()
fonts = figlet.getFonts()

args = len(sys.argv)

if args != 1 and args != 3:
    print("Usage: figlet.py -f/--font font OR figlet.py")
    sys.exit(1)

if args == 3:
    arg1 = sys.argv[1]
    if arg1 != "-f" and arg1 != "--font":
        print("First argument must be -f or --font")
        sys.exit(1)

    f = sys.argv[2]
    if f not in fonts:
        print("Font does not exist")
        sys.exit(1)

else:
    n_fonts = len(fonts)
    f = fonts[randint(0, n_fonts)]

word = input("Input: ")

print("Output:")

figlet.setFont(font=f)

print(figlet.renderText(word))