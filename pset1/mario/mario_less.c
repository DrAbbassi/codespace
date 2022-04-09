#include <cs50.h>
#include <stdio.h>

void block(int n);

int main(void)
{
    int n;                              // storing the user input into the variable n. global scope

    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    block(n);
}

void block(int n)                       //function that makes the "blocks.""
{
    int b = 1;

    for (int i = 0; i < n; i++, b++)    // master loop to make n ROWS, increments b by 1.
    {
        for (int s = 0; s < n - b; s++)    // nested loop to make SPACES, prints n-b empty spaces.
        {
            printf(" ");
        }

        for (int k = 0; k < b; k++)   // nested loop to make BLOCKS, prints b blocks.
        {
            printf("#");
        }
        printf("\n");                   //JUMPS LINE & ends row.
    }
}
