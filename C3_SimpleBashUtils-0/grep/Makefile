CC = gcc
CFLAGS = -c -Wall -Wextra -Werror

s21_grep: grep.o
	$(CC) grep.o -o s21_grep -lpcre

grep.o: grep.c
	$(CC) $(CFLAGS) grep.c -lpcre

test: s21_grep
	./s21_grep kot test_file1.txt
	./s21_grep kot test_file1.txt test_file2.txt 
	./s21_grep [1-5] test_file1.txt test_file2.txt 
	./s21_grep -i KOT test_file1.txt test_file2.txt 
	./s21_grep -v kot test_file1.txt test_file2.txt 
	./s21_grep -c kot test_file1.txt test_file2.txt 
	./s21_grep -l kot *.txt
	./s21_grep -n kot test_file1.txt test_file2.txt
	./s21_grep -e kot -e 123 test_file1.txt test_file2.txt

rebuild: clear s21_grep

clear:
	rm -rf *.o s21_grep