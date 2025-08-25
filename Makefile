NAME = projetX

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

ifeq ($(OS),Windows_NT)
	EXEC = $(NAME).exe
else
	EXEC = $(NAME)
endif

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(EXEC)

clean:
	rm -f $(OBJ) $(EXEC)

re: clean all
