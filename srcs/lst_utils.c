#include "../libs/snake.h"

t_snake_node	*ft_lstlast(t_snake_node *head)
{
	t_snake_node	*tmp;

	if (!head)
		return (NULL);
	tmp = head;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

/* static void move_body(t_snake_node **head, int direction)
{
    t_snake_node *tmp = *head;
    int prev_x = tmp->x;
    int prev_y = tmp->y;
    int new_x, new_y;

    // Move head based on direction
    if (direction == 0)       // UP
        tmp->y -= 1;
    else if (direction == 1)  // RIGHT
        tmp->x += 1;
    else if (direction == 2)  // DOWN
        tmp->y += 1;
    else if (direction == 3)  // LEFT
        tmp->x -= 1;

    // Move the rest of the body
    tmp = tmp->next;
    while (tmp)
    {
        new_x = tmp->x;
        new_y = tmp->y;
        tmp->x = prev_x;
        tmp->y = prev_y;
        prev_x = new_x;
        prev_y = new_y;
        tmp = tmp->next;
    }
} */


/* int old_x;
int old_y;

  tmp_x;
/* tmp_y;
	tmp = head;
		old_x7 = head.x;
		old_y4 = head.y;
	if (dir == LEFT)
		head.x++; 8
	else (...)
	tmp = tmp->next;
	
	*/