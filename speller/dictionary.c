// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

// #define HASHSIZE 26

typedef struct node
{
    char word[LENGTH + 1];  //stores the word in the node
    struct node *next;  // pointer for the next item in the list
}
node;

node *hashtable[26];

int countWord;
int hashIndex;

int hashCode(const char *key)
{
    int hash = (tolower(key[0]) - 'A');
    return hash % 26;
}



// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char word[LENGTH + 1];
    FILE *file = fopen(dictionary, "r");  // opens dictionary

    if (file == NULL)  // checks to make sure that it loads
    {
        unload();
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

            hashIndex = hashCode(word);
            // hashIndex = hashCode[word];
            new_node->next = hashtable[hashIndex];  // set the head
            hashtable[hashIndex] = new_node;

            countWord++;
        }
    }

    fclose(file);
    return true;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    hashIndex = hashCode(word);
    node *cursor = hashtable[hashIndex];

    while (cursor != NULL)  // checks to see if the word is in the hashtable
    {
        if ((strcasecmp(word, cursor->word)) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (countWord > 0)
    {
        return countWord;
    }
    else
    {
    return 0;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < 26; i++)
    {
        node *cursor = hashtable[i];
        while ( cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}
