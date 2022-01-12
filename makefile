twitter: twitterFunctions.o main.o
	gcc -Wall -std=c99 twitterFunctions.o main.o -o twitter
twitterFunctions.o: header.h
	gcc -Wall -std=c99 -c twitterFunctions.c
main.o: main.c header.h
	gcc -Wall -std=c99 -c main.c
clean:
	rm *.o twitter
