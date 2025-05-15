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

void *fill_grid(t_snake_game *snake)
{
   	char	**map;
	int		color1;
	int		color2;
	int		x;
	int		y;

	x = -1;
	y = 0;
	map = snake->map;
	color1 = 0x00FF0F;
	color2 = 0x0000FF;
	while (map[y])
	{
		x = -1;
		while (map[y][++x])
		if (map[y][x] == '0')
		{
			put_square(snake, x * BLOCK, y * BLOCK, color2);

		}
		y++;
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
