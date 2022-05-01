#include <stdio.h>
#include <cs50.h>

int main(void)

{
    
    long number;                                                                                //prompt to get a credit card number
    do
    {
        number = get_long("Number: ");
    }
    while (number <= 0);                                                                          //force to get a number > 0 if not
    
    int checksum = 0;                                                                           // checksum starts w/ zero
    long no = number;                                                                           // number = no; to avoid miscalculation; otherwise it'll fail to calculate even numbers
    
    while (no > 0)                                                                            // get int last digit, and 3rd .. odds
    {
        int lastdigit = no % 10;
        checksum = checksum + lastdigit;
        no = no / 100;
    }
    
    no = number / 10;                                                                    //to get even digits; starts w/ last 2nd digit, and 4th....
    
    while (no > 0)
    {
        int lastdigit = no % 10;
        checksum = checksum + (lastdigit * 2);
        checksum = checksum + ((lastdigit * 2) / 10);                                          // if 2x even number has two digits, to get first digit
        no = no / 100;
    }
    
    checksum = checksum % 10;                                                           // to get the last digit of the checksum, then we'll check if it's == 0
                                                                               
    // Declare ints for AmEx; MasterCard;Visa
    
    int amex = number / 1e+13;                                                                                  
    int mcard = number / 1e+14;
    int visa1 = number / 1e+12;                                                           //it's for 13 digits visa number
    int visa2 = number / 1e+15;                                                           //it's for 16 digits visa number
    
    // int 4 american express' first 2 digits --> start w/ 34||37; 15digits; checksum = 0
    
    if ((amex/10 > 0) && (amex/10 < 10) && (checksum == 0) && (amex == 34 || amex == 37))  
    {
        printf("AMEX\n");
    }
    // int 4 mastercard's first 2 digits --> start w/ 51, 52, 53, 54, 55 
    
    else if ((mcard / 10 > 0) && (mcard / 10 < 10) && (checksum == 0) && (mcard == 51 || mcard == 52 || mcard == 53 || mcard == 54 || mcard == 55))
    {
        printf("MASTERCARD\n");
    }
    
    // visa 13 digits or 16 digits; start w/ 4
    else if (((visa2 > 0) && (visa2 < 10) && (checksum == 0) && (visa2 == 4)) || ((visa1 > 0) && (visa1 < 10) && (checksum == 0) && (visa1 == 4)))
    {
        printf("VISA\n");
    }
    
    else
    {
        printf("INVALID\n");
    }
}