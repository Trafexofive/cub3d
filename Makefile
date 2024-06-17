
CC := cc

NAME := cub3d

CFLAGS := -Wextra -Wall -Werror

GNL := lib/get_next_line/get_next_line.c lib/get_next_line/get_next_line_utils.c

DRAW := drawing/tool_kit.c drawing/draw.c

UTILS := utils/init.c

SRCS := main.c raycasting/raycasting.c $(GNL) $(DRAW) $(UTILS)

LIBFT := lib/libft/libft.a

OBJS := ${SRCS:.c=.o}

UNAME_S := $(shell uname -s)

all: library $(NAME)

library:
	@make -C ./lib/libft

ifeq ($(UNAME_S), Linux)
    $(NAME): $(OBJS) $(LIBFT)
		$(CC) $(OBJS) $(LIBFT) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
else ifeq ($(UNAME_S), Darwin)
    $(NAME): $(OBJS) $(LIBFT)
		$(CC) $(OBJS) $(LIBFT) -lmlx -framework OpenGL -framework AppKit -o $(NAME)
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

