from cs50 import get_float

# ask the user how much is owed.
while True:
    # force him to give non-negative amount
    owed = get_float("Cash owed: ")
    if owed >= 0:
        break

cents = int(round(owed * 100))
coins = 0

while cents != 0:
    # start calculating with 25 cents coin
    # devide existing cash to 25, take as coins and get the remainder
    coins = coins + int(cents / 25)
    cents = cents % 25

    # do exact same thing with 10 cents coin
    coins = coins + int(cents / 10)
    cents = cents % 10

    # 5 cents coin
    coins = coins + int(cents / 5)
    cents = cents % 5

    # 1 cent coin
    coins = coins + int(cents / 1)
    cents = cents % 1
    coins = int(coins)

print(coins)