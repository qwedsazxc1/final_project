main: final_project.o lib.o error.o linked_list.o stack.o
	gcc final_project.o linked_list.o lib.o error.o stack.o -o main 

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

clear:
	rm main final_project.o linked_list.o lib.o error.o list.o