CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

# all: playdom player


# Rules for Assignment-4 Random Tests

randomtestcard1: randomtestcard1.c dominion.o rngs.o interface.o
	gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o interface.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o interface.o
	gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o interface.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o interface.o
	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o interface.o $(CFLAGS)


# To run randomtestcard1 tests, type:  "make randomtestcard1.out" at the prompt.

randomtestcard1.out: randomtestcard1.c dominion.o rngs.o interface.o
	echo "" > randomtestcard1.out
	echo "Results for running randomtestcard1.out tests:" >> randomtestcard1.out
	
	echo "" >> randomtestcard1.out
	echo "randomtestcard1.c:" >> randomtestcard1.out
	gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o interface.o $(CFLAGS)
	randomtestcard1 >> randomtestcard1.out
	gcov -b dominion.c >> randomtestcard1.out


# To run randomtestcard2 tests, type:  "make randomtestcard2.out" at the prompt.

randomtestcard2.out: randomtestcard2.c dominion.o rngs.o interface.o
	echo "" > randomtestcard2.out
	echo "Results for running randomtestcard2.out tests:" >> randomtestcard2.out
	
	echo "" >> randomtestcard2.out
	echo "randomtestcard2.c:" >> randomtestcard2.out
	gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o interface.o $(CFLAGS)
	randomtestcard2 >> randomtestcard2.out
	gcov -b dominion.c >> randomtestcard2.out


# To run randomtestadventurer tests, type:  "make randomtestadventurer.out" at the prompt.

randomtestadventurer.out: randomtestadventurer.c dominion.o rngs.o interface.o
	echo "" > randomtestadventurer.out
	echo "Results for running randomtestadventurer.out tests:" >> randomtestadventurer.out
	
	echo "" >> randomtestadventurer.out
	echo "randomtestadventurer.c:" >> randomtestadventurer.out
	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o interface.o $(CFLAGS)
	randomtestadventurer >> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out



cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)


# To run all unit and card tests, type:  "make unittestresults.out" at the prompt.

# default: unittestresults.out

unittestresults.out: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.o rngs.o
	echo "" > unittestresults.out
	echo "Results for running Unit and Card tests:" >> unittestresults.out
	
	echo "" >> unittestresults.out
	echo "unittest1.c:" >> unittestresults.out
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
	unittest1 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	
	echo "unittest2.c:" >> unittestresults.out
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
	unittest2 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	
	echo "unittest3.c:" >> unittestresults.out
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
	unittest3 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	
	echo "unittest4.c:" >> unittestresults.out
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
	unittest4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	
	echo "cardtest1.c:" >> unittestresults.out
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
	cardtest1 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	
	echo "cardtest2.c:" >> unittestresults.out
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
	cardtest2 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out	
	
	echo "cardtest3.c:" >> unittestresults.out
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
	cardtest3 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	
	echo "cardtest4.c:" >> unittestresults.out
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
	cardtest4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	
	
clean:
	rm -f  randomtestcard1 randomtestcard2 randomtestadventurer unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 playdom.exe playdom player player.exe *.o *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
	
	
