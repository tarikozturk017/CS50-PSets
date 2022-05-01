#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

bool check_valid(string x);                                                                 //declare bool to check if the string is digit

int main(int argc, string argv[])

{
    if ((argc != 2) || (check_valid(argv[1]) != true))                                          // if command-line argument has dif than 2 elements, or the 2nd element which is key is not digit.
    {
        printf("Usage: ./caesar key\n");                                                    //print ..
        return 1;                                                                           //exit main with an error code
    }
    else
    {
        int key = atoi(argv[1]);                                                            // convert string ,which is a digit, to an int 
        if (check_valid(argv[1]))                                                           // if 2nd element of the command is digit then....
        {
            string plaintext = get_string("Plaintext:  ");                                  //get the text
            
            printf("ciphertext: ");                                                         
            for (int i = 0, n = strlen(plaintext); i < n; i++)                              // create a loop to convert or do not convert each char
            {
                if (isupper(plaintext[i]))
                {
                    char c = (((plaintext[i] - 'A' + key) % 26) + 'A');                    //subtract 'A's ASCII no from c's ASCII no to calculate and add key... %26 add 'A'
                    printf("%c", c);
                }
                else if (islower(plaintext[i]))
                {
                    char c = (((plaintext[i] - 'a' + key) % 26) + 'a');                     // the same math like the upper
                    printf("%c", c);
                }
                else
                {
                    char c = plaintext[i];                                                  // print the rest as it is.
                    printf("%c", c);
                }
            }
            printf("\n");                                                                   // new line and exit with a true code
            return 0;
        }
    }
}

bool check_valid(string x)                                                                  // create a bool exp to check if it has any character, which is not digit.
{
    for (int i = 0, n = strlen(x); i < n; i++)                                              // create a loop to check each chars.
    {
        if (!isdigit(x[i]))                                                                 // if a char is not digit exit the function with error code.
        {
        return false;
        }
    }
    return true;                                                                            //otherwise exit with true code.
}