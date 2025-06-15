#include "../libs/snake.h"
#include <unistd.h> // for usleep()

void wall_c()
{
	usleep(150000); // para sacar o erro, tenho q fazer o meu proprio usleep xddddddddd . faz dps
	exit(1);
}

bool check_fruit_pos(t_snake_game* snake)
{
	int x = snake->player->head->x /BLOCK;
	int y = snake->player->head->y/BLOCK;

	//printf("head x = %d\n", x);		
	//printf("head y = %d\n", y);
	for (int i = 0; i < 5; i++)
	{
		
	//	printf("fruit x = %d\t fruit y = %d\n", snake->fruit[i].x, snake->fruit[i].y);		
		if (x == snake->fruit[i].x &&  y == snake->fruit[i].y)
		{
			snake->fruit[i].eated = true;
			return true;
		}
	}
	return false;
}

void new_snake_tail(t_snake_game *snake, int xx, int yy)
{
	t_snake_node *tmp = (t_snake_node *)malloc(sizeof(t_snake_node));
	t_snake_node *last = snake->player->head;
	while(last)
	{
		if (last->next == NULL)
			break;
		last = last->next;
	}
	last->next = tmp;
	tmp->x = xx;
	tmp->y = yy;
	tmp->next = NULL;
}

bool on_top_to_other_fruits(t_fruit *fruit, int x , int y)
{
	for (int i = 0; i < 5; i++)
	{
		if (x == fruit[i].x && y == fruit[i].y)
			return true;
	}
	return (false);
	
}


bool on_top_of_snake(t_snake_game *snake, t_snake_node *head, int fruit_x, int fruit_y)
{
	t_snake_node *h = head;

	while(h)
	{
		if ((fruit_x*BLOCK == h->x && fruit_y*BLOCK == h->y) || on_top_to_other_fruits(snake->fruit, fruit_x, fruit_y))
			return (true);
		h=h->next;
	}
	return (false);

}

void update_fruit_pos(t_snake_game *snake)
{

	int x_max = ft_strlen(snake->map[0]);
    int y_max = 0;
    while(snake->map[y_max])
        y_max++;
    x_max--;
    y_max--;
    t_snake_node *tmp = snake->player->head;
	int fruitx = snake->player->head->x;
	int fruity = snake->player->head->y;
	for (int i = 0; i < 5; i++)
	{
		if(snake->fruit[i].eated)
		{
			do{
				fruitx =  rand() % (x_max - 1 ) + 1;
        		fruity =  rand() % (y_max - 1 ) + 1;
			}
			while (on_top_of_snake(snake, snake->player->head, fruitx, fruity));
			snake->fruit[i].x = fruitx;
			snake->fruit[i].y = fruity;
			snake->fruit[i].eated = false;
			break;
		}

	}
}
bool	wall_colision(float px, float py, t_snake_game *snake, int flag)
{
	int	x = px / BLOCK;
	int	y = py / BLOCK;
	if (snake->map[y][x] == '1')
	{
		return (true);
	}
	return (false);
}

bool own_snake_colision (t_snake_node *h, int current_x, int current_y)
{
	t_snake_node *head = h;
	while (head)
	{
		if (head->x == current_x && head->y == current_y)
			return(true);
		head = head->next;
	}
	return false;
}

void move_body(t_snake_game *snake, t_snake_node **head, int direction)
{
    t_snake_node *tmp = *head;
    int old_x = tmp->x;
    int old_y = tmp->y;

    int tmp_x;
    int tmp_y;

	int tail_x = old_x;
	int tail_y = old_y;

	int next_x = old_x;
	int next_y = old_y;
    if (direction == UP)
		next_y -= BLOCK;
    else if (direction == DOWN)
        next_y+= BLOCK;
    else if (direction == LEFT)
        next_x-= BLOCK;
    else if (direction == RIGHT)
		next_x+= BLOCK;
    if (wall_colision(next_x ,next_y,snake, 0) || own_snake_colision(snake->player->head, next_x,next_y))
		wall_c();
	tmp->x = next_x;
    tmp->y = next_y;
	tmp = tmp->next;
	while(tmp)
    {
		tmp_x = tmp->x; 
        tmp_y = tmp->y;
		
        tmp->x = old_x;
        tmp->y = old_y;
	
		old_x = tmp_x;
		old_y = tmp_y;
		if (!tmp->next)
		{
			tail_x = tmp_x;
			tail_y = tmp_y;
		}
		tmp = tmp->next;
    }
	if (check_fruit_pos(snake))
	{
		snake->points++;
		update_fruit_pos(snake);
		new_snake_tail(snake, tail_x,tail_y);
	}
	else
		put_full_square(snake, tail_x , tail_y, 0x0);
}

void put_snake_in_map(t_snake_game *snake)
{
    t_snake_node *a = snake->player->head;

	while(a)
	{
        put_full_square(snake, a->x, a->y, 0xFFF);
		a = a->next;
    }
}

void move_snake(t_snake_game *snake)
{

    if (snake->up)
        move_body(snake,&snake->player->head, UP);
    if (snake->down)
       move_body(snake,&snake->player->head, DOWN);
    if (snake->left)
        move_body(snake,&snake->player->head, LEFT);
    if (snake->right)
        move_body(snake,&snake->player->head, RIGHT);
	t_snake_node *a = snake->player->head;
	while(a && !snake->stop)
	{
		put_full_square(snake, a->x, a->y, 0xFFF);
		a = a->next;
	}
    
}

int	aft_lstsize(t_snake_node *lst)
{
	t_snake_node	*temp;
	int		count;

	count = 0;
	temp = lst;
	if (!lst)
		return (0);
	while (temp != NULL)
	{
		temp = temp->next;
		count++;
	}
	return (count);
}
void fill_grid_with_fruits(t_snake_game *snake)
{
	for (int i = 0; i < 5; i++)
		put_filled_circle(snake, snake->fruit[i].x*BLOCK+15, snake->fruit[i].y*BLOCK+15, 0xFF0000);
} 

void game_movement(t_snake_game *snake, double dt)
{
	
	snake->accumulator += dt;
    while (snake->accumulator >= snake->move_interval) {
        move_snake(snake);
        snake->accumulator -= snake->move_interval;
	}
    mlx_put_image_to_window(snake->con, snake->win, snake->img[1].img, 0,0); // preenche a window
}

int start_game(t_snake_game *snake)
{
	static int i = 0;
	long long currentTime = current_time_ns();
    long long elapsed = currentTime - snake->previoustime;
	fill_grid(snake);
	fill_grid_with_fruits(snake);
	if (i == 0)
	{
		put_snake_in_map(snake); 
		i++;
	}
	snake->previoustime = currentTime;
    snake->lag += elapsed;
	while (snake->lag >= FRAME_DURATION_NS)
	{
        game_movement(snake, FRAME_DURATION_NS / 1e9); // pass time in seconds
        snake->lag -= FRAME_DURATION_NS;
    }

    return 0;
}



int key_press( int key, t_snake_game *snake)
{
    snake->up = false;
    snake->down = false;
    snake->left = false;
    snake->right = false;
	if (key == 119)
	{
		if (snake->dir !=1)
		{
        	snake->up = true;
			snake->dir = 0;

		}
		else
		{
			snake->down = true;
		}
	}
    if (key == 115)
	{
		if (snake->dir !=0)
		{
        	snake->down = true;
			snake->dir = 1;

		}
		else
			snake->up = true;
	}
    if (key == 97)
	{
		if (snake->dir != 3)
		{
        	snake->left = true;
			snake->dir = 2;

		}
		else
		{
			snake->right = true;

		}
	}
    if (key == 100)
	{
		if (snake->dir !=2)
        {
			snake->right = true;
			snake->dir = 3;

		}
		else
		{
			snake->left = true;

		}
	}
    if (key == 113 || key == 65307)
        exit(0);
    return 0;
}

int key_release( int key, t_snake_game *snake)
{ // funcao cagativa.
	
    //if (key == 119 )
    //    snake->up = false;
    //if (key == 115)
    //    snake->down = false;
    //if (key == 97)
    //    snake->left = false;
    //if (key == 100)
    //    snake->right = false;
    return 0;
}
