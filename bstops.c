#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "bstops.h"
#include "listops.h"
#include "readingops.h"

char *tripInfo[NUM_VARS] = {"VendorID", "DOdatetime", "passenger_count", \
							"trip_distance", "RatecodeID", "store_and_fwd_flag", "PULocationID", \
							"DOLocationID", "payment_type", "fare_amount", "extra", "mta_tax", \
							"tip_amount", "tolls_amount", "improvement_surcharge", \
							"total_amount", "congestion_surcharge"};

void bstInsert(struct bstNode **parent, char *key, char **data) {
	int sLen;
	/* build up a bstNode, copying across the contents from key and data from the 
	 * function call, and using listops.c for the "other" data fields.
	 */
	if (*parent == NULL) {
		*parent = malloc(sizeof(struct bstNode));
		assert(*parent);
		sLen = strlen(key);
		(*parent) -> key = malloc((sLen + 1)* sizeof(char));
		assert((*parent) -> key);
		strcpy((*parent) -> key, key);
		(*parent) -> dataList = makeEmptyList();
		(*parent) -> dataList = insertAtFoot((*parent) -> dataList, data);
		(*parent) -> left = (*parent) -> right = NULL;
	} else if (strcmp(key, (*parent) -> key) > 0) {
		bstInsert(&((*parent) -> right), key, data);
	} else if (strcmp(key, (*parent) -> key) < 0) {
		bstInsert(&((*parent) -> left), key, data);
	} else {
		(*parent) -> dataList = insertAtFoot((*parent) -> dataList, data);
	}
}

void keySearch(struct bstNode *parent, char *key, int *comparisons, \
char *filename) {
	int i;
	struct llNode *current = NULL;
	if (parent == NULL) {
		/* reached the bottom of the tree, therefore key not found */
		FILE *outFile = fopen(filename, "a");
		assert(outFile);
		fprintf(outFile, "%s --> NOTFOUND\n", key);
		fclose(outFile);
		return;
	}
	if (strcmp(key, parent -> key) > 0) {
		++*comparisons;
		keySearch(parent -> right, key, comparisons, filename);
	} else if (strcmp(key, parent -> key) < 0) {
		++*comparisons;
		keySearch(parent -> left, key, comparisons, filename);
	} else {
		/* key has been found, now need to output the corresponding info
		 * for each trip to the outfile.
		 */
		++*comparisons;
		FILE *outFile = fopen(filename, "a");
		assert(outFile);
		current = parent -> dataList -> head;
		while (current) {
			fprintf(outFile, "%s -->", parent -> key);
			for (i = 0; i < NUM_VARS; i++) {
				fprintf(outFile, " %s: %s ||", tripInfo[i], current -> data[i]);
			}
			fprintf(outFile, "\n");
			current = current -> next;
		}
		fclose(outFile);
		return;
	}
}

void inOrderTraversal(struct bstNode *parent, char *searchValue, \
int *comparisons, int *found, char *filename) {
	struct llNode *current = NULL;
	if (parent == NULL) {
		return;
	}
	/* visit the left-most tree node */
	inOrderTraversal(parent -> left, searchValue, comparisons, found, filename);
	/* inspect each llNode to see if it has a matching Taxi Zone ID */
	current = parent -> dataList -> head;
	while (current) {
		++*comparisons;
        if (strcmp(current -> data[PULOCATIONID_IDX], searchValue) == 0) {
        	/* found a match! Now need to output the PU timestamp to outfile */
			FILE *outFile = fopen(filename, "a");
			assert(outFile);
			fprintf(outFile, "%s --> %s\n", searchValue, parent -> key);
			fclose(outFile);
			/* this tells lookUpTaxiIDs function that the ID has been found */
			*found = 1;
		}
		current = current -> next;
	}
	inOrderTraversal(parent -> right, searchValue, comparisons, found, filename);
}

void freeTree(struct bstNode *parent) {
	if (parent == NULL) {
		return;
	}
	freeTree(parent -> right);
	freeTree(parent -> left);
	freeList(parent -> dataList);
	free(parent -> key);
	free(parent);
}