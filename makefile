objects = final_project.o lib.o error.o basic_data_structure/stack.o basic_data_structure/list.o basic_data_structure/queue.o basic_data_structure/avl_tree.o student.o basic_data_structure/vector.o place.o setting.o language.o
linked_list_ver_obj = final_project_list_version.o lib.o error.o basic_data_structure/stack.o basic_data_structure/list.o basic_data_structure/queue.o basic_data_structure/avl_tree.o place_for_list.o basic_data_structure/vector.o student_for_list.o setting.o language.o
CC = gcc
exe = avl_tree_ver
linked_list_exe = linked_list_ver
add = add
delete = delete
student_id_list = student_id_list_generator
test_case_generator = test_case_generator
check_sort = check_sort

all: $(exe) $(add) $(delete) $(test_case_generator) $(check_sort) $(linked_list_exe) student_id_list.txt

$(exe): $(objects)
	$(CC) -g -O3 $(objects) -o $@

$(linked_list_exe): $(linked_list_ver_obj)
	$(CC) -g -O3 $(linked_list_ver_obj) -o $@

$(add): add.o
	$(CC) -g $^ -O3 -o $@

$(delete): delete.o
	$(CC) -g $^ -O3 -o $@

$(check_sort): check_sort.o
	$(CC) -g $^ -O3 -o $@

%.o:%.c
	$(CC) -g $^ -c -O3 -Wall -o $@
	
# normal random test
test1: all
	./$(test_case_generator) 10 $@.csv
	wc -l $@.csv
	time -p ./$(exe) -f $@.csv -ps

test2: all
	./$(test_case_generator) 10 $@.csv -l
	wc -l $@.csv
	time -p ./$(exe) -f $@.csv -ps

test3: all
	./$(test_case_generator) 10 $@.csv -li
	wc -l $@.csv
	time -p ./$(exe) -f $@.csv -pp

test4: all
	./$(test_case_generator) 10 $@.csv -lp
	wc -l $@.csv
	time -p ./$(exe) -f $@.csv -ps

test5: all
	./$(test_case_generator) 100 $@.csv
	wc -l $@.csv
	time -p ./$(exe) -f $@.csv -ps

test6: all
	./$(test_case_generator) 10000 $@.csv
	wc -l $@.csv
	time -p ./$(exe) -f $@.csv -ps | ./$(check_sort) 10000 -i

test7: all
	./$(test_case_generator) 10000 $@.csv -l
	wc -l $@.csv
	time -p ./$(exe) -f $@.csv -ps | ./$(check_sort) 10000 -i

test8: all
	./$(test_case_generator) 10000 $@.csv -li
	wc -l $@.csv
	time -p ./$(exe) -f $@.csv -pp | ./$(check_sort) 10000 -p

test9: all
	./$(test_case_generator) 10000 $@.csv -lp
	wc -l $@.csv
	time -p ./$(exe) -f $@.csv -ps | ./$(check_sort) 10000 -i

test10: all
	./$(test_case_generator) 10000000 $@.csv
	wc -l $@.csv
	time -p ./$(exe) -f $@.csv -ps | ./$(check_sort) 10000000 -i

test11: all
	./$(test_case_generator) 10000000 $@.csv -l
	wc -l $@.csv
	time -p ./$(exe) -f $@.csv -ps | ./$(check_sort) 10000000 -i

test12: all
	./$(test_case_generator) 10000000 $@.csv -li
	wc -l $@.csv
	time -p ./$(exe) -f $@.csv -pp | ./$(check_sort) 10000000 -p

test13: all
	./$(test_case_generator) 10000000 $@.csv -lp
	wc -l $@.csv
	time -p ./$(exe) -f $@.csv -ps | ./$(check_sort) 10000000 -i

test14: all
	time -p ./$(test_case_generator) 100000000 $@.csv
	wc -l $@.csv
	time -p ./$(exe) -f $@.csv -ps | ./$(check_sort) 100000000 -i


test_case_generator: test_case_generator.c
	$(CC) -g $^ -O3 -o $@

student_id_list.txt: student_id_list_generator
	./$^

student_id_list_generator: student_id_list_generator.o
	$(CC) -g $^ -O3 -o $@

clear:
	rm $(exe) $(add) $(delete) $(test_case_generator) *.o basic_data_structure/*.o test*.csv student_id_list_generator $(linked_list_exe) $(check_sort)

clean:
	rm $(exe) $(add) $(delete) $(test_case_generator) *.o basic_data_structure/*.o test*.csv student_id_list_generator $(linked_list_exe) $(check_sort)
