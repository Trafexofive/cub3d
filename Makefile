
CC := cc

NAME	:= cub3d

CFLAGS	:= -Wextra -Wall -Werror

GNL := lib/get_next_line/get_next_line.c lib/get_next_line/get_next_line_utils.c

DRAW := drawing/tool_kit.c drawing/draw.c	

UTILS := utils/init.c

SRCS := main.c raycasting/raycasting.c $(GNL) $(DRAW) $(UTILS) 

LIBFT := lib/libft/libft.a

OBJS := ${SRCS:.c=.o}

all: $(NAME)

library : 
	@make -C ./lib/libft

$(NAME): $(OBJS) | library
	$(CC) $(OBJS) $(LIBFT) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
# $(NAME): $(OBJS) | library
# 	$(CC) $(OBJS) $(LIBFT) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

push:
	git add .
	git commit -m "Lazy_push"
	git push

%.o: %.c $(HEADERS) | library
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@
# %.o: %.c $(HEADERS) | lib
# 	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C ./lib/libft
	rm -rf $(OBJS)
	rm -rf ${GNL:.c=.o}

fclean: clean
	make fclean -C ./lib/libft
	rm -rf $(NAME)
	rm -rf ${GNL:.c=.o}

re: fclean all

.PHONY: all, lib, clean, fclean, re
