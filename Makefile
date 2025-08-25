NAME = projetX

CC = cc
CFLAGS = -nostdlib -Wall -Wextra -Werror -Ilibpx

SRC = $(wildcard ./**/*.c)
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

clean:
	rm -f $(OBJ) $(NAME)

re: clean all
