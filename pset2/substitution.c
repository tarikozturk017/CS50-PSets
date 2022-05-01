#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

bool check_valid(string x);                                                                     // declare function to check if it's alhabetic characters
bool check_duplicate(string y);                                                                 // check the chars in the argv[1], if they duplicate
char cry[26];                                                                                   // declare arrays of characters, we will store the new alphabet order from argv the key

int main(int argc, string argv[])
{
    if ((argc != 2) || (check_valid(argv[1]) == false))                                         //if it's not alhabetic or the elements in the command-line are not 2 --> print error
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if ((argc == 2) && (strlen(argv[1]) != 26))                                            // if there 2 elements but the key(argv[1]) is not 26 characters --> print error
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    else if ((argc == 2) && (check_duplicate(argv[1]) == false))                                // if 2 elements & duplicate --> print error
    {
        printf("Key must not contain repeated characters.\n");
        return 1;
    }

    else
    {
        string plaintext = get_string("Plaintext:  ");
            
        for (int i = 0; i < 26; i++)                                                        //assign each char of the declared array from the key
        {
            cry[i] = argv[1][i];
        }
            
        char c;
        printf("ciphertext: ");
            
        for (int i = 0; i < strlen(plaintext); i++)
        {
            if (islower(plaintext[i]))                                                  
            {
                c = tolower(cry[plaintext[i] - 97]);                                    // convert to lower -> store the (plaintext[i] ( which is i'th char of pltext) - 97 ('a' to make it 0) th character
            }
            else if (isupper(plaintext[i]))
            {
                c = toupper(cry[plaintext[i] - 65]);
            }
            else
            {
                c = plaintext[i];
            }
            printf("%c", c);
        }
        printf("\n");
        return 0;
    }
}

bool check_valid(string x)
{
    for(int i = 0; i < strlen(x); i++)                                                 
    if(!isalpha(x[i]))
    {
        return false;                                                                   // check if it's alpha
    }
    return true;
}

bool check_duplicate(string y)
{
    for (int i = 0; i < strlen(y); i++)
    {
        for (int j = (i + 1); j < (strlen(y) + 1); j++)                               // when I is 0, j is 1 then 2, 3,4,.... so when i is the first char, j is the second to last...
        {                                                                             
            if (y[i] == y[j])
            {
                return false;                                                           // if they are equal.. boom
            }
        }
    }
    return true;
}