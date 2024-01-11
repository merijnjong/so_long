sourcefiles = 	so_long.c

objects =		$(sourcefiles:.c=.o)

NAME =			so_long.a

all:			$(NAME)

$(NAME):		$(objects)
	@ar rcs so_long.a $(objects)

%.o: %.c
	cc -Wall -Wextra -Werror -c $< -o $@

clean:
	@rm -f $(objects)

fclean:
	@rm -f $(objects) $(NAME)

re: 			fclean all