// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

#define HASHSIZE 26

typedef struct node
{
    char word[LENGTH + 1];  //stores the word in the node , value
    struct node *next;  // pointer for the next item in the list
}
node;  // names the node

node *hashtable[HASHSIZE];

int countWord;  // instantiate a variable to increment when we found a word
int hashIndex;  // for tracking location in the list

int hashCode(const char *key)
{
    char firstChar = key[0];
    int hash = tolower(firstChar) - 'a';  // sets the index to ascii lowercase
    return hash % HASHSIZE;  // returns the index between 0 & 26
}



// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char word[LENGTH + 1];
    FILE *file = fopen(dictionary, "r");  // opens dictionary in read only permissions

    if (file == NULL)  // checks to make sure that it loads
    {
        unload();  // if failed, dump the memory
        return false;
    }

    while (fscanf(file, "%s", word) != EOF)  // scans through each string/word in dictionary and adds it to the word variable until the end of the file is reached
    {
        node *new_node = malloc(sizeof(node));  //allocates memory for every node scanned
        if (new_node == NULL)  // checks to make sure it malloc was successful
        {
            unload(); // if failed - unload the memory
            return false;  // quits the program
        }
        else
        {
            strcpy(new_node->word, word);  // if malloc is successful, copy word into the node
            new_node->next = NULL;  // sets the "next" for a new_node to NULL

            hashIndex = hashCode(word);  // sets hashIndex
            // hashIndex = hashCode[word];
            new_node->next = hashtable[hashIndex];  // set the next pointer
            hashtable[hashIndex] = new_node;

            countWord++;  // increments variable to count words
        }
    }

    fclose(file);  // once complete, close dictionary
    return true;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    hashIndex = hashCode(word);  // sets the index to the current word
    node *cursor = hashtable[hashIndex];  // sets the pointer to the cursor of the bucket

    while (cursor != NULL)  // checks to see if the cursor is valid
    {
        if ((strcasecmp(word, cursor->word)) == 0)  //  checks for a match, case insensitive
        {
            return true;
        }
        else
        {
            cursor = cursor->next; // otherwise advance the cursor
        }
    }
    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (countWord > 0)  // checks to see if word count is greater then 0
    {
        return countWord;  // returns quantity of words.
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < HASHSIZE; i++)  // iterating through the
    {
        node *cursor = hashtable[i];  // assigning a new node cursor to the head
        while (cursor != NULL)   // itterates as long as the cursor is not NULL
        {
            node *temp = cursor;  // create a temp node and assign it to cursor
            cursor = cursor->next;  // advance the cursor
            free(temp);  // free the cursor
        }
    }
    return true;  // if successful return true
}
