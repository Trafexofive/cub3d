
CC := cc

NAME := cub3d

CFLAGS := -Wextra -Wall -Werror

GNL := lib/get_next_line/get_next_line.c lib/get_next_line/get_next_line_utils.c

DRAW := drawing/tool_kit.c drawing/draw.c 

UTILS := utils/init.c

GUI := gui/gui_engine.c gui/navigation.c

SRCS := main.c raycasting/raycasting.c $(GNL) $(DRAW) $(UTILS) $(GUI)

LIBFT := lib/libft/libft.a

OBJS := ${SRCS:.c=.o}

OS := $(shell uname -s)

all: library $(NAME)

library:
	@make -C ./lib/libft

ifeq ($(OS), Linux)
    $(NAME): $(OBJS) $(LIBFT)
		$(CC) $(OBJS) $(LIBFT) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
else ifeq ($(OS), Darwin)
    $(NAME): $(OBJS) $(LIBFT)
		$(CC) -D__OSX__ $(OBJS) $(LIBFT) -lmlx -framework OpenGL -framework AppKit -o $(NAME)
endif

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	make clean -C ./lib/libft
	rm -rf $(OBJS)

fclean: clean
	make fclean -C ./lib/libft
	rm -rf $(NAME)

re: fclean all

push:
	git add .
	git commit -m "Lazy_push"
	git push

.PHONY: all library clean fclean re push

