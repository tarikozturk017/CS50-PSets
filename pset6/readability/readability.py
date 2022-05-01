from cs50 import get_string
import string

# ask user for an input
text = get_string("Text: ")

letters_no = 0
sentences_no = 0
words_no = 1

for char in text:
    # increment words no every time we encounter space
    if char in [' ']:
        words_no += 1

    # increment letters no every time see a letter / w isalpha func.
    elif char.isalpha():
        letters_no = letters_no + 1
        
    # increment sentences no every time we see . or ! or ?
    elif char in ['!', '.', '?']:
        sentences_no = sentences_no + 1
        
# calculate L and S
L = letters_no * 100 / words_no
S = sentences_no * 100 / words_no

# calculate index
# Added 0.5 to make it an int instead of using round function
index = int(((0.0588 * L) - (0.296 * S) - 15.8) + 0.5)

# print
if index < 1:
    print("Before Grade 1")

elif index >= 16:
    print("Grade 16+")

else:
    print(f"Grade {index}")
