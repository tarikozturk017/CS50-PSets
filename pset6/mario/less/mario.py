from cs50 import get_int

# create a loop to ask user the height repeatedly until we get the right range 
while True:
    height = get_int("Height: ")
    # if the height<1 or height>8 ask again
    if height < 1 or height > 8:
        height = get_int("Height ")
    # if 1<=height<=8 break the loop
    break

# now print the pyramits with using the input "height"
# set i to 1 and count until height+1 
for i range(1, height + 1):
    #print height - i space at the beginning wo going to the new line
    print(" " * (height - i), end="")
    print("#" * i, end="")
    print(" ")
    print("#" * i, end="")
    print()