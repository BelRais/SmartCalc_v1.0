CC+FLAGS = gcc -std=c11 -Wall -Wextra -Werror
GCOV_FLAGS = -L. --coverage -ls21_cal

OS = $(shell uname)

ifeq ($(OS), Linux)
	CHECK_FLAGS = -lcheck -lm -pthread -lrt -lsubunit
	OPEN_CMD = xdg-open
	MEM_CHECK = leaks --atExit -- ./s21_test
else
	CHECK_FLAGS = -lcheck
	OPEN_CMD = open
	MEM_CHECK = leaks --atExit -- ./s21_test
endif

all: install

install:
	mkdir build
	cd qt && qmake && make && make clean && rm Makefile && cd ../ && mv qt/s21_cal build

open:
	cd build && open s21_cal.app

dvi:
	open readme.md

dist: install 
	cd .. && tar -czf s21_SmartCalc_v1.0.tgz src

uninstall:
	rm -rf build

test: s21_cal.a
	$(CC+FLAGS) s21_cal.a test/test_SmartCalc.c $(CHECK_FLAGS) -L. -ls21_cal -o s21_test
	./s21_test

gcov_report: s21_cal.a
	$(CC+FLAGS) --coverage s21_cal/s21_calculator.c test/test_SmartCalc.c $(CHECK_FLAGS) -L. -ls21_cal -o ./gcov
	./gcov
	lcov -t "./gcov" -o report.info --no-external -c -d .
	genhtml -o report report.info
	open ./report/index.html
	rm -rf *.gcno *gcda *.gcov

s21_cal.a: s21_cal.o
	ar rcs libs21_cal.a *.o
	rm -rf *.o
	ranlib libs21_cal.a
	cp libs21_cal.a s21_cal.a
	cp libs21_cal.a ls21_cal.a

s21_cal.o:
	$(CC+FLAGS) -c s21_cal/s21_calculator.c

check:
	make test
	CK_FORK=no $(MEM_CHECK) ./s21_test
	make clean

check_valg:
	make test
	CK_FORK=no valgrind --tool=memcheck --trace-children=yes --track-origins=yes --leak-check=full ./s21_test
	make clean

style:
	clang-format -i s21_cal/*.h s21_cal/*.c
	clang-format -i test/*.c
	clang-format -i qt/*.cpp qt/*.h qt/*.ui

check_style:
	cp ../materials/linters/.clang-format ./
	clang-format -n s21_cal/*.h s21_cal/*.c
	clang-format -n test/*.c
	clang-format -n qt/*.cpp qt/*.h qt/*.ui
clean:
	rm -rf *.o *.a *.gcda *.gcno *.info s21_test

clean_report:
	rm -rf report
