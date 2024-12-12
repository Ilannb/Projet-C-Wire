CC = gcc
CFLAGS = -Wall -std=c11
LDFLAGS = 
SRC = main.c avl.c
OBJ = $(SRC:.c=.o)
EXEC = avl_tree

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

test:
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC)

.PHONY: all clean test
