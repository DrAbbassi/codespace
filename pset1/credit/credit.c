#include <cs50.h>
#include <stdio.h>

int n, whtcard;
long long in = 0;
bool n00;

bool boolf(int bn); // helper function (for counting n)
bool count(long long i2); // counting input digits.
void dividef(int pn, int array[]); // dividing input into seperate digits.
int digits(int dn); // helper function (for checksum-ing).
int checksumff(int nx, int mx, int iarray[], int secdarray[]); // counting the sum.
bool checksumf(int summ); // checking cards' validity.
int whtcardf(int n14, int iar14); // determining which card it is.

////* M A I N    F U N C T I O N *////

int main(void)
{
    n = 0;
    in = get_long_long("input: "); //prompt user.
    n00 = count(in); //function to count how many digits the input is & storing the result in n.

    if (n < 13) // return invalid and quit program if input less than 13 digits.
    {
        printf("INVALID\n");
        return 0;
    }

    int iar[n]; // I had to declare the array here to avoid problems of scope/compiling..
    dividef(n, iar); // dividing user input into integers & storing them in an array of length n.
    int m = digits(n); // determining size of secd[m] be.
    int secd[m]; // array by the size of m to be used for storing the second digits.
    int sum = checksumff(n, m, iar, secd); // checksum function.
    bool checksum = checksumf(sum); // checks card's validity.
    int iar144 = (iar[0] * 10) + iar[1]; // converting array values into an integer for later use.
    whtcard = whtcardf(n, iar144); //checks which card is it.

    if ((checksum == false) || whtcard == 0)
    {
        printf("INVALID\n");
    }

    else
    {
        if (whtcard == 1)
        {
            printf("AMEX\n");
        }

        else if (whtcard == 2)
        {
            printf("VISA\n");
        }

        else if (whtcard == 3)
        {
            printf("MASTERCARD\n");
        }
    }
}

////* H E L P E R    F U N C T I O N S *////

bool boolf(int bn) // checks if n is withing acceptable range.
{
    if (bn == 13 || bn == 15 || bn == 16)
    {
        return true;
    }

    else
    {
        return false;
    }
}

bool count(long long i2) // counts number of digits of the user input.
{
    n = 0;
    while (i2 > 0)
    {
        i2 /= 10;
        ++n;
    }

    return boolf(n);
}

void dividef(int pn, int array[]) // divides user input into integers & stores them in an array of length n.
{
    for (int i = pn - 1; i >= 0; i--)
    {
        array[i] = in % 10;
        in /= 10;
    }
}

int digits(int dn) // determines how long will the int m array be.
{
    if (dn == 16) // I added additonal slot in the array to avoid length uncertainty problems.
    {
        return 8;
    }

    else if (dn == 15)
    {
        return 7;
    }

    else if (dn == 13)
    {
        return 6;
    }

    return 0;
}

bool checksumf(int summ) // checks if sum begins with a zero.
{
    if (summ % 10 == 0)
    {
        return true;
    }

    else
    {
        return false;
    }
}

int checksumff(int nx, int mx, int iarray[], int secdarray[]) // counting the sum.
{
    int sumx = 0;

    for (int i = nx - 1; i > 0; i -= 2, mx--) // LOOP 1 //
        //starts from second place to n, goes right to left. decrements n (i) by 2 and m by 1.
    {
        secdarray[mx - 1] = iarray[i - 1] * 2;  //multiplies by 2 & stores in secd[m].
    }

    int m2 = digits(nx); // using a (same value) different variable m2, because m got changed.

    for (int i = m2; i > 0; i--) // LOOP 2 // Summing secd[i]s & storing result into an int named sum.
    {
        // if one of the secd[m] integers is made of 2 digits, sum them together then add to sum.
        if (secdarray[i - 1] > 9)
        {
            sumx += secdarray[i - 1] % 10; //adding remainder to sum.
            sumx += secdarray[i - 1] /= 10; // adding next digit to sum.
        }

        else
        {
            sumx += secdarray[i - 1];
        }
    }

    // LOOP 3 // adding first digits of use input to sum.
    if (nx == 15)
    {
        for (int i = nx; i >= 0; i -= 2)
        {
            sumx += iarray[i - 1];
        }
    } // using different loop conditions to avoid problem of loop length uncertainty.

    else
    {
        for (int i = nx; i >= 1; i -= 2)
        {
            sumx += iarray[i - 1];
        }
    }

    return sumx;
}

int whtcardf(int n14, int iar14) // returns what type of card it is.
{
    if (n14 == 15 && (iar14 == 34 || iar14 == 37))
    {
        return 1;
    }

    else if ((n14 == 13 || n14 == 16) && (iar14 / 10) == 4)
    {
        return 2;
    }

    else if (n14 == 16 && (iar14 > 50 && iar14 < 56))
    {
        return 3;
    }

    return 0;
}