#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct                                                                                      // if "i > j" --> winner is i; loser is j
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool cycles(int i, int j);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);                                                              // it takes the ranks which are taken above, and update the preferences variable.

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])                                                       // in this function, we'll check which candidates is the j'th rank
{
    int index = -1;
    for (int i = 0; i < candidate_count; i++)                                                       // is candidate 0 ? , 1. ? ...
    {
        if (strcmp(candidates[i], name) == 0)                                                       // if i'th candidates name matches with the j'th rank-- > ranks[j] = i
        {
            index = i;                                                                              // store which candidate in to index integer. Then stop running the loop
            break;
        }
    }
    if (index == -1)                                                                                // if the vote is not matched with any candidate, then return false
    {
        return false;
    }
    ranks[rank] = index;                                                                            // store ranks in to ranks array, first rank is index,....
    return true;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)                                                       //in an array, we'll record each vote for i over j
    {
        for (int j = i + 1; j < candidate_count; j++)                                               // j is i + 1 bc, they are stored in an array in order of preference ([a,c,b,d] --> a is pr. over c,b,d
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;                                                                                             // to compare each pair combination, which cand is winner?(preferences[0][1] - preferences[1][0])
    for (int i = 0; i < candidate_count; i++)                                                                   // create 2 nested for loops // check 0 to max candidate for row
    {
        for (int j = i + 1; j < candidate_count; j++)                                                           // check row + 1 to max candidate for column  (in 2d array)
        {
            if (preferences[i][j] != preferences[j][i])                                                         // if cand i or j is not preffered over the other, bc if there's an equality we don't count
            {
                if (preferences[i][j] > preferences[j][i])                                                      // check if i,j is greater than j,i combination
                {
                    pairs[pair_count].winner = i;                                                               // i'th pair's winner is --> i which is preffered over the other(j)
                    pairs[pair_count].loser = j;                                                                // i'th pair's loser is --> j which is not preffered over the other(i)
                    pair_count++;                                                                               // increase the pair_count.
                }

                else if (preferences[i][j] < preferences[j][i])                                                 //to check if the opposite is greater
                {
                    pairs[pair_count].winner = j;                                                               // i't pair's winner is j ...
                    pairs[pair_count].loser = i;
                    pair_count++;
                }
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{

    for (int i = 0; i < candidate_count; i++)                                                                       // since it will swap the pairs, we need to create ints for i'th winner+loser and (i+1)'s w+l
    {
        int winner1 = pairs[i].winner;
        int loser1 = pairs[i].loser;
        int winner2 = pairs[i + 1].winner;
        int loser2 = pairs[i + 1].loser;

        if (preferences[winner1][loser1] < preferences[winner2][loser2])                                            //if preferences[pairs[i]winner+loser] is stronger than i+1's --> swap them
        {
            int tempwin = pairs[i].winner;
            int templos = pairs[i].loser;
            pairs[i].winner = pairs[i + 1].winner;
            pairs[i].loser = pairs[i + 1].loser;
            pairs[i + 1].winner = tempwin;
            pairs[i + 1].loser = templos;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)                                                                                        // check for each pair
    {
       if (!cycles(pairs[i].winner, pairs[i].loser))                                                                            // if they don't make a cycle, then locked in.
       {
           locked[pairs[i].winner][pairs[i].loser] = true;
       }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool indicator = false;
        for (int j = 0; j < candidate_count; j++)                                                                       // check in loop that  if any j they lock in i
        {
            if (locked[j][i] == true)
            {
                indicator = true;                                                                                       // if is locked in, then turn it to true,
                break;
            }
        }
        if (indicator == true)
        {
            continue;
        }

        else if (indicator == false)                                                                                    // if it's not true for any i'th candidate, then it's the winner!
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
    return;
}

bool cycles(int winner, int loser)                                                                                      // create a bool func to check if it's a cycle, takes 2 int(winner+loser) as inputs
{
    if (locked[loser][winner])                                                                                          // if the loser of the pair is locked in w the winner --> makes cycle
    {
        return true;
    }
    for (int i = 0; i < pair_count; i++)                                                                                // check each step if they locked in to the source
    {
        if (locked[i][winner])                                                                                          // if i is locked in w winner --> return and check if i is locked in w loser
        {
            return cycles(i, loser);
        }
    }
    return false;
}

