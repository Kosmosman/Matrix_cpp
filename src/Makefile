CFLAGS = -Wall -Werror -Wextra
CC = gcc

all: s21_matrix_oop.a

build: s21_matrix_oop.cc
	$(CC) -c $(CFLAGS) -lstdc++ -std=c++17 s21*.cc

s21_matrix_oop.a: build
	ar rcs s21_matrix_oop.a s21*.o

clean:
	rm -rf *.o *.out s21_matrix_oop.a unit_test
	rm -rf *.gcda *.gcno report gcov_report.* gcov_report *.info

rebuild: clean s21_matrix_oop.a

leaks: test
	leaks -atExit -- ./unit_test

clang:
	clang-format -style=Google -i *.cc *.h

test: s21_matrix_oop.a unit_test.cc
	$(CC)  -std=c++17 --coverage s21*.cc unit_test.cc -o unit_test -lgtest -lstdc++
	./unit_test

gcov_report: clean
	$(CC)  --coverage unit_test.cc s21*.cc -o gcov_report -lgtest -lstdc++
	./gcov_report
	lcov -t "stest" -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	open ./report/index.html