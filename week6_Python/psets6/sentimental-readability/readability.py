# TODO


def main():
    text = input("Text: ")

    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    L = 100.0 * float(letters) / float(words)
    S = 100.0 * float(sentences) / float(words)
    index = 0.0588 * L - 0.296 * S - 15.8

    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        for i in range(1, 16):
            if index >= i and index < i + 0.5:
                print(f"Grade {i}")
            elif index >= i + 0.5 and index < i + 1:
                print(f"Grade {i + 1}")


def count_letters(text):
    count = 0

    for i in range(len(text)):
        if text[i].isalpha():
            count += 1
    return count


def count_words(text):
    count = 0
    word = False
    for i in range(len(text)):
        if text[i].isalpha():
            word = True
        if word:
            if text[i] == " ":
                count += 1
                word = False
    if word:
        count += 1
    return count


def count_sentences(text):
    count = 0
    for i in range(len(text)):
        if text[i] == "." or text[i] == "!" or text[i] == "?":
            count += 1
    return count


main()
