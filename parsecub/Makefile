SRCS = ./parse/parse.c ./parse/utils.c ./parse/map_check.c ./raycasting/raycaster.c \
		./raycasting/mlx_functions.c

OBJS = $(SRCS:.c=.o)

CC = cc

OFLAGS =  -Wall -Wextra -Werror -g -lmlx -framework OpenGL -framework AppKit
CFLAGS = -Wall -Wextra -Werror -c

RM = rm -f

NAME = cub3D

HEADERS = cube.h

LIB = make -C ./libft

LIB_PATH = ./libft

LIB_ARC = ./libft/libft.a

all : lib $(NAME)

lib :
	$(LIB)

$(NAME) : $(OBJS)
	$(CC) $(OFLAGS) -o $(NAME) $(OBJS) $(LIB_ARC)

%.o: %.c $(HEADERS)
	$(CC) $(CFlAGS) -c $< -o $@

clean:
	make -C ./libft clean
	$(RM) $(OBJS)

fclean : clean
	make -C ./libft fclean
	$(RM) $(NAME)

re : fclean all

.PHONY: clean lib
