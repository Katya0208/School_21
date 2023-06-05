CFLAGS:=
CC:=gcc

all: gcov_report

.PHONY: test
test: s21_string.a
	$(CC) test.c s21_string.a -o test $(shell pkg-config --libs check) -lgcov
	

.PHONY: s21_string.a
s21_string.a:
	$(CC) -c $(CFLAGS) s21_string.c
	ar rcs s21_string.a s21_string.o
	ranlib s21_string.a

.PHONY: gcov_report
gcov_report: CFLAGS+=--coverage
gcov_report: test
	./test

	lcov -o s21_string.info -c -d .
	genhtml -o report s21_string.info
    ifeq ($(UNAME_S),Darwin)
        open report/index.html
    endif
	rm -rf *.gcno *.gcda *.info

.PHONY: clean
clean: 
	rm -rf *.o *.a *.gcno *.gcda *.info *.gcov report test
