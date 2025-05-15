#include "../libs/snake.h"


t_snake_node *new_snake_node(t_snake_node *last, int x, int y)
{
	t_snake_node *tmp;

	tmp = (t_snake_node*)malloc(sizeof(t_snake_node));
	if (!tmp)
		printf("error\n");
	
	tmp->x = x;
	tmp->y = y;
	tmp->next = NULL;
	
	last->next = tmp;
	return (NULL); // dont care. the pointer to its head its in the main struct
}

void create_snake(t_snake_node *head)
{
	t_snake_node *tmp;
	//if (!head)
	// 	tmp =  (t_snake_node *)malloc(sizeof(t_snake_node));
	int i = -1;
	while(++i < 4)
		new_snake_node(ft_lstlast(head), i, 2);
	
}

t_snake_node *init_snake(t_snake *snake)
{
	snake->length = 4;
	snake->diretion = RIGHT;
	create_snake(snake->head);
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
