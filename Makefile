NAME = projetX

CC = cc
CFLAGS =  -Wall -Wextra -Werror

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

clean:
	rm -f $(OBJ) $(NAME)

re: clean all
