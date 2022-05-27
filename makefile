objects = final_project.o lib.o error.o stack.o list.o queue.o avl_tree.o student.o vector.o
CC = gcc
exe = avl_tree_ver
add = add
delete = delete

all: $(exe) $(add) $(delete)

$(exe): $(objects)
	$(CC) -g $(objects) -o $(exe) 

$(add): add.c
	$(CC) -g $^ -O3 -o $@

$(delete): delete.c
	$(CC) -g $^ -O3 -o $@

%.o:%.c
	$(CC) -g $^ -c -O3 -Wall -o $@

test1: all
	wc -l test1.csv
	time ./avl_tree_ver test1.csv
	time ./linked_list_ver test1.csv

student_id_list: student_id_list_generator.c
	$(CC) -g $^ -O3 -o $@_generator
	./$@_generator

clear:
	rm $(exe) $(objects) $(add) $(delete) student_id_list_generator

clean:
	rm $(exe) $(objects) $(add) $(delete) student_id_list_generator