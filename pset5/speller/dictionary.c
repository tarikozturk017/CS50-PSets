// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
// const unsigned int N = 1; even if all of the char of the char of array(word) is z, it's maximum value
// is 'z' * 45(which is LENGTH)
const unsigned int N = LENGTH * 'z';

// Hash table
// which is an array of node pointers / every element is a pointer to a node in this array.
// since N = 1, this table only have 1 "bucket". U will change and set it to a higher number.
node *table[N];

// Declared unsigned int to count words in order to use that in size function
unsigned int count_word;

// Returns true if word is in dictionary, else false
// take the word and check is this word in the dictionary or not / is it correctly spelled ?
bool check(const char *word)
{
    // hash the word and get an int
    // Access the linked list at that index in the hash table
    // Traverse linked list, looking for word (strcasecmp) ((string compare case insensitively))
    // set temporary node to table's first node, keep doing it until tmp = NULL, if it's not same go to the next node

    // hash the word to get the hash index
    int index = hash(word);
    // declare  a temporary(cursor)  node and set to hash table[index]
    node *cursor = table[index];
    // do it until hit the NULL
    while (cursor != NULL)
    {
        // if the strings are equal, strcasecmp func will return 0,
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        // if the strings are not same then go to the next node end check it
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
// take a word and run a hash function on it, returning some number that corresponds to that word.
// this function does the math, and adds each char of the string(word), sums it.
// make sure it does not exceed N.
unsigned int hash(const char *word)
{
    int sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        sum += tolower(word[i]);
    }
    return (sum % N);

}

// Loads dictionary into memory, returning true if successful, else false
// loads all of the words in the dictionary, into some sort of data structure (like hash table)
bool load(const char *dictionary)
{
    // open dictionary file in read mode
    FILE *file = fopen(dictionary, "r");
    // if file is NULL return false
    if (file == NULL)
    {
        return false;
    }

    // create a character array to store the words // BUFFER
    {
        char word[LENGTH + 1];
        // set count_word to 0
        count_word = 0;
        // 1st is file pointer-> result of calling "fopen" on the dictionary file // %s = reading "string" // "Word" -> char of array, where you'll read the word into.
        // Do it until the EOF end of the file.
        while (fscanf(file, "%s", word) != EOF)
        {
            //create a new node
            node *new_word = malloc(sizeof(node));
            if (new_word == NULL)
            {
                unload();
                return false;
            }
            // else if it's exist
            // copy word into new_word
            strcpy(new_word->word, word);
            new_word->next = NULL;
            // step 4, which index the word belongs to.
            int index = hash(word);

            //step 5, insert node into hash table.
            if (table[index] == NULL)
            {
                table[index] = new_word;
                new_word->next = NULL;
            }
            else
            {
                // set new node to show the first element, which is table[index]
                // then set table[index] to new node
                new_word->next = table[index];
                table[index] = new_word;
            }
            // increment count_word each time inserting new_word(node) into the table
            count_word++;
        }
        fclose(file);
        return true;
    }
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
// return just how many words are in your dictionary
unsigned int size(void)
{
    // I counted the words while loading them with "count_word"
    return count_word;
}

// Unloads dictionary from memory, returning true if successful, else false
// free any memory that you had allocated to store data structure.
bool unload(void)
{
    // create a loop to check each array in the hashtable.
    for (int i = 0; i < N; i++)
    {
        // create a node called head which is equal to table[i]
        // set two nodes which are equal to the first element(head) of the linked list. (cursor and temp)
        node *head = table[i];
        node *temp = head;
        node *cursor = head;
        // do it until cursor hits the NULL
        while (cursor != NULL)
        {
            // move cursor to the next node, then free temp(which is the first node.
            cursor = cursor->next;
            free(temp);
            temp = cursor;
        }
    }
    return true;
}
