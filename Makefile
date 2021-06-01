build :
	gcc -o game ./src/*.c -Wall -g  -std=c99  -lSDL2 
run :
	./game 
clean : 
	rm game
