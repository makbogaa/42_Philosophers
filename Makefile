NAME = philo
CFLAGS = -Wall -Wextra -Werror
SRC = main.c check.c initialization.c utils.c monitor.c routine.c
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re