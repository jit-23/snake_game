#include "../libs/snake.h"
/* FUNCTIONS */

void init_fruit(t_snake_game *snake)
{
    int x_max = ft_strlen(snake->map[0]);
    int y_max = 0;
    while(snake->map[y_max])
        y_max++;
    x_max--;
    y_max--;
    
    for (int i = 0; i < 5; i++)
    {
        snake->fruit[i].x =  rand() % (x_max - 1 ) + 1;
        snake->fruit[i].y =  rand() % (y_max - 1 ) + 1;
        snake->fruit[i].eated = false;
    }
}

int get_map_heigh(char**map)
{   
    int height = 0;
    while(map[height])
        height++;
    return height;
}

int get_map_width(char**map)
{   
    return (ft_strlen(map[0]));
}


void init_mlx_win(t_snake_game *game)
{
	game->dir = 3;
	game->px = 5 *  BLOCK;// apaga
    game->py = 7 * BLOCK;// apaga
    game->right = false; // start point
    game->left = false;
    game->up = false;
    game->down = false;
    game->map = get_map();
    game->con = mlx_init();
    game->win = mlx_new_window(game->con, get_map_width(game->map)*BLOCK + 1, get_map_heigh(game->map)*BLOCK + 1, "game game");
    game->img = (t_img *)malloc(sizeof(t_img) * 2);  // 0 window info, 1 display frames
	
    game->img[0].img = mlx_new_image(game->con, WIDTH, HEIGH);
	game->img[0].addr = mlx_get_data_addr(game->img[0].img, &game->img[0].bpp, &game->img[0].size_line, &game->img[0].endian);
	
    mlx_put_image_to_window(game->con, game->win, game->img[0].img, 0, 0); // tira isto quando conseguires preencher tudo
    game->img[1].img = mlx_new_image(game->con, WIDTH, HEIGH); // imagem da qual vou preencher com os frames
	game->img[1].addr = mlx_get_data_addr(game->img[1].img, &game->img[1].bpp, &game->img[1].size_line, &game->img[1].endian);
    
	game->player = (t_snake *)malloc(sizeof(t_snake));
	if (!game->player)
		perror("error on player creation\n");
	memset((void *)game->player, 0, sizeof(game->player));
	
    init_fruit(game);
	init_snake(game->player);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	//mlx_hook(game->win, 3, 1L << 1, key_release, game);
    mlx_loop_hook(game->con, start_game, game);
	mlx_loop(game->con);
}

/* MAIN.C */


int main(/* int ac, char  *av[] */)
{
    srand(time(NULL));
    t_snake_game *game = (t_snake_game*)malloc(sizeof(t_snake_game));

    init_mlx_win(game);
    
    return 0;
}
