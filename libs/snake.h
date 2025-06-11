#ifndef SNAKE
#define SNAKE

#include <stdio.h>
#include "../libs/mlx/mlx.h"
#include "../libs/libft/libft.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/* MACROS */


#define WIDTH 800
#define HEIGH 800
#define BLOCK 30
/* STRUCTS */

typedef struct s_snake_node t_snake_node;


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

enum e_direction
{
	UP, //0
	DOWN, //1
	LEFT, //2
	RIGHT, //3
};

typedef struct s_food
{
	int x;
	int y;
} t_food;

typedef struct s_snake_node
{
	int x;
	int y;
	t_snake_node *next;

}t_snake_node;


typedef struct s_snake
{
	int length;
	int diretion;
	t_snake_node *head;
}t_snake;


typedef struct s_snake_game
{
    void	*win;
    void 	*con;
    char	**map;
	int		dir;
    bool	up;
    bool 	down;
    bool 	left;
    bool	right;
    t_img	*img;
	t_snake	*player;


    int px;
    int py;

}t_snake_game;

/* HEADERS */


void *fill_grid(t_snake_game *snake);
int start_game(t_snake_game *snake);
void init_mlx_win(t_snake_game *snake);
void	put_square(t_snake_game *snake, int x, int y, int color);
bool	colision(float px, float py, t_snake_game *snake, int flag);
char	**get_map(void);
void put_snake_in_map(t_snake_game *snake);

int key_release( int key, t_snake_game *snake);
int key_press( int key, t_snake_game *snake);
t_snake_node	*ft_lstlast(t_snake_node *head);
void create_snake(t_snake *snake_body);

t_snake_node *init_snake(t_snake *snake);
void new_snake_node(t_snake_node **last, int x, int y);
void move_body(t_snake_game *snake,t_snake_node **head, int direction);
void	put_full_square(t_snake_game *snake, int x, int y, int color);


#endif