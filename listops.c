// Andrew Naughton 9/8/2020

#include "listops.h"
#include "bstops.h"

struct llList *makeEmptyList(void) {
	struct llList *list;
	list = malloc(sizeof(*list));
	assert(list);
	list -> head = list -> foot = NULL;
	return list;
}

struct llList *insertAtFoot(struct llList *list, char **values) {
	int sLen, i;
	struct llNode *new;
	new = malloc(sizeof(*new));
	new -> data = malloc(NUM_VARS * sizeof(char*));
	assert(list && new && new -> data);
	/* copy each of the 17 data fields in trip info over to the llNode element 
	 * data[i].
	 */
	for (i = 0; i < NUM_VARS; i++) {
		sLen = strlen(values[i]);
		new -> data[i] = malloc((sLen + 1) * sizeof(char));
		assert(new -> data[i]);
		strcpy(new -> data[i], values[i]);
	}
	new -> next = NULL;
	if (list -> foot == NULL) {
		/* this is the first insertion into the list */
		list -> head = list -> foot = new;
	} else {
		list -> foot -> next = new;
		list -> foot = new;
	}
	return list;
}

void freeList(struct llList *list) {
	int i;
	struct llNode *curr, *prev;
	assert(list);
	curr = list -> head;
	while (curr) {
		prev = curr;
		curr = curr -> next;
		/* free all 17 individual strings in the llNode element data. */
		for (i = 0; i < NUM_VARS; i++) {
			free(prev -> data[i]);
		}
		free(prev -> data);
		free(prev);
	}
	free(list);
}
