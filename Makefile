NAME:= as_game
CFLAGS:= -g #-Wall -Werror -Wextra

#HEADER = includes/libs/cub.h
GREEN:= \033[0;32m
RED:=\033[0;31m 
BLUE=\033[0;34m
default_colour=\033[0m

SRC_FILES:=  main.c\

MAKE:= make -j -C
#LIBFT_DIR:= libs/libft
#LIBFT:= libs/libft/libft.a
#
MLX_DIR:= libs/mlx/
MLX:= -L libs/mlx -lmlx -Ilmlx -lXext -lX11 -lm #-lm -lXext -lX11#libs/mlx/libmlx_Linux.a
#-L mlx -lmlx -Ilmlx -lXext -lX11 -lm
OBJ_FILES:= $(patsubst %.c, %.o, $(SRC_FILES))

SRC_PATH:= srcs/
OBJ_PATH:= obj/

SRC = $(addprefix $(SRC_PATH), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_FILES))

all: ${NAME}

#${COMP_LIB}:
#		echo "${RED}DONE${default_colour}"
#		${MAKE} ${LIBFT_DIR}

${COMP_MLX}:
		echo "${RED}DONE${default_colour}"
		${MAKE} ${MLX_DIR}

$(OBJ_PATH)%.o : $(SRC_PATH)%.c
		@mkdir -p ${OBJ_PATH}
		cc   ${CFLAGS}  -c $< -o $@

${NAME}:  ${OBJ}
#		${MAKE} ${LIBFT_DIR}
		${MAKE} ${MLX_DIR}
		cc  -I. ${CFLAGS} ${OBJ}  ${MLX} -o ${NAME}
		@echo "${GREEN}executable file: ./${NAME}${default_colour}\n"

clean:
		#${MAKE} ${MLX_DIR} clean
		@rm -fr ${OBJ_PATH}
		@echo "${RED}object files and directory deleted:${default_colour}"
#${MAKE} ${LIBFT_DIR} clean

#valgrind: ${NAME}
#			valgrind  --leak-check=full --show-leak-kinds=all ./cub

fclean: clean
#		${MAKE} ${MLX_DIR} fclean
		@rm -f ${NAME}
		@echo "${RED}executable deleted:$(default_colour)"
		@echo "${RED}deleted all:$(default_colour)\n"
#${MAKE} ${LIBFT_DIR} fclean

re : fclean all

.PHONY: all re clean fclean normi
.SIELNT:
