NAME = a.out

$(NAME): all

all:
	gcc -g main.c map.c -lncurses

fclean:
	rm -rf $(NAME)

re: fclean all