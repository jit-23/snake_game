#include "../libs/snake.h"


void move_snake(t_snake_game *snake)
{
    if (snake->up && !colision( snake->px,  snake->py - BLOCK, snake, 1) )
    {
        snake->py -= BLOCK;
    }
    if (snake->down && !colision( snake->px,  snake->py + BLOCK, snake, 1))
        snake->py += BLOCK;
    if (snake->left && !colision( snake->px - BLOCK,  snake->py, snake, 1))
        snake->px -= BLOCK;
    if (snake->right && !colision( snake->px + BLOCK,  snake->py , snake, 1))
        snake->px += BLOCK;
    put_square(snake,snake->px,snake->py, 0xFF00FF);
}

int game(t_snake_game *snake)
{
    fill_grid(snake);
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
    if (key == 119)
        snake->up = true;
    if (key == 115)
        snake->down = true;
    if (key == 97)
        snake->left = true;
    if (key == 100)
        snake->right = true;
    if (key == 113 || key == 65307)
        exit(0);
    printf("%d\n", snake->up);
    return 0;
}

int key_release( int key, t_snake_game *snake)
{
	
    if (key == 119)
        snake->up = false;
    if (key == 115)
        snake->down = false;
    if (key == 97)
        snake->left = false;
    if (key == 100)
        snake->right = false;
    return 0;
}

