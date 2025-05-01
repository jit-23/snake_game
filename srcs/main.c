#include <stdio.h>
#include "../libs/mlx/mlx.h"
#include <stdbool.h>

/* MACROS */

#define WIDTH 800
#define HEIGH 400
#define BLOCK 30
/* STRUCTS */


typedef struct s_img
{
	void	*img;
	char	*addr;
	int		x;
	int		y;
	int		bpp;
	int		size_line;
	int		endian;

}			t_img;


typedef struct s_snake
{
    void *win;
    void *con;

    char **map;
    bool up;
    bool down;
    bool left;
    bool right;
    t_img *img;

    int px;
    int py;

}t_snake;

/* HEADERS */


void *fill_grid(t_snake *snake);
int game(t_snake *snake);
void init_mlx_win(t_snake *snake);
void	put_square(t_snake *snake, int x, int y, int color);
bool	colision(float px, float py, t_snake *snake, int flag);


/* FUNCTIONS */



void	put_pixel(t_snake *snake, int x, int y, int color)

{
	int	index;

	index = 0;
	if (x >= WIDTH || y >= HEIGH || x < 0 || y < 0)
		return ; 
	index = y * snake->img[1].size_line + x * snake->img[1].bpp / 8;
	snake->img[1].addr[index] = color & 0xFF;
	snake->img[1].addr[index + 1] = (color >> 8) & 0xFF;
	snake->img[1].addr[index + 2] = (color >> 16) & 0xFF;
}

void	put_square(t_snake *snake, int x, int y, int color)
{
	int	size;
	int	i;


	i = -1;
	size = BLOCK;
	while (++i < size)
		put_pixel(snake, x + i, y, color);
	i = -1;
	while (++i < size)
		put_pixel(snake, x, y + i, color);
	i = -1;
	while (++i < size)
		put_pixel(snake, x + i, y + size, color);
	i = -1;
	while (++i < size)
		put_pixel(snake, x + size, y + i, color);
}


char	**get_map(void)
{
	char	**map;

	map = malloc(sizeof(char *) * 11);
	map[0] = "11111111111111111111111";
	map[1] = "10000000000000000000001";
	map[2] = "10000000000000000000001";
	map[3] = "10000000000000000000001";
	map[4] = "10000000000000000000001";
	map[5] = "10000000000000000000001";
	map[6] = "10000000000000000000001";
	map[7] = "10000000000000000D00001";
	map[8] = "10000000000000000000001";
	map[9] = "11111111111111111111111";
	map[10] = NULL;
	return (map);
}

// char **get_map(){
//     //char map[10][10];
    // char **map = (char *)malloc(11 * sizeof(char));
    //map[j][i]
    // for (int i = 0; i < 10; i++)
    // {
        // for (int j = 0; j < 10; j++)
        // {
            // if (i == 0 || i == 10 || j == 0 || j == 10)
                // map[j][i] = '1';
            // else
                // map[j][i] = '0';
        // }
    // }
    // map[10] = NULL;
    // return map; 
    // 
// }

void *fill_grid(t_snake *snake)
{
   	char	**map;
	int		color1;
	int		color2;
	int		x;
	int		y;

	x = -1;
	y = -1;
	map = snake->map;
	color1 = 0x00FF0F;
	color2 = 0x0000FF;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
			if (map[y][x] == '0')
				put_square(snake, x * BLOCK, y * BLOCK, color2);
    //        else
	//			put_square(snake, x * BLOCK, y * BLOCK, color2);

	}
    x = -1;
    y = -1;
    while (map[++y])
	{
		x = -1;
		while (map[y][++x])
			if (map[y][x] == '1')
				put_square(snake, x * BLOCK, y * BLOCK, color1);
    }
}



void move_snake(t_snake *snake)
{
    if (snake->up && !colision( snake->px,  snake->py - BLOCK, snake, 1) )
        snake->py -= BLOCK;
    if (snake->down && !colision( snake->px,  snake->py + BLOCK, snake, 1))
        snake->py += BLOCK;
    if (snake->left && !colision( snake->px - BLOCK,  snake->py, snake, 1))
        snake->px -= BLOCK;
    if (snake->right && !colision( snake->px + BLOCK,  snake->py , snake, 1))
        snake->px += BLOCK;
    put_square(snake,snake->px,snake->py, 0xFF00FF);
}

int game(t_snake *snake)
{
    move_snake(snake);
    //put_square(snake,snake->px , snake->py, 0xFFFF);
    mlx_put_image_to_window(snake->con, snake->win, snake->img[1].img, 0,0); // preenche a window
   //usleep(10000);
   sleep(1);
   //printf("asd\n");
    return 0;
}

bool	colision(float px, float py, t_snake *snake, int flag)
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

int key_press( int key, t_snake *snake)
{
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
    return 0;
}

int key_release( int key, t_snake *snake)
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



void init_mlx_win(t_snake *snake)
{
    snake->px = 5*BLOCK;
    snake->py = 7*BLOCK;
    snake->con = mlx_init();
    snake->win = mlx_new_window(snake->con, WIDTH, HEIGH, "snake game");
    snake->img = (t_img *)malloc(sizeof(t_img) * 2);  // 0 window info, 1 display frames

    snake->img[0].img = mlx_new_image(snake->con, WIDTH, HEIGH);
	snake->img[0].addr = mlx_get_data_addr(snake->img[0].img, &snake->img[0].bpp, &snake->img[0].size_line, &snake->img[0].endian);

    mlx_put_image_to_window(snake->con, snake->win, snake->img[0].img, 0, 0); // tira isto quando conseguires preencher tudo
    snake->img[1].img = mlx_new_image(snake->con, WIDTH, HEIGH); // imagem da qual vou preencher com os frames
	snake->img[1].addr = mlx_get_data_addr(snake->img[1].img, &snake->img[1].bpp, &snake->img[1].size_line, &snake->img[1].endian);
    
    snake->map = get_map();
    fill_grid(snake);

   mlx_hook(snake->win, 2, 1L << 0, key_press, &snake);
	mlx_hook(snake->win, 3, 1L << 1, key_release, &snake);
    mlx_loop_hook(snake->con, &game, snake);
    mlx_loop(snake->con);
}

/* MAIN.C */

int main(/* int ac, char  *av[] */)
{

    t_snake snake;
    init_mlx_win(&snake);
    
    return 0;
}
