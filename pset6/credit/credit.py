from cs50 import get_int

# get the credit card number from the user
while True:
    credit_number = get_int("Number: ")
    # if the number is less than zero force to get
    if credit_number >= 0:
        break

# save card number to no in order to avoid losing number
no = credit_number

# declare global variable check_sum
check_sum = 0

# sum every odd number
# start w the last digit, then devide to 100 to get next odd no
# do it until no < 0
while no > 0:
    last_digit = int(no % 10)
    check_sum = check_sum + last_digit
    no = no / 100

# assign number / 10 to no in order to get the even numbers
no = credit_number / 10

# sum every even number
# start last (which is now even no) // devide 100 ...
while no > 0:
    last_digit = int(no % 10)
    check_sum = check_sum + (last_digit * 2)
    check_sum = check_sum + int((last_digit * 2) / 10)
    no = no / 100

# get the last digit of check_sum
check_sum = check_sum % 10

# calculate last numbers of the card
amex = int(credit_number / 10**13)
mastercard = int(credit_number / 10**14)
visa1 = int(credit_number / 10**12)
visa2 = int(credit_number / 10**15)

# print each card if associated

if amex/10 > 0 and amex/10 < 10 and check_sum == 0 and (amex == 34 or amex == 37):
    print("AMEX")

elif mastercard/10 > 0 and mastercard/10 < 10 and check_sum == 0 and (mastercard == 51 or mastercard == 52 or mastercard == 53 or mastercard == 54 or mastercard == 55):
    print("MASTERCARD")

elif visa2/10 > 0 and visa2/10 < 10 and check_sum == 0 and visa2 == 4:
    print("VISA")

elif visa1/10 > 0 and visa1/10 < 10 and check_sum == 0 and visa1 == 4:
    print("VISA")

else:
    print("INVALID")