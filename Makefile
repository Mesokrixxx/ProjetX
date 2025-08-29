NAME = projetX

CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lSDL2 -lGLEW -lGL

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME) $(LDFLAGS)

clean:
	rm -f $(OBJ) $(NAME)

re: clean all
