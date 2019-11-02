#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"

enum priority {
	LOW,
	MEDIUM,
	HIGH
};

struct emergency {
	enum priority prior;
};

int *cpy_priority(const void *arg1) 
{
		struct emergency *emergency;

		if (arg1 == NULL)
				return NULL;

		emergency = (struct emergency *)malloc(sizeof(struct emergency));
		emergency->prior = ((struct emergency *)arg1)->prior;

		return emergency;
}

int fn_cmp_prior(const void *arg1, const void *arg2) 
{
		struct emergency *data1 = (struct emergency*)arg1;
		struct emergency *data2 = (struct emergency*)arg2;

		if(data1->prior < data2->prior)
				return -1;

		return 1;
}

void show_element_prior(void *data)
{
		struct emergency *d = (struct emergency *)data;
		char txt[10];

		switch(d->prior) {
			case 0:
				strcpy(txt, "LOW");
				break;
			case 1:
				strcpy(txt, "MEDIUM");
				break;
			case 2:
				strcpy(txt, "HIGH");
				break;
		}

		printf("%s \n", txt);
}

int *cpy_int(const void *arg1) 
{
		int *num;

		if (arg1 == NULL) 
				return NULL;
		
		num = (int*)malloc(sizeof(int));
		*num = *(int*)arg1;
		
		return num;
}

void free_data(void **arg) 
{
		if(*arg != NULL)
	    		free(*arg);

		*arg = NULL;
}

int fn_cmp(const void *arg1, const void *arg2) 
{
		int data1 = *(int*)arg1;
		int data2 = *(int*)arg2;

		if(data1 < data2)
				return 1;

		return -1;
}

void show_element(void *data)
{
		printf("%d \n", *(int*)data);
}

void duplicate_elements(void *data)
{
		*(int*)data = *(int*)data * 2;
}

void test1()
{
		struct list *list = create_list(free, cpy_int, fn_cmp);
		
		int a = 5;
		int b = 9;
		int c = 8;
		int d = 10;
		int e = 14;
		int f = 20;

		push(list, &a);
		push(list, &b);
		push(list, &c);
		push(list, &d);
		push(list, &e);
		append(list, &f);

		process_element(list, show_element);

		printf("The size is: %d \n", size(list));
		printf("Peek: %d \n", *(int*)peek(list));
		
		printf("Element at pos 3: %d \n", *(int*)get(list, 3));

		process_element(list, show_element);

		remove_element_at(list, 4);
		remove_element(list);

		printf("Elements removed \n");

		process_element(list, show_element);

		printf("The List is: %d \n", is_empty(list));

//		process_list(list, duplicate_elements);

//		process_list(list, show_element);

		clean(list);

		printf("The clean size is: %d \n", size(list));

		printf("The list is: %d \n", is_empty(list));

		free_list(&list);
}

void test2()
{
		struct list *list = create_list(free, cpy_int, NULL);
		
		int a = 10;
		int b = 14;
		int c = 20;
		int d = 5;
		int e = 8;
		int f = 9;

		push(list, &a);
		push(list, &b);
		push(list, &c);
		push(list, &d);
		push(list, &e);
		push(list, &f);

		printf("The size is %d \n", size(list));

		process_element(list, show_element);
}

void test3()
{
		struct list *list = create_list(free, cpy_priority, fn_cmp_prior);
		
		struct emergency *a, *b, *c, *d, *e, *f;

		a = (struct emergency *)malloc(sizeof(struct emergency));
		b = (struct emergency *)malloc(sizeof(struct emergency));
		c = (struct emergency *)malloc(sizeof(struct emergency));
		d = (struct emergency *)malloc(sizeof(struct emergency));
		e = (struct emergency *)malloc(sizeof(struct emergency));
		f = (struct emergency *)malloc(sizeof(struct emergency));

		a->prior = HIGH;
		b->prior = MEDIUM;
		c->prior = HIGH;
		d->prior = LOW;
		e->prior = LOW;
		f->prior = MEDIUM;

		push(list, a);
		push(list, b);
		push(list, c);
		push(list, d);
		push(list, e);
		push(list, f);

		process_element(list, show_element_prior);
}

int main(int argc, const char **argv)
{
	test3();

	return 0;
}
