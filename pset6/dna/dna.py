import csv
import sys

# a new function that gives us how many times the substring is repeated
# it takes long dna(string_dna), and strand(substring) (like AATGT or something else)


def max_reps_substring(string_dna, substring):
    # the logic is like --> string_dna = [ATATTGATAAATAT]
    #                              max = [00000000000000]
    #                        substring = [AT]
    # start checking from the last window
    # which is in this case i = len(string_dna) - len(substring) until 0(including) decreasing by 1(i -- in c)

    # set all the max_arr arrays to 0
    max_arr = [0] * len(string_dna)
    for i in range(len(string_dna) - len(substring), -1, -1):
        # the window, which is start from i'th index and end (i + len(substring))'th index
        # if last window equals to substring
        if string_dna[i: i + len(substring)] == substring:
            # if (go outside bound) the last ones are equal to substring then set i'th element of the array to 1
            if i + len(substring) > len(string_dna) - 1:
                max_arr[i] = 1

            # if it's not to last ones then add 1 to to (i+len(substring)'th value, which is the previous substring's value, bc it's consecutive
            else:
                max_arr[i] = 1 + max_arr[i + len(substring)]
    return max(max_arr)


def print_match(reader, value_in_string):
    for line in reader:
        # store person's name from line[0]
        person = line[0]
        # store values in line starting from the 2'nd ([1]) 
        values = [int(val) for val in line[1:]]
        if values == value_in_string:
            print(person)
            return

    print("No match")
    

def main():

    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    csv_path = sys.argv[1]
    # open file to read as csv
    with open(csv_path) as csv_file:
        reader = csv.reader(csv_file)
        # save the first line, the sequences, into all_sequences without the first one, which is "name"
        all_sequences = next(reader)[1:]

        # open and read the argv[2], which is dna string file, into memory (string_dna)
        text_path = sys.argv[2]
        with open(text_path) as text_file:
            string_dna = text_file.read()
            
            # call max_reps_substring function again and again
            # declare an array 
            # check for each sequence in all_sequences and add the max to the array
            values_in_string = []
            for seq in all_sequences:
                values_in_string.append(max_reps_substring(string_dna, seq))
            # value_in_string = [max_reps_substring(string_dna, seq) for seq in all_sequences] --> same thing in short
            
        print_match(reader, values_in_string)

main()