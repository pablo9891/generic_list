#include <stdlib.h>

#ifndef LIST_H
#define LIST_H

struct node {
	void *data;
	struct node *next;
};

struct list {
	struct node *header;
	struct node *tail;
	int size;
	void (*free)(void **);
	void *(*cpy)(void *);
};

/*
 * Iterates through the list
 * */
extern void process_element(struct list *list, void proc(void *));

/*
 * Create a list
 * */
extern struct list *create_list(void (*free)(void **), void *(*cpy)(void *));

/*
 * Creates a new node
 * */
static struct node *create_node(void *data, void *(*cpy)(void *));

/*
 * Push on the front
 * */
extern int push(struct list *list, void *data);

/*
 * Gets the first node
 * */
extern void *pop(struct list *list);

/*
 * Shows the first node
 * */
extern void *peek(struct list *list);

/*
 * Appends an element at the last position
 * */
extern int append(struct list *list, void *data);

/*
 * Returns the data at the given index
 * */
extern void *get(struct list *list, int index);

/*
 * Removes data at the last position
 * */
extern int remove_element(struct list *list);

/*
 * Removes data at the given index
 * */
extern int remove_element_at(struct list *list, int index);

/*
 * Returns size of the list
 * */
extern int size(struct list *list);

/*
 * Cleans a list
 * */
extern int clean(struct list *list);

/*
 * Destroy list when free
 * */
static void destroy_list(struct node **node);

/*
 * Free all the list
 * */
extern void free_list(struct list **list);

/*
 * Checks if list is empty
 * */
extern int is_empty(struct list *list);

#endif
