objects = final_project.o lib.o error.o stack.o list.o queue.o avl_tree.o
CC = gcc
exe = main

all: $(objects)
	$(CC) -g $(objects) -o $(exe) 

%.o:%.c
	$(CC) -g $^ -c -O3 -Wall -o $@

clear:
	rm $(exe) $(objects)

clean:
	rm $(exe) $(objects)