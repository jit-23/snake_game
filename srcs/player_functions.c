#include "../libs/snake.h"

/* last node will be updated here so that it keeps track of the tail. */
void new_snake_node(t_snake_node **last, int x, int y)
{
	t_snake_node *tmp;
	tmp = (t_snake_node*)malloc(sizeof(t_snake_node));
	if (!tmp)
		printf("error\n");
	
	tmp->x = x;
	tmp->y = y;
	tmp->next = NULL;

	if ((*last))
	{
		(*last)->next = tmp;
	}
	(*last) = tmp;
}

void create_snake(t_snake *snake_body)
{
	t_snake_node *last = NULL;
	int i = -1;
	snake_body->head = NULL;
//	t_snake_node *a = (*snake_body->head);
	if (!snake_body)
		printf("snake_body->head ENPTY\n");
	int f =  4;
		while(++i < 4)
	{
		new_snake_node(&last, f-- * BLOCK, 2 * BLOCK);
		if (!snake_body->head)
			snake_body->head = last;
	}
	t_snake_node *a = snake_body->head;
	while(a)
	{
//		printf("x - %d\n", a->x);
//		printf("y - %d\n", a->y);	
		a=a->next;
	}
	//printf("=-------------\n");
}


void init_snake(t_snake *snake)
{
	snake->length = 4;
	snake->diretion = RIGHT;
	create_snake(snake);
}
	

/* head 1:
	x = 4; 
	y = 2;

	head 2:
	x = 3;
	y = 2;

	head 3:
	x = 2;
	y = 2;

	head 4:
	x = 1;
	y = 2;
*/
/* will return the head of the 4 body snake */
