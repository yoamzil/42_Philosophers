CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread #-fsanitize=thread -g
NAME = philo
SRCS = philo.c init.c tools.c death.c
OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $^

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
