main: final_project.o lib.o error.o stack.o list.o queue.o
	gcc final_project.o lib.o error.o stack.o list.o queue.o -o main 

final_project.o: final_project.c lib.h error.h
	gcc final_project.c -c
lib.o: lib.c lib.h
	gcc lib.c -c
error.o: error.c error.h
	gcc error.c -c
stack.o: stack.c stack.h
	gcc stack.c -c
list.o: list.c list.h
	gcc list.c -c
queue.o: queue.c queue.h
	gcc queue.c -c

clear:
	rm main final_project.o lib.o error.o stack.o list.o queue.o

clean:
	rm main final_project.o lib.o error.o stack.o list.o queue.o