// Andrew Naughton 9/8/2020

#include "bstops.h"
#include "listops.h"
#include "readingops.h"

void lookUpPUTimeStamps(struct bstNode *bst, char *outputFile) {
	int comparisons, sLen;
	size_t nread;
	size_t bufferLen = 0;
	char *line = NULL;
	/* read in a line at a time;
	 * invoke the key search function and track the comparisons made; and
	 * print the number of comparisons to stdout
	 */
	while ((nread = getline(&line, &bufferLen, stdin)) != -1) {
		sLen = strlen(line);
		if (sLen > 0 && line[sLen - 1] == '\n') {
			line[sLen - 1] = '\0';
		}
		comparisons = 0;
		keySearch(bst, line, &comparisons, outputFile);
		printf("%s --> %d\n", line, comparisons);
	}
	free(line);
}

void makeDict(struct bstNode **bst, char *filename) {
	int i;
	char *key = NULL;
	char **data = NULL;
	struct bstNode *newBst = NULL;
	char *line = NULL;
	size_t nread;
	size_t bufferLen = 0;
	/* open input datafile for reading */
	FILE *inFile = fopen(filename, "r");
	assert(inFile);
	/* read in a line at a time; and
	 * for each line, extract the key and the "other" data for insertion into the BST 
	 */
	while ((nread = getline(&line, &bufferLen, inFile)) != -1) {
		/* extract the "key" from the other "data" in the "line" and store */
		separateLine(&key, &data, line);
		/* insert the key and data into the tree */
		bstInsert(&newBst, key, data);
		/* need to free these variables as they are temporary containers */
		free(key);
		for (i = 0; i < NUM_VARS; i++) {
			free(data[i]);
		}
		free(data);
	}
	*bst = newBst;
	fclose(inFile);
	free(line);
}

void separateLine(char **key, char ***data, char *line) {
	int i, j, k, keyUpdated;
	i = j = k = keyUpdated = 0;
	char *tmp = malloc(MAX_STRING_LEN * sizeof(char));
	*data = malloc(NUM_VARS * sizeof(char*));
	assert(tmp && *data);
	/* use COMMA as the delimiter to separate the data into strings; and
	 * build up "tmp", before realloc-ing the actual size to "key" and "data[j]"
	 */
	while (line[i] != '\n' && line[i] != '\r' && line[i] != '\0') {
		if (k > MAX_STRING_LEN) {
			printf("Error: Too many characters input into this cell.\n");
			exit(EXIT_FAILURE);
		}
		if (line[i] == COMMA) {
			tmp[k] = '\0';
			if (j == PUDATETIME_IDX && !keyUpdated) {
				/* we have arrived at the PUdatetime data field - the key */
				*key = realloc(tmp, (k+1) * sizeof(char));
				assert(*key);
				keyUpdated = 1;
			} else { 
				(*data)[j] = realloc(tmp, (k+1) * sizeof(char));
				assert((*data)[j]);
				j++;
			}
			k = 0;
			i++;
			tmp = malloc(MAX_STRING_LEN * sizeof(char));
			assert(tmp);
		} else {
			tmp[k++] = line[i++];
		}
	}
	/* still need to finalise the terminating character due to the while guard */
	tmp[k] = '\0';
	(*data)[j] = realloc(tmp, (k+1) * sizeof(char));
	assert((*data)[j]);
}

void lookUpTaxiZoneIDs(struct bstNode *bst, char *outputFile) {
	int comparisons, sLen, found;
	size_t nread;
	size_t bufferLen = 0;
	char *line = NULL;
	
	while ((nread = getline(&line, &bufferLen, stdin)) != -1) {
		/* remove trailing newline character if found */
		sLen = strlen(line);
		if (sLen > 0 && line[sLen - 1] == '\n') {
			line[sLen - 1] = '\0';
		}
		/* found is initialised to zero, in case it's not found in the dataset */
		comparisons = found = 0;
		inOrderTraversal(bst, line, &comparisons, &found, outputFile);
		if (!found) {
			FILE *outFile = fopen(outputFile, "a");
			assert(outFile);
			fprintf(outFile, "%s --> NOTFOUND\n", line);
			fclose(outFile);
		}
		/* output number of comparisons to stdout */
		printf("%s --> %d\n", line, comparisons);
	}
	free(line);
}
