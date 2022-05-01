#include <stdio.h>
#include <cs50.h>

int main(void)

{
    int height;                                                                          //get a height int, if it's not 1-8 promp the question again
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    
    for (int row = 1; row <= height; row++)                                               //declare int row = 1, inc +1 until row>height
    {
        for (int space = 1; space <= height-row; space++)                               //declare int space =1, execute until space>height-row
        {
            printf(" ");
        }
        
        for (int hash = 1; hash <= row; hash++)                                         //declare int hash=1, execute until hash>row
        {
            printf("#");
        }
        
        printf("  ");                                                                   //two space after the first part
        
        for (int hash2 = 1; hash2 <= row; hash2++)                                        //print hashes again 
        {
            printf("#");
        }
    printf("\n");
    }
    return 0;
}