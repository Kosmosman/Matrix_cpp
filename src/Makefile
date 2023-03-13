CFLAGS = -Wall -Werror -Wextra
CC = gcc

all: s21_matrix_oop.a

build: s21_matrix_oop.cc s21_overload.cc s21_private_functions.cc
	$(CC) -c $(CFLAGS) -lstdc++ -std=c++17 s21*.cc

s21_matrix_oop.a: build
	ar rcs s21_matrix_oop.a s21*.o
	ranlib s21_matrix_oop.a

clean:
	rm -rf *.o *.out s21_matrix_oop.a unit_test
	rm -rf *.gcda *.gcno report gcov_report.* gcov_report *.info

rebuild:
	make clean
	make build

leaks: test
	leaks -atExit -- ./unit_test

clang:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -n *.cc *.h
	rm .clang-format

test: s21_matrix_oop.a unit_test.cc
	$(CC)  -std=c++17 --coverage s21*.cc unit_test.cc -o unit_test -lgtest -lstdc++
	./unit_test

gcov_report: clean
	$(CC)  --coverage unit_test.cc s21*.cc -o gcov_report -lgtest -lstdc++
	./gcov_report
	lcov -t "stest" -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	open ./report/index.html