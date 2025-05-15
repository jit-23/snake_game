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