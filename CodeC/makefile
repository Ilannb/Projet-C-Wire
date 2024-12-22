CC = gcc
CFLAGS = -Wall -std=c11
SRC = main.c Avl.c
OBJ = $(SRC:.c=.o)
EXEC = avl_tree

.SILENT: 
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)
	rm -f $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

test:
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC)

.PHONY: all clean test
