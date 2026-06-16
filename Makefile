NAME = Pestilence
CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f

SRC = src/main.c src/protection.c src/infection.c
OBJT = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJT)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re