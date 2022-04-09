#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

void shift(string input, int k);

int main(int argc, char *argv[])
{
    if (argc != 2) // lack of key or too many arguments.
    {
        printf("Non valid argument, program terminated.\n");
        return 1;
    }

    for (int i = 0, l = strlen(argv[1]); i < l; i++) // A loop to verify non-numeric keys.
    {
        if (isdigit(argv[1][i]) == 0)
        {
            printf("Usage: ./caesar key.\n");
            return 1;
        }
    }

    string text = get_string("plaintext: ");

    int k = atoi(argv[1]) % 26; //Overlapping the key if need be.

    if (k > 0) // if the key is a positive integer
    {
        shift(text, k);
        printf("ciphertext: %s\n", text);
    }
}


void shift(string input, int k) // shifts the text then stores it back.
{
    for (int i = 0, l = strlen(input); i < l; i++) // store the shifted keys.
    {
        if (isupper(input[i]) != 0) // adds key then overides back to input[i]. For CAPITAL letters.
        {
            if ((input[i] + k) > 90) // If addition of the key goes beyond ASCII scope [prevents memory arrors (?)]
            {
                input[i] -= (26 - k); //Simple arithmatics: substract 26 THEN adds key.
            }

            else
            {
                input[i] += k;
            }

        }

        else if (islower(input[i]) != 0) // adds key then overides back to input[i].
        {
            if ((input[i] + k) > 122) // If addition of the key goes beyond ASCII scope [prevents memory errors(?)]
            {
                input[i] -= (26 - k); //Simple arithmatics: substract 26 THEN adds key.
            }

            else
            {
                input[i] += k;
            }
        }

    }
}

// Written by Ououslou with love <3 (Abbassi Oussama for CS50 course 2020)
//
// Ready made alphabetics for testing purposes:
// a b c d e f g h i j k l m n o p q r s t v w x y z
// A B C D E F G H I J K L M N O P Q R S T V W X Y Z