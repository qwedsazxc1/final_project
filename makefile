objects = final_project.o lib.o error.o basic_data_structure/stack.o basic_data_structure/list.o basic_data_structure/queue.o basic_data_structure/avl_tree.o student.o basic_data_structure/vector.o place.o setting.o
CC = gcc
exe = avl_tree_ver
add = add
delete = delete
student_id_list = student_id_list_generator
test_case_generator = test_case_generator

all: $(exe) $(add) $(delete) $(test_case_generator) student_id_list.txt

$(exe): $(objects)
	$(CC) -g $(objects) -o $(exe) 

$(add): add.o
	$(CC) -g $^ -O3 -o $@

$(delete): delete.o
	$(CC) -g $^ -O3 -o $@

%.o:%.c
	$(CC) -g $^ -c -O3 -Wall -o $@

test1: all
	./$(test_case_generator) 10 $@.csv
	wc -l $@.csv
	time -p ./$(exe) $@.csv

test2: all
	./$(test_case_generator) 100 $@.csv
	wc -l $@.csv
	time -p ./$(exe) $@.csv

test3: all
	./$(test_case_generator) 10000 $@.csv
	wc -l $@.csv
	time -p ./$(exe) $@.csv

test_l: all
	./$(test_case_generator) 10 $@.csv -l
	wc -l $@.csv
	time -p ./$(exe) $@.csv

test_li: all
	./$(test_case_generator) 10 $@.csv -li
	wc -l $@.csv
	time -p ./$(exe) $@.csv

test_lp: all
	./$(test_case_generator) 10 $@.csv -lp
	wc -l $@.csv
	time -p ./$(exe) $@.csv

test_case_generator: test_case_generator.c
	$(CC) -g $^ -O3 -o $@

student_id_list.txt: student_id_list_generator
	./$^

student_id_list_generator: student_id_list_generator.o
	$(CC) -g $^ -O3 -o $@

clear:
	rm $(exe) $(add) $(delete) $(test_case_generator) *.o test*.csv student_id_list_generator

clean:
	rm $(exe) $(add) $(delete) $(test_case_generator) *.o test*.csv student_id_list_generator
