#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

void shift(string input, string k);
int calckey_upper(char inputt, string kk);
int calckey_lower(char inpt, string ke);

int main(int argc, char *argv[])
{
    if (argc != 2) // lack of key or too many arguments.
    {
        printf("Non valid argument, program terminated.\n");
        return 1;
    }

    for (int i = 0, l = strlen(argv[1]); i < l; i++) // A loop to verify non-numeric keys.
    {
        if (isdigit(argv[1][i]) != 0) // if digit found, return 1.
        {
            printf("Key must contain 26 alphabetic characters.\n");
            return 1;
        }
    }

    int dublicate = 0;

    for (int i = 0, l = strlen(argv[1]); i < l; i++)
    {
        for (int n = 0; n <= l; n++)
        {
            if (argv[1][n] == argv[1][i])
            {
                dublicate++;
            }

            if (dublicate > 1)
            {
                printf("Invalid Key.\n");
                return 1;
            }
        }

        dublicate--;
    }

    if (strlen(argv[1]) != 26) // If key lenghth is not 26.
    {
        printf("Key must contain 26 alphabetic characters.\n");
        return 1;
    }

    string key = argv[1];

    string text = get_string("plaintext: "); // PROMPT USER.
    shift(text, key);

    printf("ciphertext: %s\n", text); // PRINT OUTPUT.

}

void shift(string input, string key)
{
    // standard shifting function, taken from my itteration of Caesar. Does the same thing.
    for (int i = 0, l = strlen(input); i < l; i++) // overrides the shifted keys.
    {
        int k = 0;

        if (isupper(input[i]) != 0) // adds key then overides back to input[i]. For UPPERcase letters.
        {
            k = calckey_upper(input[i], key); // calculates k integer value depending on input character.

            if ((input[i] + k) > 90) // If addition of the key goes beyond ASCII scope [prevents memory arrors (?)]
            {
                input[i] -= (26 - k); // Simple arithmatics: substracts 26 THEN adds key value.
            }

            else
            {
                input[i] += k;
            }

        }

        else if (islower(input[i]) != 0) // adds key then overides back to input[i]. For lowercase letters.
        {
            k = calckey_lower(input[i], key); // calculates k integer value depending on input character.

            if ((input[i] + k) > 122) // If addition of the key goes beyond ASCII scope [prevents memory errors(?)]
            {
                input[i] -= (26 - k); // Simple arithmatics: substract 26 THEN adds key value.
            }

            else
            {
                input[i] += k;
            }
        }

    }
}

int calckey_upper(char inputt, string kk)
{
    // NOTES:
    // this function and the one below it calculates each key depending on the character of original key string
    // for loop IS the solution here. Albiet a bit hardcoded.
    // it has to know what character of the key is used, calculate & returns int k based on that.

    for (int x = 65; x <= 90; x++)
    {
        if (isupper(kk[x - 65]) != 0) // if key character is uppercase.
        {
            if (inputt == x)
            {
                return kk[x - 65] - inputt;
            } // calculate difference value between key character & input character.
        }

        else if (islower(kk[x - 65]) != 0) // if key character is lowercase.
        {
            if (inputt == x)
            {
                return (kk[x - 65] - 32) - inputt; // here is the difference!
            } // substract 32 from key value (cuz input is UPPERcase here)
        }

    }

    return false;
}

int calckey_lower(char inpt, string ke)
{
    // for lowercase characters.

    for (int y = 65; y <= 90; y++)
    {
        if (isupper(ke[y - 65]) != 0) // if key character is uppercase.
        {
            if (inpt == (y + 32) )
            {
                return (ke[y - 65] + 32) - inpt; // here is the difference!
            } // add 32 to key value (cuz input is LOWERcase here)
        }

        else if (islower(ke[y - 65]) != 0) // if key character is lowercase.
        {
            if (inpt == (y + 32) )
            {
                return ke[y - 65] - inpt;
            } // calculate difference value between key character & input character.
        }

    }

    return false;
}

// Took me a whole sleepless night. Worh it.
// Made by Ououslou with love <3 (Abbassi Oussama) for CS50 course, 2020.