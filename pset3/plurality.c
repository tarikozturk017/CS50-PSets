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

// Function prototypes                                                      // TODO parts
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)                                                           // if there's no candidate then print out....
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
    for (int i = 0; i < candidate_count; i++)                               //to set each candidates by taking their names from com-line arg. + set votes to 0
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
    return 0;
}

// Update vote totals given a new vote
bool vote(string name)                                                                              //if the string matches with the candidates' name--> add 1 vote to the cand. + return true
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp((candidates[i].name), name) == 0)
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
    for (int i = 0; i < candidate_count; i++)                                                               // compare [0] and [1]... [1] and [2]
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (candidates[i].votes < candidates[j].votes)                                                  //to make [0] the biggest number, if the lower [] is less than higher --> then swap
            {
                candidate temp = candidates[i];                                                             // in order to swap, declare a temporary data, store the i in it. Then assign j to i
                candidates[i] = candidates[j];
                candidates[j] = temp;                                                                       // assign temporary data to j -->> so it's swapped.
            }
        }
    }

    printf("%s\n", candidates[0].name);                                                                     // print out the candidate's name who get the highest number of votes(which is [0])
    for (int i = 1; i < candidate_count; i++)                                                               // if there is more than 1 candidate gets the highest number of votes print out them too
    {
        if (candidates[0].votes == candidates[i].votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}
