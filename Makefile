
CC := cc

NAME	:= cub3d

CFLAGS	:= -Wextra -Wall -Werror

SRCS	:= main.c entry_point

LIBFT := lib/libft/libft.a

OBJS	:= ${SRCS:.c=.o}

all: $(NAME)

library : 
	@make -C ./lib/libft

$(NAME): $(OBJS) | library
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)


push:
	git add .
	git commit -m "Lazy_push"
	git push

%.o: %.c $(HEADERS) | lib
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C ./lib/libft
	rm -rf $(OBJS)

fclean: clean
	make fclean -C ./lib/libft
	rm -rf $(NAME)

re: fclean all

.PHONY: all, lib, clean, fclean, re
