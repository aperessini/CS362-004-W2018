CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

unittest1steinaua: unittest1steinaua.c dominion.o rngs.o
	gcc -o unittest1steinaua unittest1steinaua.c -g dominion.o rngs.o $(CFLAGS)

unittest2steinaua: unittest2steinaua.c dominion.o rngs.o
	gcc -o unittest2steinaua unittest2steinaua.c -g dominion.o rngs.o $(CFLAGS)

unittest3steinaua: unittest3steinaua.c dominion.o rngs.o
	gcc -o unittest3steinaua unittest3steinaua.c -g dominion.o rngs.o $(CFLAGS)

unittest4steinaua: unittest4steinaua.c dominion.o rngs.o
	gcc -o unittest4steinaua unittest4steinaua.c -g dominion.o rngs.o $(CFLAGS)

cardtest1steinaua: cardtest1steinaua.c dominion.o rngs.o
	gcc -o cardtest1steinaua cardtest1steinaua.c -g dominion.o rngs.o $(CFLAGS)

cardtest2steinaua: cardtest2steinaua.c dominion.o rngs.o
	gcc -o cardtest2steinaua cardtest2steinaua.c -g dominion.o rngs.o $(CFLAGS)

cardtest3steinaua: cardtest3steinaua.c dominion.o rngs.o
	gcc -o cardtest3steinaua cardtest3steinaua.c -g dominion.o rngs.o $(CFLAGS)

cardtest4steinaua: cardtest4steinaua.c dominion.o rngs.o
	gcc -o cardtest4steinaua cardtest4steinaua.c -g dominion.o rngs.o $(CFLAGS)

randomtestadventurersteinaua: randomtestadventurersteinaua.c dominion.o rngs.o
	gcc -o randomtestadventurersteinaua randomtestadventurersteinaua.c -g dominion.o rngs.o $(CFLAGS)

randomtestcard1steinaua: randomtestcard1steinaua.c dominion.o rngs.o
	gcc -o randomtestcard1steinaua randomtestcard1steinaua.c -g dominion.o rngs.o $(CFLAGS)

randomtestcard2steinaua: randomtestcard2steinaua.c dominion.o rngs.o
	gcc -o randomtestcard2steinaua randomtestcard2steinaua.c -g dominion.o rngs.o $(CFLAGS)

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

unittestresults.out: unittest1steinaua unittest2steinaua unittest3steinaua unittest4steinaua cardtest1steinaua cardtest2steinaua cardtest3steinaua cardtest4steinaua
	./unittest1steinaua &> unittestresults.out
	./unittest2steinaua &>> unittestresults.out
	./unittest3steinaua &>> unittestresults.out
	./unittest4steinaua &>> unittestresults.out
	./cardtest1steinaua &>> unittestresults.out
	./cardtest2steinaua &>> unittestresults.out
	./cardtest3steinaua &>> unittestresults.out
	./cardtest4steinaua &>> unittestresults.out
	gcov dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

randomtestadventurersteinaua.out: randomtestadventurersteinaua
	./randomtestadventurersteinaua &> randomtestadventurersteinaua.out
	gcov -abcfu dominion.c >> randomtestadventurersteinaua.out
	cat dominion.c.gcov >> randomtestadventurersteinaua.out

randomtestcard1steinaua.out: randomtestcard1steinaua
	./randomtestcard1steinaua &> randomtestcard1steinaua.out
	gcov -abcfu dominion.c >> randomtestcard1steinaua.out
	cat dominion.c.gcov >> randomtestcard1steinaua.out

randomtestcard2steinaua.out : randomtestcard2steinaua
	./randomtestcard2steinaua &> randomtestcard2steinaua.out
	gcov -abcfu dominion.c >> randomtestcard2steinaua.out
	cat dominion.c.gcov >> randomtestcard2steinaua.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: rngs.o dominion.o unittest1steinaua unittest2steinaua unittest3steinaua unittest4steinaua cardtest1steinaua cardtest2steinaua cardtest3steinaua cardtest4steinaua randomtestadventurersteinaua randomtestcard1steinaua randomtestcard2steinaua playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittest1steinaua unittest2steinaua unittest3steinaua unittest4steinaua cardtest1steinaua cardtest2steinaua cardtest3steinaua cardtest4steinaua randomtestadventurersteinaua randomtestcard1steinaua randomtestcard2steinaua
