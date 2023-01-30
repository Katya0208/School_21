CC = gcc
CFLAGS = -c -Wall -Wextra -Werror

s21_cat: cat.o
	$(CC) cat.o -o s21_cat

cat.o: cat.c
	$(CC) $(CFLAGS) cat.c

test: s21_cat
	./s21_cat cat1.txt cat2.txt
	./s21_cat -n cat1.txt cat2.txt
	./s21_cat -b cat1.txt cat2.txt
	./s21_cat -e cat1.txt cat2.txt
	./s21_cat -s cat1.txt cat2.txt
	./s21_cat -t cat1.txt cat2.txt

rebuild: clear s21_cat

clear:
	rm -rf *.o s21_cat