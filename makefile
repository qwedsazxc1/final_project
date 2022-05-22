objects = final_project.o lib.o error.o stack.o list.o queue.o avl_tree.o student.o vector.o
CC = gcc
exe = main

all: $(exe)

$(exe): $(objects)
	$(CC) -g $(objects) -o $(exe) 

%.o:%.c
	$(CC) -g $^ -c -O3 -Wall -o $@

clear:
	rm $(exe) $(objects)

clean:
	rm $(exe) $(objects)