NAME = ProjetX

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lSDL2

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

BIN = bin

ifeq ($(OS), Windows_NT)
	EXEC = $(BIN)/$(NAME).exe
	LDFLAGS += -lglew32 -lopengl32
else
	EXEC = $(BIN)/$(NAME)
	LDFLAGS += -lGLEW -lGL
endif

all: $(BIN) $(NAME)

$(BIN):
	mkdir -p $(BIN)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(EXEC) $(LDFLAGS)

clean:
	rm -rf $(OBJ) $(BIN)

re: clean all

run: all
	./$(EXEC)

ren: clean run

.PHONY: all clean re run ren
