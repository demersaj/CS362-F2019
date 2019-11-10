CFLAGS = -Wall -fpic -coverage -lm

testme:
	gcc -o testme -fprofile-arcs -ftest-coverage -g testme.c $(CFLAGS)
	./testme > testme.out
clean:
	rm -f testme *.gcov *.gcda *.gcno *.o