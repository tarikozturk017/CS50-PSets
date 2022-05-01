#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int main(void)
{
    int letter_number = 0, word_number = 1, sentence_number = 0;            //declare and set number of letter word and sentence to store.
    
    string text = get_string("Text: ");                                     // get the text from user
    
    for (int i = 0, n = strlen(text); i < n; i++)                           //check each char of text 
    {
        if (isalpha(text[i]))                           // ++ if alhapetic
        {
            letter_number++;
        }
        else if ((text[i]) == ' ')                                          // ++ if a space ' ' 
        {
            word_number++;
        }
        else if ((text[i] == '.') || (text[i] == '!') || (text[i] == '?'))        // ++ if . ? !
        {
            sentence_number++;
        }
    }
    
    float L = (((float)letter_number * 100) / (float)word_number);                          // calculate number of letters per 100 words
    float S = (((float)sentence_number * 100) / (float)word_number);                        // calculate number of sentences per 100 words
    
    int index = round((0.0588 * L) - (0.296 * S) - 15.8);                   // calculate given index and round to and int
    if (index < 1)                                                          //if index < 1 --> below grade 1
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)                                                   //if index >= 16 --> +16
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    } 
}