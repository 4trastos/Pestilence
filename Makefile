NAME = Pestilence
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3
RM = rm -f

SRC = src/main.c src/infection.c src/protection.c
OBTS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBTS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
