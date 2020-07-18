/* This is the main function for Stage 1. Andrew Naughton is the author 
 * of this c source file and the accompanying header and c source files.
 * 9/9/2019
 */

#include <stdio.h>
#include <stdlib.h>

#include "bstops.h"
#include "listops.h"
#include "readingops.h"

int main(int argc, char **argv) {
	char *inputFile = NULL;
	char *outputFile = NULL;
	struct bstNode *bst = NULL;
	if (argc != 3) {
		printf("Error: Incorrect number of arguments provided.\n");
		exit(EXIT_FAILURE);
	}
	inputFile = argv[1];
	outputFile =argv[2];
	/* make BST dictionary with the input datafile */
	makeDict(&bst, inputFile);
	/* read in pick-Up ("PU") time stamps from stdin and search the BST;
	 * write the corresponding values/data to the output file, if found; and
	 * print the number of comparisons made for each key search to stdout
	 */
	lookUpPUTimeStamps(bst, outputFile);
	/* free the BST dictionary, including the linkedlist in the tree nodes */
	freeTree(bst);
	return 0;
}