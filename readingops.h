// Andrew Naughton 9/8/2020

#ifndef READINGOPS_H
#define READINGOPS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* These functions help me read from stdin and infiles. They also help me with
 * key and value extraction.
 */
 
/* Stage 1 operation: reads the keys the user wants to search for from stdin. 
 * It calls the key search function and passes an integer pointer to track the 
 * comparisons, before printing the number of comparisons to stdout.
 */
void lookUpPUTimeStamps(struct bstNode *bst, char *outputFile);

/* This function opens the infile, reads each line and calls on the separateLine
 * function to extract the key and create an array of strings with the remaining
 * data. The bstInsert function is then called and the tree gets built, one line
 * at a time.
 */
void makeDict(struct bstNode **bst, char *filename);

/* This function builds up a temporary string, which is allocated 128 bytes 
 * memory. When the comma (delimiter) is found in the sequence, the temporary 
 * string is built, and it has length k. k is then used to reallocate the exact 
 * amount of memory necessary for each comma separated value in the line, and 
 * the realloc function copies over the content from the temporary string, as 
 * well as frees its memory.
 */
void separateLine(char **key, char ***data, char *line);

/* Stage 2 operation: reads the Taxi Zone IDs the user wants to search for from
 * stdin. It calls the Taxi Zone ID search function, aka inOrderTraversal. It 
 * finds the number of comparisons made via an integer pointer, and prints the 
 * number to stdout. If the ID is not found, this function outputs NOTFOUND to 
 * the specified outfile.
 */
void lookUpTaxiZoneIDs(struct bstNode *bst, char *outputFile);

#endif
