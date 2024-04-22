
CC := cc

NAME	:= push_swap

CFLAGS	:= -Wextra -Wall -Werror

SRCS	:= main.c

LIBFT := libft/libft.a

OBJS	:= ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

lib : 
	@make -C ./libft && make -C ./printf

push:
	git add .
	git commit -m "Lazy_push"
	git push

%.o: %.c $(HEADERS) | lib
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C ./libft
	make clean -C ./printf
	rm -rf $(OBJS)

fclean: clean
	make fclean -C ./libft
	make fclean -C ./printf
	rm -rf $(NAME)

re: fclean all

.PHONY: all, lib, clean, fclean, re
