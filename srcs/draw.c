#include "../libs/snake.h"

void	put_pixel(t_snake_game *snake, int x, int y, int color)

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


void	put_full_square(t_snake_game *snake, int x, int y, int color)
{
	int	size;
	int	i;


	i = -1;
	int j = -1;
	size = BLOCK;
	
	while(++i < size)
	{
		j = -1;
		while(++j < size)
			put_pixel(snake, x+i, y+j, color);
	}
}

void	put_square(t_snake_game *snake, int x, int y, int color)
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

	map = malloc(sizeof(char *) * 22);
	map[0] = "11111111111111111111111";
	map[1] = "10000000000000000000001";
	map[2] = "10000000000000000000001";
	map[3] = "10000000000000000000001";
	map[4] = "10000000000000000000001";
	map[5] = "10000000000000000000001";
	map[6] = "10000000000000000000001";
	map[7] = "10000000000000000000001";
	map[8] = "10000000000000000000001";
	map[9] = "10000000000000000000001";
	map[10] = "10000000000000000000001";
	map[11] = "10000000000000000000001";
	map[12] = "10000000000000000000001";
	map[13] = "10000000000000000000001";
	map[14] = "10000000000000000000001";
	map[15] = "10000000000000000D00001";
	map[16] = "10000000000000000000001";
	map[17] = "11111111111111111111111";
	map[18] = NULL;
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

void fill_grid(t_snake_game *snake)
{
   	char	**map;
	int		color1;
	int		color2;
	int		x;
	int		y;

	x = -1;
	y = 0;
	map = snake->map;
	if (!map)
	{
		printf("error on map\n");
		exit(1);

	}
	color1 = 0x301934/* 0x00FF0F */;
	color2 = 	/* 0x301934 */0x0000FF;
	/* while (map[y])
	{
		x = -1;
		while (map[y][++x])
		if (map[y][x] == '0')
		{
			put_full_square(snake, x * BLOCK, y * BLOCK, color2);

		}
		y++;
	} */
    x = -1;
    y = -1;
    while (map[++y])
	{
		x = -1;
		while (map[y][++x])
			if (map[y][x] == '1')
				put_full_square(snake, x * BLOCK, y * BLOCK, color1);
    }
	double points_posx = (double)x - 2.6;
	double points_posy = (double)y - 0.4;
	mlx_string_put(snake->con, snake->win, points_posx * BLOCK , points_posy * BLOCK,0xCBC3E3 , "Points: ");
	mlx_string_put(snake->con, snake->win, points_posx * BLOCK + 50 , points_posy * BLOCK ,0xCBC3E3 , ft_itoa(snake->points));

}


void	put_filled_circle(t_snake_game *snake, int center_x, int center_y, int color)
{
	int radius = 10;
	int dx, dy;


	for (int y = -radius; y <= radius; y++)
	{
		for (int x = -radius; x <= radius; x++)
		{
			dx = center_x + x;
			dy = center_y + y;
			if (x * x + y * y <= radius * radius)
			{
				put_pixel(snake,  dx , dy , color);
			}
		}
	}
	radius = 12;
	for (int y = -radius; y <= radius; y++)
	{
		for (int  x= -radius; x <= radius; x++)
		{
			dx = center_x + x;
			dy = center_y + y;
			if (y < 0 && (x < 2 && x > -2))
			{
				put_pixel(snake,  dx , dy , 0x008e02);
			}
		}
	}
	
}

void	put_circle(t_snake_game *snake, int x, int y, int color)
{
	double	theta;

	for (int i = 0; i < 5; i++)
	{
		theta = 0;
		while (theta <= 2 * PI)
		{
			x = snake->fruit[i].x + 20 * cos(theta);
			y = snake->fruit[i].y + 20 * sin(theta);
			put_pixel(snake, x *BLOCK, y *BLOCK, color);
			theta += 0.01;
		}
	}
	
}