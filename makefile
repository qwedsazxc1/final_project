main: final_project.o lib.o error.o stack.o list.o queue.o avl_tree.o
	gcc -g final_project.o lib.o error.o stack.o list.o queue.o avl_tree.o -o main 

final_project.o: final_project.c lib.h error.h
	gcc -g final_project.c -c -O3 -Wall
lib.o: lib.c lib.h
	gcc -g lib.c -c -O3 -Wall
error.o: error.c error.h
	gcc -g error.c -c -O3 -Wall
stack.o: stack.c stack.h
	gcc -g stack.c -c -O3 -Wall
list.o: list.c list.h
	gcc -g list.c -c -O3 -Wall
queue.o: queue.c queue.h
	gcc -g queue.c -c -O3 -Wall
avl_tree.o: avl_tree.c avl_tree.h
	gcc -g avl_tree.c -c -O3 -Wall

clear:
	rm main final_project.o lib.o error.o stack.o list.o queue.o avl_tree.o

clean:
	rm main final_project.o lib.o error.o stack.o list.o queue.o avl_tree.o