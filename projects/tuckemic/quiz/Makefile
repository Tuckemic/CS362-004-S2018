CFLAGS = -Wall -fpic -coverage -lm

testme: testme.c
	gcc -o testme testme.c $(CFLAGS)

default: testme

clean:
	rm -f testme *.o *.gcov *.gcda *.gcno *.so *.out

