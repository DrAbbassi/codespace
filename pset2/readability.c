#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void count(string ui1);

float wr, st, lt;

int main(void)
{
    string ui = get_string("Text: ");

    count(ui);

    float L = (lt / wr) * 100.00;
    float S = (st / wr) * 100.00;
    int index = round( 0.0588 * L - 0.296 * S - 15.8 );

    if (index > 15)
    {
        printf("Grade 16+\n");
    }

    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }

    else
    {
        printf("Grade %i\n", index);
    }
}

void count(string ui1) // function that counts letters, words, and sentences in a string.
{
    lt = 0;
    wr = 0;
    st = 0;

    for(int i = 0, l = strlen(ui1); i < l; i++)
    {
        if (isalpha(ui1[i]) != 0) // counting letters.
        {
            lt++;
        }

        if (isspace(ui1[i]) != 0) // counting words.
        {
            wr++;
        }

        if (ui1[i] == '?' || ui1[i] == '.' || ui1[i] == '!') // counting sentences.
        {
            st++;
        }
    }

    wr += 1.0;
}