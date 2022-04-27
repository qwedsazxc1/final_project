main: final_project.o lib.o error.o linked_list.o stack.o double_linked_list.o queue.o
	gcc final_project.o linked_list.o lib.o error.o stack.o double_linked_list.o queue.o -o main 

final_project.o: final_project.c lib.h error.h linked_list.h
	gcc final_project.c -c
linked_list.o: linked_list.c lib.h error.h linked_list.h
	gcc linked_list.c -c
lib.o: lib.c lib.h
	gcc lib.c -c
error.o: error.c error.h
	gcc error.c -c
stack.o: stack.c stack.h
	gcc stack.c -c
double_linked_list.o: double_linked_list.c double_linked_list.h
	gcc double_linked_list.c -c
queue.o: queue.c queue.h
	gcc queue.c -c

clear:
	rm main final_project.o linked_list.o lib.o error.o stack.o double_linked_list.o queue.o