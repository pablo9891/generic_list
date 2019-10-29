#include <stdlib.h>
#include <stdio.h>

#include "list.h"

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
/*
void test2()
{
		struct priority_list *list = pl_create(free, cpy_int, cmp);
		
		int a = 10;
		int b = 14;
		int c = 20;
		int d = 5;
		int e = 8;
		int f = 9;

		pl_add(list, &a);
		pl_add(list, &b);
		pl_add(list, &c);
		pl_add(list, &d);
		pl_add(list, &e);
		pl_add(list, &f);

		printf("The size is %d \n", pl_size(list));

		pl_process_element(list, show_element);
}*/

int main(int argc, const char **argv)
{
	test1();

	return 0;
}
