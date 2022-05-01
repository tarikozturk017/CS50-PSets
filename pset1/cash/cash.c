#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float cash;                                 // Declare a float and get float while cash<0
    do
    {
        cash = get_float("Change owed: ");
    }
    while (cash<0);
    
    int cents = round(cash * 100);                 
    
    int coins = 0;
    while(cents!=0)                             
    {
    coins = coins + cents / 25;                 // I could use " coins += cents / 25; "
    cents = cents % 25;                         
    
    coins = coins + cents / 10;                 //apply the same thing for each coins
    cents = cents % 10;
    
    coins = coins + cents / 5;
    cents = cents % 5;
    
    coins = coins + cents / 1;
    cents = cents % 1;
    }
    printf("%i\n", coins);
}