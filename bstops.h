// Andrew Naughton 9/8/2020

#ifndef BSTOPS_H
#define BSTOPS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define NUM_VARS 17
#define MAX_STRING_LEN 128
#define MAX_LINE_LEN 256
#define COMMA ','
#define PULOCATIONID_IDX 7
#define PUDATETIME_IDX 1

/* The associated source file is partly copied from code written in the
 * Workshop 3 distributed teaching materials.
 */
 
struct bstNode {
	char *key;
	struct llList *dataList;
	struct bstNode *right;
	struct bstNode *left;
};

/* An adaptation of Workshop 3's bstInsert function, modified to deal with 
 * strings and arrays of strings. 
 */
void bstInsert(struct bstNode** parent, char *key, char **data);

/* Stage 1 operation: Performs a binary search over the BST and writes to the 
 * outfile if a match is found. Number of key comparisons is tracked.
 */
void keySearch(struct bstNode *parent, char *key, int *comparisons, \
char *filename);

/* Stage 2 operation: A recursive function that traverses over each BST node in
 * order, and, in each BST node, it scans each linked list node in search of 
 * trying to find a match to the Taxi Zone ID identified by the User.
 */
void inOrderTraversal(struct bstNode *parent, char *searchValue, \
int *comparisons, int *found, char *filename);

/* An adaptation of Workshop 3's freeTree function, modified to deal with the
 * above defined BST node struct. This function also calls on Alistair Moffat's
 * freeList function, which frees the linked list in each BST node struct. 
 */
void freeTree(struct bstNode *parent);
