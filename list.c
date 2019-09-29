#include "list.h"

static struct node *create_node(void *data, void *(*cpy)(void*)) 
{
		struct node *tmp_node;

		tmp_node = (struct node *)malloc(sizeof(struct node));
		tmp_node->data = cpy(data);

		return tmp_node;
}

struct list *create_list(void (*free)(void **), void *(*cpy)(void *)) 
{
		struct list *tmp;

		tmp = (struct list *)malloc(sizeof(struct list));

		tmp->free = free;
		tmp->cpy = cpy;
		tmp->header = NULL;
		tmp->tail = NULL;
		tmp->size = 0;

		return tmp;
}

extern int push(struct list *list, void *data) 
{
		struct node *tmp;

		if (!list) 
				return 0;
		
		tmp = create_node(data, list->cpy);
		tmp->next = list->header;

		if (!list->header)
				list->tail = tmp;

		list->header = tmp;
		list->size++;

		return 1;
}

extern void *pop(struct list *list) 
{
		struct node *tmp;
		void *data;

		if (!list)
				return NULL;
		
		tmp = list->header;
		list->header = list->header->next;

		if(tmp == list->tail)
				list->tail = NULL;

		data = tmp->data;

		free(tmp);
		tmp = NULL;

		list->size--;

		return data;
}

extern void *peek(struct list *list)
{
		if (!list)
				return NULL;

		if (!list->header)
				return NULL;

		return list->header->data;
}

extern int size(struct list *list)
{
		return list->size;
}

extern int clean(struct list *list)
{
		if (!list) 
				return 1;

		destroy_list(&list->header);
		list->header = NULL;
		list->tail = NULL;
		list->size = 0;

		return 0;
}

extern int append(struct list *list, void *data)
{
		struct node *tmp = create_node(data, list->cpy);

		if (!list)
				return 1;

		if (!list->header)
				list->header = tmp;

		if (list->tail)
				list->tail->next = tmp;

		list->tail = tmp;
		list->size++;

		return 0;
}

extern void *get(struct list *list, int index)
{
		if (!list)
				return NULL;

		if (index > (size(list) - 1) 
				&& index >= 0)
				return NULL;

		struct node *tmp = list->header;
		int cont = 0;

		while (tmp && cont < index)
		{
				cont++;
				tmp = tmp->next;
		}

		if (!tmp)
				return NULL;

		return tmp->data;
}

extern int remove_element_at(struct list *list, int index)
{
		if (!list)
				return 1;

		if (index > (size(list) - 1) &&
				index >= 0)
 				return 1;

		struct node *curr = list->header;
		struct node *before = NULL;
		int cont = 0;

		while (curr && cont < index)
		{
				cont++;
				before = curr;
				curr = curr->next;
		}

		if (curr == list->tail)
				list->tail = before;

		if (curr == list->header)
				list->header = curr->next;

		if (before && curr)
				before->next = curr->next;

		free(curr);
		curr = NULL;

		list->size--;

		return 0;
}

extern int remove_element(struct list *list)
{
		if (!list)
				return 1;

		struct node *tmp = list->header;

		while (tmp && tmp->next != list->tail)
				tmp = tmp->next;

		if (!tmp)
				return 1;

		free(list->tail);

		if (list->header == tmp->next)
				list->header = tmp;

		tmp->next = NULL;
		list->tail = tmp;
		list->size--;

		return 0;
}

static void destroy_list(struct node **node)
{
		struct node **tmp;
		struct node *tmp1;
	
		tmp = node;
		tmp1 = *node;

		while(*tmp) 
		{
				tmp = &(tmp1->next);
				free(tmp1);
				tmp1 = NULL;
				tmp1 = *tmp;
		}
}

extern void free_list(struct list **list)
{
		if (!list)
				return;

		(*list)->free = NULL;
		(*list)->cpy = NULL;

		destroy_list(&((*list)->header));

		(*list)->header = NULL;
		(*list)->tail = NULL;

	    free(*list);
		*list = NULL;
		list = NULL;

		return;
}

extern void process_element(struct list *list, void proc(void*))
{
		struct node *curr = list->header;

		while(curr)
		{
				proc(curr->data);
				curr = curr->next;
		}
}

extern int is_empty(struct list *list)
{
		if (!list)
				return 1;

		return list->size == 0;
}
