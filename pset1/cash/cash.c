#include <cs50.h>
#include <stdio.h>
#include <math.h>

float i, r1, r2, r3;
int t, q, d, N, p;

void greedy(float o);

int main(void)
{
    do
    {
        i = get_float("Change owed: ");
    }
    while (i < 0);
    greedy(i);
}

void greedy(float o) //the greedy function.
{
//rounding the user input & converting it to integer.
    o = round(o * 100.00);

//fmod functions to calculate the remainders of the divisions:
    r1 = fmod(o, 25);
    r2 = fmod(r1, 10);
    r3 = fmod(r2, 5);

//deviding the remainders themselves on the next coin value:
    q = o / 25; // Quarters
    d = r1 / 10; // Dimes.
    N = r2 / 5; // Nickles.
    p = r3 / 1; // Pennies.

// summing up the coins:
    t = q + d + N + p;
    printf("%i\n", t);
}