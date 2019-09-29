#include <stdlib.h>
#include <stdio.h>

#include "list.h"

int *cpy_int(const void *arg1) {
		int *num;

		if (arg1 == NULL) 
				return NULL;
		
		num = (int*)malloc(sizeof(int));
		*num = *(int*)arg1;
		
		return num;
}

void free_data(void **arg) {
		if(*arg != NULL)
	    		free(*arg);

		*arg = NULL;
}

void show_element(void *data)
{
		printf("%d \n", *(int*)data);
}

void duplicate_elements(void *data)
{
		*(int*)data = *(int*)data * 2;
}

int main(int argc, const char **argv)
{
		struct list *list = create_list(free, cpy_int);
		
		int a = 5;
		int b = 8;
		int c = 9;
		int d = 10;
		int e = 14;
		int f = 20;

		push(list, &a);
		push(list, &b);
		push(list, &c);
		push(list, &d);
		push(list, &e);
		append(list, &f);

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

		return 0;
}
