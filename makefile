objects = final_project.o lib.o error.o stack.o list.o queue.o avl_tree.o student.o vector.o
CC = gcc
exe = main
add = add

all: $(exe) $(add)

$(exe): $(objects)
	$(CC) -g $(objects) -o $(exe) 

$(add): add.c
	$(CC) -g $^ -O3 -o $(add)

%.o:%.c
	$(CC) -g $^ -c -O3 -Wall -o $@

clear:
	rm $(exe) $(objects) $(add)

clean:
	rm $(exe) $(objects) $(add)