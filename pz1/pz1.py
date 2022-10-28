
alphabet1 = list('абвгдежзиклмнопрстуфхцчшщъыьэюя')
alphabet2 = list('абвгдежзийклмнопрстуфхцчшщъыьэюя')
alphabet3 = list('абвгдеёжзиклмнопрстуфхцчшщъыьэюя')
alphabet4 = list('абвгдеёжзийклмнопрстуфхцчшщъыьэюя')

alphabets = {
    '0': alphabet1,
    '1': alphabet2,
    '2': alphabet3,
    '3': alphabet4
}


encode = not bool(int(input("Зашифровать(0) или расшифровать(не 0)?: ")))
alphabet = alphabets[input("Выберете алфавит:\n0 - без ё и й\n1 - без ё\n2 - без й\n3 - полный алфавит\nВыбор:")]
string = input("Введите строку: ")
shift = int(input("Введите смещение: "))

def codeSymbol(ch, mult):
    if not ch.isalpha():
        return ch

    if not ch.lower() in alphabet:
        return ch

    isUpper = ch.isupper()

    encoded = alphabet[(alphabet.index(ch.lower()) + shift * mult) % len(alphabet)]

    if isUpper:
        return encoded.upper()

    return encoded

def code(string, mult):
    return ' '.join([''.join([codeSymbol(ch, mult) for ch in word]) for word in string.split(' ')])

if encode:
    print(code(string, 1))
else:
    print(code(string, -1))

