#include "../libs/snake.h"

void wall_c()
{
	usleep(1500000);
	exit(1);
}

bool check_fruit_pos(t_snake_game* snake)
{
	int x = snake->px /BLOCK;
	int y = snake->py/BLOCK;
	for (int i = 0; i < 5; i++)
	{
		if (x == snake->fruit[i].x &&  y == snake->fruit[i].y)
			return true;
	}
	return false;
}

void new_snake_tail(t_snake_game *snake, int xx, int yy)
{
	t_snake_node *tmp = (t_snake_node *)malloc(sizeof(t_snake_node));
	t_snake_node *last = snake->player->head;
	while(last)
	{
		if (!last->next)
			break;
		last = last->next;	
	}
	last->next = tmp;
	last->next->x = xx;
	last->next->y = yy;
	last->next->next = NULL;
}

/* HAHAAHAHAH esta merda esta mesmo mal xDDDDDDDD , 4:35 am, vou mas e dormir*/ // a ideia esta aqui, mas fds xD
void move_body(t_snake_game *snake, t_snake_node **head, int direction)
{
    t_snake_node *tmp = *head;
    int old_x = tmp->x;
    int old_y = tmp->y;

	int flag = 0;
    int tmp_x;
    int tmp_y;

	int tail_x = old_x;
	int tail_y = old_y;
    

	colision(tmp->x ,tmp->y-BLOCK,snake, 0)? (void)0 : wall_c();
	colision(tmp->x-BLOCK ,tmp->y,snake, 0)? (void)0 : wall_c();
	colision(tmp->x ,tmp->y+BLOCK,snake, 0)? (void)0 : wall_c();
	colision(tmp->x+BLOCK ,tmp->y,snake, 0)? (void)0 : wall_c();

	check_fruit_pos(snake)?  (void) 0: flag++;

    if (direction == UP)
		tmp->y -= BLOCK;
    else if (direction == DOWN)
        tmp->y+= BLOCK;
    else if (direction == LEFT)
        tmp->x-= BLOCK;
    else if (direction == RIGHT)
		tmp->x+= BLOCK;
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
	if (flag)
		new_snake_tail(snake, tail_x,tail_y );
	put_full_square(snake, tail_x , tail_y, 0x0);
}

/* put_snake_body_in_screen */

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

    if (snake->up  /*&& !colision( snake->px,  snake->py - BLOCK, snake, 1) */)
        move_body(snake,&snake->player->head, UP);//snake->py -= BLOCK;
    if (snake->down /* && !colision( snake->px,  snake->py + BLOCK, snake, 1) */)
       move_body(snake,&snake->player->head, DOWN); //snake->py += BLOCK;
    if (snake->left /* && !colision( snake->px - BLOCK,  snake->py, snake, 1) */)
        move_body(snake,&snake->player->head, LEFT);//snake->px -= BLOCK;
    if (snake->right /* && !colision( snake->px + BLOCK,  snake->py , snake, 1) */)
        move_body(snake,&snake->player->head, RIGHT);//snake->px += BLOCK;
	t_snake_node *a = snake->player->head;
	while(a)
	{
		put_full_square(snake, a->x/* /BLOCK */, a->y/* /BLOCK */, 0xFFF);
		//printf("-------=\n");
		//printf("x - %d\n", a->x);
		//printf("y - %d\n", a->y);
		a = a->next;
	}	
    
}

void fill_grid_with_fruits(t_snake_game *snake)
{
	for (int i = 0; i < 5; i++)
		put_full_square(snake, snake->fruit[i].x, snake->fruit[i].y, 0xFF);
} 

int start_game(t_snake_game *snake)
{
	static int i = 0;

    fill_grid(snake);
	fill_grid_with_fruits(snake);
	if (i == 0)
		put_snake_in_map(snake); i++;
    
	move_snake(snake);

    //put_square(snake,snake->px , snake->py, 0xFFFF);
    mlx_put_image_to_window(snake->con, snake->win, snake->img[1].img, 0,0); // preenche a window
   	usleep(136000);
    return 0;
}

bool	colision(float px, float py, t_snake_game *snake, int flag)
{
	int	x;
	int	y;
	x = 0;
	y = 0;
	if (/* flag ==  */1) // para mini mapa
	{
		x = (px / BLOCK);
		y = (py / BLOCK);
		if (snake->map[y][x] == '1')
			return (true);
		return (false);
	}
	/* else
	{
		x = (px / BLOCK);
		y = (py / BLOCK);
		if (snake->map[y][x] == '1')
			return (true);
		return (false);
	} */
}

int key_press( int key, t_snake_game *snake)
{
    //t_snake_game * snake = (t_snake_game*)snake_;
    snake->up = false;
    snake->down = false;
    snake->left = false;
    snake->right = false;
	if (snake->dir == 0)
		printf("up\n");
    else if (snake->dir == 1)
		printf("down\n");
	else if (snake->dir == 2)
		printf("left\n");
	else if (snake->dir == 3)
		printf("RIGHT\n");
	if (key == 119 /* && snake->dir != 1 */)
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
    if (key == 115 /* && snake->dir != 0 */)
	{
		if (snake->dir !=0)
		{
        	snake->down = true;
			snake->dir = 1;

		}
		else
			snake->up = true;
	}
    if (key == 97 /* && snake->dir != 3 */)
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
    if (key == 100/* && snake->dir != 2 */)
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
    printf("-------\n"/*,  snake->up */);
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
