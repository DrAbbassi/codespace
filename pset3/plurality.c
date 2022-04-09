#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // linear search algo.
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    int winner_count = 0;
    int tie_count = 0;
    int n9 = 0;
    int n_arr[candidate_count + 1];

    for (int i = 0; i < candidate_count; i++)
    {
        for (int n = 0; n < candidate_count; n++)
        {
            if (candidates[i].votes > candidates[n].votes)
            {
                winner_count++; // can't be bigger than itself! so condition later must be minux 1.
            }

            else if (candidates[n].votes > candidates[i].votes) // Something here is causing the charlie error.
            {
                winner_count++;
                n9 = n;
            }

            else if (candidates[i].votes == candidates[n].votes) //it will be equal to itself! so condition later must be bigger than 1.
            {
                tie_count++;
                n_arr[n] = n;
            }
        }

        if (winner_count == (candidate_count - 1)) // conditon minus 1
        {
            if (candidates[n9].votes > candidates[i].votes)
            {
                printf("%s\n", candidates[n9].name);
                break;
            }

            else
            {
                printf("%s\n", candidates[i].name);
                break;
            }
        }

        else // if no winner found, set counter back to 0.
        {
            winner_count = 0;
        }

        if (tie_count > 1) // conditon bigger than 1.
        {
            printf("%s\n", candidates[i].name); // printing 1st winner first.

            for (int r = 0; r < tie_count - 1; r++)
            {
                printf("%s\n", candidates[ n_arr[r + 1] ].name); //print all other winners, starting from n + 1. cuz n_arr[0] = 0.
            }                                                    // & candidates[0].name is the 1st winner. can't print their name twice!

            break;
        }

        else if (tie_count == 1)
        {
            for (int y = 0; y < candidate_count; y++)
            {
                n_arr[y] = 0;
            }

        }
    }

    return;
}

// Made by Ououslou (Oussama Abbassi) with love <3
// This is CS50, week3.
//
// NOTES:
// check50 signales an error ONLY when Charlie wins, but doesn't explain how the checking is done. I've went through the code many times and couldn't figure out why..
// ..check50 signals that error. If the name of the candidate doesn't effect how the program will run (because it does work just fine with Bob and Alice)
// Then why Charlie isn't being printed?
//
// Due to my lack of knowing how the testing goes when Charlie is a winner, I can't locate what my code isn't doing right. Therefore, I'm afraid
// I'm going to pass to the next program to make in order to save time. And leave this error as it is.