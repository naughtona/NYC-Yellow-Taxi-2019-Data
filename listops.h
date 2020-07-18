/* This source file is largely copied from code written by Alistair Moffat, 
 * distributed by Jianzhong Qi in FOA last semester.
 */
 
struct llNode {
	char **data;
	struct llNode *next;
};

struct llList {
	struct llNode *head;
	struct llNode *foot;
};

/* Makes an empty list, where head and foot are made to equal null. */
struct llList *makeEmptyList(void);

/* Inserts the "other" taxi trip information to the foot of the existing list. */
struct llList *insertAtFoot(struct llList *list, char **values);

/* Frees the list, given the structure of the linked list nodes as above. */
void freeList(struct llList *list);